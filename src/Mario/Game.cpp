#include "Mario/Game.h"

Game::Game(int speed): speed_(speed)
{
    window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Mario");

    // TODO: create background
    floor_ = new Background(FLOOR_ASSET_PATH, FLOOR_WIDTH, FLOOR_HEIGHT);
    floor_->setPosition(sf::Vector2f(FLOOR_X, FLOOR_Y));

    bricks_[0] = new Background(BRICK_ASSET_PATH, FIRST_FLOOR_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[1] = new Background(BRICK_ASSET_PATH, FIRST_FLOOR_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[2] = new Background(BRICK_ASSET_PATH, MIDDLE_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[3] = new Background(BRICK_ASSET_PATH, SHORT_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[4] = new Background(BRICK_ASSET_PATH, SHORT_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[5] = new Background(BRICK_ASSET_PATH, LAST_FLOOR_BRICK_WIDTH, BRICK_HEIGHT);
    bricks_[6] = new Background(BRICK_ASSET_PATH, LAST_FLOOR_BRICK_WIDTH, BRICK_HEIGHT);

    bricks_[0]->setPosition(sf::Vector2f(FIRST_FLOOR_BRICK_X_LEFT, FIRST_FLOOR_BRICK_Y));
    bricks_[1]->setPosition(sf::Vector2f(FIRTS_FLOOR_BRICK_X_RIGHT, FIRST_FLOOR_BRICK_Y));
    bricks_[2]->setPosition(sf::Vector2f(MIDDLE_BRICK_X, MIDDLE_BRICK_Y));
    bricks_[3]->setPosition(sf::Vector2f(SHORT_BRICK_X_LEFT, SHORT_BRICK_Y));
    bricks_[4]->setPosition(sf::Vector2f(SHORT_BRICK_X_RIGHT, SHORT_BRICK_Y));
    bricks_[5]->setPosition(sf::Vector2f(LAST_FLOOR_BRICK_X_LEFT, LAST_FLOOR_Y));
    bricks_[6]->setPosition(sf::Vector2f(LAST_FLOOR_BRICK_X_RIGHT, LAST_FLOOR_Y));

    pipes_[0] = new Background(PIPE_ASSET_PATH, PIPE_WIDTH, PIPE_HEIGHT);
    pipes_[1] = new Background(PIPE_ASSET_PATH, PIPE_WIDTH, PIPE_HEIGHT);
    pipes_[2] = new Background(PIPE_S_ASSET_PATH, PIPE_S_WIDTH, PIPE_S_HEIGHT);
    pipes_[3] = new Background(PIPE_S_ASSET_PATH, PIPE_S_WIDTH, PIPE_S_HEIGHT);

    // TODO: Find a generic solution?
    pipes_[0]->flip(Y_AXIS);
    pipes_[0]->setPosition(sf::Vector2f(PIPE_X_LEFT+PIPE_WIDTH/2,PIPE_Y+PIPE_HEIGHT/2));
    pipes_[1]->setPosition(sf::Vector2f(PIPE_X_RIGHT,PIPE_Y));
    pipes_[2]->setPosition(sf::Vector2f(PIPE_S_X_LEFT, PIPE_S_Y));
    pipes_[3]->flip(Y_AXIS);
    pipes_[3]->setPosition(sf::Vector2f(PIPE_S_X_RIGHT+PIPE_S_WIDTH/2, PIPE_S_Y+PIPE_S_HEIGHT/2));

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && onFloor(mario_))
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
    bricks_[0]->draw(window_);
    bricks_[1]->draw(window_);
    bricks_[2]->draw(window_);
    bricks_[3]->draw(window_);
    bricks_[4]->draw(window_);
    bricks_[5]->draw(window_);
    bricks_[6]->draw(window_);
    pipes_[0]->draw(window_);
    pipes_[1]->draw(window_);
    pipes_[2]->draw(window_);
    pipes_[3]->draw(window_);
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