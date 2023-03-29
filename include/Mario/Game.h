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
        sf::Texture pipe_texture_;
        sf::Texture pipe_s_texture_;


        sf::Sprite floor_sprite_;
        sf::Sprite left_pipe_sprite_;
        sf::Sprite right_pipe_sprite_;
        sf::Sprite left_pipe_s_sprite_;
        sf::Sprite right_pipe_s_sprite_;



    public:
        Game();
        void uploadTextures();
        void setSpriteTextures();
        void setSpritePositions();

        void drawBackground(sf::RenderWindow& window);

        void update();
        bool onFloor(Object *obj);
        bool checkCollision(Turtle *t, Mario *m, int& side);
};

#endif