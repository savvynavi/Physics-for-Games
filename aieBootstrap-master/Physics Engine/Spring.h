#pragma once
#include"PhysicsObject.h"

class Rigidbody;

class Spring : public PhysicsObject{
public:
	Spring(Rigidbody* body1, Rigidbody* body2, float restLength, float springCoef, float damping = 0.1f, glm::vec2 contact1 = glm::vec2(0, 0), glm::vec2  contact2 = glm::vec2(0, 0));
	~Spring();

	void fixedUpdate(glm::vec2 gravity, float timeStep);
	void debug();
	void makeGizmo();
protected:
	Rigidbody* m_body1;
	Rigidbody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 m_contact2;

	float m_damping;
	float m_restLength;
	float m_springCoefficient;

	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

