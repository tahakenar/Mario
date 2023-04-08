#ifndef GAME_H
#define GAME_H

#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"
#include "Mario/Object.h"

class Game
{
    private:

    public:
        void drawBackground(sf::RenderWindow &window);
        bool onFloor(Object *obj);
        bool checkCollision(Turtle *t, Mario *m, int &side);
};

#endif