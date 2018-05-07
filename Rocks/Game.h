#pragma once

#include "Application.h"
#include "Renderer2D.h"

namespace pkr {
	class Fighter;
	class BulletPool;
	class RockPool;
	class ParticlePool;
}

class Game : public aie::Application {
public:

	Game();
	virtual ~Game();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	int					m_score;
	int					m_hiscore;

	double				m_timer;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	pkr::Fighter*		m_player;			//Holds the player's fighter
	pkr::BulletPool*	m_bullet_pool;		//Holds the bullets of the player's fighter ship
	pkr::RockPool*		m_rock_pool;		//Holds the enemy asteroids
	pkr::ParticlePool*	m_particle_pool;	//Holds explosion particles


};