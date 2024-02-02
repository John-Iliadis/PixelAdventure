//
// Created by Gianni on 2/02/2024.
//

#ifndef PLATFORMER_TRAP_HPP
#define PLATFORMER_TRAP_HPP

#include <SFML/Graphics/Drawable.hpp>


class Trap : public sf::Drawable
{
public:
    virtual ~Trap() = default;

    virtual void update(double dt) = 0;

    virtual sf::FloatRect get_collider() const = 0;
};


#endif //PLATFORMER_TRAP_HPP
