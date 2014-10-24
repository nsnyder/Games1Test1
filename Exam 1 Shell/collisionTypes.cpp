// Programming 2D Games
// Copyright (c) 2011, 2012 by: 
// Charles Kelly
// Collision types demo
// Press '1', '2' or '3' to select collision type for ship.

#include "collisionTypes.h"

//=============================================================================
// Constructor
//=============================================================================
CollisionTypes::CollisionTypes()
{
	//nothing here, move on
}

//=============================================================================
// Destructor
//=============================================================================
CollisionTypes::~CollisionTypes()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void CollisionTypes::initialize(HWND hwnd)
{
    Game::initialize(hwnd); 

	//ADD Puck and Paddle initialization code here

	// Puck
	if (!puckTM.initialize(graphics, PUCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Puck texture initialization failed"));
	if (!puck.initialize(this, puckNS::WIDTH,puckNS::HEIGHT,0, &puckTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init puck"));

	// Paddle
	if (!paddleTM.initialize(graphics, PADDLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Paddle texture initialization failed"));
	if (!paddle.initialize(this, paddleNS::WIDTH,paddleNS::HEIGHT,0, &paddleTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init paddle"));
    
	//ADD Font initialization code here
	dxFont = new TextDX();
    if(dxFont->initialize(graphics, FONT_SIZE, false, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
    
	score = 0;
	
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void CollisionTypes::update()
{
	//ADD Keyboard control code here
	VECTOR2 pos = paddle.getPosition();
    
	if (input->isKeyDown(VK_UP))
	{
		pos.y += frameTime * -paddle.getVelocity().y;     // move ship along Y
	}
	if (input->isKeyDown(VK_DOWN))
	{
		pos.y += frameTime * paddle.getVelocity().y;     // move ship along Y
	}
	if (input->isKeyDown(VK_LEFT))
	{
		pos.x += frameTime * -paddle.getVelocity().x;     // move ship along X 
	}
	if (input->isKeyDown(VK_RIGHT))
	{
		pos.x += frameTime * paddle.getVelocity().x;     // move ship along X 
	}
	paddle.setPosition(pos);

	paddle.update(frameTime);
	puck.update(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void CollisionTypes::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void CollisionTypes::collisions()
{
    collisionVector.x = 0;      // clear collision vector
    collisionVector.y = 0;
	//ADD Collision detection code here

	if(puck.collidesWith(paddle,collisionVector) && !puck.getCollision()) {
		puck.changeDirectionX();
		puck.changeDirectionY();
		puck.setCollision(true);
		audio->playCue(FX);
		score++;
	} else {
		// See if it's still colliding
		puck.setCollision(puck.collidesWith(paddle,collisionVector));
	}
	
}

//=============================================================================
// Render game items
//=============================================================================
void CollisionTypes::render()
{
	// Integer to string conversion here
	std::stringstream s2;
	s2 << score;


    graphics->spriteBegin();                // begin drawing sprites
	paddle.draw();
    puck.draw();

	// Add output  here

	// Printing code skeleton
	
	dxFont->print(s2.str(),10,10);         // display message

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void CollisionTypes::releaseAll()
{
	paddleTM.onLostDevice();
	puckTM.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void CollisionTypes::resetAll()
{
	paddleTM.onResetDevice();
	puckTM.onResetDevice();
    Game::resetAll();
    return;
}
