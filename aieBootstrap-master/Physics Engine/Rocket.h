#pragma once
#include"Sphere.h"
#include"PhysicsScene.h"
#include"Input.h"

class Rocket : public Sphere{
public:
	Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, PhysicsScene* physScene);
	~Rocket();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
protected:
	float m_radius;
	glm::vec4 m_colour;
	aie::Input* m_input;
	PhysicsScene* m_physScene;
};


