#ifndef TURTLE_H
#define TURTLE_H

#include "Mario/Object.h"
#include <cstdlib>

class Turtle : public Object
{
    private:
        float vx_;
        float vy_;
        bool heading_changed_;

        sf::Clock clock_; // handle random events & speed increase etc
        sf::Time elapsed_time_;

    public:
        Turtle(sf::RenderWindow *window);
        void move();
        void jump(bool down);
        void fall(void);
        void loadTextures(void);
        void setLateralSpeed(float vx);
        void setVerticalSpeed(float vy);
        void gravityEffect(bool set);
        void setHeading(int heading);
        void setState(int state);
        void updateTexture();
        void checkToTeleport();
        void teleport(int pipe);
};


#endif