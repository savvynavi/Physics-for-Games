#include "Rigidbody.h"


Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : 
	PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass){

}

Rigidbody::~Rigidbody(){

}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep){
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