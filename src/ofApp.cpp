#include "ofApp.h"

void ofApp::setup() {
     //visuals
     ofSetVerticalSync(true);
     ofBackground(255, 255, 255);
     background.load("images/background.jpg");
     mouseX = ofGetWindowWidth();
     mouseY = 0;
     //define motion patterns
     sinMotion = new SinMotionPattern(500, 500); //amplitude, period (ms)
     accelMotion = new AccelMotionPattern(1.02);
     linMotion = new LinMotionPattern();
     boomMotion = new BoomerangMotionPattern(600); //initial speed,

     player = new PlayerEntity(new SpriteSystem());

     //Shot images*************
     if (shot0.load("images/shot0.png") && shot1.load("images/shot1.png") && shot2.load("images/shot2.png"))
     {
          player->getChildPrototype()->addImage(&shot0, Sprite::NEUTRAL);
          player->getChildPrototype()->addImage(&shot1, Sprite::NEUTRAL);
          player->getChildPrototype()->addImage(&shot2, Sprite::NEUTRAL);
     }
     if (shotDes0.load("images/shotDes0.png") && shotDes1.load("images/shotDes1.png"))
     {
          player->getChildPrototype()->addImage(&shotDes0, Sprite::DESTROYED);
          player->getChildPrototype()->addImage(&shotDes1, Sprite::DESTROYED);
     }

     //Player images***********
     if (Starship0.load("images/Starship0.png") && Starship1.load("images/Starship1.png") && Starship2.load("images/Starship2.png"))
     {
          player->addImage(&Starship0, Sprite::NEUTRAL);
          player->addImage(&Starship1, Sprite::NEUTRAL);
          player->addImage(&Starship2, Sprite::NEUTRAL);
     }
     if (StarshipDam0.load("images/StarshipDam0.png") && StarshipDam1.load("images/StarshipDam1.png"))
     {
          player->addImage(&StarshipDam0, Sprite::DAMAGED);
          player->addImage(&StarshipDam1, Sprite::DAMAGED);
     }
     if (StarshipDes0.load("images/StarshipDes0.png") && StarshipDes1.load("images/StarshipDes1.png") && StarshipDes2.load("images/StarshipDes2.png") 
          && StarshipDes3.load("images/StarshipDes3.png") && StarshipDes4.load("images/StarshipDes4.png") && StarshipDes5.load("images/StarshipDes5.png"))
     {
          player->addImage(&StarshipDes0, Sprite::DESTROYED);
          player->addImage(&StarshipDes1, Sprite::DESTROYED);
          player->addImage(&StarshipDes2, Sprite::DESTROYED);
          player->addImage(&StarshipDes3, Sprite::DESTROYED);
          player->addImage(&StarshipDes4, Sprite::DESTROYED);
          player->addImage(&StarshipDes5, Sprite::DESTROYED);
     }
     //player setup
     player->setAnimated(true);
     player->getChildPrototype()->setAnimated(true);
     player->getChildPrototype()->setVelocity(ofVec3f(0, -500, 0));
     player->getChildPrototype()->setLifespan(2400);
     player->setEmitterSound("audio/fire21.mp3");
     player->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0));    //initialize position
     player->setHitpoints(10);
     player->setBulletDamage(2);
     player->setRate(3.2);
     shipAccel = 14;

     //bombEnemy images
     bombEnemy = new EnemyEntity(new SpriteSystem());
     if (bomb0.load("images/bomb0.png") && bomb1.load("images/bomb1.png"))
     {
          bombEnemy->getChildPrototype()->addImage(&bomb0, Sprite::NEUTRAL);
          bombEnemy->getChildPrototype()->addImage(&bomb1, Sprite::NEUTRAL);
     }
     if (bombDam0.load("images/bombDam0.png") && bombDam1.load("images/bombDam1.png"))
     {
          bombEnemy->getChildPrototype()->addImage(&bombDam0, Sprite::DAMAGED);
          bombEnemy->getChildPrototype()->addImage(&bombDam1, Sprite::DAMAGED);
     }
     if (bombDes0.load("images/bombDes0.png") && bombDes1.load("images/bombDes1.png") && bombDes2.load("images/bombDes2.png")
          && bombDes3.load("images/bombDes3.png") && bombDes4.load("images/bombDes4.png") && bombDes5.load("images/bombDes5.png"))
     {
          bombEnemy->getChildPrototype()->addImage(&bombDes0, Sprite::DESTROYED);
          bombEnemy->getChildPrototype()->addImage(&bombDes1, Sprite::DESTROYED);
          bombEnemy->getChildPrototype()->addImage(&bombDes2, Sprite::DESTROYED);
          bombEnemy->getChildPrototype()->addImage(&bombDes3, Sprite::DESTROYED);
          bombEnemy->getChildPrototype()->addImage(&bombDes4, Sprite::DESTROYED);
          bombEnemy->getChildPrototype()->addImage(&bombDes5, Sprite::DESTROYED);
     }
     //load images
     particle0.load("images/particle0.png");
     particle1.load("images/particle1.png");
     particle2.load("images/particle2.png");
     particle3.load("images/particle3.png");
     particle4.load("images/particle4.png");

     //bombEnemy setup
     bombEnemy->getChildPrototype()->setAnimated(true);
     bombEnemy->getChildPrototype()->setHitpoints(10);
     bombEnemy->setCollisionDamage(2);
     bombEnemy->getSpriteSystem()->addDestroySound("audio/Explo1.mp3");
     bombEnemy->getSpriteSystem()->addDestroyParticles();
     bombEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle0);
     bombEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle1);
     bombEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle2);
     bombEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle3);
     bombEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle4);
     bombEnemy->setSpawnIndex(0);
     bombEnemy->setScorePerKill(20);
     bombEnemy->stop();

     //beeEnemy images
     beeEnemy = new EnemyEntity(new SpriteSystem());
     if (bee0.load("images/bee0.png") && bee1.load("images/bee1.png") && bee2.load("images/bee2.png"))
     {
          beeEnemy->getChildPrototype()->addImage(&bee0, Sprite::NEUTRAL);
          beeEnemy->getChildPrototype()->addImage(&bee1, Sprite::NEUTRAL);
          beeEnemy->getChildPrototype()->addImage(&bee2, Sprite::NEUTRAL);
     }
     if (beeDam0.load("images/beeDam0.png") && beeDam1.load("images/beeDam1.png"))
     {
          beeEnemy->getChildPrototype()->addImage(&beeDam0, Sprite::DAMAGED);
          beeEnemy->getChildPrototype()->addImage(&beeDam1, Sprite::DAMAGED);
     }
     if (beeDes0.load("images/beeDes0.png") && beeDes1.load("images/beeDes1.png") && beeDes2.load("images/beeDes2.png"))
     {
          beeEnemy->getChildPrototype()->addImage(&beeDes0, Sprite::DESTROYED);
          beeEnemy->getChildPrototype()->addImage(&beeDes1, Sprite::DESTROYED);
          beeEnemy->getChildPrototype()->addImage(&beeDes2, Sprite::DESTROYED);
     }
     //beeEnemy setup
     beeEnemy->getChildPrototype()->setAnimated(true);
     beeEnemy->getChildPrototype()->setHitpoints(3);
     beeEnemy->setCollisionDamage(1);
     beeEnemy->getSpriteSystem()->addDestroySound("audio/Explo1.mp3");
     beeEnemy->getSpriteSystem()->addDestroyParticles();
     beeEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle0);
     beeEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle1);
     beeEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle2);
     beeEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle3);
     beeEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle4);
     beeEnemy->setSpawnIndex(0);
     beeEnemy->setScorePerKill(10);
     beeEnemy->stop();

     //tomatoEnemy images
     tomatoEnemy = new EnemyEntity(new SpriteSystem());
     if (tomato0.load("images/tomato0.png") && tomato1.load("images/tomato1.png"))
     {
          tomatoEnemy->getChildPrototype()->addImage(&tomato0, Sprite::NEUTRAL);
          tomatoEnemy->getChildPrototype()->addImage(&tomato1, Sprite::NEUTRAL);
     }
     if (tomatoDam0.load("images/tomatoDam0.png") && tomatoDam1.load("images/tomatoDam1.png"))
     {
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDam0, Sprite::DAMAGED);
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDam1, Sprite::DAMAGED);
     }
     if (tomatoDes0.load("images/tomatoDes0.png") && tomatoDes1.load("images/tomatoDes1.png") && tomatoDes2.load("images/tomatoDes2.png")
          && tomatoDes3.load("images/tomatoDes3.png") && tomatoDes4.load("images/tomatoDes4.png"))
     {
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDes0, Sprite::DESTROYED);
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDes1, Sprite::DESTROYED);
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDes2, Sprite::DESTROYED);
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDes3, Sprite::DESTROYED);
          tomatoEnemy->getChildPrototype()->addImage(&tomatoDes4, Sprite::DESTROYED);
     }
     //tomatoEnemy setup
     tomatoEnemy->getChildPrototype()->setAnimated(true);
     tomatoEnemy->getChildPrototype()->setHitpoints(16);
     tomatoEnemy->setCollisionDamage(4);
     tomatoEnemy->getSpriteSystem()->addDestroyParticles();
     tomatoEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle0);
     tomatoEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle1);
     tomatoEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle2);
     tomatoEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle3);
     tomatoEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle4);
     tomatoEnemy->getSpriteSystem()->addDestroySound("audio/Explo1.mp3");
     tomatoEnemy->setSpawnIndex(0);
     tomatoEnemy->setScorePerKill(40);
     tomatoEnemy->stop();


     //flowerEnemy images
     flowerEnemy = new EnemyEntity(new SpriteSystem());
     if (flower0.load("images/flower0.png") && flower1.load("images/flower1.png") && flower2.load("images/flower2.png"))
     {
          flowerEnemy->getChildPrototype()->addImage(&flower0, Sprite::NEUTRAL);
          flowerEnemy->getChildPrototype()->addImage(&flower1, Sprite::NEUTRAL);
          flowerEnemy->getChildPrototype()->addImage(&flower2, Sprite::NEUTRAL);
     }
     
     if (flowerDam0.load("images/flowerDam0.png") && flowerDam1.load("images/flowerDam1.png"))
     {
          flowerEnemy->getChildPrototype()->addImage(&flowerDam0, Sprite::DAMAGED);
          flowerEnemy->getChildPrototype()->addImage(&flowerDam1, Sprite::DAMAGED);
     }

     if (flowerDes0.load("images/flowerDes0.png") && flowerDes1.load("images/flowerDes1.png") && flowerDes2.load("images/flowerDes2.png")
          && flowerDes3.load("images/flowerDes3.png") && flowerDes4.load("images/flowerDes4.png"))
     {
          flowerEnemy->getChildPrototype()->addImage(&flowerDes0, Sprite::DESTROYED);
          flowerEnemy->getChildPrototype()->addImage(&flowerDes1, Sprite::DESTROYED);
          flowerEnemy->getChildPrototype()->addImage(&flowerDes2, Sprite::DESTROYED);
          flowerEnemy->getChildPrototype()->addImage(&flowerDes3, Sprite::DESTROYED);
          flowerEnemy->getChildPrototype()->addImage(&flowerDes4, Sprite::DESTROYED);
     }

     //flowerEnemy setup
     flowerEnemy->getChildPrototype()->setAnimated(true);
     flowerEnemy->getChildPrototype()->setHitpoints(18);
     flowerEnemy->setCollisionDamage(3);
     flowerEnemy->getSpriteSystem()->addDestroyParticles();
     flowerEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle0);
     flowerEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle1);
     flowerEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle2);
     flowerEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle3);
     flowerEnemy->getSpriteSystem()->particles->particleImages.push_back(&particle4);
     flowerEnemy->getSpriteSystem()->addDestroySound("audio/Explo1.mp3");
     flowerEnemy->setSpawnIndex(0);
     flowerEnemy->setScorePerKill(50);
     flowerEnemy->stop();

     //text and state setup
     font.load("munro.ttf", 28);
     headerFont.load("munro.ttf", 60);
     bHide = true;
     bGodMode = false;
     gameState = GAME_NOT_STARTED;
     phase = -1;
}

