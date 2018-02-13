#include "Box.h"
#include<Gizmos.h>



Box::Box(glm::vec2 position, glm::vec2 velocity, float mass, float width, float height, glm::vec4 colour, float linDrag, float angDrag) : 
	Rigidbody(BOX, position, velocity, 0, mass, linDrag, angDrag), m_width(width), m_height(height), m_colour(colour), m_extents(width / 2, height / 2){
	this->setMoment(1.0f / 12.0f * m_mass * width * height);
}


Box::~Box(){

}

void Box::fixedUpdate(glm::vec2 gravity, float timestep){
	Rigidbody::fixedUpdate(gravity, timestep);

	//store local axes
	float cosine = cosf(m_rotation);
	float sine = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cosine, sine));
	m_localY = glm::normalize(glm::vec2(-sine, cosine));
}

void Box::makeGizmo(){
	glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}