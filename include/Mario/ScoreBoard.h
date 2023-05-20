#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "definitions.h"


class ScoreBoard
{
    private:
        std::string score_;
        int lives_;
        sf::Font font_;
        sf::Text score_text_;
        sf::Sprite head_;
        sf::Texture head_texture_;

    public:
        ScoreBoard();
        void setScore(int score);
        void setLives(int lives);
        int getLives(void);
        std::string getScore(void);
        void printScore(sf::RenderWindow &window);
        void printLives(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window, sf::Sprite &sprite);
};

#endif