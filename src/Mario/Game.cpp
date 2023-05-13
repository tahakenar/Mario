#include "Mario/Game.h"
#include "spdlog/spdlog.h"

Game::Game(int speed): speed_(speed)
{
    window_ = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Sahane Kazim");

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
    mario_->setPosition(sf::Vector2f(WINDOW_WIDTH/2, FLOOR_Y-200));

    down_ = false;
    up_ = false;
    left_ = false;
    right_ = false;

    // TODO: Initialize turtles
    // turtles_ = addTurtle();
    // turtles_[0].setPosition(sf::Vector2f(WINDOW_WIDTH/4, FLOOR_Y-MARIO_HEIGHT));
    turtles_ = new Turtle(window_); 
    turtles_->setPosition(sf::Vector2f(WINDOW_WIDTH/4, 270));


    score_board_ = new ScoreBoard();

    game_state_ = GameStates::MENU;
}

void Game::handleMarioEvents()
{
    if (game_state_ == GameStates::PLAY)
    {
        mario_->setFallFlag(true);

        if (left_ && onFloor(mario_))
        {
            mario_->run(MARIO_LATERAL_LEFT_SPEED, HEADING_LEFT);
        }
        if (right_ && onFloor(mario_))
        {
            mario_->run(MARIO_LATERAL_RIGHT_SPEED, HEADING_RIGHT);
        }
        if (up_ && onFloor(mario_))
        {
            mario_->jump();
        }
        if (!(left_) && !(right_) && onFloor(mario_) && !(up_) && mario_->getSpeedX() != 0)
        {
            mario_->slide();
        }
        if (!(up_) && onFloor(mario_) && mario_->getSpeedX() == 0)
        {
            mario_->setState(MarioStates::STILL);
            mario_->updateTexture();
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

        if (hitCeiling(mario_))
        {
            mario_->gravityEffect(true);
            mario_->setVerticalSpeed(5);
        }
    }
    else if (game_state_ == GameStates::DIED)
    {
        mario_->setState(MarioStates::FALL);
        mario_->updateTexture();

        if (mario_->getFallFlag())
        {
            mario_->fall();
            mario_->setFallFlag(false);
        }
        mario_->move();
        mario_->gravityEffect(true);
        if (mario_->boundingBox().top >= FLOOR_Y)
        {
            if (score_board_->getLives() > 0)
            {
                mario_->setState(MarioStates::STILL);
                mario_->setPosition(sf::Vector2f(WINDOW_WIDTH/2, FLOOR_Y-200));
                mario_->updateTexture();
                mario_->setLateralSpeed(0);
                mario_->setVerticalSpeed(0);
                mario_->draw(*window_);
                left_ = false;
                right_ = false;
                game_state_ = GameStates::PLAY;
            }
            else
                game_state_ = GameStates::GAMEOVER;
        }
    }

}

void Game::handleTurtleEvents()
{

    if (turtles_->getState() == TurtleStates::DIE)
    {
        if (turtles_->getFallFlag())
        {
            turtles_->fall();
            turtles_->setLateralSpeed(0);
            turtles_->setFallFlag(false);
        }
        //TODO: Delete turtle
        if (turtles_->boundingBox().top >= FLOOR_Y)
        {
            turtles_->setState(TurtleStates::WALK);
            turtles_->updateTexture();
            turtles_->setVerticalSpeed(0);
            turtles_->setPosition(sf::Vector2f(WINDOW_WIDTH/4, 270));
        }
        
        turtles_->move();
        turtles_->gravityEffect(true);
    }
    else
    {
        turtles_->setFallFlag(true);
        turtles_->move();
        if (onFloor(turtles_))
        {
            turtles_->gravityEffect(false);
        }
        else
        {
            turtles_->gravityEffect(true);
        }
    }



}

void Game::handleCharCollisions()
{
    if (game_state_ == GameStates::PLAY)
    {
        int up = 3;
        if (this->checkCollision(turtles_, mario_, up) && !(onFloor(mario_)))
        {
            score_board_->setScore(std::stoi(score_board_->getScore())+100);
            mario_->setVerticalSpeed(-10);
            turtles_->setState(TurtleStates::DIE);
            // mario_->setVerticalSpeed(-10);
            // turtles_->fall();
            // turtles_->setLateralSpeed(0);
        }
        // DOWN
        int lateral = 2;
        if (this->checkCollision(turtles_, mario_, lateral) && onFloor(mario_))
        {
            score_board_->setLives(score_board_->getLives()-1);
            game_state_ = GameStates::DIED;     
        }
    }
}

void Game::play(void)
{
    this->drawBackground(*window_);



    sf::Event event;
    if (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_->close();
        
        if (event.type == sf::Event::KeyPressed)
        {
            // spdlog::info("Key pressed");
            switch (event.key.code)
            {
            case  sf::Keyboard::Up:
                // spdlog::info("Up button pressed");
                up_ = true;
                break;
            case sf::Keyboard::Left:
                // spdlog::info("Left button pressed");
                left_ = true;
                break;
            case sf::Keyboard::Right:
                // spdlog::info("Right button pressed");
                right_ = true;
                break;
            case sf::Keyboard::Down:
                // spdlog::info("Down button pressed");
                down_ = true;
                // TESTING PURPOSES
                // score_board_->setScore(std::stoi(score_board_->getScore())+1);
                score_board_->setLives(score_board_->getLives()-1);
                game_state_ = GameStates::DIED;
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                left_ = false;
                break;
            case sf::Keyboard::Right:
                right_ = false;
                break;
            default:
                break;
            }
        }
    }

    this->handleCharCollisions();
    this->handleMarioEvents();
    this->handleTurtleEvents();
    

    mario_->draw(*window_);
    turtles_->draw(*window_);
    up_ = false;
    down_ = false;
}

void Game::menu(void)
{
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    sf::Text header;
    sf::Text play_button;

    header.setFont(font);
    play_button.setFont(font);
    header.setCharacterSize(90);
    play_button.setCharacterSize(60);
    header.setFillColor(sf::Color::Red);
    play_button.setFillColor(sf::Color::White);
    header.setString("Sahane Kazim");
    play_button.setString("Play");
    header.setOrigin(sf::Vector2f(header.getLocalBounds().width/2.f, 0));
    header.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f,100.f));
    play_button.setOrigin(sf::Vector2f(play_button.getLocalBounds().width/2.f, 0));
    play_button.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f,300.f));

    sf::Sprite menu_head;
    sf::Texture mario_head;
    mario_head.loadFromFile(MARIO_HEAD);
    menu_head.setTexture(mario_head);
    menu_head.setScale(sf::Vector2f(2.f,2.f));
    menu_head.setOrigin(sf::Vector2f(menu_head.getLocalBounds().width/2.f, menu_head.getLocalBounds().height/2.f));
    menu_head.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f, 600));

    window_->draw(header);
    window_->draw(play_button);
    window_->draw(menu_head);

    sf::Event event;
    if (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_->close();
        
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button ==  sf::Mouse::Left)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window_);
                if (play_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(localPosition)))
                    game_state_ = GameStates::PLAY;
            }
            
        }
    }
}

