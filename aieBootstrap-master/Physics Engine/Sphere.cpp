#include "Sphere.h"
#include"Plane.h"
#include<Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, float elasticity, bool kinematic, float rotation, float linDrag, float angDrag) :
	Rigidbody(SPHERE, position, velocity, rotation, mass, elasticity, kinematic, linDrag, angDrag), m_radius(radius), m_colour(colour){
	this->setMoment(0.5f * m_mass * m_radius * m_radius);
}


Sphere::~Sphere(){
}

void Sphere::makeGizmo(){
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(0, 0, 0, 1));
}