#pragma once
#include <pkr\math\Vector2.h>
#include "BulletIterator.h"

//Prototypes
namespace aie {
	class Texture;
	class Renderer2D;
}

namespace pkr {
	class Bullet;

class BulletPool
{
	Bullet*					m_bullets;		
	int						MAX_BULLETS;
	float					m_bulletLifeTime;
	float					m_bulletAttack;

	Bullet*					m_firstAvailable;

	//Textures
	aie::Texture*			m_tex_bullet;

public:
	BulletPool(int poolsize);
	~BulletPool();

	BulletIterator			begin() { return BulletIterator(m_firstAvailable); }
	BulletIterator			end() { return BulletIterator(); }

	void					request(Vector2 pos, Vector2 vel);
	void					restore(Bullet* bullet);
	void					restoreAll();	//Frees up all objects in pool

	void					update(float deltaTime);
	void					draw(aie::Renderer2D* renderer);

	//Get pointers to in use
	float					getBulletDamage() { return m_bulletAttack; }

	//Getters and setters
	Bullet*					operator[](int index) const;
	int						size() { return MAX_BULLETS; }

	//test
	Bullet*		operator -> () { return m_bullets; }

};

}
