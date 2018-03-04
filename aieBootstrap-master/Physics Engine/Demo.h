#pragma once
#include"State.h"
#include"PhysicsScene.h"
#include"Input.h"
#include"Plane.h"
#include"Sphere.h"
#include"Box.h"
#include"Spring.h"

class StateManager;

class Demo : public State{
public:
	Demo(StateManager* sm, PhysicsScene* physScene);
	~Demo();

	virtual void onUpdate(float timeStep);
	virtual void onDraw();
	virtual void onEnter();
	virtual void onExit();
	
	void reset();
	void startup();
	void drawAtMouse();
	glm::vec2 gizmoCoords(glm::vec2 screenCoords);
private:
	StateManager* m_sm;
	PhysicsScene* m_physicsScene;
	aie::Input* m_input;

	glm::vec2 m_gizmoCoordinates;
	int m_mouseX, m_mouseY;
	glm::vec2 mousePos;
};