void Game::gameOver(void)
{
    sf::Font font;
    font.loadFromFile(FONT_PATH);
    sf::Text header;
    sf::Text score;


    sf::Text restart_button;
    restart_button.setFont(font);
    restart_button.setCharacterSize(60);
    restart_button.setString("Replay!");
    restart_button.setFillColor(sf::Color::Green);
    restart_button.setOrigin(sf::Vector2f(restart_button.getLocalBounds().width/2.f, 0));
    restart_button.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f,600.f));

    header.setFont(font);
    score.setFont(font);
    header.setCharacterSize(90);
    score.setCharacterSize(60);
    header.setFillColor(sf::Color::Red);
    score.setFillColor(sf::Color::White);
    header.setString("GAME OVER");
    score.setString("Your score: " + score_board_->getScore());
    header.setOrigin(sf::Vector2f(header.getLocalBounds().width/2.f, 0));
    header.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f,100.f));
    score.setOrigin(sf::Vector2f(score.getLocalBounds().width/2.f, 0));
    score.setPosition(sf::Vector2f(WINDOW_WIDTH/2.f,300.f));

    window_->draw(header);
    window_->draw(score);
    window_->draw(restart_button);

    sf::Event event;
    if (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_->close();
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button ==  sf::Mouse::Left)
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(*window_);
                if (restart_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(localPosition)))
                {
                    game_state_ = GameStates::PLAY;
                    score_board_->setLives(3);
                    score_board_->setScore(0);
                    mario_->setState(MarioStates::STILL);
                    mario_->updateTexture();
                    mario_->setPosition(sf::Vector2f(WINDOW_WIDTH/2, FLOOR_Y-200));
                    mario_->setLateralSpeed(0);
                    mario_->setVerticalSpeed(0);
                    left_ = false;
                    right_ = false;
                    game_state_ = GameStates::PLAY;
                }
            }
            
        }
    }
}

