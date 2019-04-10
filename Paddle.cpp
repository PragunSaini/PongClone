
// self defined headers
#include "Paddle.h"


// Constructor to create a paddle
Paddle::Paddle(Color paddleColor, float wallMargin){
    // load file as texture according to color
    if (paddleColor == Color::Blue){
        texture.loadFromFile("resources/paddle_blue.png");
    }
    if (paddleColor == Color::Red){
        texture.loadFromFile("resources/paddle_red.png");
    }

    // set the texture as the sprite
    sprite.setTexture(texture);
    // store the wall margin for use
    this->wallMargin = wallMargin;

    // set no movement
    movingDown = movingUp = false;

    SPEED = 1.0f;
}

// set the position of the paddle
void Paddle::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
}

// draw the paddle sprite on the screen
void Paddle::draw(){
    parentWindow->draw(sprite);
}

// get the size of the texture
sf::Vector2u Paddle::getSize(){
    return texture.getSize();
}

// get the surrounding box for collision detection
sf::FloatRect Paddle::getBounds(){
    return sprite.getGlobalBounds();
}


// function to move the paddle
void Paddle::movePaddle(){
    if (movingUp && spaceUp()){
        sprite.move(sf::Vector2f(0.f, -SPEED));
    }
    if (movingDown && spaceDown()){
        sprite.move(sf::Vector2f(0.f, SPEED));
    }
}
