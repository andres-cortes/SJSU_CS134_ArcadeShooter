//  Kevin M. Smith - CS 134 SJSU
//  Andres Cortes added ability to render particles as images instead of drawn circles.
#include "Particle.h"

TransformObject::TransformObject() {
     position = ofVec3f(0, 0, 0);
     scale = ofVec3f(1, 1, 1);
     rotation = 0;
}

void TransformObject::setPosition(const ofVec3f & pos) {
     position = pos;
}

Particle::Particle() {

	// initialize particle with some reasonable values first;
	//
	velocity.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	forces.set(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 100;
	damping = .99;
	mass = 1;
     hasImage = false;
	color = ofColor::aquamarine;
}

void Particle::draw() {
     if (hasImage)
     {
          ofSetColor(255, 255, 255, 255);
          image->draw(position);
     }
     else
     {
          ofSetColor(0, 0, 0);
          ofDrawCircle(position, radius);
     }
}

void Particle::integrate() {

	
	// interval for this step
	//
	float dt = 1.0 / ofGetFrameRate();

	// update position based on velocity
	//
	position += (velocity * dt);

	// update acceleration with accumulated paritcles forces
	// remember :  (f = ma) OR (a = 1/m * f)
	//
	ofVec3f accel = acceleration;    // start with any acceleration already on the particle
	accel += (forces * (1.0 / mass));
	velocity += accel * dt;

	// add a little damping for good measure
	//
	velocity *= damping;

	// clear forces on particle (they get re-added each step)
	//
	forces.set(0, 0, 0);
}

//  return age in seconds
//
float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime)/1000.0;
}

void Particle::addImage(ofImage * img)
{
     image = img;
     hasImage = true;
}

