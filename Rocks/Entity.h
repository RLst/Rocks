#pragma once
#include <glm/vec2.hpp>

//This class is a base class that holds all game objects ie. fighter, rocks, bullets
//Benefits:
//1. I can make one universal object pool to hold all objects
//2. Collisions should be easier to calculate since they're all the same entity


class Entity
{
	/*
	bool			m_alive;
	union {
		//In use
		struct {
			//General
			glm::vec2		pos;
			glm::vec2		vel;
			float			smooth;
			float			life;
			float			resetlife;
			aie::Texture*	tex;

			//Fighter related (move these later)
			glm::vec2		tarPos;
			glm::vec2		tarAng;
			float			speed;
			float			angSpeed;

			float			bulletSpeed;
			float			lastTimeShot;
			float			shootDelay;
			float			gunOffset;

			//Bullet
			float			damage;

			//Particle
			ParticleEffect	type;

			//Rock
			RockType		type;
			float			collisionRadius;
			float			damage;

		} live;

		//Free
		Entity*			next;
	} m_state;
	*/
public:
	Entity();
	~Entity();
};

