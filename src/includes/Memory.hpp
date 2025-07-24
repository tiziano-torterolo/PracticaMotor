#pragma once
#include <tuple>
#include <vector>
#include <type_traits>

template<typename... Components>
class Memory {
public:
    std::tuple<std::vector<Components>...> pools;

    explicit Memory(std::size_t n =1000);

    ~Memory();                                // Destructor
    Memory(const Memory& other); // Constructor de copia
    Memory(Memory&& other) noexcept; // Constructor de movimiento
    Memory& operator=(const Memory& other); // Asignación copia
    Memory& operator=(Memory&& other) noexcept; // Asignación movimiento


    inline void setSize(std::size_t n) ;

    template<typename T>
    __forceinline std::vector<T>& getPool() ;

    template<typename T, typename... Args>
    inline void emplace(Args&&... args) ;

    template<typename T>
    inline auto begin()-> typename std::vector<T>::iterator;

    template<typename T>
    inline auto end()-> typename std::vector<T>::iterator;

    template<typename T>
    inline auto begin()-> typename std::vector<T>::iterator const ;

    template<typename T>
    inline auto end()-> typename std::vector<T>::iterator const ;
};