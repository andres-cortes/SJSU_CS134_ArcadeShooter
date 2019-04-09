#pragma once
#include "Sprite.h"
#include "ParticleEmitter.h"
class MotionPattern {
public:
     virtual void setSpriteVelocity(Sprite *) = 0;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
     SpriteSystem();
     void add(Sprite);
     void remove(int);
     void update();
     void reset();
     void setMotionType(MotionPattern *);
     int collisionsNear(ofVec3f point, float dist);
     int deaths = 0;
     int reapDeaths();
     void draw();
     void addDestroySound(string soundLocation);
     void addDestroyParticles();
     void playDestroySound();
     vector<Sprite> sprites;
     ParticleEmitter * particles;
     MotionPattern * moPatt;

     TurbulenceForce *turbForce;
     GravityForce *gravityForce;
     ImpulseRadialForce *radialForce;
private:
     bool hasDestroyParticles;
     bool hasDestroySound;
     ofSoundPlayer destroySound;
};

class LinMotionPattern : public MotionPattern {
public:
     LinMotionPattern() { }; 
     void setSpriteVelocity(Sprite *); //Dont need to change particle velocity if linear motion
};

class SinMotionPattern : public MotionPattern {
public:
     SinMotionPattern(float amp, float per);
     void setSpriteVelocity(Sprite *);
     void setParams(float amp, float per);
private:
     float amplitude;
     float period;
};

class AccelMotionPattern : public MotionPattern {
public:
     AccelMotionPattern(float intsty);
     void setSpriteVelocity(Sprite *);
private:
     float intensity;
};

class BoomerangMotionPattern : public MotionPattern {
public:
     BoomerangMotionPattern(float initialYV);
     void setSpriteVelocity(Sprite *);
private:
     float initialYVel;
};