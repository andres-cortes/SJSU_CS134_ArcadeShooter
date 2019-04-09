#include "PlayerEntity.h"
PlayerEntity::PlayerEntity(SpriteSystem *spriteSys) : Emitter(spriteSys)
{
     xAccel = 0;
     yAccel = 0;
     xVel = 0;
     yVel = 0;
     rate = 3;
     speedDamping = 0.025;
     bulletDamage = 0;
     playerRot = 0;
     drawable = true;
     setRelativeSpawnPoint(ofVec3f(0, -40, 0));                                   //set spawn point of lazers
     hitpoints = 10;
     maxHitpoints = 10;
     level = 1;
     exp = 0;
}

void PlayerEntity::update()
{
     childProto->setVelocity(ofVec3f(0, -450, 0));
     //****************************PLAYER ROTATION****************************
     ofVec3f playerToPtr(trans.x - mouseX, trans.y - mouseY, 0);
     if (trans.x - mouseX > 0)
     {
          playerRot = -playerToPtr.angle(ofVec3f(0, 1, 0));
     }
     else
     {
          playerRot = -360 + playerToPtr.angle(ofVec3f(0, 1, 0));
     }
     setRotate(playerRot);

     //*******************************PLAYER BOUNDS & SPEED*****************************
     //check left and right bound
     if ((trans.x - width / 2 + xVel / ofGetFrameRate()) < 0 || (trans.x + width / 2 + xVel / ofGetFrameRate()) > 1920)
     {
          xVel = -xVel; //this produces a "bouncing" effect off the sides of the screen
     }
     else
     {
          xVel += xAccel - (xVel*(speedDamping)); 
     }
     //check top and bottom bound
     if ((trans.y - height / 2 + yVel / ofGetFrameRate()) < 0 || (trans.y + height / 2 + yVel / ofGetFrameRate()) > 1060)
     {
          yVel = -yVel;
     }
     else
     {
          yVel += yAccel - (yVel*(speedDamping));
     }
     setXVelocity(xVel);
     setYVelocity(yVel);
     checkLevel();
     Emitter::update();
}

int PlayerEntity::collisionsNear(ofVec3f point, float dist) {
     vector<ofVec3f> points;
     points.push_back(ofVec3f(trans.x - width / 2, trans.y, 0));
     points.push_back(ofVec3f(trans.x + width / 2, trans.y, 0));
     points.push_back(ofVec3f(trans.x, trans.y - height / 2, 0));
     points.push_back(ofVec3f(trans.x, trans.y + height / 2, 0));
     int coll = 0;
     int i = 0;
     while (i < points.size())
     {
          ofVec3f v = points.at(i) - point;
          if (v.length() < dist)
          {
               coll++;
          }
          i++;
     }
     return coll;
}

void PlayerEntity::checkLevel()
{
     if (exp > levelUps[level-1])  //reach condition for level up
     {
          level++;
          rate = rate + 0.2;  //increase bullet rate
          if (level % 2 == 0)      //every other level, increase bullet damage
               bulletDamage += 1;
          maxHitpoints++;     //increase max hitpoints and restore them
          hitpoints = maxHitpoints;
     }
}

float PlayerEntity::getRate()
{
     return rate;
}

void PlayerEntity::setMouse(int x, int y)
{
     mouseX = x;
     mouseY = y;
}

void PlayerEntity::setXAccel(float ax)
{
     xAccel = ax;
}

void PlayerEntity::setYAccel(float ay)
{
     yAccel = ay;
}

void PlayerEntity::setDamping(float d)
{
     speedDamping = d;
}

void PlayerEntity::setBulletDamage(int d) 
{
     bulletDamage = d;
}

void PlayerEntity::setMaxHP(int h)
{
     maxHitpoints = 10;
}

void PlayerEntity::addExp(int e)
{
     exp += e;
}

int PlayerEntity::getBulletDamage() 
{
     return bulletDamage;
}

int PlayerEntity::getMaxHP()
{
     return maxHitpoints;
}

int PlayerEntity::getExp()
{
     return exp;
}

int PlayerEntity::getLevel()
{
     return level;
}