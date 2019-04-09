#include "SpriteSystem.h"


SpriteSystem::SpriteSystem()
{
     moPatt = new LinMotionPattern();
     hasDestroySound = false;
     hasDestroyParticles = false;

     turbForce = new TurbulenceForce(ofVec3f(-20, -20, 0), ofVec3f(20, 20, 0));
     gravityForce = new GravityForce(-200);
     radialForce = new ImpulseRadialForce(5000);

     particles = new ParticleEmitter();
     particles->sys->addForce(turbForce);
     particles->sys->addForce(gravityForce);
     particles->sys->addForce(radialForce);
     particles->setVelocity(ofVec3f(0, 0, 0));
     particles->setOneShot(true);
     particles->setEmitterType(RadialEmitter);
     particles->setGroupSize(40);
     particles->position = ofVec3f(500, 500, 0);
}

void SpriteSystem::add(Sprite s) {
     sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
     sprites.erase(sprites.begin() + i);
}

// remove all sprites within a given dist of point
//
int SpriteSystem::collisionsNear(ofVec3f point, float dist) {
     vector<Sprite>::iterator s = sprites.begin();
     vector<Sprite>::iterator tmp;
     int coll = 0;
     while (s != sprites.end()) {
          ofVec3f v = s->trans - point;
          if (v.length() < dist && s->getState() < Sprite::DESTROYED) {
               if (hasDestroySound)
               {
                    destroySound.play();
               }
               if (hasDestroyParticles)
               {
                    particles->position = ofVec3f(s->getXPos(), s->getYPos(), 0);
                    particles->sys->reset();
                    particles->start();
               }
               if (s->hasDestroyAnim())
               {
                    s->setState(Sprite::DESTROYED);
               }
               else
               {
                    tmp = sprites.erase(s);
                    s = tmp;
               }
               coll++;
          }
          else s++;
     }
     return coll;
}


//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteSystem::update() {
     if (hasDestroyParticles)
     {
          particles->update();
     }

     if (sprites.size() == 0) return;
     vector<Sprite>::iterator s = sprites.begin();
     vector<Sprite>::iterator tmp;
     // check which sprites have exceed their lifespan and delete
     // from list.  When deleting multiple objects from a vector while
     // traversing at the same time, use an iterator.
     //
     while (s != sprites.end()) {
          //if hitPoints depleted (and not already destroyed or set to deletion), set to destroyed (this will play destroyed animation)
          if (s->getHitpoints() <= 0 && s->getState() < Sprite::DESTROYED && s->getState())
          {
               if (hasDestroySound)
               {
                    destroySound.play();
               }
               if (hasDestroyParticles)
               {
                    particles->position = ofVec3f(s->getXPos(), s->getYPos(), 0);
                    particles->sys->reset();
                    particles->start();
               }
               s->setState(Sprite::DESTROYED);
               deaths++;
          }
          //if lifespan is up, erase, or if ready for deletion, erase
          if ((s->getLifespan() != -1 && s->age() > s->getLifespan()) || s->getState() == Sprite::READY_FOR_DELETION) {
               tmp = sprites.erase(s);
               s = tmp;
          }
          else s++;
     }

     //  Animate and move sprites
     //
     for (int i = 0; i < sprites.size(); i++) {
          moPatt->setSpriteVelocity(&sprites[i]);
          sprites[i].update();
     }

}

//  Render all the sprites
//
void SpriteSystem::draw() {
     for (int i = 0; i < sprites.size(); i++) {
          sprites[i].draw();
     }
     if (hasDestroyParticles)
     {
          particles->draw();
     }
}

void SpriteSystem::reset()
{
     sprites.clear();
     deaths = 0;
}

int SpriteSystem::reapDeaths()
{
     int retDeaths = deaths;
     deaths = 0;
     return retDeaths;
}

void SpriteSystem::setMotionType(MotionPattern * ptn)
{
     moPatt = ptn;
}

void SpriteSystem::addDestroySound(string soundLocation)
{
     if (destroySound.load(soundLocation))
     {
          hasDestroySound = true;
     }

}

void SpriteSystem::playDestroySound()
{
     if (hasDestroySound)
     {
          destroySound.play();
     }
}

void SpriteSystem::addDestroyParticles()
{
     hasDestroyParticles = true;
}
//
void LinMotionPattern::setSpriteVelocity(Sprite * spr)
{
     //if linear motion, no need to change velocity;
}


SinMotionPattern::SinMotionPattern(float amp, float per)
{
     amplitude = amp;
     period = per;
}
void SinMotionPattern::setSpriteVelocity(Sprite * spr)
{
     spr->setVelocity(ofVec3f(amplitude * sin(spr->age()/ period), spr->getVelocity().y, 0));
}

void SinMotionPattern::setParams(float amp, float per)
{
     amplitude = amp;
     period = per;
}

AccelMotionPattern::AccelMotionPattern(float intsty)
{
     intensity = intsty;
}
void AccelMotionPattern::setSpriteVelocity(Sprite * spr)
{
     spr->setVelocity(ofVec3f(spr->getVelocity().x, spr->getVelocity().y * intensity, 0));
}

BoomerangMotionPattern::BoomerangMotionPattern(float initialYV)
{
     initialYVel = initialYV;
}

void BoomerangMotionPattern::setSpriteVelocity(Sprite * spr)
{
     float halfLife = spr->getLifespan() /2;
     float mul = (halfLife - spr->age()) / halfLife;
     spr->setVelocity(ofVec3f(spr->getVelocity().x, initialYVel * mul, 0));
}