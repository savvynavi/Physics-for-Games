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
	aie::Gizmos::add2DCircle(m_position, 1, 12, glm::vec4(1, 1, 1, 1));
}

bool Box::checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& penetration, glm::vec2& edgeNorm){
	float minX, maxX, minY, maxY;
	float boxW = box.getWidth();
	float boxH = box.getHeight();
	int numLocatContacts = 0;
	glm::vec2 localContact(0, 0);

	bool first = true;
	for(float x = -box.getExtents().x; x < boxW; x += boxW){
		for(float y = -box.getExtents().y; y < boxH; y += boxH){
			//pos in worldspace(changed getCentre to getPosition, should be same thing)
			glm::vec2 p = box.getPosition() + x * box.getLocalX() + y * box.getLocalY();
			//pos in our boxs space
			glm::vec2 p0(glm::dot(p - box.getPosition(), box.getLocalX()), glm::dot(p - box.getPosition(), box.getLocalY()));

			if(first == true || p0.x < minX){
				minX = p0.x;
			}
			if(first == true || p0.x > maxX){
				maxX = p0.x;
			}
			if(first == true || p0.y < minY){
				minY = p0.y;
			}
			if(first == true || p0.y > maxY){
				maxY = p0.y;
			}

			if(p0.x >= -box.getExtents().x && p0.x <= box.getExtents().x && p0.y >= -box.getExtents().y && p0.y <= box.getExtents().y){
				numLocatContacts++;
				localContact += p0;
			}
			first = false;
		}
	}

	if(maxX < -box.getExtents().x || minX > box.getExtents().x || maxY < -box.getExtents().y || minY > box.getExtents().y){
		return false;
	}
	if(numLocatContacts == 0){
		return false;
	}
	bool res = false;

	contact += box.getPosition() + (localContact.x * box.getLocalX() + localContact.y * box.getLocalY()) / (float)numLocatContacts;
	numContacts++;

	float pen0 = box.getExtents().x - minX;
	if(pen0 > 0 && (pen0 < penetration || penetration == 0)){
		edgeNorm = box.getLocalX();
		penetration = pen0;
		res = true;
	}

	pen0 = maxX + box.getExtents().x;
	if(pen0 > 0 && (pen0 < penetration || penetration == 0)){
		edgeNorm = -box.getLocalX();
		penetration = pen0;
		res = true;
	}

	pen0 = box.getExtents().y - minY;
	if(pen0 > 0 && (pen0 < penetration || penetration == 0)){
		edgeNorm = box.getLocalY();
		penetration = pen0;
		res = true;
	}

	pen0 = maxY + box.getExtents().y;
	if(pen0 > 0 && (pen0 < penetration || penetration == 0)){
		edgeNorm = -box.getLocalY();
		penetration = pen0;
		res = true;
	}
	return res;
}