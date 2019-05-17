#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* ballonFileName;
	const char* fireballFileName;
	const char* bgFile;
	const char* titleFile;
	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	ballonFileName = "../balloon.png";
	fireballFileName = "../fireball.bmp";
	bgFile = "../bg.png";
	titleFile = "../title.png";
	#else
	ballonFileName = "/Users/izzaanwar/Desktop/PongL/TemplateCrossPlatform/balloon.png";
	fireballFileName = "fireball.bmp";
	bgFile = "/Users/izzaanwar/Desktop/PongL/TemplateCrossPlatform/bg.png";
	titleFile ="/Users/izzaanwar/Desktop/PongL/TemplateCrossPlatform/title.png";
	#endif

	title = new TexRect(titleFile, -1.585, 1, 3.15, 2);
	bg = new TexRect(bgFile, -1.585, 1, 3.15, 2);

	// paddles
	leftPaddle = new Rect(-1.545, .25, .075, .5);
	rightPaddle = new Rect(1.475, .25, .075, .5);
    
    // ball
    ball = new TexRect(ballonFileName, 0, 0, 0.15, 0.15);

    hit = false;
	titleVisible = true;
    
    setRate(1);
    start();
}

void Game::action(){

	/*--------------
	impose top and bottom boundary:
	if we hit the top or bottom of the window go the other way!
	------------------*/
	ball->setY(ball->getY() + my);
	ball->setX(ball->getX() + mx);

	if (ball->getY() > topY  || ball->getY() < botY)
	{
		my *= -1;
	}

	/*--------------
	impose left and right boundary:
	if we hit the left or right of the window, respective player gets a point, ball ends up in the middle
	------------------*/
	if (ball->getX() > rightX)
	{
        std::cout << "Player 1 wins the round! " << std::endl;
		reset();
		//std::cout << "reset!" << std::endl;
	}
	if(ball->getX() < leftX)
	{
        std::cout << "Player 2 wins the round! " << std::endl;
		reset();
		//std::cout << "reset!" << std::endl;
	}

   // to handle collisions
    
    if (!hit){
		float rightX = ball->getX() + ball->getW();
		float rightY = ball->getY() - ball->getH();
		float leftX = ball->getX();
		float leftY = ball->getY() + ball->getH();

		if (rightPaddle->contains(rightX + thresholdX , rightY + thresholdY) || leftPaddle->contains(leftX - thresholdX, leftY - thresholdY)) 
		{
			float randR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float randG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float randB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			leftPaddle->setR(randR);
			leftPaddle->setG(randG);
			leftPaddle->setB(randB);

			rightPaddle->setR(randR);
			rightPaddle->setR(randG);
			rightPaddle->setR(randB);
			mx *= -1;
		}

    }
}

void Game::draw() const {
	if (titleVisible) {
		title->draw(0.0);
	}
	leftPaddle->draw();
	rightPaddle->draw();
	ball->draw(0.0);
	bg->draw(0);
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
		titleVisible = false;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
	/*////			  /////
	//////LEFT PADDLE /////
	*////             /////

	// up 
	else if (key == 'q') { 
		//std::cout << "Updated Y is: " << leftPaddle->getY() << std::endl;
		//// Let's make the upper bound .97
        
		if (leftPaddle->getY() <= 0.97)
		{
			leftPaddle->setY(leftPaddle->getY() + .08);
			//std::cout << "Updated Y is: " << leftPaddle->getY() << std::endl;
		}
		else if (leftPaddle->getY() > .97)
		{
			leftPaddle->setY(leftPaddle->getY());
		}
	}

	// down
	else if (key == 'a') {
	//	// Let's make the lower bound -.47
		if (leftPaddle->getY() > -0.47)
		{
			leftPaddle->setY(leftPaddle->getY() - 0.08 );
			//std::cout << "Updated Y is: " << leftPaddle->getY() << std::endl;
		}
		else if (leftPaddle->getY() <= -0.47)
		{
			leftPaddle->setY(leftPaddle->getY());
		}
	}

	/*////			   /////
	//////Right PADDLE /////
	*////              /////

	//up
	else if (key == 'o') {
		if (rightPaddle->getY() <= 0.97)
		{
			rightPaddle->setY(rightPaddle->getY() + .07);
			//std::cout << "Updated Y is: " << rightPaddle->getY() << std::endl;
		}
	}
	else if (key == 'l') {
		if (rightPaddle->getY() > -0.47)
		{
			rightPaddle->setY(rightPaddle->getY() - .07);
			//std::cout << "Updated Y is: " << rightPaddle->getY() << std::endl;
		}
	}
}

void Game::reset()
{
	ball->setX(0);
	ball->setY(0);
}

Game::~Game(){
    stop();
	delete leftPaddle, rightPaddle, ball, title, bg;
}
