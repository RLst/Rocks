#include "ParticlePool.h"
#include "Particle.h"
#include <Texture.h>
#include "GameDefines.h"
#include <cassert>

namespace pkr {

ParticlePool::ParticlePool()
{
}

ParticlePool::ParticlePool(int poolSize) : MAX_PARTICLES(poolSize)
{
	//Set particle settings
	m_DEFAULT_life = 0.25f;	//seconds

	//Load textures
	m_tex = new aie::Texture("../bin/textures/ball.png");

	//Create object pool
	m_particles = new Particle[MAX_PARTICLES];

	//Set first available
	m_firstAvailable = &m_particles[0];

	//Each object points to the next
	for (int i = 0; i < MAX_PARTICLES - 1; ++i) {
		m_particles[i].setNext(&m_particles[i + 1]);
	}

	//The last one terminates the list
	m_particles[MAX_PARTICLES - 1].setNext(NULL);
}


ParticlePool::~ParticlePool()
{
	delete[] m_particles;
}

void ParticlePool::create(Vector2 pos, ParticleEffect type)
{
	//Make sure there are available objects in the pool
	assert(m_firstAvailable != NULL);
	//if (m_firstAvailable == NULL) return;

	//Allocate free particle from the pool
	Particle* newParticle = m_firstAvailable;
	m_firstAvailable = (Particle)newParticle->getNext();

	///////
	//Setup 
	///////
	//Random velocity
	//static float maxParticleSpeed = 250.0f;
	//Vector2 vel;
	//vel.x = Random(-maxParticleSpeed, maxParticleSpeed);
	//vel.y = Random(-maxParticleSpeed, maxParticleSpeed);
	Vector2 vel = { 0,0 };	//Meh... particles don't really need to move; life too short

	//Initialise the particle
	newParticle->init(pos, vel, m_DEFAULT_life, m_tex, type);
};


void ParticlePool::restore(Particle* particle)
{
	particle->setNext(m_firstAvailable);
	m_firstAvailable = particle;
}

void ParticlePool::restoreAll()
{
	//Kill all objects and hopefully the game::update() deals with the cleanup
	for (int i = 0; i < this->size() - 1; ++i)
	{
		m_particles[i].kill();
	}
}

void ParticlePool::update(float deltaTime)
{
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		//Handle particle life
		if (m_particles[i].update(deltaTime)) {
			//Restore back to pool once particle life ends
			restore(&m_particles[i]);
		}
	}
}

void ParticlePool::draw(aie::Renderer2D * renderer)
{
	//Draw all active particles
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		if (m_particles[i].isAlive()) {
			m_particles[i].draw(renderer);
		}
	}
}

}