//--------------------------------------------------------------
void ofApp::update() {
     if (gameState == GAME_IN_PROGRESS)
     {
          //update Enemies
          bombEnemy->update();
          beeEnemy->update();
          tomatoEnemy->update();
          flowerEnemy->update();

          //update any score change
          player->addExp(bombEnemy->getScoreChange());
          player->addExp(tomatoEnemy->getScoreChange());
          player->addExp(beeEnemy->getScoreChange());
          player->addExp(flowerEnemy->getScoreChange());

          //update player
          player->update();
          //check collisions
          checkCollisions();
          //update enemy spawn patterns
          changePhase();
          //update HUD strings
          updateHUD();
          //player movement
          if (directionInput[0] == true)//a
          {
               player->setXAccel(-shipAccel);
          }
          if (directionInput[1] == true)//d
          {
               player->setXAccel(shipAccel);
          }
          if (directionInput[2] == true)//s
          {
               player->setYAccel(shipAccel);
          }
          if (directionInput[3] == true)//w
          {
               player->setYAccel(-shipAccel);
          }
          if (directionInput[0] == false && directionInput[1] == false)
          {
               player->setXAccel(0);
          }
          if (directionInput[2] == false && directionInput[3] == false)
          {
               player->setYAccel(0);
          }

     }
     if (player->getState() == Sprite::READY_FOR_DELETION)
     {
          gameState = GAME_OVER;
     }
}

