#pragma once
#include <glm\vec2.hpp>
#include "Object.h"

namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {

enum ParticleEffect;

class Particle : public Object
{
private:
	ParticleEffect	type;	//Particle effect type

	//union {
	//	//Live
	//	struct {
	//		glm::vec2		pos;	//Position
	//		glm::vec2		vel;	//Velocity
	//		aie::Texture*	tex;	//Texture
	//	} live;
	//	//Free
	//	Particle*			next;
	//} m_state;

public:
	Particle();
	~Particle();

	//Particle specific constructor
	//Particle(const Vector2 &pos, const Vector2 &vel, float life, aie::Texture* tex, ParticleEffect type);

	//void			dervInit();
	void			init(const Vector2 &pos, const Vector2 &vel, float life, aie::Texture *tex, ParticleEffect type);

	void			update(float deltaTime) override;
	void			draw(aie::Renderer2D * renderer) override;

	//void			onInit();
	//void			init(glm::vec2 pos, glm::vec2 vel, float life, aie::Texture* tex, ParticleEffect type);
};

}
