#pragma once

#include <pkr\math\Vector2.h>
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

	union {
		//Live
		struct {
			Vector2			pos;	//Position
			Vector2			vel;	//Velocity
			aie::Texture*	tex;	//Texture
			ParticleEffect	type;
		} live;
		//Free
		Particle*			next;
	} m_state;

public:
	Particle();
	~Particle() override;

	//Particle specific constructor
	//Particle(const Vector2 &pos, const Vector2 &vel, float life, aie::Texture* tex, ParticleEffect type);

	//void			dervInit();
	void			init(const Vector2 &pos, const Vector2 &vel, float life, aie::Texture *tex, ParticleEffect type);

	bool			update(float deltaTime) override;
	void			draw(aie::Renderer2D * renderer) override;

	//void			onInit();
	//void			init(Vector2 pos, Vector2 vel, float life, aie::Texture* tex, ParticleEffect type);
};

}