//--------------------------------------------------------------
//*********************DRAWING HERE*****************************
//--------------------------------------------------------------
void ofApp::draw() {
     if (gameState == GAME_IN_PROGRESS)
     {
          background.draw(0, 0, 0);
          bombEnemy->draw();
          beeEnemy->draw();
          tomatoEnemy->draw();
          flowerEnemy->draw();
          player->draw();

          if (!bHide) {
               gui.draw();
          }
          int h = ofGetWindowHeight();
          //Text color
          ofSetColor(50, 50, 50);
          //God Mode Indicator
          if (bGodMode)
          {
               font.drawString("GOD MODE", 1600, h - 100);
          }
          //HP
          font.drawString(hpText, 50, h - 50);
          //BULLET DAMAGE
          font.drawString(bulletText, 220, h - 50);
          //BULLET FIRE RATE
          font.drawString(rateText, 520, h - 50);
          //Score
          font.drawString(scoreText, 1600, h - 50);
          //LVL
          font.drawString(lvlText, 850, 50);

          if (!bHide)
          {
               //FR
               font.drawString(fpsText, 1600, 50);
               //TIME
               font.drawString(timeText, 50, 50);
          }
          ofSetColor(255, 255, 255);
     }
     else if(gameState == GAME_NOT_STARTED)
     {
          //if game not started (put all main menu stuff here)
          ofSetColor(0, 0, 0);
          headerFont.drawString("BOMBS, BEES, AND OTHER BADLY DRAWN THINGS", 260, ofGetWindowHeight() / 2 - 100);
          font.drawString("PRESS SPACE TO START", ofGetWindowWidth() / 2 - 180, ofGetWindowHeight() / 2);
          ofSetColor(255, 255, 255);
     }
     else if (gameState == GAME_OVER)
     {
          ofSetColor(0, 0, 0);
          font.drawString("GAME OVER", ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
          string finalScoreText = "FINAL SCORE: " + to_string(player->getExp());
          font.drawString(finalScoreText, ofGetWindowWidth() / 2 - 120, ofGetWindowHeight() / 2 + 50);
          font.drawString("PRESS SPACE TO TRY AGAIN", ofGetWindowWidth() / 2 - 200, ofGetWindowHeight() / 2 + 100);
          ofSetColor(255, 255, 255);
     }
     else if (gameState == GAME_WON)
     {
          ofSetColor(0, 0, 0);
          font.drawString("YOU WON!!!", ofGetWindowWidth() / 2 - 120, ofGetWindowHeight() / 2);
          string finalScoreText = "FINAL SCORE: " + to_string(player->getExp());
          font.drawString(finalScoreText, ofGetWindowWidth() / 2 - 120, ofGetWindowHeight() / 2 + 50);
          font.drawString("PRESS SPACE TO PLAY AGAIN", ofGetWindowWidth() / 2 - 200, ofGetWindowHeight() / 2 + 100);
          ofSetColor(255, 255, 255);
     }
}

//--------------------------------------------------------------
//*********************HUD UPDATE HERE*************************
//--------------------------------------------------------------
void ofApp::updateHUD()
{
     scoreText = "Score: " + to_string(player->getExp());
     hpText = "HP: " + to_string(player->getHitpoints()) + "/" + to_string(player->getMaxHP());
     bulletText = "Bullet Damage: " + to_string(player->getBulletDamage());
     lvlText = "Player Level: " + to_string(player->getLevel());

     ostringstream temp;
     temp << fixed << setprecision(2);
     temp << player->getRate();
     rateText = "Bullet Rate: " + temp.str();

     if (!bHide)
     {
          timeText = "Time: " + to_string((int)(ofGetElapsedTimeMillis() - startTime));
          fpsText = to_string(ofGetFrameRate()) + " FPS";
     }
}

//--------------------------------------------------------------
//*********************COLLISION STUFF HERE*************************
//--------------------------------------------------------------
void ofApp::checkCollisions() {
     //Bomb enemies
     SpriteSystem * bombSys = bombEnemy->getSpriteSystem();
     int bsize = bombSys->sprites.size();
     for (int i = 0; i < bsize; i++)
     {
          Sprite * sprite = &bombSys->sprites[i];
          int col;
          // if bomb sprite is active (not destoryed or despawning) 
          if (sprite->getState() < Sprite::DESTROYED)
          {
               // see if a player spawned entity (bullet) hits it
               if (col = player->getSpriteSystem()->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0)
               {
                    sprite->changeHitpoints(-col * player->getBulletDamage());
                    sprite->setState(Sprite::DAMAGED);;
                    col = 0;
               }
               // see if the player hits it
               if ((col = player->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0) && player->getState() < Sprite::DESTROYED)
               {
                    player->setState(Sprite::DAMAGED);
                    bombEnemy->getSpriteSystem()->playDestroySound(); //need to manually play destroy sound since we did not subtract hp
                    sprite->setState(Sprite::DESTROYED);              //we do this instead of subtracting hp so that the player is only hit once
                    player->changeHitpoints(-col * bombEnemy->getCollisionDamage());
               }
          }
     }

     //bee enemies
     SpriteSystem * beeSys = beeEnemy->getSpriteSystem();
     int besize = beeSys->sprites.size();
     for (int i = 0; i < besize; i++)
     {
          Sprite * sprite = &beeSys->sprites[i];
          int col;
          // if bee sprite is active (not destoryed or despawning) 
          if (sprite->getState() < Sprite::DESTROYED)
          {
               // see if a player spawned entity (bullet) hits it
               if (col = player->getSpriteSystem()->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0)
               {
                    sprite->changeHitpoints(-col * player->getBulletDamage());
                    sprite->setState(Sprite::DAMAGED);;
                    col = 0;
               }
               // see if the player hits it
               if ((col = player->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0) && player->getState() < Sprite::DESTROYED)
               {
                    player->setState(Sprite::DAMAGED);
                    beeEnemy->getSpriteSystem()->playDestroySound(); //need to manually play destroy sound since we did not subtract hp
                    sprite->setState(Sprite::DESTROYED);              //we do this instead of subtracting hp so that the player is only hit once
                    player->changeHitpoints(-col * beeEnemy->getCollisionDamage());
               }
          }
     }

     //tomato enemies
     SpriteSystem * tomatoSys = tomatoEnemy->getSpriteSystem();
     int tsize = tomatoSys->sprites.size();
     for (int i = 0; i < tsize; i++)
     {
          Sprite * sprite = &tomatoSys->sprites[i];
          int col;
          // if tomato sprite is active (not destoryed or despawning) 
          if (sprite->getState() < Sprite::DESTROYED)
          {
               // see if a player spawned entity (bullet) hits it
               if (col = player->getSpriteSystem()->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0)
               {
                    sprite->changeHitpoints(-col * player->getBulletDamage());
                    sprite->setState(Sprite::DAMAGED);;
                    col = 0;
               }
               // see if the player hits it
               if ((col = player->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0) && player->getState() < Sprite::DESTROYED)
               {
                    player->setState(Sprite::DAMAGED);
                    tomatoEnemy->getSpriteSystem()->playDestroySound(); //need to manually play destroy sound since we did not subtract hp
                    sprite->setState(Sprite::DESTROYED);              //we do this instead of subtracting hp so that the player is only hit once
                    player->changeHitpoints(-col * tomatoEnemy->getCollisionDamage());
               }
          }
     }

     //flower enemies
     SpriteSystem * flowerSys = flowerEnemy->getSpriteSystem();
     int fsize = flowerSys->sprites.size();
     for (int i = 0; i < fsize; i++)
     {
          Sprite * sprite = &flowerSys->sprites[i];
          int col;
          // if flower sprite is active (not destoryed or despawning) 
          if (sprite->getState() < Sprite::DESTROYED)
          {
               // see if a player spawned entity (bullet) hits it
               if (col = player->getSpriteSystem()->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0)
               {
                    sprite->changeHitpoints(-col * player->getBulletDamage());
                    sprite->setState(Sprite::DAMAGED);;
                    col = 0;
               }
               // see if the player hits it
               if ((col = player->collisionsNear(sprite->trans, sprite->getWidth() / 2) > 0) && player->getState() < Sprite::DESTROYED)
               {
                    player->setState(Sprite::DAMAGED);
                    flowerEnemy->getSpriteSystem()->playDestroySound(); //need to manually play destroy sound since we did not subtract hp
                    sprite->setState(Sprite::DESTROYED);              //we do this instead of subtracting hp so that the player is only hit once
                    player->changeHitpoints(-col * flowerEnemy->getCollisionDamage());
               }
          }
     }

     //Set player to destroyed if hp depleted
     if (player->getHitpoints() <= 0 && player->getState() < Sprite::DESTROYED && !bGodMode)
     {
          player->setState(Sprite::DESTROYED);
     }
}

//--------------------------------------------------------------
//*********************INPUT STUFF HERE*************************
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
     player->setMouse(x, y);
}

