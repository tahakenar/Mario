#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include "Mario/Object.h"
#include "Mario/Turtle.h"
#include "Mario/Mario.h"
#include "Mario/Object.h"
#include "Mario/Background.h"
#include "Mario/ScoreBoard.h"

class Game
{
    private:
        int speed_;
        int game_state_;
        bool mario_fall_flag_;

        bool up_;
        bool down_;
        bool left_;
        bool right_;

        sf::RenderWindow* window_;
        Background* floor_;
        Background* bricks_[7];
        Background* pipes_[4];

        Turtle* turtles_;
        Mario* mario_;
        ScoreBoard* score_board_;

    public:
        Game(int speed);
        void play(void);
        void menu(void);
        void handleMarioEvents();
        void handleTurtleEvents();
        void handleCharCollisions();
        void gameOver(void);
        void update(void);
        void drawBackground(sf::RenderWindow &window);
        bool checkFloorIntersection(const sf::IntRect& obj, const sf::IntRect& floor);
        bool checkCeilingIntersection(const sf::IntRect& obj, const sf::IntRect& ceiling);
        bool onFloor(Object *obj);
        bool hitCeiling(Object *obj);
        Turtle* addTurtle(void);
        bool checkCollision(Turtle *t, Mario *m, int &side);
        // TODO: Handle mario & turtle events in functions
};

#endif