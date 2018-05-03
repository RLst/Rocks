#pragma once

//Prototypes
#include <glm\vec2.hpp>

namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {
	class Bullet;

class BulletPool
{
	//static const int POOL_SIZE = 25;
	//Bullet* m_bullets[POOL_SIZE];
	int						MAX_BULLETS;
	Bullet*					m_bullets;
	Bullet*					m_firstAvailable;

	//Textures
	aie::Texture*			m_tex_bullet;
	aie::Texture*			m_tex_rock_sml;
	aie::Texture*			m_tex_rock_med;
	aie::Texture*			m_tex_rock_lge;

public:
	BulletPool(int maxBullets);
	~BulletPool();

	void request(glm::vec2 &pos, glm::vec2 &vel);
	void update(float dt);
	void draw(aie::Renderer2D* renderer);
	int size() { return MAX_BULLETS; }
};

}
