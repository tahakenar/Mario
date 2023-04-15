#ifndef MARIO_H
#define MARIO_H

#include "Mario/Object.h"

class Mario : public Object
{
    private:
        float vx_;
        float vy_;

    public:
        Mario(sf::RenderWindow *window);
        void move();
        void jump(bool down);
        void fall(void);
        void loadTextures(void);
        void setLateralSpeed(float vx);
        void lateralSpeedDecay();
        void setVerticalSpeed(float vy);
        void gravityEffect(bool set);
        float getSpeedX(void);
};

#endif