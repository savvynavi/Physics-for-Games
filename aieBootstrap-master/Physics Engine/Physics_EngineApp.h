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

#include"Pool.h"

class Physics_EngineApp : public aie::Application {
public:

	Physics_EngineApp();
	virtual ~Physics_EngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void mouseToWorld();

	void cradleSetUp();
	void frictionExampleSetup();
	void contactForceTest();
	void springTest();
	void pool();
	void pinball();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	StateManager*		m_sm;
	PhysicsScene*		m_physicsScene;
	Sphere*				m_ball1;
	Sphere*				m_ball2;
	Sphere*				m_ball3;
	Sphere*				m_ball4;
	Sphere*				m_ball5;

	Box*				m_box1;
	Box*				m_box2;
	Box*				m_box3;
	Box*				m_box4;
	Box*				m_box5;

	//Rocket*				m_rocket;
	Plane*				m_plane1;
	Plane*				m_plane2;
	Plane*				m_plane3;

	Spring*				m_spring1;

	Pool*				m_pool;
	Pinball*			m_pinball;
	MainMenu*			m_mainMenu;

	glm::vec2			m_mousePos;
	int					m_mouseX, m_mouseY;
	glm::vec2			m_mouseWorldCoord;
};