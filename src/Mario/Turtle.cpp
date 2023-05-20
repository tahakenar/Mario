#include "Mario/Turtle.h"
#include "spdlog/spdlog.h"


Turtle::Turtle(sf::RenderWindow *window) : Object(window), walk_speed_(TURTLE_WALK_SPEED) {
  window_ = window;
  heading_ = HEADING_LEFT;
  state_ = TurtleStates::WALK;
  next_ = nullptr;

  this->loadTextures();
  sprite_.setTexture(textures_[0]);

  this->setLateralSpeed(-walk_speed_);

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

void Turtle::move() {
  sf::Vector2f goal_turtle_pos = this->getPosition();
  goal_turtle_pos.x += vx_;
  goal_turtle_pos.y += vy_;
  this->setPosition(goal_turtle_pos);

  elapsed_time_ = clock_.getElapsedTime();
  if (elapsed_time_.asSeconds() > 3) {
    this->increaseSpeed();
    if (rand() % 2 == 0) {
      // left
      this->setHeading(HEADING_LEFT);
      this->setLateralSpeed(-walk_speed_);
    } else {
      // right
      this->setHeading(HEADING_RIGHT);
      this->setLateralSpeed(walk_speed_);
    }
    clock_.restart();
  }

  if (pos_.x == LATERAL_INTERACTION_TRESHOLD && heading_ == HEADING_LEFT) {
    this->setHeading(HEADING_RIGHT);
    this->setLateralSpeed(walk_speed_);
  }

  if (pos_.x + TURTLE_WIDTH == WINDOW_WIDTH - LATERAL_INTERACTION_TRESHOLD &&
      heading_ == HEADING_RIGHT) {
    this->setHeading(HEADING_LEFT);
    this->setLateralSpeed(-walk_speed_);
  }
}

// HARD CODED BUG FIX
void Turtle::correctCorruptedPosition() {
  if ((pos_.x < 0 || pos_.x > WINDOW_WIDTH) ||
      (pos_.y < 0 || pos_.y >= FLOOR_Y) || (isnan(pos_.x)) || isnan(pos_.y)) {
    // spdlog::warn("Corrupted position, correcting");
    this->setPosition(sf::Vector2f(WINDOW_WIDTH / 4, 262));
  }
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

void Turtle::increaseSpeed(){ 
    if (walk_speed_ < 20)
        walk_speed_ += 0.5;
}


void Turtle::setVerticalSpeed(float vy)
{
    vy_ = vy;
}

void Turtle::gravityEffect(bool set) {
  if (set)
    vy_ = vy_ >= -TURTLE_JUMP_SPEED ? -TURTLE_JUMP_SPEED
                                    : vy_ + GRAVITY_COEFFICIENT;
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


void Turtle::updateTexture() {
  if (state_ == TurtleStates::WALK) {
    animation_change_cnt_++;
    if (animation_change_cnt_ == 4) {
      sprite_.setTexture(textures_[walk_states_]);
      walk_states_++;
      animation_change_cnt_ = 0;
    }
    if (walk_states_ == 3) walk_states_ = 0;
  }
  if (state_ == TurtleStates::DIE) {
    sprite_.setTexture(textures_[4]);
  }

  if (heading_ == HEADING_RIGHT) {
    sprite_.setScale(1.f, 1.f);
    sprite_.setOrigin(0, sprite_.getOrigin().y);
  }

  if (heading_ == HEADING_LEFT) {
    sprite_.setScale(-1.f, 1.f);
    sprite_.setOrigin(+TURTLE_WIDTH, sprite_.getOrigin().y);
  }
}


void Turtle::checkToTeleport() {
  if (pos_.y > LOWER_TELEPORT_Y) {
    if (pos_.x < (PIPE_X_LEFT + PIPE_WIDTH)) 
       this->teleport(LEFT_PIPE);
    if (pos_.x > (PIPE_X_RIGHT - MARIO_WIDTH)) 
       this->teleport(RIGHT_PIPE);
  }
}


void Turtle::teleport(int pipe) {
  if (pipe == LEFT_PIPE) {
    this->setPosition(
        sf::Vector2f(PIPE_S_X_LEFT + PIPE_S_WIDTH, UPPER_TELEPORT_Y));
  }
  if (pipe == RIGHT_PIPE) {
    this->setPosition(
        sf::Vector2f(PIPE_S_X_RIGHT - MARIO_WIDTH, UPPER_TELEPORT_Y));
  }
}

