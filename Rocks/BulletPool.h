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

public:
	BulletPool(int poolsize);
	~BulletPool();

	void request(glm::vec2 pos, glm::vec2 vel);
	void restore(Bullet* bullet);

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

	//Getters and setters
	int size() { return MAX_BULLETS; }
};

}