void ofApp::mouseDragged(int x, int y, int button) {
     player->setMouse(x, y);
}

//Note that the keys do not change velocity of the player, but the acceleration (force vectors)
void ofApp::keyPressed(int key) {

     if (key == 'a' || key == 'A' || key == OF_KEY_LEFT)
     {
          directionInput[0] = true;
     }
     if (key == 'd' || key == 'D' || key == OF_KEY_RIGHT)
     {
          directionInput[1] = true;
     }
     if (key == 'f' || key == 'F')
     {
          ofToggleFullscreen();
     }
     if (key == 'h' || key == 'H')
     {
          bHide = !bHide;
     }
     if (key == 'g' || key == 'G')
     {
          bGodMode = !bGodMode;
     }
     if (key == 's' || key == 'S' || key == OF_KEY_DOWN)
     {
          directionInput[2] = true;
     }
     if (key == 'w' || key == 'W' || key == OF_KEY_UP)
     {
          directionInput[3] = true;
     }
     if (key == ' ')
     {
          if (gameState == GAME_IN_PROGRESS)
          {
               player->start();
          }
          else if (gameState == GAME_NOT_STARTED)
          {
               gameState = GAME_IN_PROGRESS;
               startTime = ofGetElapsedTimeMillis();
               timeOfLastPhaseChange = ofGetElapsedTimeMillis();
          }
          else if (gameState == GAME_OVER)
          {
               reset();
          }
     }
}

