#pragma once
#include "Emitter.h"
#include <stdlib.h> 
//EnemyEntity is an Emitter that spawns enemies off screen in various patterns. It also defines properties of an enemy type
//
//
class EnemyEntity : public Emitter {
public:
     static const int TOP = 0;
     static const int BOTTOM = 1;
     static const int L_RANDOM_SPAWN = 0;
     static const int L_WAVE_ONE_SPAWN = 2;
     static const int L_WAVE_TWO_SPAWN = 3;
     static const int L_WAVE_TWO_CROSS_SPAWN = 4;
     static const int L_LINE_TWO_SPAWN = 5;

     EnemyEntity(SpriteSystem *spriteSys);
     void update();
     void cycleLocation();
     int getCollisionDamage();
     int getSpawnLocation();
     void setCollisionDamage(int damage);
     void setSpawnLocation(int locat);
     void setPattern(int p);
     void setScorePerKill(int s);
     void setSpawnIndex(int i);
     int getScoreChange();

private:
     int scorePerKill;
     int collisionDamage;
     int spawnFrom; //location on screen
     int lastSpawnIndex; //last index a sprite spawned from
     vector<int> spawnIndexes; //locations sprites will spawn each frame
     int pattern; 
     int numToSpawn;
     bool persToggle;
};