#pragma once
//  Kevin M. Smith - CS 134 SJSU

#include "ofMain.h"
#include "Particle.h"


//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
public:
	bool applyOnce = false;
	bool applied = false;
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
	void setLifespan(float);
	void reset();
	void draw();
	vector<Particle> particles;
	vector<ParticleForce *> forces;
};

// Some convenient built-in forces
//
class GravityForce: public ParticleForce {
	ofVec3f gravity;
public:
	GravityForce(float g);
	void updateForce(Particle *);
     void setGravity(float g);
};

class TurbulenceForce : public ParticleForce {
	ofVec3f tmin, tmax;
public:
	TurbulenceForce(const ofVec3f & min, const ofVec3f &max);
	void updateForce(Particle *);
     void setTurbulence(const ofVec3f & min, const ofVec3f &max);
};

class ImpulseRadialForce : public ParticleForce {
	float magnitude;
     float height;
public:
	ImpulseRadialForce(const float magnitude);
	void updateForce(Particle *);
     void setMagnitude(float mag);
};
