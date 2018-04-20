#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "SpaceFighter.h"
#include "Bullet.h"

class SpaceFighter;

class RocksApp : public aie::Application {
public:

	RocksApp();
	virtual ~RocksApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	//Player*				m_player;
	//float				m_timer;

	SpaceFighter		m_player;
	Bullet*				m_bullets;
	
};