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

public:
	RockPool();
	RockPool(unsigned int);
	~RockPool();
};

}
