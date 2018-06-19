#pragma once
#include <glm/vec2.hpp>

//This class is a base class that holds all game objects ie. fighter, rocks, bullets
//Benefits:
//1. I can make one universal object pool to hold all objects
//2. Collisions should be easier to calculate since they're all the same entity

namespace aie {
	class Texture;
}

namespace pkr {

enum ParticleEffect;
enum RockType;

class Entity
{
	//Free list essentials



	//bool			m_alive;
	union {
		//In use
		struct {
			//General
			glm::vec2		m_pos;
			glm::vec2		m_vel;
			float			m_smooth;
			float			m_life;
			float			m_resetlife;
			aie::Texture*	m_tex;
			/*
			//Fighter related (move these later)
			glm::vec2		m_tarPos;
			glm::vec2		m_tarAng;
			float			m_speed;
			float			m_angSpeed;

			float			m_bulletSpeed;
			float			m_lastTimeShot;
			float			m_shootDelay;
			float			m_gunOffset;

			//Bullet
			float			m_damage;

			//Particle
			ParticleEffect	m_type;

			//Rock
			RockType		m_type;
			float			m_collisionRadius;
			float			m_damage;
			*/
		} live;

		//Free
		Entity*				m_next;
	};
	
public:
	Entity();
	~Entity();
};

}
