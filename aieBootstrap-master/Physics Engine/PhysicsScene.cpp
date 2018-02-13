#include<iostream>

#include "PhysicsScene.h"
#include"PhysicsObject.h"
#include"Rigidbody.h"
#include"Sphere.h"
#include"Plane.h"
#include"Box.h"

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
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2Box,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2Box,
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2Box
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

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2){
	return box2Plane(obj2, obj1);
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
		if(intersection > 0){
			glm::vec2 contact = sphere->getPosition() + (collisionNorm * (-sphere->getRadius()));
			plane->resolveCollision(sphere, contact);
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
			glm::vec2 contact = 0.5f * (sphere1->getPosition() + sphere2->getPosition());
			sphere1->resolveCollision(sphere2, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2){
	return box2Sphere(obj2, obj1);
}

bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2){
	Box* box = dynamic_cast<Box*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);

	if(box != nullptr && plane != nullptr){
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5 * std::fminf(box->getWidth(), box->getHeight());

		//checks which side the centre of mass is on
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();
		float comFromPlane = glm::dot(box->getPosition() - planeOrigin, plane->getNormal());

		//checks all 4 corners to see if we've hit a plane
		for(float x = -box->getExtents().x; x < box->getWidth(); x += box->getWidth()){
			for(float y = -box->getExtents().y; y < box->getHeight(); y += box->getHeight()){
				//get pos of the corner in world space
				glm::vec2 p = box->getPosition() + x * box->getLocalX() + y * box->getLocalY();

				float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());

				//total velocity of the point
				float velocityIntoPlane = glm::dot(box->getVelocity() + box->getAngularDrag() * (-y * box->getLocalX() + x* box->getLocalY()), plane->getNormal());

				//if this corner on opp side of COM and continuting that way, need to resolve collision
				if( (distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) || (distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0)){
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		//if there's been a hit, get average collision velocity into plane, get acc needed to stop/reverse, and average pos at which to apply force
		if(numContacts > 0){
			float collisionV = contactV / (float)numContacts;
			glm::vec2 acceleration = -plane->getNormal() * ((1.0f + box->getElasticity()) * collisionV);
			glm::vec2 localContact = (contact / (float)numContacts) - box->getPosition();

			float r = glm::dot(localContact, glm::vec2(plane->getNormal().y, -plane->getNormal().x));
			float mass0 = 1.0f / (1.0f / box->getMass() + (r * r) / box->getMoment());

			//apply force
			box->applyForce(acceleration * mass0, localContact);
			//return true;
		}
	}
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2){
	return false;
}