#include "./includes/SlotMap.hpp"



namespace Engine{

template<typename T>
SlotMap<T>::SlotMap(std::size_t n){
    std::cout <<"SlotMap: Creando nuevo de tamaño ="<<n<<std::endl;
    comps = new T[n];
    refs = new T*[n];
    nextfree = new std::size_t[n] ;
    
    freeIndexStorage = 0;
    freeIndexRefs = 0;
    capacity=n;
    lastAddedRef = 0;
    for (size_t i = 0; i < n; i++){
        refs[i]=nullptr;
    }
    for (size_t i = 0; i < n; i++){
        nextfree[i]=i+1;
    }
}

template<typename T>
SlotMap<T>::~SlotMap(){
    delete[] comps;
    delete[] refs;
    delete[] nextfree;
}

template<typename T>
[[deprecated("SlotMap is not resizable right")]]
inline void SlotMap<T>::reserve(std::size_t n){
    
}

template<typename T>
template<typename IteratorBegin,typename IteratorEnd>
[[deprecated("SlotMap is not resizable right")]]
inline void SlotMap<T>::reserve(std::size_t n,IteratorBegin begin,IteratorEnd end){
    return;

    
}

template<typename T>
template<typename... Args>
T** SlotMap<T>::create(Args&&... args){
    
    if(freeIndexStorage==capacity){
        throw std::runtime_error("SlotMapError: No se puede añadir porque SlotMap esta lleno size="+capacity);
    }
    
    auto temp = &(refs[freeIndexRefs]);

    emplace_back(std::forward<Args>(args)...);
    
    return temp;
}

template<typename T>
template<typename Component>
T** SlotMap<T>::create(Component&& args){
    
    if(freeIndexStorage==capacity){
        throw std::runtime_error("SlotMapError: No se puede añadir porque SlotMap esta lleno size="+capacity);
    }
    
    auto temp = &(refs[freeIndexRefs]);

    push_back(std::forward<Component>(args));
    
    return temp;
}

template<typename T>
template< typename... Args>
inline void SlotMap<T>::emplace_back(Args&&... args){
    comps[freeIndexStorage] = T(std::forward<Args>(args)...);
    refs[freeIndexRefs] = &comps[freeIndexStorage];    
    freeIndexStorage++;
    lastAddedRef = freeIndexRefs;
    freeIndexRefs = nextfree[freeIndexRefs];
}

template<typename T>
template<typename Component>
inline void SlotMap<T>::push_back(Component&& args){
    comps[freeIndexStorage] = std::forward<Component>(args) ;
    refs[freeIndexRefs] = &comps[freeIndexStorage];    
    freeIndexStorage++;
    lastAddedRef = freeIndexRefs;
    freeIndexRefs = nextfree[freeIndexRefs];
}

template<typename T>
inline auto SlotMap<T>::begin(){
    return comps;
}

template<typename T>
inline auto SlotMap<T>::end(){
    return comps + freeIndexStorage;
}

template<typename T>
template<typename Preadicate>
void SlotMap<T>::removeIf(Preadicate&& pred){
    for (auto it = end()-1; it != begin()-1;--it ) {
        if (std::invoke(pred, it)) {
            remove(it); 
        }
    }
}

template<typename T>
void SlotMap<T>::remove(T** elementRef){
    auto LastInRefsArray = getLastRef();
    if(*LastInRefsArray == *elementRef){
        removeLast(elementRef);
        return;
    }
    removeByIndex( elementRef - (refs) );
}

template<typename T>
void SlotMap<T>::remove(T* element){
    remove( getRefFromStore(element) ); // yo se que no es lo mas optimo pero tampoco esta mal
}

template<typename T>
void SlotMap<T>::removeByIndex(std::size_t index){
    // Tomar el ultimo valor y cambiarlo con el primer
    //ir a referencias y switchear los que tengan la referencia de los valores cambiados

    //Casos particulares, remover ultimo, remover no elemento, remover elemento removido
    std::cout <<index ;
    if (index>=freeIndexStorage){
        throw std::runtime_error("SlotMapError: index>freeIndexStorage");
        return;//aca no se si deberia ser > o >=
    }

    if (freeIndexStorage<1){
        throw std::runtime_error("SlotMapError: freeIndexStorage<1");
        return;

    }

    if(index >= capacity){
        throw std::runtime_error("SlotMapError: index >= capacity");
        return;
    }

    auto LastInRefsArray = getLastRef();
    auto IndexOfLastInRefsArray = LastInRefsArray - refs;

    if(LastInRefsArray == nullptr){
        throw std::runtime_error("SlotMapError: getLastRef() == nullptr");
        return;
    }
    if(*LastInRefsArray == refs[index]){
        removeLast(&refs[index]);
        return;
    }

    
    std::swap(*LastInRefsArray,refs[index]);
    std::swap(*(*LastInRefsArray),*refs[index]);

    freeIndexStorage--;

    auto freeIndexRefsTmp = freeIndexRefs;
    nextfree[index] = freeIndexRefsTmp;
    freeIndexRefs = index;

}


template<typename T>
void SlotMap<T>::removeLast(T** LastRef){
    (*LastRef)->~T();
    std::size_t index = LastRef - refs;
    freeIndexStorage--;
    nextfree[index]=freeIndexRefs;
    freeIndexRefs=index; 
}


/// @return 
template<typename T>
FORCEINLINE T   SlotMap<T>::getLast(){
    return comps[freeIndexStorage-1];
}

template<typename T>
FORCEINLINE T*  SlotMap<T>::getLastStore(){
    return &comps[freeIndexStorage-1];
}

template<typename T>
FORCEINLINE T** SlotMap<T>::getLastRef(){
//    T* comps;
//    T** refs;
    return getRefFromStore(getLastStore());
}

template<typename T>
FORCEINLINE std::size_t SlotMap<T>::getLastRefIndex  (){
    return (getLastRef()-(refs)  );
}

template<typename T>
FORCEINLINE std::size_t SlotMap<T>::getLastSotreIndex(){
    return ( getLastStore()-(comps) );
}
  
template<typename T>
template<typename Predicate>
FORCEINLINE void SlotMap<T>::forEach(Predicate&& pred){
    std::for_each(begin(),end(), std::forward<Predicate>(pred));
}

template<typename T>
FORCEINLINE T** SlotMap<T>::getRefFromStore(T* store){
    T** it = std::find_if(refs,(refs + capacity),[store](T* t){return t==store;});
    return (it != (refs + capacity)) ? it : nullptr;
}

}