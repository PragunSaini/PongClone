#ifndef __BALL_H__
#define __BALL_H__

// header files
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

// self defined header
#include "Entity.h"
#include "Paddle.h"

// to track the scores
extern int scoreRed;
extern int scoreBlue;

class Ball : public Entity {

    // private members
    private:
        // to play sound on ball bounce
        sf::SoundBuffer bounceBuffer;
        sf::Sound ballBounce;

        // store velocity of ball
        float dx;
        float dy;

        // wall margin to check wall collision
        float wallMargin;

        // clocks to use to check time since collision
        sf::Clock lastCollision;


        float RandomNumber(float Min, float Max){
            return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) ;
        }

        // generate a random velocity of the ball
        float randomVelocity(){
            float speed = RandomNumber(2, 3) - RandomNumber(2, 3);
            while(speed > -0.25 && speed < 0.25){
                speed = RandomNumber(2, 3) - RandomNumber(2, 3);
            }
            return speed;
        }

        // check for a wall collision
        bool wallCollision(){
            return (sprite.getPosition().y <= wallMargin) ||
            (sprite.getPosition().y >= parentWindow->getSize().y - wallMargin - texture.getSize().y);
        }

        //store collision
        bool hasCollidedWithPaddle;

        // store ball in window
        bool outOfBounds;


    // public members
    public:

        // consructor to make a ball
        Ball(float);

        // set Parent window
        void setParentWindow(sf::RenderWindow *parentWindow){
            this->parentWindow = parentWindow;
        }

        // set the position of the ball
        void setPosition(sf::Vector2f);

        // draw to the screen
        void draw();

        // get the size of ball texture
        sf::Vector2u getSize();

        // get the ball hitbox for collision detection
        sf::FloatRect getBounds();

        // check collision with walls
        bool checkWallCollision();

        // checkCollision with a paddle
        bool checkPaddleCollision(Paddle *paddle);

        // change values on ball collision with a paddle
        void paddleCollision(bool collision, float paddleYVelocity);

        // Move the ball while checking for collision
        bool moveBall();

        // to check if ball is in window or not
        bool checkOutOfBounds();

};

#endif