void ofApp::keyReleased(int key) {
     if (key == 'a' || key == 'A' || key == OF_KEY_LEFT)
     {
          directionInput[0] = false;
     }
     if (key == 'd' || key == 'D' || key == OF_KEY_RIGHT)
     {
          directionInput[1] = false;
     }
     if (key == 's' || key == 'S' || key == OF_KEY_DOWN)
     {
          directionInput[2] = false;
     }
     if (key == 'w' || key == 'W' || key == OF_KEY_UP)
     {
          directionInput[3] = false;
     }
     if (key == ' ')
     {
          player->stop();
     }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::mouseReleased(int x, int y, int button) {}

void ofApp::mouseEntered(int x, int y) {}

void ofApp::mouseExited(int x, int y) {}

void ofApp::windowResized(int w, int h) {}

void ofApp::gotMessage(ofMessage msg) {}

void ofApp::dragEvent(ofDragInfo dragInfo) {}


void ofApp::changePhase()
{

     if (phase == -1) // then just started, start with basic bomb enemies
     {
          bombEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          bombEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 300, 0));
          bombEnemy->getSpriteSystem()->setMotionType(linMotion);
          bombEnemy->setRate(3);
          bombEnemy->getChildPrototype()->setLifespan(8000);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
          bombEnemy->start();
     }

     if (ofGetElapsedTimeMillis() - timeOfLastPhaseChange < 15000)    //for now, we update phase every 10 seconds.
     {
          return;
     }

     if (phase == 0)     //tomato waves
     {
          bombEnemy->stop();
          tomatoEnemy->setPattern(EnemyEntity::L_WAVE_TWO_CROSS_SPAWN);
          tomatoEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 100, 0));
          tomatoEnemy->getSpriteSystem()->setMotionType(accelMotion);
          tomatoEnemy->setRate(1.4);
          tomatoEnemy->getChildPrototype()->setLifespan(8000);
          tomatoEnemy->start();
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }

     else if (phase == 1)     //bee wave
     {
          tomatoEnemy->stop();
          beeEnemy->start();
          beeEnemy->setPattern(EnemyEntity::L_WAVE_ONE_SPAWN);
          beeEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 120, 0));
          beeEnemy->getSpriteSystem()->setMotionType(sinMotion);
          beeEnemy->setRate(4.0);
          beeEnemy->getChildPrototype()->setLifespan(10000);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 2)     //tomato random
     {
          beeEnemy->stop();
          tomatoEnemy->start();
          tomatoEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          tomatoEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 50, 0));
          tomatoEnemy->setRate(3.0);
          tomatoEnemy->getSpriteSystem()->setMotionType(accelMotion);
          tomatoEnemy->getChildPrototype()->setLifespan(5000);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 3)     //bomb zig zag
     {
          tomatoEnemy->stop();
          bombEnemy->start();
          bombEnemy->setPattern(EnemyEntity::L_LINE_TWO_SPAWN);
          bombEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 300, 0));
          bombEnemy->setRate(4.0);
          bombEnemy->getChildPrototype()->setLifespan(4000);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 4)     //bee, random fast
     {
          bombEnemy->stop();
          beeEnemy->start();
          beeEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          beeEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 500, 0));
          beeEnemy->setRate(2.4);
          beeEnemy->getChildPrototype()->setLifespan(7000);
          sinMotion->setParams(500, 300); //amp, per
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 5)     //flower random
     {
          beeEnemy->stop();
          flowerEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          flowerEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 300, 0));
          flowerEnemy->setRate(1.4);
          flowerEnemy->getChildPrototype()->setLifespan(7000);
          flowerEnemy->getSpriteSystem()->setMotionType(boomMotion);
          flowerEnemy->start();
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 6)     //bee cross
     {
          flowerEnemy->stop();
          beeEnemy->start();
          beeEnemy->setPattern(EnemyEntity::L_WAVE_TWO_CROSS_SPAWN);
          beeEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 300, 0));
          beeEnemy->setRate(4);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 7)     //bees and bombs
     {
          flowerEnemy->stop();
          beeEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          bombEnemy->start();
          bombEnemy->setPattern(EnemyEntity::L_RANDOM_SPAWN);
          bombEnemy->getChildPrototype()->setVelocity(ofVec3f(0, 300, 0));
          bombEnemy->setRate(2);
          bombEnemy->getChildPrototype()->setLifespan(4000);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 8)     //bees and tomatos
     {
          bombEnemy->stop();
          tomatoEnemy->start();
          tomatoEnemy->setPattern(EnemyEntity::L_WAVE_ONE_SPAWN);
          tomatoEnemy->setRate(2);
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 9) // flowers and tomatos
     {
          beeEnemy->stop();
          flowerEnemy->start();
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 10) // flowers and bees
     {
          beeEnemy->start();
          tomatoEnemy->stop();
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else if (phase == 11) // everything :O
     {
          beeEnemy->start();
          bombEnemy->start();
          phase++;
          timeOfLastPhaseChange = ofGetElapsedTimeMillis();
     }
     else  // end of the game
     {
          bombEnemy->stop();
          tomatoEnemy->stop();
          beeEnemy->stop();
          gameState = GAME_WON;
     }

}

void ofApp::reset()
{
     player->setHitpoints(10);
     player->setBulletDamage(2);
     player->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0));    //initialize position
     player->setRate(3.2);
     player->setState(Sprite::NEUTRAL);
     bombEnemy->getSpriteSystem()->reset();
     bombEnemy->stop();
     beeEnemy->getSpriteSystem()->reset();
     beeEnemy->stop();
     tomatoEnemy->getSpriteSystem()->reset();
     tomatoEnemy->stop();
     player->getSpriteSystem()->reset();
     shipAccel = 14;
     bGodMode = false;
     gameState = GAME_NOT_STARTED;
     phase = -1;

     //gameState = GAME_IN_PROGRESS;
     startTime = ofGetElapsedTimeMillis();
     timeOfLastPhaseChange = ofGetElapsedTimeMillis();
}