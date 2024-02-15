//
// Created by Gianni on 15/02/2024.
//

#include "easing_functions.hpp"


namespace easing_functions
{
    float linear(float t)
    {
        assert(t >= 0);

        return t > 1? 1 : t;
    }

    float ease_out_quint(float t)
    {
        assert(t >= 0);

        if (t > 1) t = 1;

        return 1 - std::pow(1 - t, 5);
    }

    float ease_in_out_cubic(float t)
    {
        assert(t >= 0);

        if (t > 1) t = 1;

        return t < 0.5 ? 4 * std::pow(t, 3) : 1 - std::pow(-2 * t + 2, 3) / 2;
    }
}
