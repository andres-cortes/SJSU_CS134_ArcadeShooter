#include "ofMain.h"
#include "Emitter.h"

//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) : Sprite() {
     sys = spriteSys;
     xVel = 0;
     yVel = 0;
     width = 50;
     height = 50;
     lastSpawned = 0;
     lastRot = 0;
     rate = 1;    // sprites/sec
     started = false;
     drawable = false;
     hasSound = false;
     childProto =  new Sprite();
     childProto->setAnimated(true);
     childProto->setDimensions(50,50);
     childProto->setVelocity(ofVec3f(0, -100, 0));
     velocity = ofVec3f(0, 0, 0);
     relativeSpawnPoint = ofVec3f(0, 0, 0);
}

Emitter::Emitter(ofVec3f pos, float w, float h, float birth, float life, SpriteSystem *spriteSys) : Sprite(pos, w, h, birth, life)
{
     sys = spriteSys;
     xVel = 0;
     yVel = 0;
     width = 50;
     height = 50;
     lastSpawned = 0;
     lastRot = 0;
     rate = 1;    // sprites/sec
     started = false;
     drawable = false;
     hasSound = false;
     childProto = new Sprite();
     childProto->setDimensions(50, 50);
     childProto->setVelocity(ofVec3f(0, -100, 0));
     velocity = ofVec3f(0, 0, 0);
     relativeSpawnPoint = ofVec3f(0, 0, 0);
}

//  Draw the Emitter if it is drawable
void Emitter::draw() {
     if (drawable) {
          Sprite::draw();
     }
     // draw sprite system
     sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
     if (started)
     {
          float time = ofGetElapsedTimeMillis();
          if ((time - lastSpawned) > (1000.0 / rate)) {
               if (hasSound)
               {
                    emitSound.play();
               }
               // update rotation of emitter. Child will have this same rotation value when spawned
               if (lastRot != rot)
               {
                    relativeSpawnPoint.rotate(rot - lastRot, ofVec3f(0, 0, 1));
                    lastRot = rot;
               }
               childProto->trans = trans + relativeSpawnPoint;
               // rotate child vector
               childProto->setVelocity(childProto->getVelocity().rotate(rot, ofVec3f(0, 0, 1)));
               // set child vector
               childProto->setRotate(rot);
               childProto->setBirthtime(time);
               // finally, add sprite to system
               Sprite temp = *childProto;
               sys->add(temp);
               lastSpawned = time;
          }
     }
     //move emitter
     Sprite::update();
     velocity.x = xVel;
     velocity.y = yVel;
     trans += velocity / ofGetFrameRate();
     //sprite system move
     sys->update();
}

// Start/Stop the emitter.
//
void Emitter::start() {
     started = true;
}

void Emitter::stop() {
     started = false;
}

float Emitter::maxDistPerFrame() {
     return  childProto->getVelocity().length() / ofGetFrameRate();
}

//
//*************************************GETTERS AND SETTERS************************
//
void Emitter::setXVelocity(float x) {
     xVel = x;
}

void Emitter::setYVelocity(float y) {
     yVel = y;
}

void Emitter::setEmitterSound(string soundLocation)
{
     emitSound.load(soundLocation);
     hasSound = true;
}

void Emitter::setRate(float r) {
     rate = r;
}

void Emitter::setRelativeSpawnPoint(ofVec3f rel)
{
     relativeSpawnPoint = rel;
}

void Emitter::setDrawable(bool b)
{
     drawable = b;
}

float Emitter::getWidth() {
     return width;
}

float Emitter::getHeight() {
     return height;
}

SpriteSystem * Emitter::getSpriteSystem()
{
     return sys;
}

Sprite * Emitter::getChildPrototype()
{
     return childProto;
}
