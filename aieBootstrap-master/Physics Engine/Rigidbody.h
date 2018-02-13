#pragma once
#include<glm\ext.hpp>
#include"PhysicsObject.h"

class Rigidbody : public PhysicsObject{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float linDrag = 0.3f, float angDrag = 0.3f);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force, glm::vec2 position);
	void resolveCollision(Rigidbody* sctor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	float getMass() { return m_mass; }
	void setMass(float mass) { m_mass = mass; }
	float getElasticity() { return m_elasticity; }

	float getLinearDrag() { return m_linearDrag; }
	void setLinearDrag(float linearDrag) { m_linearDrag = linearDrag; }
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float angularDrag) { m_angularDrag = angularDrag; }

	void setMoment(float moment) { m_moment = moment; }
	float getMoment() { return m_moment; }

	float getAngularVelocity() { return m_angularVelocity; }
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;
	float m_elasticity;

	float m_linearDrag;
	float m_angularDrag;

	float m_linearVelocity;
	float m_angularVelocity;
	float m_moment;

	//bool m_isKinematic;
};