#include "Mario/Object.h"
#include <iostream>

Object::Object(sf::RenderWindow *window)
{
    window_ = window;
    state_ = 0;
    heading_ = HEADING_LEFT;
}

void Object::setPosition(sf::Vector2f pos)
{
    if (pos.y > FLOOR_Y)
    {
        pos.y = FLOOR_Y;
    }
    if (pos.x < LATERAL_INTERACTION_TRESHOLD)
    {
        pos.x = LATERAL_INTERACTION_TRESHOLD;
    }
    if (pos.x > WINDOW_WIDTH - MARIO_WIDTH - LATERAL_INTERACTION_TRESHOLD)
        pos.x = WINDOW_WIDTH - MARIO_WIDTH - LATERAL_INTERACTION_TRESHOLD;

    pos_ = pos;
    sprite_.setPosition(pos_);


}

sf::Vector2f Object::getPosition()
{
    return pos_;
}

sf::IntRect Object::boundingBox(void)
{
    sf::FloatRect bounding_box =  sprite_.getGlobalBounds();
    sf::IntRect int_bounding_box = static_cast<sf::IntRect>(bounding_box);
    return int_bounding_box;
}

void Object::draw(sf::RenderWindow &window)
{
    window.draw(sprite_);
}

void move(void)
{
    return;
}

void fall(void)
{
    return;
}

void jump(bool down)
{
    return;
}


