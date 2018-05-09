#pragma once

//Prototypes
namespace aie {
	class Renderer2D;
	class Texture;
}

namespace pkr {
	class Rock;
	class Fighter;
	class BulletPool;
	class ParticlePool;

class RockPool
{
private:
	int				MAX_ROCKS;
	Rock*			m_rocks;			//Rock array
	Rock*			m_firstAvailable;
	float			m_baseRockSpeed;	//Adds to the speed of the rocks; crude way to increase game difficulty

	//Pointers to the rock textures
	aie::Texture*	m_tex_rock_sml;
	aie::Texture*	m_tex_rock_med;
	aie::Texture*	m_tex_rock_lge;

public:
	//RockPool();
	RockPool(int poolsize);
	~RockPool();

	void			update(float deltaTime);
	void			draw(aie::Renderer2D* renderer);
	
	void			request(Fighter * player);	//A random size rock will be roughly hurled at the player
	void			restore(Rock* rock);
	void			resetRockSpeed() { m_baseRockSpeed = 0.0f; }

	//Collisions
	void HandlePlayerCollision(Fighter * player, ParticlePool* particlePool);
	void HandleBulletCollision(BulletPool * bullets, ParticlePool* particlePool, int &score);
				
	//Getters and setters
	//Rock*			operator[](int index) const;	//?
	int				size() { return MAX_ROCKS; }
};

}
