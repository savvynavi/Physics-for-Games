#pragma once
#include<glm\ext.hpp>

class Sphere;
class Plane;
//class Box;

enum ShapeType{
	PLANE = 0,
	SPHERE,
	BOX
};

class PhysicsObject{
protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition(){};

	virtual void collision(PhysicsObject* other) = 0;
	virtual bool sphereCollision(Sphere* other) = 0;
	virtual bool planeCollision(Plane* other) = 0;
	//virtual bool collision(Box* other) = 0;
protected:
	ShapeType m_shapeID;
};