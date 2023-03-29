#ifndef GAME_H
#define GAME_H

#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"

class Game
{
    private:
        sf::RenderWindow *window_;
        sf::Texture floor_texture_;
        sf::Sprite floor_sprite_;

    public:
        Game();
        void update();
        void drawBackground(sf::RenderWindow& window);
        bool onFloor(Object *obj);
        bool checkCollision(Turtle *t, Mario *m, int& side);
};

#endif