#include "Sprite.h"

//
// Base Object
//
BaseObject::BaseObject() {
     trans = ofVec3f(0, 0, 0);
     scale = ofVec3f(1, 1, 1);
     rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
     trans = pos;
}

//
// Basic Sprite Object
//
Sprite::Sprite() {
     velocity = ofVec3f(0, 0, 0);
     lifespan = -1;      // lifespan of -1 => immortal 
     birthtime = 0;
     bAnimated = false;
     neutralImageCount = 0;
     damagedImageCount = 0;
     destroyedImageCount = 0;
     imageCurrent = 0;
     hitpoints = 10;
     lastTime = ofGetSystemTimeMillis();
     name = "UnamedSprite";
     width = 20;
     height = 20;
     animLoopCount = 0;
     currentState = NEUTRAL;

}

//copy constructor
Sprite::Sprite(const Sprite &other)
{
     trans = other.trans;
     rot = other.rot;
     name = other.name;
     bAnimated = other.bAnimated;
     animLoopCount = other.animLoopCount;
     currentState = other.currentState;
     neutralImageCount = other.neutralImageCount;
     damagedImageCount = other.damagedImageCount;
     destroyedImageCount = other.destroyedImageCount;
     imageCurrent = other.imageCurrent;
     hitpoints = other.hitpoints;
     lastTime = ofGetSystemTimeMillis();
     birthtime = other.birthtime; // elapsed time in ms
     lifespan = other.lifespan;  //  time in ms
     width = other.width;
     height = other.height;
     neutralImage = other.neutralImage;
     damagedImage = other.damagedImage;
     destroyedImage = other.destroyedImage;
     velocity = other.velocity; // in pixels/sec

}

Sprite::Sprite(ofVec3f pos, float w, float h, float birth, float life) {
     velocity = ofVec3f(0, 0, 0);
     trans = pos;
     birthtime = birth;
     lifespan = life;
     bAnimated = false;
     neutralImageCount = 0;
     damagedImageCount = 0;
     destroyedImageCount = 0;
     imageCurrent = 0;
     hitpoints = 10;
     lastTime = ofGetSystemTimeMillis();
     name = "UnamedSprite";
     width = w;
     height = h;
     animLoopCount = 0;
     currentState = NEUTRAL;

}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
     return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::addImage(ofImage * img, int state) {
     if (state == NEUTRAL)
     {
          neutralImage.push_back(img);
          neutralImageCount++;
     }
     else if (state == DAMAGED)
     {
          damagedImage.push_back(img);
          damagedImageCount++;
     }
     else if (state == DESTROYED)
     {
          destroyedImage.push_back(img);
          destroyedImageCount++;
     }
     //dimensions of the sprite are the dimensions of the first NEUTRAL image added (this is arbitrary)
     width = neutralImage.at(0)->getWidth();
     height = neutralImage.at(0)->getHeight();     
}
//  Render the sprite
//
void Sprite::draw() {
     ofSetColor(255, 255, 255, 255);
     //sprite at least needs one neutralImage
     if (neutralImageCount > 0) {
          //draw image with rotation
          ofPushMatrix();
          ofTranslate(trans.x, trans.y);
          ofRotateDeg(rot);
          //decide which to draw, can move to update if too processor intensive (shouldn't be, its O(1))
          if (currentState == NEUTRAL)
          {
               neutralImage.at(imageCurrent)->draw(-width / 2.0, -height / 2.0);
          }
          else if (currentState == DAMAGED && damagedImageCount > 0)
          {
               damagedImage.at(imageCurrent)->draw(-width / 2.0, -height / 2.0);
          }
          else if (currentState == DESTROYED && destroyedImageCount > 0)
          {
               destroyedImage.at(imageCurrent)->draw(-width / 2.0, -height / 2.0);
          }
          ofPopMatrix();
     }
}

//handles animation
void Sprite::update()
{
     //if not destroyed or deleted, move
     if (currentState < DESTROYED)
     {
          trans += velocity / ofGetFrameRate();
     }

     if (!bAnimated) return;

     //animation stuff
     float curTime = ofGetSystemTimeMillis();
     if ((curTime - lastTime) > 50) {
          imageCurrent++;
          //loop neutral animation
          if (currentState == NEUTRAL && imageCurrent == neutralImageCount)
          {
               imageCurrent = 0;
          }
          //play damaged animation twice, then set back to neutral
          else if (currentState == DAMAGED && imageCurrent == damagedImageCount)
          {
               imageCurrent = 0;
               if (animLoopCount == 2)
               {
                    animLoopCount = 0;
                    setState(NEUTRAL);
               }
               animLoopCount++;
          }
          //play destroyed image once, then mark for deletion
          else if (currentState == DESTROYED && imageCurrent == destroyedImageCount)
          {
               setState(READY_FOR_DELETION);
               imageCurrent--;
          }
          lastTime = curTime;
     }
}

//
//**********************************GETTERS AND SETTERS****************************************
//
void Sprite::setRotate(float rotation)
{
     rot = rotation;
}

void Sprite::setVelocity(ofVec3f vel)
{
     velocity = vel;
}

void Sprite::setDimensions(float w, float h)
{
     width = w;
     height = h;
}

void Sprite::setLifespan(float ls)
{
     lifespan = ls;
}

void Sprite::setAnimated(bool anim)
{
     bAnimated = anim;
}

void Sprite::setState(int state)
{
     if (state < 0 || state > 3)
     {
          cout << "ERROR: invalid state";
          return;
     }
     imageCurrent = 0;
     currentState = state;
     
}

void Sprite::setBirthtime(float birth)
{
     birthtime = birth;
}

void Sprite::setHitpoints(int hp)
{
     hitpoints = hp;
}

void Sprite::changeHitpoints(int delta)
{
     hitpoints += delta;
}
ofVec3f Sprite::getVelocity()
{
     return velocity;
}

float Sprite::getLifespan()
{
     return lifespan;
}

float Sprite::getWidth()
{
     return width;
}

float Sprite::getHeight()
{
     return height;
}

float Sprite::getXPos()
{
     return trans.x;
}

float Sprite::getYPos()
{
     return trans.y;
}

int Sprite::getState()
{
     return currentState;
}

bool Sprite::hasDestroyAnim()
{
     return destroyedImage.size() > 0;
}
int Sprite::getHitpoints()
{
     return hitpoints;
}
