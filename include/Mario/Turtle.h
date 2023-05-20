#ifndef TURTLE_H
#define TURTLE_H

#include "Mario/Object.h"
#include <cstdlib>

class Turtle : public Object
{
  private:
    float walk_speed_;
    float vx_;
    float vy_;
    bool heading_changed_;

    Turtle* next_;
    friend class Game;

    sf::Clock clock_;  // handle random events & speed increase etc
    sf::Time elapsed_time_;


    public:
        Turtle(sf::RenderWindow* window);
        ~Turtle();
        void move();
        void correctCorruptedPosition();
        void jump(bool down);
        void fall(void);
        void loadTextures(void);
        void setLateralSpeed(float vx);
        void increaseSpeed();
        void setVerticalSpeed(float vy);
        void gravityEffect(bool set);
        void setHeading(int heading);
        void setState(int state);
        int getState();
        void updateTexture();
        void checkToTeleport();
        void teleport(int pipe);
};


#endif