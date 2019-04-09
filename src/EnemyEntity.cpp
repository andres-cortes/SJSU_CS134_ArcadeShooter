#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(SpriteSystem *spriteSys) : Emitter(spriteSys)
{
     collisionDamage = 2;
     //default position
     spawnFrom = TOP;
     lastSpawnIndex = 0;
     pattern = L_RANDOM_SPAWN;
     drawable = false;
     scorePerKill = 10;
     srand(time(NULL));
     persToggle = true;
}

void EnemyEntity::update()
{
     if (started)
     {
          float time = ofGetElapsedTimeMillis();
          if ((time - lastSpawned) > (1000.0 / rate)) {

               childProto->setVelocity(childProto->getVelocity().rotate(rot, ofVec3f(0, 0, 1))); // rotate direction
               childProto->setRotate(rot);   // rotate image
               childProto->setBirthtime(time);
               cycleLocation();
               for (int i = 0; i < spawnIndexes.size(); i++)     // add all sprites to system at specified indexes
               {
                    trans = ofVec3f(spawnIndexes[i] * ofGetWindowWidth() / 16, -80, 0);
                    childProto->trans = trans;
                    Sprite temp = *childProto;
                    sys->add(temp);
               }
               spawnIndexes.clear();
               lastSpawned = time;
          }
     }
     //sprite system move
     sys->update();
}

void EnemyEntity::cycleLocation()
{
     // 16 subdivisions on top
     if (pattern == L_RANDOM_SPAWN)
     {
          int r = rand() % 15 + 1; //from 1 to 15, random
          if (lastSpawnIndex == r)
          {
               r++; //no two spawns at same spot
          }
          spawnIndexes.push_back(r);
          lastSpawnIndex = r;
     }
     else if (pattern == L_WAVE_ONE_SPAWN)
     {
          lastSpawnIndex = lastSpawnIndex % 15 + 1; //from 1 to 15, spawnIndex++
          spawnIndexes.push_back(lastSpawnIndex);
     }
     else if (pattern == L_WAVE_TWO_SPAWN)
     {
          lastSpawnIndex = lastSpawnIndex % 15 + 1; //from 1 to 15, spawnIndex++
          spawnIndexes.push_back(lastSpawnIndex);
          spawnIndexes.push_back((lastSpawnIndex+7) % 15 + 1);
     }
     else if (pattern == L_WAVE_TWO_CROSS_SPAWN)
     {
          lastSpawnIndex = lastSpawnIndex % 15 + 1; //from 1 to 15, spawnIndex++
          spawnIndexes.push_back(lastSpawnIndex);
          if (lastSpawnIndex != 8)
          {
               spawnIndexes.push_back(16 - lastSpawnIndex);
          }
     }
     else if (pattern == L_LINE_TWO_SPAWN)
     {
          if (lastSpawnIndex > 7 || lastSpawnIndex == 0)
          {
               persToggle = !persToggle;
          }
          if (persToggle)
          {
               lastSpawnIndex++;
          }
          else
          {
               lastSpawnIndex--;
          }
          spawnIndexes.push_back(lastSpawnIndex);
          spawnIndexes.push_back(lastSpawnIndex + 7);
     }

}

int EnemyEntity::getCollisionDamage()
{
     return collisionDamage;
}

int EnemyEntity::getSpawnLocation()
{
     return spawnFrom;
}

int EnemyEntity::getScoreChange()
{
     return scorePerKill * sys->reapDeaths();
}

void EnemyEntity::setCollisionDamage(int damage)
{
     collisionDamage = damage;
}

void EnemyEntity::setSpawnLocation(int locat)
{
     spawnFrom = locat;
}

void EnemyEntity::setPattern(int p)
{
     pattern = p;
     lastSpawnIndex = 0;
     persToggle = false;
}

void EnemyEntity::setScorePerKill(int s)
{
     scorePerKill = s;
}

void EnemyEntity::setSpawnIndex(int i)
{
     lastSpawnIndex = i;
}