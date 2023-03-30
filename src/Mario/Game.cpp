#include "Mario/Game.h"

Game::Game()
{
    window_ = new sf::RenderWindow(sf::VideoMode(1024, 1024), "Mario");

    uploadTextures();
    setSpriteTextures();
    setSpritePositions();

}

void Game::uploadTextures()
{
    floor_texture_.loadFromFile("../assets/floor.png");
    pipe_texture_.loadFromFile("../assets/pipe.png");
    pipe_s_texture_.loadFromFile("../assets/pipeS.png");
    brick_texture_.loadFromFile("../assets/brick.png");
    brick_texture_.setRepeated(true);
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

    right_lower_brick_sprite_.setTexture(brick_texture_);
    right_lower_brick_sprite_.setTextureRect(sf::IntRect(0,0, brick_texture_.getSize().x*12, brick_texture_.getSize().y));
    right_lower_brick_sprite_.setOrigin(brick_texture_.getSize().x*12/2.0, brick_texture_.getSize().y/2.0);

    right_mid_brick_sprite_.setTexture(brick_texture_);
    right_mid_brick_sprite_.setTextureRect(sf::IntRect(0,0,brick_texture_.getSize().x*4, brick_texture_.getSize().y));
    right_mid_brick_sprite_.setOrigin(brick_texture_.getSize().x*4/2.0, brick_texture_.getSize().y/2.0);

    right_upper_brick_sprite_.setTexture(brick_texture_);
    right_upper_brick_sprite_.setTextureRect(sf::IntRect(0,0,brick_texture_.getSize().x*14, brick_texture_.getSize().y));
    right_upper_brick_sprite_.setOrigin(brick_texture_.getSize().x*14/2.0, brick_texture_.getSize().y/2.0);

    left_lower_brick_sprite_.setTexture(brick_texture_);
    left_lower_brick_sprite_.setTextureRect(sf::IntRect(0,0, brick_texture_.getSize().x*12, brick_texture_.getSize().y));
    left_lower_brick_sprite_.setOrigin(brick_texture_.getSize().x*12/2.0, brick_texture_.getSize().y/2.0);

    left_mid_brick_sprite_.setTexture(brick_texture_);
    left_mid_brick_sprite_.setTextureRect(sf::IntRect(0,0,brick_texture_.getSize().x*4, brick_texture_.getSize().y));
    left_mid_brick_sprite_.setOrigin(brick_texture_.getSize().x*4/2.0, brick_texture_.getSize().y/2.0);

    left_upper_brick_sprite_.setTexture(brick_texture_);
    left_upper_brick_sprite_.setTextureRect(sf::IntRect(0,0,brick_texture_.getSize().x*14, brick_texture_.getSize().y));
    left_upper_brick_sprite_.setOrigin(brick_texture_.getSize().x*14/2.0, brick_texture_.getSize().y/2.0);

    mid_brick_sprite_.setTexture(brick_texture_);
    mid_brick_sprite_.setTextureRect(sf::IntRect(0,0, brick_texture_.getSize().x*16, brick_texture_.getSize().y));
    mid_brick_sprite_.setOrigin(brick_texture_.getSize().x*16/2.0, brick_texture_.getSize().y/2.0);

}

void Game::setSpritePositions()
{
    floor_sprite_.setPosition(sf::Vector2f(window_->getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y));
    right_pipe_sprite_.setPosition(sf::Vector2f(window_->getSize().x-pipe_texture_.getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y-pipe_texture_.getSize().y));
    left_pipe_sprite_.setPosition(sf::Vector2f(0+pipe_texture_.getSize().x/2.0f, window_->getSize().y-floor_texture_.getSize().y-pipe_texture_.getSize().y));
    right_pipe_s_sprite_.setPosition(sf::Vector2f(window_->getSize().x-pipe_s_texture_.getSize().x/2.0f, 200));
    left_pipe_s_sprite_.setPosition(sf::Vector2f(pipe_s_texture_.getSize().x/2.0f, 200));

    right_lower_brick_sprite_.setPosition(sf::Vector2f(window_->getSize().x-180, 720));
    right_mid_brick_sprite_.setPosition(sf::Vector2f(window_->getSize().x-60, 530));
    right_upper_brick_sprite_.setPosition(sf::Vector2f(window_->getSize().x-210, 300));
    left_lower_brick_sprite_.setPosition(sf::Vector2f(180, 720));
    left_mid_brick_sprite_.setPosition(sf::Vector2f(60, 530));
    left_upper_brick_sprite_.setPosition(sf::Vector2f(210,300));
    mid_brick_sprite_.setPosition(sf::Vector2f(window_->getSize().x/2.0f, 500));
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
    window.draw(right_lower_brick_sprite_);
    window.draw(right_mid_brick_sprite_);
    window.draw(right_upper_brick_sprite_);
    window.draw(left_lower_brick_sprite_);
    window.draw(left_mid_brick_sprite_);
    window.draw(left_upper_brick_sprite_);
    window.draw(mid_brick_sprite_);
}