# SJSU_CS134_ArcadeShooter
An "arcade shooter" example using C++ and openframeworks.

To compile and run this project, create a new openframeworks project (if you don't know how, the easiest way is to download open frameworks and use the project Generator) with the ofxGui addon, then open, build, and run from your IDE of choice (I used Visual Studio 2017).

This is definitely not the cleanest code I've written, but I did my best to make it easy to add functionality. The base class for most of the game objects is Sprite. Emitter inherits from Sprite, but adds the functionality of being able to spawn other sprites (to manage the spawning and despawning, it uses SpriteSystem). The Particle and ParticleEmitter classes are similar, but particles behave differently in that they cannot interact with other objects, and are controlled by simple physics calculations. All "Entity" objects inherit from Emitter. 

If anyone has questions feel free to message me!
