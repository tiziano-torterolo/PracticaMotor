#include "./includes/SlotMap.hpp"



namespace Engine{

template<typename T>
SlotMap<T>::SlotMap(std::size_t n){
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
    comps[freeIndexStorage] = T(std::forward<Args>(args)...);
    refs[freeIndexRefs] = &comps[freeIndexStorage];
    auto temp = &(refs[freeIndexRefs]);
    freeIndexStorage++;
    lastAddedRef = freeIndexRefs;
    freeIndexRefs = nextfree[freeIndexRefs];
    return temp;
}

template<typename T>
template< typename... Args>
inline void SlotMap<T>::emplace_back(Args&&... args){

}

template<typename T>
inline auto SlotMap<T>::begin(){

}

template<typename T>
inline auto SlotMap<T>::end(){

}

template<typename T>
template<typename M>
void SlotMap<T>::removeIf(M& m){

}

template<typename T>
void SlotMap<T>::remove(T** elementRef){
    auto element = std::find_if(comps,comps+std::size(comps),true);
    if(element==comps+std::size(comps)){
        return;
    }
    std::size_t index = std::distance(comps.begin(), element);
    removeByIndex(index);
}

template<typename T>
void SlotMap<T>::removeByIndex(std::size_t index){
    std::cout << "Swap"<<lastAddedRef << " <->" << index<< std::endl;
    std::swap((refs[lastAddedRef]),(refs[index]));
    std::cout << "Swap"<<(refs[lastAddedRef]) << " <->" << (refs[index])<< std::endl;
    std::cout << "Swap"<<(*refs[lastAddedRef])<< " <->" << (*refs[index])<< std::endl;
    std::swap((*refs[lastAddedRef]),(*refs[index]));
    freeIndexStorage--;
    nextfree[index]=freeIndexRefs;
    freeIndexRefs=index;
    std::cout <<"free="<<freeIndexRefs << "store="<<freeIndexStorage << " newxfree " << nextfree[index]<< std::endl;
    
}
    
    
}