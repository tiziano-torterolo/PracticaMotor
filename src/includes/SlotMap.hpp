#pragma once
#include <tuple>
#include <array>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <functional>

namespace Engine{
#ifdef _WIN32
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline __attribute__((always_inline))
#endif

    
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

    template<typename Preadicate>
    void removeIf(Preadicate&& );

    void remove(T**);
    
    FORCEINLINE void remove(T*);
    
    void removeLast(T**);
    
    void remove(T**,T**);

    template<typename Preadicate>
    FORCEINLINE void forEach(Preadicate&&);

    void removeByIndex(std::size_t);

private:

    FORCEINLINE T   getLast     ();
    FORCEINLINE T** getLastRef  ();
    FORCEINLINE T*  getLastStore();

    FORCEINLINE T** getRefFromStore(T*);
    
    FORCEINLINE std::size_t getLastRefIndex  ();
    FORCEINLINE std::size_t getLastSotreIndex();

};
    
    
}