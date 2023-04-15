#include "Mario/Mario.h"

Mario::Mario(sf::RenderWindow *window): Object(window)
{
    window_ = window;

    this->loadTextures();

    sprite_.setTexture(textures_[0]);   // initially
}

void Mario::loadTextures(void)
{
    textures_[0].loadFromFile(MARIO_1);
    textures_[1].loadFromFile(MARIO_2);
    textures_[2].loadFromFile(MARIO_3);
    textures_[3].loadFromFile(MARIO_4);
    textures_[4].loadFromFile(MARIO_5);
    textures_[5].loadFromFile(MARIO_6);
    textures_[6].loadFromFile(MARIO_7);
}

void Mario::move()
{
    sf::Vector2f goal_mario_pos = getPosition();
    goal_mario_pos.x += vx_ * MARIO_STEP_SIZE;
    setPosition(goal_mario_pos);
}

void Mario::setSpeed(float vx, float vy)
{
    vx_ = vx;
    vy_ = vy;
}
