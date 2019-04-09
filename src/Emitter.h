#pragma once
#include "SpriteSystem.h"

//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter. Can spawn other emitters as well.
//
class Emitter : public Sprite {
public:
     Emitter(SpriteSystem *);
     Emitter(ofVec3f pos, float w, float h, float birth, float life, SpriteSystem *);
     void draw();
     void update();
     void start();
     void stop();
     void setXVelocity(float x);
     void setYVelocity(float y);
     void setRate(float);
     void setEmitterSound(string soundLocation);
     void setRelativeSpawnPoint(ofVec3f rel);
     void setDrawable(bool b);
     float getWidth();
     float getHeight();
     Sprite * getChildPrototype();
     SpriteSystem * getSpriteSystem();
     float maxDistPerFrame();

protected:
     SpriteSystem *sys;
     Sprite *childProto;
     ofVec3f velocity;
     ofVec3f relativeSpawnPoint;
     ofSoundPlayer emitSound;
     float xVel;
     float yVel;
     float rate;
     float lastSpawned;
     float lastRot;
     bool hasSound;
     bool started;
     bool drawable;
};
