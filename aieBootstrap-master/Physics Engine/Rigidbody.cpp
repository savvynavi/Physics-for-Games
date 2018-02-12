#include "Rigidbody.h"


Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float linDrag, float angDrag) : 
	PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass), m_linearDrag(linDrag), m_angularDrag(angDrag){

}

Rigidbody::~Rigidbody(){

}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep){
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	m_position += m_velocity * timeStep;
	applyForce(gravity * m_mass * timeStep);
}

void Rigidbody::debug(){

}

//newtons 2nd law
void Rigidbody::applyForce(glm::vec2 force){
	glm::vec2 acceleration = { force.x / m_mass, force.y / m_mass };
	m_velocity += acceleration;
}

//newtons 3rd law
void Rigidbody::applyForceToActor(Rigidbody* actor2, glm::vec2 force){
	if(actor2 != nullptr){
		actor2->applyForce(force);
		this->applyForce(-force);
	}
}

void Rigidbody::resolveCollision(Rigidbody* actor2){
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	//if moving away from each other, returns sout
	if(glm::dot(normal, relativeVelocity) > 0){
		return;
	}

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1/m_mass) + (1/actor2->getMass())));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);
}