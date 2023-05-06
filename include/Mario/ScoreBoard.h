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

/*
    sf::Font font;
    font.loadFromFile("../assets/font.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(score_board_->getScore());
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    window_->draw(text);


        int lives = score_board_->getLives();

        for (int i = 0; i < lives; i++)
        {
            sf::Sprite head;
            sf::Texture head_texture;
            head_texture.loadFromFile("../assets/mariohead.png");
            head.setTexture(head_texture);
            head.setPosition(sf::Vector2f(i*50, 90));
            window_->draw(head);
        }

*/

#endif