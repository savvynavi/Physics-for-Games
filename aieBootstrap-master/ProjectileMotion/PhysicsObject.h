#pragma once
#include<glm\ext.hpp>

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
protected:
	ShapeType m_shapeID;
};