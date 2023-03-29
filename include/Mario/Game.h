#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"

class Game
{
    private:


    public:
        Game();
        void drawBackground(sf::RenderWindow& window);
        bool onFloor(Object *obj);
        bool checkCollision(Turtle *t, Mario *m, int& side);
};

#endif