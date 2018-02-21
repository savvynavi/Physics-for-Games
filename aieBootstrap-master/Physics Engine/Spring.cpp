#include "Spring.h"
#include"Rigidbody.h"
#include<Gizmos.h>

Spring::Spring(Rigidbody* body1, Rigidbody* body2, float restLength, float springCoef, float damping, glm::vec2 contact1, glm::vec2  contact2) : 
	PhysicsObject(JOINT), m_body1(body1), m_body2(body2), m_restLength(restLength), m_springCoefficient(springCoef), m_damping(damping), m_contact1(contact1), m_contact2(contact2){

}


Spring::~Spring(){
	delete m_body1;
	delete m_body2;
}

void Spring::fixedUpdate(glm::vec2 gravity, float timeStep){
	glm::vec2 p1 = m_body1->getPosition();
	glm::vec2 p2 = m_body2->getPosition();
	glm::vec2 dist = p1 - p2;
	float length = glm::length(dist);

	//apply damping
	glm::vec2 relVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	//hookes law
	glm::vec2 force = dist * m_springCoefficient * (m_restLength - length) - m_damping * relVelocity;

	m_body1->applyForce(force * timeStep, p1 - m_body1->getPosition());
	m_body2->applyForce(-force * timeStep, p2 - m_body2->getPosition());
	
	//remove p values later and just make them these
	m_contact1 = p1;
	m_contact2 = p2;
}

void Spring::debug(){

}

void Spring::makeGizmo(){
	aie::Gizmos::add2DLine(m_contact1, m_contact2, glm::vec4(1, 1, 1, 1));
}