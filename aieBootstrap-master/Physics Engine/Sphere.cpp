#include "Sphere.h"
#include"Plane.h"
#include<Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, bool collisionOn, float linDrag = 0.3f, float angDrag = 0.3f) :
	Rigidbody(SPHERE, position, velocity, 0, mass, linDrag, angDrag), m_radius(radius), m_colour(colour), m_collisionOn(collisionOn){

}


Sphere::~Sphere(){
}

void Sphere::makeGizmo(){
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* other){
	if(m_collisionOn == false){
		return false;
	}

	Sphere* tmpOther = dynamic_cast<Sphere*>(other);
	//if the cast succeeded, do collision things
	if(tmpOther == nullptr){
		return false;
	}

	//if distance between them is less than combined radii, collision happens
	float distance = glm::distance(this->getPosition(), tmpOther->getPosition());
	if(distance <= (this->getRadius() + tmpOther->getRadius())){
		return true;
	} else{
		return false;
	}
}