#include "Mario/ScoreBoard.h"
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
ScoreBoard::ScoreBoard()
{
    score_ = std::to_string(0);
    lives_ = 3;

    font_.loadFromFile(FONT_PATH);
    score_text_.setFont(font_);
    score_text_.setString(this->getScore());
    score_text_.setCharacterSize(60);
    score_text_.setFillColor(sf::Color::White);

    head_texture_.loadFromFile(MARIO_HEAD);
    head_.setTexture(head_texture_);
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

void ScoreBoard::printScore(sf::RenderWindow &window)
{
    score_text_.setString(this->getScore());
    window.draw(score_text_);
}

void ScoreBoard::printLives(sf::RenderWindow &window)
{
    for (int i = 0; i < lives_; i++)
    {
        head_.setPosition(sf::Vector2f(i*50, 90));
        window.draw(head_);
    }
}

void ScoreBoard::draw(sf::RenderWindow &window, sf::Sprite &sprite)
{
    window.draw(sprite);
}
