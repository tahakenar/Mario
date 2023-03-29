#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Object
{
    protected:
        sf::Texture textures_[8];
        sf::Sprite sprite_;
        sf::Vector2f pos_;
        sf::RenderWindow window_;
        int state_;
        int heading_;

    public:
        Object(sf::RenderWindow *window);
        void setPosition(sf::Vector2f pos);
        sf::Vector2f getPosition();
        sf::IntRect boundingBox(void);
        void draw(sf::RenderWindow &window);
        void move(void);
        void fall(void);
        void jump(bool down);
};


#endif