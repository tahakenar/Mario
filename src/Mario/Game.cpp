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
    mario_->setPosition(sf::Vector2f(WINDOW_WIDTH/2, FLOOR_Y-MARIO_HEIGHT));

    // TODO: Initialize turtles

    // turtles_ = new Turtle(window_);

    score_board_ = new ScoreBoard();

    game_state_ = GameStates::MENU;
    mario_fall_flag_ = true;
}

void Game::play(void)
{
    std::cout << "Mario top play: " << mario_->boundingBox().top << std::endl;
    static bool up = false;
    static bool left = false;
    static bool right = false;
    static bool down = false;
    mario_fall_flag_ = true;

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
                up = true;
                break;
            case sf::Keyboard::Left:
                // spdlog::info("Left button pressed");
                left = true;
                break;
            case sf::Keyboard::Right:
                // spdlog::info("Right button pressed");
                right = true;
                break;
            case sf::Keyboard::Down:
                // spdlog::info("Down button pressed");
                down = true;
                // TESTING PURPOSES
                score_board_->setScore(std::stoi(score_board_->getScore())+1);
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
                left = false;
                break;
            case sf::Keyboard::Right:
                right = false;
                break;
            default:
                break;
            }
        }
    }

    if (left && onFloor(mario_))
    {
        mario_->run(MARIO_LATERAL_LEFT_SPEED, HEADING_LEFT);
    }
    if (right && onFloor(mario_))
    {
        mario_->run(MARIO_LATERAL_RIGHT_SPEED, HEADING_RIGHT);
    }
    if (up && onFloor(mario_))
    {
        mario_->jump();
    }
    if (!(left) && !(right) && onFloor(mario_) && !(up) && mario_->getSpeedX() != 0)
    {
        mario_->slide();
    }
    if (!(up) && onFloor(mario_) && mario_->getSpeedX() == 0)
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


    mario_->draw(*window_);
    up = false;
    down = false;
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

void Game::die()
{
    window_->clear();
    this->drawBackground(*window_);
    mario_->setState(MarioStates::FALL);
    mario_->updateTexture();
    mario_->gravityEffect(true);
    
    if (mario_fall_flag_)
    {
        mario_->fall();
        mario_fall_flag_ = false;
    }
    mario_->move();
    mario_->draw(*window_);

    sf::Event event;
    if (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_->close();
    }

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
            game_state_ = GameStates::PLAY;
        }
        else
            game_state_ = GameStates::GAMEOVER;
    }
}

void Game::gameOver(void)
{
   sf::Font font;
    font.loadFromFile(FONT_PATH);
    sf::Text header;
    sf::Text score;

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

    sf::Event event;
    if (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_->close();
    }
}

void Game::update(void)
{

    while (window_->isOpen())
    {

        window_->clear();

        if (game_state_ == GameStates::MENU)
            this->menu();
        
        if (game_state_ == GameStates::PLAY)
            this->play();
        
        if (game_state_ == GameStates::DIED)
            this->die();

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
        if ((mid_point > floor.left) && (mid_point < floor.width + floor.left))
            return true;
    }
    return false;
}

bool Game::checkCeilingIntersection(const sf::IntRect& obj, const sf::IntRect& ceiling)
{
    int mid_point = obj.left + obj.width/2;
    if (abs(ceiling.top + ceiling.height - obj.top) < CEILING_INTERACTION_TRESHOLD)
            if ((mid_point > ceiling.left) && (mid_point < ceiling.width + ceiling.left))
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