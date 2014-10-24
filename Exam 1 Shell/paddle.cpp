
#include "paddle.h"

//=============================================================================
// default constructor
//=============================================================================
Paddle::Paddle() : Entity()
{
    spriteData.width = paddleNS::WIDTH;           
    spriteData.height = paddleNS::HEIGHT;
    spriteData.x = paddleNS::X;                   
    spriteData.y = paddleNS::Y;
    spriteData.rect.bottom = paddleNS::HEIGHT/2;    
    spriteData.rect.right = paddleNS::WIDTH;
	velocity.x = 0                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
	edge.bottom = paddleNS::HEIGHT/2;
	edge.top = -paddleNS::HEIGHT/2;
	edge.right = paddleNS::WIDTH/2;
	edge.left = -paddleNS::WIDTH/2;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Paddle::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	setPosition(VECTOR2(paddleNS::X,paddleNS::Y));
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Paddle::update(float frameTime)
{
    Entity::update(frameTime);
    //ADD POSITION UPDATING HERE
	VECTOR2 pos = getPosition();
	pos.x += frameTime * getVelocity().x;     // move ship along X 
	if(target) {
		pos.y += frameTime * velocity.y * -1;     // move ship along Y
	}

    // ADD WRAPPING CODE HERE.
	if(pos.x+paddleNS::WIDTH < 1)
		pos.x = GAME_WIDTH-1;
	if(pos.x+1 > GAME_WIDTH)
		pos.x = -paddleNS::WIDTH+1;
	/*if(pos.y+1 > GAME_HEIGHT) {
		pos.y = 50-paddleNS::HEIGHT;
	}*/
	

	// ADD "Top of screen" CODE HERE
	
	if(pos.y-paddleNS::HEIGHT/2 < 0) {
		pos.y = paddleNS::Y;
		setTarget(false);
	}
		
	
	//ADD spriteData.x, spriteData.y assignments here from Entity::position
	setPosition(pos);
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
	

}