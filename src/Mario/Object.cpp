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
    if (pos.x > 0 && pos.x < WINDOW_WIDTH - MARIO_WIDTH)
    {
        pos_ = pos;
        sprite_.setPosition(pos_);
    }
}

sf::Vector2f Object::getPosition()
{
    return pos_;
}

sf::IntRect Object::boundingBox(void)
{
    sf::FloatRect bounding_box =  sprite_.getGlobalBounds();
    sf::IntRect int_bounding_box;
    int_bounding_box.height = static_cast<int>(bounding_box.height);
    int_bounding_box.width = static_cast<int>(bounding_box.width);
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


