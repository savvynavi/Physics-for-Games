#pragma once
#include<glm\ext.hpp>

class Sphere;
class Plane;
//class Box;

enum ShapeType{
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject{
protected:
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition(){};
	virtual ShapeType getShapeID(){ return m_shapeID; }
protected:
	ShapeType m_shapeID;
};