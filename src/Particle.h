//  Kevin M. Smith - CS 134 SJSU
#pragma once

#include "ofMain.h"

class ParticleForceField;

class TransformObject {
public:
     TransformObject();
     ofVec3f position, scale;
     float rotation;
     bool	bSelected;
     void setPosition(const ofVec3f &);
};

class Particle {
public:
	Particle();
     void addImage(ofImage * img);
	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f forces;
	float	damping;
	float   mass;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    integrate();
	void    draw();
	float   age();        // sec
	ofColor color;
private:
     ofImage * image;
     bool hasImage;
};


