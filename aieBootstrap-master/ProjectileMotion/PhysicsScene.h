#pragma once
#include<glm\ext.hpp>
#include<list>

class PhysicsObject;

class PhysicsScene{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimestep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }
protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::list<PhysicsObject*> m_actors;
};

