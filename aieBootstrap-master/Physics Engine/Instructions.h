#pragma once
#include<list>
#include<Gizmos.h>
#include"State.h"
#include"Renderer2D.h"
#include"Font.h"
#include"Input.h"
#include"PhysicsScene.h"
#include"Plane.h"
#include"Sphere.h"
#include"Box.h"

class StateManager;

class Instructions : public State{
public:
	Instructions(PhysicsScene* physScene, StateManager* sm, aie::Renderer2D* renderer, aie::Font* font);
	~Instructions();

	virtual void onUpdate(float timeStep);
	virtual void onDraw();
	virtual void onEnter();
	virtual void onExit();

private:
	PhysicsScene* m_physicsScene;
	StateManager* m_sm;
	aie::Renderer2D* m_renderer;
	aie::Font* m_font;
	aie::Font* m_font2;
	aie::Input* m_input;
};

