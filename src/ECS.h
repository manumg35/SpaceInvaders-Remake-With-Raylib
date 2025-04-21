#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "raylib.h"

class Component 
{
public:
    virtual ~Component() = default;
};

class Entity
{ 
public:

    Entity(): id(nextEntityID++) {};

    // ~Entity()
    // {
    //     for(auto& [type, index] : componentIndices)
    //     {
    //         std::vector<void*>& pool = componentPools[type];
    //         delete static_cast<Component*>(pool[index]);
    //     }
    // }

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        std::vector<void*>& pool = componentPools[typeid(T)];
        pool.push_back(new T(std::forward<Args>(args)...));
        componentIndices[typeid(T)] = pool.size() - 1;
        
        return *static_cast<T*>(pool.back());
    }

    template<typename T>
    T* GetComponent()
    {
        auto it = componentIndices.find(typeid(T));
        if(it == componentIndices.end())
            return nullptr;
        
        return static_cast<T*>(componentPools[typeid(T)][it->second]);
    }
    bool isActive{true};

private:
    // Map each component type to a vector storing all instances of that type
    static inline std::unordered_map<std::type_index, std::vector<void*>> componentPools;
    // Map each entity to the index of its component in the pool
    std::unordered_map<std::type_index, int> componentIndices;

    static inline int nextEntityID{0};
    int id; 
    
    
};