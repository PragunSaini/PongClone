// header files
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
// using namespace std;

// self defined headers
#include "Ball.h"
#include "Paddle.h"

// The main game class
class Game {

    private:
        // the window and it's dimensions
        sf::RenderWindow gameWindow;
        const float WINDOW_WIDTH = 1400.f;
        const float WINDOW_HEIGHT = 1400.f * (2.f / 3.f);

        // walls and their dimensions/color
        const sf::Vector2f WALL_DIMENSION = sf::Vector2f(WINDOW_WIDTH, 20);
        const sf::Color WALL_COLOR = sf::Color(25, 255, 0);

        sf::RectangleShape topWall;
        sf::RectangleShape bottomWall;
        sf::RectangleShape dividerWall;

        // Game entities
        Ball *ball;
        Paddle *paddleLeft;
        Paddle *paddleRight;

        // margin between edge and paddle
        const float PADDLE_MARGIN = 0.f;

        // game state
        bool gameState; // false for stopped and true for running.

        // to display scores
        sf::Font font;
        sf::Text score_red;
        sf::Text score_blue;

        // function to process events
        void processEvents(){
            sf::Event event;
            while(gameWindow.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed: {
                            delete ball;
                            delete paddleLeft;
                            delete paddleRight;
                            std::ofstream scoreOutput("resources/scores.txt", std::ios::app);
                            scoreOutput << "> " << scoreRed << " | " << scoreBlue << std::endl;
                            scoreOutput.close();
                            gameWindow.close();
                            break;
                        }
                    case sf::Event::KeyPressed:
                        handleKeyboard(event.key.code, true);
                        break;
                    case sf::Event::KeyReleased:
                        handleKeyboard(event.key.code, false);
                        break;
                    default: break;
                }
            }
        }

        // updates the game state by checking for collisions and moving objects
        void update(){
            if (ball->checkPaddleCollision(paddleLeft)){
                ball->paddleCollision(true, paddleLeft->getVelocity());
            }
            if (ball->checkPaddleCollision(paddleRight)){
                ball->paddleCollision(true, paddleRight->getVelocity());
            }
            if (ball->moveBall()){
                destroy();
            }
            paddleLeft->movePaddle();
            paddleRight->movePaddle();
            score_red.setPosition(sf::Vector2f(WINDOW_WIDTH/4, WALL_DIMENSION.y + 20));
            score_blue.setPosition(sf::Vector2f(2 * WINDOW_WIDTH/3, WALL_DIMENSION.y + 20));
            std::string temp;
            temp = "Score : " + std::to_string(scoreRed);
            score_red.setString(temp);
            temp = "Score : " + std::to_string(scoreBlue);
            score_blue.setString(temp);
        }

        // display the new state on the screen
        void render(){
            // clear the screen
            gameWindow.clear(sf::Color(0, 0, 0));
            // draw boundary walls
            gameWindow.draw(topWall);
            gameWindow.draw(bottomWall);
            gameWindow.draw(dividerWall);

            // draw the objects
            ball->draw();
            paddleLeft->draw();
            paddleRight->draw();

            gameWindow.draw(score_blue);
            gameWindow.draw(score_red);

            //display the window
            gameWindow.display();
        }

        // handles paddle movement
        void handleKeyboard(sf::Keyboard::Key key, bool isPressed){
            switch(key){
                case sf::Keyboard::W:
                    paddleLeft->setMovingUp(isPressed);
                    break;
                case sf::Keyboard::S:
                    paddleLeft->setMovingDown(isPressed);
                    break;
                case sf::Keyboard::Up:
                    paddleRight->setMovingUp(isPressed);
                    break;
                case sf::Keyboard::Down:
                    paddleRight->setMovingDown(isPressed);
                    break;
                case sf::Keyboard::Space:
                    gameState = (isPressed ? false : true);
                    break;
                default:
                    paddleLeft->setMovingUp(false);
                    paddleRight->setMovingUp(false);
                    paddleLeft->setMovingDown(false);
                    paddleLeft->setMovingDown(false);
            }
        }

        // destroy current ball and paddles
        void destroy(){
            delete ball;
            delete paddleLeft;
            delete paddleRight;
            reInitialize();
        }

        // to restart the game
        void reInitialize(){
            // create a window
            gameState = false;

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

        }

    public:

        // create the game constructor
        Game();

        // start the game
        void start();
};