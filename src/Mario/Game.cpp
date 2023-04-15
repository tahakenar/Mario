#include "Mario/Game.h"

Game::Game(int speed): speed_(speed)
{
    window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Mario");

    // TODO: create background

    floor_ = new Ground(FLOOR_ASSET_PATH, FLOOR_WIDTH, FLOOR_HEIGHT);
    floor_->setPosition(sf::Vector2f(FLOOR_X, FLOOR_Y));


    // Initialize Mario

    mario_ = new Mario(window_);
    mario_->setPosition(sf::Vector2f(WINDOW_WIDTH/2, FLOOR_Y-MARIO_HEIGHT));


    // TODO: Initialize turtles

}

void Game::update(void)
{
    while (window_->isOpen())
    {
        sf::Event event;
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_->close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            onFloor(mario_))
            {
                mario_->setLateralSpeed(MARIO_LATERAL_LEFT_SPEED);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && onFloor(mario_))
            {
                mario_->setLateralSpeed(MARIO_LATERAL_RIGHT_SPEED);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onFloor(mario_))
            {
                // CAUTION: Do not double jump
                mario_->setVerticalSpeed(MARIO_JUMP_SPEED);
            }
            else
            {
                mario_->setLateralSpeed(0);
            }

        }

        mario_->move();
        if (onFloor(mario_))
        {
            mario_->gravityEffect(false);
        }
        else 
        {
            mario_->gravityEffect(true);
        }
        
        window_->clear();

        this->drawBackground(*window_);
        mario_->draw(*window_);

        window_->display();
        sf::sleep(sf::milliseconds(1000/speed_));
        

        
    }
}

void Game::drawBackground(sf::RenderWindow &window)
{
    // CAUTION: Do we need to pass window as an argument?
    floor_->draw(window_);
}

bool Game::onFloor(Object *obj)
{
    // TODO: set a treshold
    sf::IntRect test_rect = obj->boundingBox();
    sf::Vector2f pos = obj->getPosition();

    if ((FLOOR_Y - (test_rect.height + pos.y)) < FLOOR_INTERACTION_TRESHOLD)
    {
        return true;
    }
    else
    {
        return false;
    }
}