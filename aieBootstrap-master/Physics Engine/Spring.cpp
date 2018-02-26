#include "Spring.h"
#include"Rigidbody.h"
#include<Gizmos.h>

Spring::Spring(Rigidbody* body1, Rigidbody* body2, float restLength, float springCoef, float damping, glm::vec2 contact1, glm::vec2  contact2) : 
	PhysicsObject(JOINT), m_body1(body1), m_body2(body2), m_restLength(restLength), m_springCoefficient(springCoef), m_damping(damping), m_contact1(contact1), m_contact2(contact2){
	
	//auto sets the length to be dist between objects
	if(m_restLength == 0){
		glm::vec2 dist = m_body2->getPosition() - m_body1->getPosition();
		m_restLength = glm::length(dist);
	}
	m_body1->setLinearVelocity(0);
	m_body2->setLinearVelocity(0);

}


Spring::~Spring(){
	delete m_body1;
	delete m_body2;
}

void Spring::fixedUpdate(glm::vec2 gravity, float timeStep){
	m_contact1 = m_body1->getPosition();
	m_contact2 = m_body2->getPosition();
	glm::vec2 dist = m_contact2 - m_contact1;
	float length = glm::length(dist);

	//apply damping
	glm::vec2 relVelocity = m_body2->getVelocity() - m_body1->getVelocity();

	//hookes law
	glm::vec2 force = dist * m_springCoefficient * (m_restLength - length) - m_damping * relVelocity;

	m_body1->applyForce(-force * timeStep, m_contact1 - m_body1->getPosition());
	m_body2->applyForce(force * timeStep, m_contact2 - m_body2->getPosition());
	
}

void Spring::debug(){

}

void Spring::makeGizmo(){
	aie::Gizmos::add2DLine(m_contact1, m_contact2, glm::vec4(1, 1, 1, 1));
}