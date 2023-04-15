#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"
#include "Mario/Object.h"
#include "Mario/Ground.h"

class Game
{
    private:
        int speed_;

        sf::RenderWindow* window_;
        Ground* floor_;

        // Ground* grounds_[8];

        // Turtle* turtles_;
        Mario* mario_;

    public:
        Game(int speed);
        void update(void);
        void drawBackground(sf::RenderWindow &window);
        bool onFloor(Object *obj);
        // bool checkCollision(Turtle *t, Mario *m, int &side);
};

#endif