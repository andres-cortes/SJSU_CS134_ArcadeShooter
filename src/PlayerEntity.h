#pragma once
#include "Emitter.h"
// An extension of Emitter, adds functionality that only the player needs
//
//
class PlayerEntity : public Emitter {
public:
     PlayerEntity(SpriteSystem *spriteSys);
     void update();
     int collisionsNear(ofVec3f point, float dist);
     void setMouse(int x, int y);
     void setXAccel(float ax);
     void setYAccel(float ay);
     void setDamping(float d);
     void setMaxHP(int h);
     void setBulletDamage(int d);
     void addExp(int e);
     void checkLevel();
     int getBulletDamage();
     float getRate();
     int getMaxHP();
     int getExp();
     int getLevel();

private:
     const int levelUps[10] = {200, 500, 950, 1520, 3000, 5500, 9000, 14000, 22000, 35000};
     int mouseX;
     int mouseY;
     int bulletDamage;
     int exp;
     int level;
     float speedDamping;
     float xAccel;
     float yAccel;
     float xVel;
     float yVel;
     float playerRot;
     int maxHitpoints;
};