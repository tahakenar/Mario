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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                mario_->setSpeed(-1, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                mario_->setSpeed(1, 0);
            }
            else 
            {
                mario_->setSpeed(0, 0);
            }

        }
        
        window_->clear();

        this->drawBackground(*window_);

        mario_->move();
        mario_->draw(*window_);

        window_->display();
        sf::sleep(sf::milliseconds(100/speed_));
    }
}

void Game::drawBackground(sf::RenderWindow &window)
{
    // CAUTION: Do we need to pass window as an argument?
    floor_->draw(window_);
}