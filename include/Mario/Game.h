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
        int live_turtle_cnt_;
        int spawned_turtle_cnt_;
        bool mario_fall_flag_;

        bool up_;
        bool down_;
        bool left_;
        bool right_;

        sf::Clock clock_; // handle random events & speed increase etc
        sf::Time elapsed_time_;

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
        void gameOver(bool win);
        void handleMarioEvents();
        void update(void);
        void drawBackground(sf::RenderWindow &window);
        bool checkFloorIntersection(const sf::IntRect& obj, const sf::IntRect& floor);
        bool checkCeilingIntersection(const sf::IntRect& obj, const sf::IntRect& ceiling);
        bool onFloor(Object *obj);
        bool hitCeiling(Object *obj);

        void turtleSpawner(void);
        Turtle* addTurtle(void);
        void removeTurtle(Turtle* t);
        void removeTurtleList();
        void drawTurtles(void);
        void handleTurtles();   // TODO: Find a better name
        void handleTurtleEvents(Turtle* turtle);
        void handleCharCollisions();

        bool checkCollision(Turtle *t, Mario *m, int &side);
        // TODO: Handle mario & turtle events in functions
};

#endif