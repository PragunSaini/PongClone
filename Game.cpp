// self defined header
#include "Game.h"

// to track the scores
int scoreRed = 0;
int scoreBlue = 0;

Game::Game(){
    // create a window
    gameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
    gameWindow.setFramerateLimit(1000);
    gameState = true;

    // create the top and bottom walls
    topWall.setFillColor(WALL_COLOR);
    topWall.setSize(WALL_DIMENSION);
    topWall.setPosition(sf::Vector2f(0, 0));

    bottomWall.setFillColor(WALL_COLOR);
    bottomWall.setSize(WALL_DIMENSION);
    bottomWall.setPosition(sf::Vector2f(0, WINDOW_HEIGHT - WALL_DIMENSION.y));

    dividerWall.setFillColor(sf::Color(25, 255, 0));
    dividerWall.setSize(sf::Vector2f(4, WINDOW_HEIGHT - 40));
    dividerWall.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - 2, 20));

    // Create a ball
    ball = new Ball(WALL_DIMENSION.y);
    ball->setPosition(sf::Vector2f(WINDOW_WIDTH/2 - ball->getSize().x/2,
                                    WINDOW_HEIGHT/2 - ball->getSize().y/2));
    ball->setParentWindow(&gameWindow);

    // Create paddles
    paddleLeft = new Paddle(Paddle::Color::Red, WALL_DIMENSION.y);
    paddleLeft->setPosition(sf::Vector2f(PADDLE_MARGIN, WINDOW_HEIGHT/2 - paddleLeft->getSize().y/2));
    paddleLeft->setParentWindow(&gameWindow);

    paddleRight = new Paddle(Paddle::Color::Blue, WALL_DIMENSION.y);
    paddleRight->setPosition(sf::Vector2f(WINDOW_WIDTH - paddleRight->getSize().x - PADDLE_MARGIN, WINDOW_HEIGHT/2 - paddleRight->getSize().y/2));
    paddleRight->setParentWindow(&gameWindow);

    font.loadFromFile("resources/SebastienSlabRound.ttf");
    score_blue.setFont(font);
    score_red.setFont(font);
    score_red.setCharacterSize(24);
    score_blue.setCharacterSize(24);
    score_red.setFillColor(sf::Color::Red);
    score_blue.setFillColor(sf::Color::Blue);
    score_red.setString("Score: 0");
    score_blue.setString("Score: 0");
    score_red.setPosition(sf::Vector2f(WINDOW_WIDTH/4, WALL_DIMENSION.y + 20));
    score_blue.setPosition(sf::Vector2f(2 * WINDOW_WIDTH/3, WALL_DIMENSION.y + 20));
}

// start the game
void Game::start(){
    while(gameWindow.isOpen()){
        processEvents();
        if (gameState){
            update();
            render();
        }
    }
}