#pragma once
#include"Rigidbody.h"

class Sphere : public Rigidbody{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float elasticity = 1, bool kinematic = false, float rotation = 0,float linDrag = 0, float angDrag = 0);
	~Sphere();

	virtual void makeGizmo();

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }
	void setColour(glm::vec4 colour) { m_colour = colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};

