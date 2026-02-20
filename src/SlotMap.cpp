#include "./includes/SlotMap.hpp"



namespace Engine{

template<typename T>
SlotMap<T>::SlotMap(std::size_t n){
    buffer = new unsigned char[ sizeof(T)*n + sizeof(T**)*n + sizeof(T*)*n + sizeof(std::size_t)*n ];

    comps.object =  new (buffer) T[n];
    comps.ref = new (buffer + sizeof(T)*n) T**[n];
    refs = new (buffer + sizeof(T)*n + sizeof(T**)*n) T*[n];
    nextfree = new (buffer + sizeof(T)*n + sizeof(T**)*n + sizeof(T*)*n) std::size_t[n] ;
    
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
    for (size_t i = 0; i < capacity; i++){
        comps.object[i].~T();
    }
    delete[] buffer;
}

template<typename T>
SlotMap<T>::SlotMap(const SlotMap& other) {
    std::cout<<"SlotMap: EL CONSTRUCTOR DE COPIA NO ESTA IMPLEMENTADO xD <"<< typeid(T).name() <<std::endl;

    buffer = new unsigned char[ sizeof(T)*other.capacity + sizeof(T**)*other.capacity + sizeof(T*)*other.capacity + sizeof(std::size_t)*other.capacity ];
    comps.object = new (buffer) T[other.capacity];
    comps.ref = new (buffer + sizeof(T)*other.capacity) T**[other.capacity];
    refs = new (buffer + sizeof(T)*other.capacity + sizeof(T**)*other.capacity) T*[other.capacity];
    nextfree = new (buffer + sizeof(T)*other.capacity + sizeof(T**)*other.capacity + sizeof(T*)*other.capacity) std::size_t[other.capacity] ;

} // Constructor de copia

template<typename T>
SlotMap<T>::SlotMap(SlotMap&& other) noexcept: 
        freeIndexStorage(other.freeIndexStorage)
        , comps(other.comps)
        , lastAddedRef(other.lastAddedRef)
        , freeIndexRefs(other.freeIndexRefs)
        , refs(other.refs)
        , capacity(other.capacity)
        , nextfree(other.nextfree) {
    std::cout<<"SlotMap: Constructor de movimiento <"<< typeid(T).name() <<std::endl;

    other.comps = nullptr;
    other.refs = nullptr;
    other.nextfree = nullptr;

    other.capacity = 0;
    other.freeIndexStorage = 0;
    other.freeIndexRefs = 0;
    other.lastAddedRef = 0;;
}  // Constructor de movimiento

template<typename T>
[[deprecated("SlotMap is not resizable right")]]
inline void SlotMap<T>::reserve(std::size_t n){
    
}

template<typename T>
template<typename IteratorBegin,typename IteratorEnd>
[[deprecated("SlotMap is not resizable right")]]
inline void SlotMap<T>::resize(std::size_t n,IteratorBegin begin,IteratorEnd end){
    
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
    comps.object[freeIndexStorage] = T(std::forward<Args>(args)...);
    refs[freeIndexRefs] = &comps.object[freeIndexStorage];
    comps.ref[freeIndexStorage] = &refs[freeIndexRefs];
    freeIndexStorage++;
    lastAddedRef = freeIndexRefs;
    freeIndexRefs = nextfree[freeIndexRefs];
}

template<typename T>
template<typename Component>
inline void SlotMap<T>::push_back(Component&& args){
    comps.object[freeIndexStorage] = args ;
    refs[freeIndexRefs] = &comps.object[freeIndexStorage];    
    comps.ref[freeIndexStorage] = &refs[freeIndexRefs];
    freeIndexStorage++;
    lastAddedRef = freeIndexRefs;
    freeIndexRefs = nextfree[freeIndexRefs];
}

template<typename T>
inline auto SlotMap<T>::begin(){
    return comps.object;
}

template<typename T>
inline auto SlotMap<T>::end(){
    return comps.object + freeIndexStorage;
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
FORCEINLINE void SlotMap<T>::remove(T** elementRef){
    auto lastInRefsArray =  getLastRef();
    if(*lastInRefsArray == *elementRef){
        removeLast(elementRef);
        return;
    }
    removeByIndex( elementRef - refs);
}

template<typename T>
void SlotMap<T>::removeLast(){
        removeLast(getLastRef());

}
template<typename T>
void SlotMap<T>::remove(T* element){
    remove( getRefFromStore(element) ); // yo se que no es lo mas optimo pero tampoco esta mal
}



template<typename T>
void SlotMap<T>::removeByIndex(std::size_t index){

    if ((refs[index]-comps.object)>=freeIndexStorage){
        std::cout<<"index: "<<index<<" freeIndexStorage: "<<freeIndexStorage<<" capacity: "<<capacity<< " in type "<<typeid(T).name()<<std::endl;
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

    auto lastInRefsArray = getLastRef();
    auto indexOfLastInRefsArray = lastInRefsArray - refs;

    if(lastInRefsArray == nullptr){
        throw std::runtime_error("SlotMapError: getLastRef() == nullptr");
        return;
    }
    if(*lastInRefsArray == refs[index]){
        removeLast(&refs[index]);
        return;
    }

    
    //Swap object to be removed with last object , Swap the pointer in refs array that points to the object to be removed with the pointer that points to the last object, Swap the pointer in comps.ref array that points to the object to be removed with the pointer that points to the last object
    std::swap(*refs[index], comps.object[freeIndexStorage-1]);
    std::swap(refs[index], refs[indexOfLastInRefsArray]);
    std::swap(comps.ref[refs[index]-comps.object], comps.ref[freeIndexStorage-1]);


    comps.object[freeIndexStorage-1].~T();

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
    return comps.object[freeIndexStorage-1];
}

template<typename T>
FORCEINLINE T*  SlotMap<T>::getLastStore(){
    return &comps.object[freeIndexStorage-1];
}

template<typename T>
FORCEINLINE T** SlotMap<T>::getLastRef(){
//    T* comps;
//    T** refs;
    return comps.ref[freeIndexStorage-1];
}

template<typename T>
FORCEINLINE std::size_t SlotMap<T>::getLastRefIndex  (){
    return (getLastRef()-(refs)  );
}

template<typename T>
FORCEINLINE std::size_t SlotMap<T>::getLastSotreIndex(){
    return ( getLastStore()-(comps.object) );
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