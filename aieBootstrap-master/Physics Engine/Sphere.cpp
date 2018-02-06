#include "Sphere.h"
#include<Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, bool collisionOn) : 
	Rigidbody(SPHERE, position, velocity, 0, mass), m_radius(radius), m_colour(colour), m_collisionOn(collisionOn){

}


Sphere::~Sphere(){
}

void Sphere::makeGizmo(){
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* other){
	return other->sphereCollision(this);
}

void Sphere::collision(PhysicsObject* other){
	other->sphereCollision(this);
}

bool Sphere::sphereCollision(Sphere* other){
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

bool Sphere::planeCollision(Plane* other){
	return false;
}

//do when box class done
//bool Sphere::collision(Box* other){
//
//}