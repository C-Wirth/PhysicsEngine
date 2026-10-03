#pragma once

#include <variant>
#include "physics/particles/Particle2D.hpp"
#include <functional>

//inline void ApplyForce(std::variant<Particle2D>& v, std::function<void()> f)
//{
//    for (std::size_t i = 0 ; i < std::variant_size_v<v> ; i++)
//    {
//        f(v[i]);
//    }
//}