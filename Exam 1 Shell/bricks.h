
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef BRICK_H                 // Prevent multiple definitions if this 
#define BRICK_H   
class Brick;

#include "entity.h"
#include "constants.h"

namespace brickNS
{
    const int WIDTH = 80;                   // image width
    const int HEIGHT = 80;                  // image height
    const int X = 0;						// location on screen
    const int Y = 10;
    const float SPEED_X = 30;                
	const float SPEED_Y = 30;
 
}

// inherits from Entity class
class Brick : public Entity
{
private:
   // puckNS::DIRECTION direction;    
    bool collision;                 
    bool target;  
	int directionX;
	int directionY;

public:
    // constructor
    Brick();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Set target
    void setTarget(bool t) {target = t;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setInvisible();
	void setVisible();
	//bool getVisibleState() (return active;}
};
#endif

