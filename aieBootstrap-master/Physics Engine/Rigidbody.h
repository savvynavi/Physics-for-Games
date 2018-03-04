#pragma once
#include<glm\ext.hpp>
#include"PhysicsObject.h"

class Rigidbody : public PhysicsObject{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float elasticity = 1,bool kinematic = false , float linDrag = 0.3f, float angDrag = 0.3f);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force, glm::vec2 position);
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	glm::vec2 getPosition()const { return m_position; }
	float getRotation()const { return m_rotation; }
	glm::vec2 getVelocity()const { return m_velocity; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }
	float getMass()const { return(m_isKinematic) ? INT_MAX : m_mass; }
	void setMass(float mass) { m_mass = mass; }
	float getElasticity()const { return m_elasticity; }
	void setElasticity(float elasticity) { m_elasticity = elasticity; }

	float getLinearDrag()const { return m_linearDrag; }
	void setLinearDrag(float linearDrag) { m_linearDrag = linearDrag; }
	float getAngularDrag()const { return m_angularDrag; }
	void setAngularDrag(float angularDrag) { m_angularDrag = angularDrag; }
	
	void setKinematic(bool state) { m_isKinematic = state; }
	bool isKinematic() { return m_isKinematic; }

	void setMoment(float moment) { m_moment = moment; }
	float getMoment()const { return (m_isKinematic) ? INT_MAX : m_moment; }

	float getAngularVelocity()const { return m_angularVelocity; }
	void setAngularVelocity(float angVel) { m_angularVelocity = angVel; }
	
	void setLinearVelocity(float vel) { m_linearVelocity = vel; }

	void nudge(glm::vec2 contactF) { m_position += contactF; }
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation;
	float m_elasticity;

	bool m_isKinematic;
	float m_linearDrag;
	float m_angularDrag;

	float m_linearVelocity;
	float m_angularVelocity;
	float m_moment;
};