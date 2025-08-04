#pragma once
#include <tuple>
#include <array>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <iostream>


namespace Engine{

template<typename T>
class SlotMap{
public:
    explicit SlotMap(std::size_t);
    ~SlotMap();

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
    inline void reserve(std::size_t,IteratorBegin,IteratorEnd);

    template< typename... Args>
    T** create(Args&&...) ;

    template< typename... Args>
    inline void emplace_back(Args&&...) ;

    inline auto begin();

    inline auto end();

    template<typename M>
    void removeIf(M& );

    void remove(T**);

    void removeByIndex(std::size_t);

};
    
    
}