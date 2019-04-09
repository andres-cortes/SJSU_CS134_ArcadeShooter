#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "PlayerEntity.h"
#include "EnemyEntity.h"
#include "Sprite.h"
#include <sstream>
#include <iomanip>

class Emitter;

class ofApp : public ofBaseApp {

public:
     static const int GAME_NOT_STARTED = 0;
     static const int GAME_IN_PROGRESS = 1;
     static const int GAME_OVER = 2;
     static const int GAME_WON = 3;
     void setup();
     void update();
     void draw();
     void checkCollisions();
     void updateHUD();
     void keyPressed(int key);
     void keyReleased(int key);
     void mouseMoved(int x, int y);
     void mouseDragged(int x, int y, int button);
     void mousePressed(int x, int y, int button);
     void mouseReleased(int x, int y, int button);
     void mouseEntered(int x, int y);
     void mouseExited(int x, int y);
     void changePhase();
     void windowResized(int w, int h);
     void dragEvent(ofDragInfo dragInfo);
     void gotMessage(ofMessage msg);
     void reset();

private:
     int mouseX;
     int mouseY;
     int gameState;
     PlayerEntity *player;
     EnemyEntity *bombEnemy;
     EnemyEntity *beeEnemy;
     EnemyEntity *tomatoEnemy;
     EnemyEntity *flowerEnemy;

     bool imageLoaded;
     bool bHide;
     bool bGodMode;
     float shipAccel;
     int phase;
     float startTime;
     float timeOfLastPhaseChange;
     bool directionInput[4];

     string scoreText, hpText, bulletText, rateText, timeText, fpsText, lvlText;
     ofxLabel screenSize;
     ofxPanel gui;
     ofTrueTypeFont font;
     ofTrueTypeFont headerFont;
     //IMAGES
     ofImage background;

     ofImage shot0, shot1, shot2;
     ofImage shotDes0, shotDes1;
     ofImage Starship0, Starship1, Starship2;
     ofImage StarshipDam0, StarshipDam1;
     ofImage StarshipDes0, StarshipDes1, StarshipDes2, StarshipDes3, StarshipDes4, StarshipDes5;

     ofImage particle0, particle1, particle2, particle3, particle4;
     ofImage bomb0, bomb1;
     ofImage bombDam0, bombDam1;
     ofImage bombDes0, bombDes1, bombDes2, bombDes3, bombDes4, bombDes5;

     ofImage bee0, bee1, bee2;
     ofImage beeDam0, beeDam1;
     ofImage beeDes0, beeDes1, beeDes2;

     ofImage tomato0, tomato1;
     ofImage tomatoDam0, tomatoDam1;
     ofImage tomatoDes0, tomatoDes1, tomatoDes2, tomatoDes3, tomatoDes4;

     ofImage flower0, flower1, flower2;
     ofImage flowerDam0, flowerDam1;
     ofImage flowerDes0, flowerDes1, flowerDes2, flowerDes3, flowerDes4;

     SinMotionPattern * sinMotion;
     AccelMotionPattern * accelMotion;
     LinMotionPattern * linMotion;
     BoomerangMotionPattern * boomMotion;
};
