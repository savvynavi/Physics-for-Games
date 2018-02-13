#include<Gizmos.h>
#include "Plane.h"
#include"Sphere.h"



Plane::Plane() : PhysicsObject(ShapeType::PLANE) {
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(ShapeType::PLANE), m_distanceToOrigin(distance), m_normal(normal) {
	m_normal = glm::normalize(m_normal);
}

Plane::~Plane(){

}

//planes don't move so this is left empty
void Plane::fixedUpdate(glm::vec2 gravity, float timeStep){

}


void Plane::makeGizmo(){
	float lineSegmentLength = 300;
	glm::vec2 centrePoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centrePoint + (parallel * lineSegmentLength);
	glm::vec2 end = centrePoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resetPosition(){
	m_distanceToOrigin = 0;
}

void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact){
	glm::vec2 normal = this->getNormal();
	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / (1 / actor2->getMass());

	glm::vec2 force = normal * j;
	actor2->applyForce(force, contact - actor2->getPosition());
}