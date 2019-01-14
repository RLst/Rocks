#pragma once

//#include <glm/vec2.hpp>
#include <pkr\math\Vector2.h>

namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {

class Particle;
enum ParticleEffect;

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

	void					create(Vector2 pos, ParticleEffect type);
	void					restore(Particle* particle);
	void					restoreAll();

	void					update(float deltaTime);
	void					draw(aie::Renderer2D* renderer);

	int						size() { return MAX_PARTICLES; }
};

}
