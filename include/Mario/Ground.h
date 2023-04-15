#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class Ground
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
        Ground(std::string asset_path, int width, int height);
        void draw(sf::RenderWindow *window);
        void setPosition(sf::Vector2f pos);

};

#endif