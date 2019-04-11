// self defined header
#include "Ball.h"

// constructor to make a ball
Ball::Ball(float wallMargin){
    // load ball texture
    texture.loadFromFile("resources/ball.png");
    // set it as aprite
    sprite.setTexture(texture);

    // load the bounce sound files
    bounceBuffer.loadFromFile("resources/bounce.ogg");
    ballBounce.setBuffer(bounceBuffer);

    // get beginning velocity of ball
    dx = randomVelocity();
    dy = randomVelocity();

    // store the wall margin value
    this->wallMargin = wallMargin;

    outOfBounds = false;
}

// set the position of the ball
void Ball::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
}

// draw to the screen
void Ball::draw(){
    parentWindow->draw(sprite);
}

// get the size of ball texture
sf::Vector2u Ball::getSize(){
    return texture.getSize();
}

// get the ball hitbox for collision detection
sf::FloatRect Ball::getBounds(){
    return sprite.getGlobalBounds();
}

// checkCollision with a paddle
bool Ball::checkPaddleCollision(Paddle *paddle){
    return getBounds().intersects(paddle->getBounds());
}

bool Ball::operator==(Paddle *paddle){
    return getBounds().intersects(paddle->getBounds());
}

// check collision with the walls
bool Ball::checkWallCollision(){
    return (sprite.getPosition().y <= wallMargin) ||
    (sprite.getPosition().y >= parentWindow->getSize().y - wallMargin - texture.getSize().y);
}

// change values on ball collision with a paddle
void Ball::paddleCollision(bool didCollide, float paddleYVelocity){
    if (lastCollision.getElapsedTime().asSeconds() >= 1){
        hasCollidedWithPaddle = didCollide;
        // add part of paddle's velocity to the ball
        dy = (dy * 1.2) + paddleYVelocity / 5;
        // reverse the direction
        dx = dx * -1.2;
        lastCollision.restart();
    }
}

bool Ball::checkOutOfBounds(){
    if (sprite.getPosition().x < 0){
        scoreBlue++;
        return true;
    }
    if (sprite.getPosition().x > parentWindow->getSize().x){
        scoreRed++;
        return true;
    }
    return false;
}


// Move the ball while checking for collision
bool Ball::moveBall(){
    // if collided with wall just reverse y direction
    if (checkWallCollision()){
        dy = -dy;
        ballBounce.play();
    }
    // paddle collision physics handled in paddleCollision function
    if (hasCollidedWithPaddle){
        ballBounce.play();
    }

    if (checkOutOfBounds()){
        return true;
    }

    hasCollidedWithPaddle = false;
    // move the ball
    sprite.move(sf::Vector2f(dx, dy));
    return false;
}

