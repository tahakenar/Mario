#include "Mario/Game.h"

Game::Game()
{
    window_ = new sf::RenderWindow(sf::VideoMode(1024, 1024), "Mario");

    uploadTextures();
    setSpriteTextures();
    setSpritePositions();

    // floor_sprite_.setTexture(floor_texture_);
    // floor_sprite_.setTextureRect(sf::IntRect(0, 0, window_->getSize().x, floor_texture_.getSize().y));
    // floor_sprite_.setPosition(sf::Vector2f(0, window_->getSize().y-floor_texture_.getSize().y));
}

void Game::uploadTextures()
{
    floor_texture_.loadFromFile("../assets/floor.png");
    pipe_texture_.loadFromFile("../assets/pipe.png");
    pipe_s_texture_.loadFromFile("../assets/pipeS.png");
}

void Game::setSpriteTextures()
{
    floor_sprite_.setTexture(floor_texture_);
    floor_sprite_.setTextureRect(sf::IntRect(0, 0, window_->getSize().x, floor_texture_.getSize().y));
    floor_sprite_.setOrigin(floor_texture_.getSize().x/2.0f, floor_texture_.getSize().y/2.0f);

    right_pipe_sprite_.setTexture(pipe_texture_);
    right_pipe_sprite_.setTextureRect(sf::IntRect(0, 0, 130, 74));
    right_pipe_sprite_.setOrigin(pipe_texture_.getSize().x/2.0f, pipe_texture_.getSize().y/2.0f);

    left_pipe_sprite_.setTexture(pipe_texture_);
    left_pipe_sprite_.setTextureRect(sf::IntRect(0, 0, 130, 74));
    left_pipe_sprite_.setOrigin(pipe_texture_.getSize().x/2.0f, pipe_texture_.getSize().y/2.0f);
    left_pipe_sprite_.setScale(sf::Vector2f(-1,1));

    right_pipe_s_sprite_.setTexture(pipe_s_texture_);
    right_pipe_s_sprite_.setTextureRect(sf::IntRect(0,0, pipe_s_texture_.getSize().x, pipe_s_texture_.getSize().y));
    right_pipe_s_sprite_.setOrigin(pipe_s_texture_.getSize().x/2.0f, pipe_s_texture_.getSize().y/2.0f);
    right_pipe_s_sprite_.setScale(sf::Vector2f(-1,1));

    left_pipe_s_sprite_.setTexture(pipe_s_texture_);
    left_pipe_s_sprite_.setTextureRect(sf::IntRect(0,0, pipe_s_texture_.getSize().x, pipe_s_texture_.getSize().y));
    left_pipe_s_sprite_.setOrigin(pipe_s_texture_.getSize().x/2.0f, pipe_s_texture_.getSize().y/2.0f);
}

void Game::setSpritePositions()
{
    floor_sprite_.setPosition(sf::Vector2f(window_->getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y));
    right_pipe_sprite_.setPosition(sf::Vector2f(window_->getSize().x-pipe_texture_.getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y-pipe_texture_.getSize().y));
    left_pipe_sprite_.setPosition(sf::Vector2f(0+pipe_texture_.getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y-pipe_texture_.getSize().y));
    right_pipe_s_sprite_.setPosition(sf::Vector2f(window_->getSize().x-pipe_s_texture_.getSize().x/2.0f, 200));
    left_pipe_s_sprite_.setPosition(sf::Vector2f(pipe_s_texture_.getSize().x/2.0f, 200));
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
        

        this->drawBackground(*window_);


        window_->display();

        sf::sleep(sf::microseconds(100));

    }
}

void Game::drawBackground(sf::RenderWindow& window)
{
    window.draw(floor_sprite_);
    window.draw(left_pipe_sprite_);
    window.draw(right_pipe_sprite_);
    window.draw(right_pipe_s_sprite_);
    window.draw(left_pipe_s_sprite_);
}