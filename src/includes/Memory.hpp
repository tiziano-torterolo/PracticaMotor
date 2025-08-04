#pragma once
#include <tuple>
#include <vector>
#include <type_traits>

namespace Engine{


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
   
    private:

        template<typename T>
        __forceinline std::vector<T>& getPool() ;


    public:

        constexpr inline void reserve(std::size_t n) ;

        template<typename T, typename... Args>
        inline void emplace(Args&&... args) ;

        template<typename T>
        inline auto begin();

        template<typename T>
        inline auto end();

        template<typename T>
        void remove(T& t);

        template<typename T>
        void removeIf(T& t);

        template<typename M>
        void forEach(M& t);

        template<typename T,typename M>
        void forEach(M& t);




};
    
}

