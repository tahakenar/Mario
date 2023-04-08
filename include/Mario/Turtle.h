#ifndef TURTLE_H
#define TURTLE_H

#include "Mario/Object.h"

class Turtle : public Object
{
    private:
        float vx_;
        float vy_;
    public:
        Turtle(sf::RenderWindow *window);
        void move();
        void jump(bool down);
        void fall(void);
};


#endif