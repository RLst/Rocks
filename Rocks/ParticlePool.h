#pragma once
#include <glm/vec2.hpp>

namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {

class Particle;
enum PARTICLE_EFFECT;

class ParticlePool
{
private:
	int						MAX_PARTICLES;
	Particle*				m_particles;
	float					m_DEFAULT_life;
	aie::Texture*			m_tex;
	Particle*				m_firstAvailable;

public:
	ParticlePool();
	ParticlePool(int poolSize);
	~ParticlePool();

	void					create(glm::vec2 pos, PARTICLE_EFFECT type);
	void					restore(Particle* particle);
	void					update(float deltaTime);
	void					draw(aie::Renderer2D* renderer);
};

}
