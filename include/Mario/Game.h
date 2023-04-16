#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"
#include "Mario/Object.h"
#include "Mario/Background.h"

class Game
{
    private:
        int speed_;

        sf::RenderWindow* window_;
        Background* floor_;
        Background* bricks_[7];
        Background* pipes_[4];

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