#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include"PhysicsScene.h"
#include"Sphere.h"
#include"Box.h"
//#include"Rocket.h"
#include"Plane.h"

class Physics_EngineApp : public aie::Application {
public:

	Physics_EngineApp();
	virtual ~Physics_EngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void cradleSetUp();
	void frictionExampleSetup();
	void boxTest();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
	Sphere*				m_ball1;
	Sphere*				m_ball2;
	Sphere*				m_ball3;
	Sphere*				m_ball4;
	Sphere*				m_ball5;

	Box*				m_box1;
	Box*				m_box2;

	//Rocket*				m_rocket;
	Plane*				m_plane1;
	Plane*				m_plane2;
	Plane*				m_plane3;
};