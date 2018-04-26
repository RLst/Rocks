#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Fighter;
class BulletPool;
class RockPool;

class Game : public aie::Application {
public:

	Game();
	virtual ~Game();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	Fighter*			m_player;			//Holds the player's fighter
	BulletPool*			m_bullet_pool;		//Holds the bullets of the player's fighter ship
	RockPool*			m_rock_pool;		//Holds the enemy asteroids
	
};