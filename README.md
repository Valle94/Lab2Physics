# Lab 3 - Projectile System

My projectile class is a c++ class found in the source section of the project. The blueprint child handles selecting the mesh, and houses the movement component that enables projectile movement. All of the launch control variables for the projectile are attached to that component in the projectile blueprint. The primary configurable values are initial and max speed, both of which are built into the component. 

The independent extension I made is a simple ammo system. It is configured such that you have 10 bullets, and when your gun is empty it will automatically start to reload, which takes 4 seconds. All of this is configurable in the editor. 

# Lab 2 - Physics Interaction

Control Used: I implemented a simple mouse click to "shoot" at the center of the screen wherever the player is facing. 

The name of my custom ActorComponent is PhysicsShooter and can be found in the c++ classes folder in the UE5 Explorer, or in the source folder in the game files. 

I added three editor configurable values: the raycast length, the impulse power (how hard you push the hit object), as well as a boolean toggle for whether the physics impulse even takes mass into account at all. 
