#include "Mario/Turtle.h"

Turtle::Turtle(sf::RenderWindow *window): Object(window)
{
    window_ = window;
    sprite_.setTexture(textures_[0]);
}

void Turtle::move()
{
    //TODO: Move randomly
}

void Turtle::jump(bool down)
{

}

void Turtle::fall()
{

}

void Turtle::loadTextures()
{
    textures_[0].loadFromFile(TURTLE_1);
    textures_[1].loadFromFile(TURTLE_2);
    textures_[2].loadFromFile(TURTLE_3);
    textures_[3].loadFromFile(TURTLE_4);
    textures_[4].loadFromFile(TURTLE_5);
}
