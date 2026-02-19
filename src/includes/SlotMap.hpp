#pragma once
#include <tuple>
#include <array>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <functional>
#include <Macros.hpp>
#include <typeinfo>
#include <concepts>

namespace Engine{

    
template<typename T>
class SlotMap{
public:
    explicit SlotMap(std::size_t);
    ~SlotMap();
    SlotMap(const SlotMap& other); // Constructor de copia
    SlotMap(SlotMap&& other) noexcept  ; // Constructor de movimiento
    SlotMap& operator=(const SlotMap& other) =  default; // Asignación copia
    SlotMap& operator=(SlotMap&& other) noexcept = default; // Asignación movimiento
private:

    std::size_t freeIndexStorage;
    T* comps;

    std::size_t lastAddedRef;
    std::size_t freeIndexRefs;
    T** refs;

    std::size_t capacity;
    std::size_t* nextfree;

public:

    inline void reserve(std::size_t);

    template<typename IteratorBegin,typename IteratorEnd>
    inline void resize(std::size_t,IteratorBegin,IteratorEnd);

    template<typename... Args>
    T** create(Args&&...) ;

    template<typename Component>
    T** create(Component&&) ;

    template<typename... Args>
    inline void emplace_back(Args&&...) ;
    
    template<typename Component>
    inline void push_back(Component&&) ;

    inline auto begin();

    inline auto end();

    template<typename Preadicate>
    void removeIf(Preadicate&& );

    FORCEINLINE void remove(T**);
    
    FORCEINLINE void remove(T*);
    
    void removeLast(T**);
    
    void removeLast();

    void remove(T**,T**);

    template<typename Preadicate>
    FORCEINLINE void forEach(Preadicate&&);

    void removeByIndex(std::size_t);

private:

    FORCEINLINE T   getLast     (); //obtiene una copia del ultimo objeto 
    FORCEINLINE T** getLastRef  (); // Obtiene el puntero al puntero que apunta al objeto
                                    // &Ref[x] -> Last*
    FORCEINLINE T*  getLastStore(); // Obtiene el puntero del ultimo objeto 

    FORCEINLINE T** getRefFromStore(T*);
    
    FORCEINLINE std::size_t getLastRefIndex  ();
    FORCEINLINE std::size_t getLastSotreIndex();

};
    
    
}