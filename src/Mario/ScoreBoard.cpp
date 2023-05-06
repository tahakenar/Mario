#include "Mario/ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    score_ = std::to_string(0);
    lives_ = 3;
}

void ScoreBoard::setScore(int score)
{
    score_ = std::to_string(score);
}

void ScoreBoard::setLives(int lives)
{
    lives_ = lives;
}

int ScoreBoard::getLives(void)
{
    return lives_;
}

std::string ScoreBoard::getScore(void)
{
    return score_;
}