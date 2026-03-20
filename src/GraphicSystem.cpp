#include "GraphicSystem.h"

template <typename Memory, typename... GraphicComponents>
inline GraphicSystem<Memory, GraphicComponents...>::GraphicSystem(Memory *mem)= default;

template <typename Memory, typename... GraphicComponents>
template <typename T>
inline void GraphicSystem<Memory, GraphicComponents...>::update(){
}