#pragma once
#include"Rigidbody.h"

class Box : public Rigidbody{
public:
	Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float height, glm::vec4 colour, float linDrag, float angDrag);
	~Box();

	virtual void fixedUpdate(glm::vec2 gravity, float timestep);
	virtual void makeGizmo();

	glm::vec2 getExtents() { return m_extents; }
	glm::vec4 getColour() { return m_colour; }

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }

	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }

protected:
	glm::vec4 m_colour;
	glm::vec2 m_extents;
	glm::vec2 m_localX;
	glm::vec2 m_localY;

	float m_width;
	float m_height;
};

