#include<iostream>

#include "PhysicsScene.h"
#include"PhysicsObject.h"
#include"Rigidbody.h"
#include"Sphere.h"
#include"Plane.h"

PhysicsScene::PhysicsScene(){
	m_timeStep = 0.01f;
	m_gravity = {0, 0};
}


PhysicsScene::~PhysicsScene(){
	for(auto pActor : m_actors){
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor){
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor){
	//removes the actor from list
	m_actors.remove(actor);
}

void PhysicsScene::update(float dt){
	
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while(accumulatedTime >= m_timeStep){
		for(auto pActor : m_actors){
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}

	//check for colisions (turn off for rocket part)
	checkForCollision();
}

void PhysicsScene::updateGizmos(){
	for(auto pActor : m_actors){
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene(){
	int count = 0;
	for(auto pActor : m_actors){
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = {
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere
};

void PhysicsScene::checkForCollision(){
	int actorCount = m_actors.size();

	//need to check for collisions against all objects except this one?????????
	//can't grab list elements easily, adding iterators to get around this
	auto oneBeforeEnd = m_actors.end();
	std::advance(oneBeforeEnd, -1);
	for(auto outer = m_actors.begin(); outer != oneBeforeEnd; outer++){
		auto oneAfterStart = outer;
		std::advance(oneAfterStart, 1);
		for(auto inner = oneAfterStart; inner != m_actors.end(); inner++){
			PhysicsObject* object1 = *outer;
			PhysicsObject* object2 = *inner;
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			//using fn pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if(collisionFunctionPtr != nullptr){
				//checks if collision occured
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2){
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2){
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if(sphere != nullptr && plane != nullptr){
		glm::vec2 collisionNorm = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		//if behind plane flip normal
		if(sphereToPlane < 0){
			collisionNorm *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if(intersection >= 0){
			plane->resolveCollision(sphere);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	//if dist between spheres less than combined radii, collision occurs
	if(sphere1 != nullptr && sphere2 != nullptr){
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if(distance <= (sphere1->getRadius() + sphere2->getRadius())){
			sphere1->resolveCollision(sphere2);
			return true;
		}
	}
	return false;
}