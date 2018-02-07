#pragma once
#include"Rigidbody.h"

class Plane : public PhysicsObject{
public:
	Plane();
	Plane(glm::vec2 normal, float distance);
	~Plane();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {}
	virtual void makeGizmo();
	virtual void resetPosition();
	
	glm::vec2 getNormal(){ return m_normal; }
	float getDistance() { return m_distanceToOrigin; }

	virtual bool collision(PhysicsObject* other);
	virtual bool sphereCollision(Sphere* other);
	virtual bool planeCollision(Plane* other) { return false; };
	//virtual bool collision(Box* other);
protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
};

