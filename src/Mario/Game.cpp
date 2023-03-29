#include "Mario/Game.h"

Game::Game()
{
    window_ = new sf::RenderWindow(sf::VideoMode(1024, 1024), "Mario");

    floor_texture_.loadFromFile("../assets/floor.png");
    floor_texture_.setRepeated(true);


    floor_sprite_.setTexture(floor_texture_);
    floor_sprite_.setTextureRect(sf::IntRect(0, 0, window_->getSize().x, floor_texture_.getSize().y));
    floor_sprite_.setPosition(sf::Vector2f(0, window_->getSize().y-floor_texture_.getSize().y));
}

void Game::update()
{
    while (window_->isOpen())
    {
        sf::Event event;
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_->close();

        }

        window_->clear();
        
        // window_->draw(floor_sprite_);

        this->drawBackground(*window_);


        window_->display();

        sf::sleep(sf::microseconds(100));

    }
}

void Game::drawBackground(sf::RenderWindow& window)
{
    window.draw(floor_sprite_);
}