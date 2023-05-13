#include "Mario/Turtle.h"
#include "spdlog/spdlog.h"

// TODO: Move them faster as time passes

Turtle::Turtle(sf::RenderWindow *window): Object(window)
{
    window_ = window;
    heading_ = HEADING_LEFT;
    state_ = TurtleStates::WALK;
    next_ = nullptr;

    this->loadTextures();
    sprite_.setTexture(textures_[0]);

    elapsed_time_ = clock_.getElapsedTime();
    spdlog::info("A turtle is initialized");
}

Turtle::~Turtle()
{
    spdlog::error("A turtle died!");
}


void Turtle::fall()
{
    this->setVerticalSpeed(MARIO_JUMP_SPEED);
}

void Turtle::move()
{
    //TODO: Move randomly

    sf::Vector2f goal_turtle_pos = this->getPosition();
    goal_turtle_pos.x += vx_;
    goal_turtle_pos.y += vy_;
    this->setPosition(goal_turtle_pos);
    // this->checkToTeleport();

    elapsed_time_ = clock_.getElapsedTime();
    if (elapsed_time_.asSeconds() > 2)
    {
        if (rand()%2 == 0)
        {
            // left
            this->setHeading(HEADING_LEFT);
            this->setLateralSpeed(-3);
        }
        else
        {
            // right
            this->setHeading(HEADING_RIGHT);
            this->setLateralSpeed(3);
        }
        clock_.restart();
        std::cout << pos_.x << " - " << pos_.y << std::endl;
    }

    if (pos_.x == LATERAL_INTERACTION_TRESHOLD && heading_ == HEADING_LEFT)
    {
        this->setHeading(HEADING_RIGHT);
        this->setLateralSpeed(3);
    }

    if (pos_.x == WINDOW_WIDTH - MARIO_WIDTH - LATERAL_INTERACTION_TRESHOLD && heading_ == HEADING_RIGHT)
    {
        this->setHeading(HEADING_LEFT);
        this->setLateralSpeed(-3);
    }

    // TESTING
    if ((pos_.x < 0 || pos_.x > WINDOW_WIDTH) || (pos_.y < 0 || pos_.y > WINDOW_HEIGHT)
    || (isnan(pos_.x)) || isnan(pos_.y))
    {
        spdlog::warn("Corrupted position, correcting");
        this->setPosition(sf::Vector2f(WINDOW_WIDTH/4, 250));
    }
    

    // this->updateTexture();    
}

void Turtle::jump(bool down)
{

}


void Turtle::loadTextures()
{
    textures_[0].loadFromFile(TURTLE_1);
    textures_[1].loadFromFile(TURTLE_2);
    textures_[2].loadFromFile(TURTLE_3);
    textures_[3].loadFromFile(TURTLE_4);
    textures_[4].loadFromFile(TURTLE_5);
}

void Turtle::setLateralSpeed(float vx)
{
    vx_ = vx;
}

void Turtle::setVerticalSpeed(float vy)
{
    vy_ = vy;
}

void Turtle::gravityEffect(bool set)
{
    if (set)
        vy_ = vy_ >= -MARIO_JUMP_SPEED ? -MARIO_JUMP_SPEED : vy_ + GRAVITY_COEFFICIENT;
    else
        vy_ = 0;
}

void Turtle::setHeading(int heading)
{
    heading_ = heading;
}


void Turtle::setState(int state)
{
    state_ = state;
}

int Turtle::getState()
{
    return state_;
}


void Turtle::updateTexture()
{
    if (state_ == TurtleStates::WALK)
    {
        animation_change_cnt_++;
        if (animation_change_cnt_ == 4)
        {
            sprite_.setTexture(textures_[walk_states_]);
            walk_states_++;
            animation_change_cnt_ = 0;
        }
        if (walk_states_ == 3)
            walk_states_ = 0;
    }
    if (state_ == TurtleStates::DIE)
    {
        sprite_.setTexture(textures_[4]);
    }

    if (heading_ == HEADING_RIGHT)
    {
        sprite_.setScale(1.f,1.f);
        sprite_.setOrigin(0, sprite_.getOrigin().y);
    }

    if (heading_ == HEADING_LEFT)
    {
        sprite_.setScale(-1.f,1.f);
        sprite_.setOrigin(+MARIO_WIDTH, sprite_.getOrigin().y);
    }
}


void Turtle::checkToTeleport()
{
    if (pos_.y > 860)
    {
        if (pos_.x < (PIPE_X_LEFT + PIPE_WIDTH))
            this->teleport(LEFT_PIPE);
        if (pos_.x > (PIPE_X_RIGHT - MARIO_WIDTH))
            this->teleport(RIGHT_PIPE);
    }
}

void Turtle::teleport(int pipe)
{
    if (pipe == LEFT_PIPE)
    {
        this->setPosition(sf::Vector2f(PIPE_S_X_LEFT + PIPE_S_WIDTH, 200));
    }
    if (pipe == RIGHT_PIPE)
    {
        this->setPosition(sf::Vector2f(PIPE_S_X_RIGHT - MARIO_WIDTH, 200));
    }
}
