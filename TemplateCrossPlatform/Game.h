#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

class Game: public AppComponent, private Timer{
    TexRect* ball;
	TexRect* bg;
	TexRect* title;

	Rect* leftPaddle;
	Rect* rightPaddle;

    bool mushroomVisible;
	bool titleVisible;
    bool hit;

	float mx = 0.0005;
	float my = 0.0005;
	float rightX = 1.4;
	float leftX = -1.5;
	float topY = 1.00;
	float botY = -.85;
	float thresholdX = .001;
	float thresholdY = .25;
public:
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    
	void reset();

    void action();

    ~Game();

};

#endif 
