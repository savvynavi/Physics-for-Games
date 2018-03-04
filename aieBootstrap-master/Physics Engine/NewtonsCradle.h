#pragma once
#include"State.h"
#include"PhysicsScene.h"
#include"Input.h"

class StateManager;

class NewtonsCradle : public State
{
public:
	NewtonsCradle(StateManager* sm, PhysicsScene* physScene);
	~NewtonsCradle();

	virtual void onUpdate(float timeStep);
	virtual void onDraw();
	virtual void onEnter();
	virtual void onExit();

	void setup();
private:
	StateManager * m_sm;
	PhysicsScene* m_physicsScene;
	aie::Input* m_input;
};

