#include "puck.h"

//=============================================================================
// default constructor
//=============================================================================
Puck::Puck() : Entity()
{
    spriteData.width = puckNS::WIDTH;           
    spriteData.height = puckNS::HEIGHT;
    spriteData.x = puckNS::X;                   
    spriteData.y = puckNS::Y;
	setPosition(VECTOR2(puckNS::X, puckNS::Y));
    spriteData.rect.bottom = puckNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = puckNS::WIDTH;
    velocity.x = 50;                             // velocity X
    velocity.y = 50;                             // velocity Y
    startFrame = 0;             // first frame of puck animation
    endFrame = 0;				// last frame of puck animation
    currentFrame = startFrame;
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
	spriteData.scale = 1;
	edge.bottom = puckNS::HEIGHT/2;
	edge.top = -puckNS::HEIGHT/2;
	edge.right = puckNS::WIDTH/2;
	edge.left = -puckNS::WIDTH/2;

}

bool Puck::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = 0;
	directionX = 1;
	setPosition(VECTOR2(puckNS::X,puckNS::Y));
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}
void Puck::changeDirectionY()
{
	 directionY *= -1;
}
void Puck::changeDirectionX()
{
	 directionX *= -1;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Puck::update(float frameTime)
{
    Entity::update(frameTime);

	VECTOR2 pos = getPosition();
	//ADD code for puck to move left/right here
	pos.x += frameTime * velocity.x * directionX;     // move ship along X 
    pos.y += frameTime * velocity.y * directionY;     // move ship along Y

	//ADD "bounce" code here. Use the changeDirectionX() or changeDirectionY() functions
    if (spriteData.x > GAME_WIDTH-puckNS::WIDTH*getScale())
    {
		pos.x = GAME_WIDTH-puckNS::WIDTH*getScale()-1;
		// audio->playCue(MISS);
		changeDirectionX();
    } 
	if (spriteData.x < 0)
    {
		pos.x = 1;
		// audio->playCue(MISS);
		changeDirectionX();
    } 

	if (spriteData.y > GAME_HEIGHT-puckNS::HEIGHT*getScale())
    {
        changeDirectionY();
		pos.y = GAME_HEIGHT-puckNS::HEIGHT*getScale() - 1;
	}
	else if (spriteData.y < 0)
	{
		changeDirectionY();
		pos.y = 1;
	}

	//ADD spriteData.x, spriteData.y assignments here from Entity::position
	setPosition(pos);
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();

}