void Game::update(void)
{

    while (window_->isOpen())
    {

        window_->clear();

        if (game_state_ == GameStates::MENU)
            this->menu();
        
        if (game_state_ == GameStates::PLAY || game_state_ == GameStates::DIED)
            this->play();
        
        if (game_state_ == GameStates::GAMEOVER)
            this->gameOver();

        window_->display();
        sf::sleep(sf::milliseconds(10000/speed_));

    }
}

void Game::drawBackground(sf::RenderWindow &window)
{
    floor_->draw(dynamic_cast<sf::RenderWindow*>(&window));

    for (const auto &brick : bricks_)
        brick->draw(dynamic_cast<sf::RenderWindow*>(&window));

    for (const auto &pipe: pipes_)
        pipe->draw(dynamic_cast<sf::RenderWindow*>(&window));

    score_board_->printLives(window);
    score_board_->printScore(window);  
}

bool Game::checkFloorIntersection(const sf::IntRect& obj, const sf::IntRect& floor)
{
    int mid_point = obj.left + obj.width/2;

    if (abs(floor.top - (obj.top + obj.height)) < FLOOR_INTERACTION_TRESHOLD)
    {
        if ((obj.left + obj.width > floor.left) && (obj.left < floor.width + floor.left))
            return true;
    }
    return false;
}

bool Game::checkCeilingIntersection(const sf::IntRect& obj, const sf::IntRect& ceiling)
{
    int mid_point = obj.left + obj.width/2;
    if (abs(ceiling.top + ceiling.height - obj.top) < CEILING_INTERACTION_TRESHOLD)
            if ((obj.left + obj.width > ceiling.left) && (obj.left  < ceiling.width + ceiling.left))
                return true;
    else
        return false;
}

bool Game::hitCeiling(Object *obj)
{
    sf::IntRect obj_bounding_box = obj->boundingBox();

    for (const auto& brick : bricks_)
    {
        if (checkCeilingIntersection(obj_bounding_box, brick->boundingBox()))
        {
            return true;
        }
    }
    return false;
}


bool Game::onFloor(Object *obj)
{
    sf::IntRect obj_bounding_box = obj->boundingBox();

    for (const auto& brick : bricks_)
    {
        if (checkFloorIntersection(obj_bounding_box, brick->boundingBox()))
        {
            obj->setPosition(sf::Vector2f(obj->getPosition().x, float(brick->boundingBox().top - obj_bounding_box.height)));
            return true;
        }
    }

    sf::IntRect floor_bb = floor_->boundingBox();
    if (checkFloorIntersection(obj_bounding_box, floor_bb))
    {
        obj->setPosition(sf::Vector2f(obj->getPosition().x, float(FLOOR_Y)-obj_bounding_box.height));
        return true;
    }
    else
    {
        return false;
    }
}

Turtle* Game::addTurtle(void)
{
    Turtle* turtle = new Turtle(window_);
    turtle->next_ = turtles_;
    turtles_ = turtle;
    return turtle;
}

bool Game::checkCollision(Turtle *t, Mario *m, int &side)
{
    if (t->getState() == TurtleStates::DIE || m->getState() == MarioStates::FALL)
        return false;

    sf::IntRect mario_bb = m->boundingBox();
    sf::IntRect turtle_bb = t->boundingBox();

    if ((mario_bb.left + mario_bb.width > turtle_bb.left && mario_bb.left < turtle_bb.left + turtle_bb.width) ||
    (mario_bb.left < turtle_bb.left + turtle_bb.width && mario_bb.left + mario_bb.width > turtle_bb.left))
    {
        if (abs((mario_bb.top + mario_bb.height) - (turtle_bb.top)) < 10 && side == UP)
        {
            return true;
        }
        if (mario_bb.top + mario_bb.height == turtle_bb.top + turtle_bb.height && side != UP)
        {
            return true;
        }
    }
    return false;
}