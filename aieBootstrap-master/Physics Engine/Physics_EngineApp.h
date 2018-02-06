#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include"PhysicsScene.h"
#include"Sphere.h"
#include"Rocket.h"
#include"Plane.h"

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
	PhysicsScene*		m_physicsScene;
	Sphere*				ball1;
	Rocket*				m_rocket;
	Plane*				m_plane;
};