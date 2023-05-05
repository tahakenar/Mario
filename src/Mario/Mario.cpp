#include "Mario/Mario.h"
#include <spdlog/spdlog.h>

Mario::Mario(sf::RenderWindow *window): Object(window)
{
    window_ = window;
    heading_ = HEADING_LEFT;
    heading_changed_ = false;


    this->loadTextures();

    sprite_.setTexture(textures_[0]);   // initially
    // sprite_.setOrigin(sprite_.getLocalBounds().width/2.f,sprite_.getLocalBounds().height);
    // sprite_.setOrigin(sprite_.getGlobalBounds().width / 2.f, sprite_.getGlobalBounds().height / 2.f);
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
    goal_mario_pos.y += vy_ * MARIO_JUMP_STEP_SIZE;
    setPosition(goal_mario_pos);
}

void Mario::setLateralSpeed(float vx)
{
    vx_ = vx;
}

void Mario::lateralSpeedDecay()
{
    if (vx_ == 0)
        return;
    else if (vx_ > 0)
    {
        vx_ -= 0.25;
    }
    else
    {
        vx_ += 0.25;
    }
}

void Mario::setVerticalSpeed(float vy)
{
    vy_ = vy;
}

void Mario::gravityEffect(bool set)
{
    if (set)
        vy_ = vy_ >= 30 ? -MARIO_JUMP_SPEED : vy_ + GRAVITY_COEFFICIENT;
    else
        vy_ = 0;
}

float Mario::getSpeedX(void)
{
    return vx_;
}

void Mario::setHeading(int heading)
{
    if (heading_ != heading)
    {
        heading_ = heading;
        heading_changed_ = true;
        spdlog::info("Heading changed");
    }
}


void Mario::setState(int state)
{
    state_ = state;
}

void Mario::updateTexture()
{
    // std::cout << "Origin: " << sprite_.getOrigin().x << " " << sprite_.getOrigin().y << std::endl;

    // sprite_.setOrigin(sf::Vector2f(textures_[0].getSize().x/2.f, 0));

    // std::cout << "Origin after set: " << sprite_.getOrigin().x << " " << sprite_.getOrigin().y << std::endl;

    if (state_ == MarioStates::STILL)
        sprite_.setTexture(textures_[0]);
    if (state_ == MarioStates::JUMP)
        sprite_.setTexture(textures_[5]);
    if (state_ == MarioStates::SLIDE)
        sprite_.setTexture(textures_[4]);

    spdlog::info("Origin: " + std::to_string(sprite_.getOrigin().x) + " - " + std::to_string(sprite_.getOrigin().y));
    if (heading_ == HEADING_LEFT)
    {
        sprite_.setScale(1.f,1.f);
        sprite_.setOrigin(0, sprite_.getOrigin().y);
        std::cout << "Left: " << sprite_.getGlobalBounds().left << std::endl;

    }
    if (heading_ == HEADING_RIGHT)
    {
        // && heading_changed_
        sprite_.setScale(-1.f,1.f);
        sprite_.setOrigin(+MARIO_WIDTH, sprite_.getOrigin().y);
        std::cout << "Right: " << sprite_.getGlobalBounds().left << std::endl;
 
        // sprite_.move(MARIO_WIDTH, 0);
    }




    // sprite_.setOrigin(sf::Vector2f(0, 0));
    // std::cout << "Ultim origin: " << sprite_.getOrigin().x << " " << sprite_.getOrigin().y << std::endl;

}

void Mario::logSpeed()
{
    spdlog::warn("Mario speed" + std::to_string(vy_));
}

void Mario::logPosition()
{
    spdlog::warn("Mario pos: " + std::to_string(pos_.y));
}
