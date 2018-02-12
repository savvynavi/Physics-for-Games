#pragma once
#include<glm\ext.hpp>
#include"PhysicsObject.h"

class Rigidbody : public PhysicsObject{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float linDrag = 0.3f, float angDrag = 0.3f);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force);
	void applyForceToActor(Rigidbody* actor2, glm::vec2 force);

	virtual bool checkCollision(PhysicsObject* other) = 0;

	glm::vec2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	float getMass() { return m_mass; }
	void setMass(float mass) { m_mass = mass; }

	float getLinearDrag() { return m_linearDrag; }
	void setLinearDrag(float linearDrag) { m_linearDrag = linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float angularDrag) { m_angularDrag = angularDrag; }

	void resolveCollision(Rigidbody* actor2);
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;

	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;

	float m_linearVelocity = 0.1f;
	float m_angularVelocity = 0.01f;
};