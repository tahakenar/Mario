#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>

class ScoreBoard
{
    private:
        std::string score_;
        int lives_;
    public:
        void setScore(int score);
        void setLives(int lives);
        int getLives(void);
};

#endif