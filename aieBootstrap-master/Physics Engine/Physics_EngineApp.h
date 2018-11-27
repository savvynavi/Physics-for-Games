#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include"PhysicsScene.h"
#include"Sphere.h"
#include"Box.h"
//#include"Rocket.h"
#include"Plane.h"
#include"Spring.h"

#include"State.h"
#include"StateManager.h"
#include"Pinball.h"
#include"MainMenu.h"
#include"Demo.h"
#include"NewtonsCradle.h"
#include"Instructions.h"

#include"Pool.h"

class Physics_EngineApp : public aie::Application {
public:

	Physics_EngineApp();
	virtual ~Physics_EngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	StateManager*		m_sm;
	PhysicsScene*		m_physicsScene;

	Pool*				m_pool;
	Pinball*			m_pinball;
	MainMenu*			m_mainMenu;
	Demo*				m_demo;
	NewtonsCradle*		m_cradle;
	Instructions*		m_instructions;

	glm::vec2			m_mousePos;
	int					m_mouseX, m_mouseY;
	glm::vec2			m_mouseWorldCoord;
};