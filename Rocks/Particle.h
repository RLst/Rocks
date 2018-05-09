#pragma once
#include <glm\vec2.hpp>

namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {

enum ParticleEffect;

class Particle
{
private:
	float					m_life;	//Life in seconds
									//Also adjusts the alpha/size?
	union {
		//Live
		struct {
			glm::vec2		pos;	//Position
			glm::vec2		vel;	//Velocity
			aie::Texture*	tex;	//Texture
			ParticleEffect	type;	//Particle effect type
		} live;
		//Free
		Particle*			next;
	} m_state;
	
public:
	Particle();
	~Particle();

	void					init(glm::vec2 pos, glm::vec2 vel, float life, aie::Texture* tex, ParticleEffect type);
	
	Particle*				getNext() { return m_state.next; }
	void					setNext(Particle* next) { m_state.next = next; }

	bool					isAlive() { return m_life > 0; }
	void					kill() { m_life = 0; }

	bool					update(float deltaTime);
	void					draw(aie::Renderer2D * renderer);


};

}
