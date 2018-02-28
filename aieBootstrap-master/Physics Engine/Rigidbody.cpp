#include "Rigidbody.h"
#define  MIN_LINEAR_THRESHOLD 0.001f
#define MIN_ROTATIONAL_THRESHOLD 0.001f


Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float elasticity, bool kinematic, float linDrag, float angDrag) :
	PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass), m_elasticity(elasticity),m_linearDrag(linDrag), m_angularDrag(angDrag), m_isKinematic(kinematic){
	m_angularVelocity = 0;
}

Rigidbody::~Rigidbody(){

}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep){
	if(m_isKinematic == true){
		//m_velocity = glm::vec2(0, 0);
		//m_angularVelocity = 0;
		gravity = glm::vec2(0, 0);
		//return;
	}
	
	m_position += m_velocity * timeStep;
	m_velocity += gravity * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	if(glm::length(m_velocity) < MIN_LINEAR_THRESHOLD){
		m_velocity = glm::vec2(0, 0);
	}

	if(abs(m_angularVelocity) < MIN_ROTATIONAL_THRESHOLD){
		m_angularVelocity = 0;
	}
}

void Rigidbody::debug(){

}

//newtons 2nd law
void Rigidbody::applyForce(glm::vec2 force, glm::vec2 position){
	glm::vec2 acceleration = { force.x / this->getMass(), force.y / this->getMass() };
	m_velocity += acceleration;
	m_angularVelocity += (force.y * position.x - force.x * position.y) / this->getMoment();
}

void Rigidbody::resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal){
	glm::vec2 normal = collisionNormal ? *collisionNormal : glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	glm::vec2 perp(normal.y, -normal.x);

	//r is the radius from axis to app of force
	float r1 = glm::dot(contact - m_position, -perp);
	float r2 = glm::dot(contact - actor2->getPosition(), perp);
	//velocity of contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;
	//velocity of contact point on actor2
	float v2 = glm::dot(actor2->getVelocity(), normal) + r2 * actor2->m_angularVelocity;

	//if they're moving closer, calc effective mass at contact point for each object, then apply forces
	if(v1 > v2){
		float mass1 = 1.0f / (1.0f / this->getMass() + (r1 * r2) / this->getMoment());
		float mass2 = 1.0f / (1.0f / actor2->getMass() + (r1 * r2) / actor2->getMoment());
	
		float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;
		glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2)* (v1 - v2) * normal;
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->getPosition());
	}
}