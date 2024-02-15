//
// Created by Gianni on 15/02/2024.
//

#ifndef PLATFORMER_EASING_FUNCTIONS_HPP
#define PLATFORMER_EASING_FUNCTIONS_HPP

#include <cmath>
#include <cassert>


namespace easing_functions
{
    float linear(float t);
    float ease_out_quint(float t);
    float ease_in_out_cubic(float t);
};


#endif //PLATFORMER_EASING_FUNCTIONS_HPP
