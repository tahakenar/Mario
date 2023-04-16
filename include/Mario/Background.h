#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "Mario/definitions.h"

class Background
{
    private:

        int width_;
        int height_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Vector2f pos_;
        sf::RenderWindow *window_;
        sf::FloatRect bounding_box_;

    public:
        Background(std::string asset_path, int width, int height);
        void draw(sf::RenderWindow *window);
        void setPosition(sf::Vector2f pos);
        void flip(int axis);
        

};

#endif