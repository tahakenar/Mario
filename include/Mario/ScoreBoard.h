#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>


class ScoreBoard
{
    private:
        std::string score_;
        int lives_;
    public:
        ScoreBoard();
        void setScore(int score);
        void setLives(int lives);
        int getLives(void);
        std::string getScore(void);
};

#endif