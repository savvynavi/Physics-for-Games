#pragma once
#include<glm\ext.hpp>
#include<Gizmos.h>
#include "Application.h"
#include "Renderer2D.h"
#include"PhysicsScene.h"

class ProjectileMotionApp : public aie::Application {
public:

	ProjectileMotionApp();
	virtual ~ProjectileMotionApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	void setUpContinuourDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		m_physicsScene;
};