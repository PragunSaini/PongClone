#ifndef __Entity__
#define __Entity__

// Header Files
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Entity class definition
class Entity {

    // protected data members
    protected:
        sf::RenderWindow* parentWindow;
        sf::Texture texture;
        sf::Sprite sprite;
    // public member functions

    public:
        virtual void setParentWindow(sf::RenderWindow* ) = 0;
        void setPosition(sf::Vector2f );
        void draw();
        sf::Vector2u getSize();
        sf::FloatRect getBound();
};

#endif // __Entity__