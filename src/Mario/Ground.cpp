#include "Mario/Ground.h"

Ground::Ground(std::string asset_path, int width, int height): width_(width), height_(height)
{
    texture_.loadFromFile(asset_path);
    texture_.setRepeated(true);

    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0,0,width_,height_));
}

void Ground::draw(sf::RenderWindow *window)
{
    window->draw(sprite_);
}

void Ground::setPosition(sf::Vector2f pos)
{
    pos_ = pos;
    sprite_.setPosition(pos_.x, pos_.y);
}
