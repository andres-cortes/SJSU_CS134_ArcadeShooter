#pragma once
//----------------------------------------------------------------------------------
//
// Basic Sprite Class
//
//
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
     BaseObject();
     ofVec2f trans, scale;
     float rot; 
     void setPosition(ofVec3f);
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
     static const int NEUTRAL = 0;
     static const int DAMAGED = 1;
     static const int DESTROYED = 2;
     static const int READY_FOR_DELETION = 3;
     Sprite();
     Sprite(const Sprite &other);
     Sprite(ofVec3f pos, float w, float h, float birth, float life);
     void draw();
     void update();
     float age();
     
     void addImage(ofImage * img, int state);
     void setVelocity(ofVec3f vel);
     void setRotate(float rotation);
     void setDimensions(float w, float h);
     void setLifespan(float ls);
     void setAnimated(bool anim);
     void setState(int state);
     void setBirthtime(float birth);
     ofVec3f getVelocity();
     float getLifespan();
     float getWidth();
     float getHeight();
     float getXPos();
     float getYPos();
     int getState();
     int getHitpoints();
     bool hasDestroyAnim();
     void setHitpoints(int hp);
     void changeHitpoints(int delta);

protected:
     string name;
     bool bAnimated;
     int currentState;
     int neutralImageCount;
     int damagedImageCount;
     int destroyedImageCount;
     int imageCurrent;
     int hitpoints;
     int animLoopCount;
     float lastTime;
     float birthtime; // elapsed time in ms
     float lifespan;  //  time in ms
     float width, height;
     vector<ofImage*> neutralImage;
     vector<ofImage*> damagedImage;
     vector<ofImage*> destroyedImage;
     ofVec3f velocity; // in pixels/sec
};