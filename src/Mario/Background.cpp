#include "Mario/Background.h"

Background::Background(std::string asset_path, int width, int height)
    : width_(width), 
      height_(height)
{
    texture_.loadFromFile(asset_path);
    texture_.setRepeated(true);
    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0,0,width_,height_));
}

void Background::draw(sf::RenderWindow *window)
{
    window->draw(sprite_);
}

void Background::setPosition(sf::Vector2f pos)
{
    pos_ = pos;
    sprite_.setPosition(pos_.x, pos_.y);
}

void Background::flip(int axis)
{
    sprite_.setOrigin(sf::Vector2f(width_/2.0,height_/2.0));
    if (axis == X_AXIS)
    {
        sprite_.setScale(sf::Vector2f(1,-1));
    }
    if (axis == Y_AXIS)
    {
        sprite_.setScale(sf::Vector2f(-1,1));
    }
}

sf::IntRect Background::boundingBox(void)
{
    sf::FloatRect bounding_box =  sprite_.getGlobalBounds();
    sf::IntRect int_bounding_box = static_cast<sf::IntRect>(bounding_box);
    return int_bounding_box;
}
