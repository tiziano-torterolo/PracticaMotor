#pragma once
#include <tuple>
#include <vector>
#include <type_traits>
#include <SlotMap.hpp>
#include <Macros.hpp>
#include <Entity.hpp>

namespace Engine{


template<typename... Components>
class Memory {
public:

    std::tuple<SlotMap<Components>...> pools;
    SlotMap<Entity<Components...>> entities;

    explicit Memory(std::size_t);

    ~Memory();                                // Destructor
    Memory(const Memory& other) = delete; // Constructor de copia
    Memory(Memory&& other) noexcept = delete; // Constructor de movimiento
    Memory& operator=(const Memory& other) = delete ; // Asignación copia
    Memory& operator=(Memory&& other) noexcept = delete; // Asignación movimiento
   
    private:

        template<typename T>
        FORCEINLINE SlotMap<T>& getPool() ;
        

    public:

        constexpr inline void reserve(std::size_t n);

        template<typename... Cs, typename... Args>
        auto createEntity(Args&&... args) ;
        

        template<typename T, typename... Args>
        inline void emplace(Args&&... args) ;

        template<typename T>
        inline auto begin();

        template<typename T>
        inline auto end();

        inline auto begin();

        inline auto end();

        template<typename T>
        void remove(T& t);

        template<typename Preadicate>
        void removeIf(Preadicate& t);

        template<typename Preadicate>
        void forEach(Preadicate&);

        template<typename T,typename Preadicate>
        void forEach(Preadicate&);




};
    
}

