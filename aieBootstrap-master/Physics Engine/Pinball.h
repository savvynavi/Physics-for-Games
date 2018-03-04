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
class Pinball : public State{
public:
	Pinball(PhysicsScene* physScene, StateManager* sm, aie::Renderer2D* renderer, aie::Font* font);
	~Pinball();
	void board();
	glm::vec2 gizmoCoords(glm::vec2 screenCoords);

	virtual void onUpdate(float timeStep);
	virtual void onDraw();
	virtual void onEnter();
	virtual void onExit();

	void paddleMovement();
	void resetBall();
	void addForceMouse();
private:
	StateManager* m_sm;
	aie::Renderer2D* m_renderer;
	aie::Font* m_font;
	aie::Input* m_input;

	PhysicsScene* m_physicsScene;
	glm::vec2 m_gizmoCoordinates;
	Box* m_leftPaddle;
	Box* m_rightPaddle;

	Sphere* m_ball;
	int m_mouseX, m_mouseY;
	glm::vec2 m_mousePosCurrent;
	glm::vec2 m_mousePosDragged;

	int m_score;
	int m_lives;
	bool mouseDrag;
};

