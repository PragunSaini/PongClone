#ifndef __PADDLE_H__
#define __PADDLE_H__

// header files
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// self defined headers
#include "Entity.h"

// Paddle Class
class Paddle : public Entity {

    // private members
    private:
        float wallMargin;   // to store top and bottom wall margin
        float SPEED = 1.0f; // speed of the paddles

        // store direction of movement
        bool movingUp;
        bool movingDown;

        // check if space left above and below to move
        bool spaceDown(){
            return sprite.getPosition().y <= parentWindow->getSize().y - wallMargin - texture.getSize().y;
        }
        bool spaceUp(){
            return sprite.getPosition().y >= wallMargin;
        }

    // public members
    public:

        enum Color {Red, Blue};

        // Constructor to create a paddle
        Paddle(Color paddleColor, float wallMargin);

        // set Parent window
        void setParentWindow(sf::RenderWindow *parentWindow){
            this->parentWindow = parentWindow;
        }

        // set the position of the paddle
        void setPosition(sf::Vector2f position);

        // draw the paddle sprite on the screen
        void draw();

        // get the size of the texture
        sf::Vector2u getSize();

        // get the surrounding box for collision detection
        sf::FloatRect getBounds();

        // getter function for velocity
        float getVelocity(){
            return SPEED * (movingDown ? 1 : -1);
        }

        // functions to set movement state of the paddle
        void setMovingUp(bool movement){
            movingUp = movement;
        }

        void setMovingDown(bool movement){
            movingDown = movement;
        }

        // function to move the paddle
        void movePaddle();
};

#endif