#pragma once
#include"PhysicsObject.h"

class Rigidbody;

class Spring : public PhysicsObject{
public:
	Spring();
	~Spring();

	void fixedUpdate();
	void debug();
	void makeGizmo();
protected:
	Rigidbody* m_body1;
	Rigidbody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 contact2;

	float m_damping;
	float m_restLength;
	float m_springCoefficient;
};

