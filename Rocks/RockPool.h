#pragma once

//#include <Texture.h>		//Won't work without this!!!
//#include "Rock.h"
namespace aie {
	class Renderer2D;
	class Texture;
}

namespace pkr {
	class Rock;
	class Fighter;

class RockPool
{
private:
	unsigned int	MAX_ROCKS = 100;	//Default 100
	Rock*			m_rocks;			//Rock array
	Rock*			m_firstAvailable;

	//Pointers to the rock textures
	aie::Texture*	m_rock_sml;
	aie::Texture*	m_rock_med;
	aie::Texture*	m_rock_lge;

public:
	RockPool();
	RockPool(unsigned int);
	~RockPool();

	void hurl(Fighter &player);	//A random size rock will be hurled at the player
	void wrap(Fighter &player);

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

	//Getters and setters
	int size() { return MAX_ROCKS; }
};

}
