#include "Particle.h"
#include <glm\vec2.hpp>
#include <Renderer2D.h>
#include <Texture.h>
#include "GameDefines.h"

namespace pkr {

Particle::Particle() : m_life(0)
{}

Particle::~Particle() 
{}

void Particle::init(glm::vec2 pos, glm::vec2 vel, float life, aie::Texture* tex, ParticleEffect type)
{
	m_life = life;
	m_state.live.pos = pos;
	m_state.live.vel = vel;
	m_state.live.tex = tex;
	m_state.live.type = type;
}

bool Particle::update(float deltaTime)
{
	if (!isAlive()) return false;

	//Move the particle
	m_state.live.pos += m_state.live.vel * deltaTime;

	//Decrease the life of the particle
	m_life -= deltaTime;

	//Return true if the particle ends
	return m_life <= 0;
}

void Particle::draw(aie::Renderer2D * renderer)
{
	//Particle settings
	static int ExplosionAmount = 5;
	static float ExplosionSpread = 60;

	switch (this->m_state.live.type) {
	case EXPLOSION:
		//Draw multiple times for one particle to make it look more spectacular

		for (int i = 0; i < ExplosionAmount; ++i) {
			//Speed up these particles
			//m_life /= 2.0f;
			renderer->drawSprite(
				m_state.live.tex,
				m_state.live.pos.x + Random(-ExplosionSpread, ExplosionSpread),
				m_state.live.pos.y + Random(-ExplosionSpread, ExplosionSpread),
				50.0f * 0.01f / m_life,
				50.0f * 0.01f / m_life);
				//m_life + 0.15 / m_life	
				//25.0f * 0.01 / m_life		//fireworks
		}
		break;

	//Basic or unspecified particle type
	case BASIC:
	default:
		renderer->drawSprite(
		m_state.live.tex, 
		m_state.live.pos.x, 
		m_state.live.pos.y, 
		0.5f / m_life, 
		0.5f / m_life);
	}


}

}
