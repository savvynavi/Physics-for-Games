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
	//dt *= 0.01f;
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
			//ignore joints/springs
			if(shapeId1 < 0 || shapeId2 < 0){
				continue;
			}

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
	float pen = 0;

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

			//pen calc
			glm::vec2 contF = collisionNorm * (sphereToPlane - sphere->getRadius());
			if(pen < sphereToPlane || pen > sphereToPlane){
				pen = sphereToPlane;
			}

			sphere->nudge(glm::vec2(pen * -contF));
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
	float pen = 0;

	//if dist between spheres less than combined radii, collision occurs
	if(sphere1 != nullptr && sphere2 != nullptr){
		float distance = glm::distance(sphere1->getPosition(), sphere2->getPosition());
		if(distance <= (sphere1->getRadius() + sphere2->getRadius())){
			glm::vec2 contact = 0.5f * (sphere1->getPosition() + sphere2->getPosition());
			sphere1->resolveCollision(sphere2, contact);

			//pen calc
			pen = distance - (sphere1->getRadius() + sphere2->getRadius());
			glm::vec2 norm = (sphere1->getPosition() - sphere2->getPosition()) / distance;
			glm::vec2 contactForce = pen * norm;

			if(sphere1->isKinematic() == false && sphere2->isKinematic() == false){
				sphere1->nudge(-contactForce * 0.5f);
				sphere2->nudge(contactForce * 0.5f);
			} else if(sphere1->isKinematic() == false){
				sphere1->nudge(-contactForce);
			} else{
				sphere2->nudge(contactForce);
			}
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
	float pen = 0;

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
				float velocityIntoPlane = glm::dot(box->getVelocity() + box->getAngularVelocity() * (-y * box->getLocalX() + x* box->getLocalY()), plane->getNormal());

				//if this corner on opp side of COM and continuting that way, need to resolve collision
				if( (distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) || (distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0)){
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;

					//calc penetration of box into plane
					if(comFromPlane >= 0){
						if(pen > distFromPlane || pen < distFromPlane){
							pen = distFromPlane;
						}
					}
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
			
			box->nudge(glm::vec2(pen * -plane->getNormal()));

			//apply force
			box->applyForce(acceleration * mass0, localContact);
			//return true;
		}
	}
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2){
	Box* box = dynamic_cast<Box*> (obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);
	float pen = 0;

	if(box != nullptr && sphere != nullptr){
		glm::vec2 circlePos = sphere->getPosition() - box->getPosition();
		float halfWidth = box->getWidth() / 2;
		float halfHeight = box->getHeight() / 2;

		int numContacts = 0;
		glm::vec2 contact(0, 0);

		//check 4 corners to see if any are inside the circle
		for(float x = -halfWidth; x <= halfWidth; x += box->getWidth()){
			for(float y = -halfHeight; y <= halfHeight; y += box->getHeight()){
				glm::vec2 p = x * box->getLocalX() + y * box->getLocalY();
				glm::vec2 dp = p - circlePos;
				if(dp.x * dp.x + dp.y * dp.y < sphere->getRadius() * sphere->getRadius()){
					numContacts++;
					contact += glm::vec2(x, y);
					pen = sphere->getRadius() - glm::length(dp);
				}
			}
		}
		glm::vec2* direction = nullptr;
		//get local pos of the circle
		glm::vec2 localPos(glm::dot(box->getLocalX(), circlePos), glm::dot(box->getLocalY(), circlePos));
		if(localPos.y < halfHeight && localPos.y > -halfHeight){
			if(localPos.x > 0 && localPos.x < halfWidth + sphere->getRadius()){
				numContacts++;
				contact += glm::vec2(halfWidth, localPos.y);
				direction = new glm::vec2(box->getLocalX());
				pen = halfWidth + sphere->getRadius() - localPos.x;
			}
			if(localPos.x < 0 && localPos.x > -(halfWidth + sphere->getRadius())){
				numContacts++;
				contact += glm::vec2(-halfWidth, localPos.y);
				direction = new glm::vec2(-box->getLocalX());
				pen = (halfWidth + sphere->getRadius()) + localPos.x;
			}
		}
		if(localPos.x < halfWidth && localPos.x > -halfWidth){
			if(localPos.y > 0 && localPos.y < halfHeight + sphere->getRadius()){
				numContacts++;
				contact += glm::vec2(localPos.x, halfHeight);
				direction = new glm::vec2(box->getLocalY());
				pen = halfHeight + sphere->getRadius() - localPos.y;
			}
			if(localPos.y < 0 && localPos.y > -(halfHeight + sphere->getRadius())){
				numContacts++;
				contact += glm::vec2(localPos.x, -halfHeight);
				direction = new glm::vec2(-box->getLocalY());
				pen = (halfHeight + sphere->getRadius()) + localPos.y;
			}
		}

		//averaging contact points, collision resolution in here
		if(numContacts > 0){
			contact = box->getPosition() + (1.0f / numContacts) * (box->getLocalX() * contact.x + box->getLocalY() * contact.y);
			box->resolveCollision(sphere, contact, direction);
			
			//pen calc
			glm::vec2 disp = sphere->getPosition() - box->getPosition();
			float magDisp = sqrtf(disp.x * disp.x + disp.y * disp.y);
			//if touching And direction has been set
			if(magDisp > 0 && direction != nullptr){
				//kinematic alterations, if one or other isKinematic, apply nudge to only other moving actor
				glm::vec2 nudgeVec = pen * *direction;

				if(box->isKinematic() == false && sphere->isKinematic() == false){
					box->nudge(-nudgeVec * 0.5f);
					sphere->nudge(nudgeVec * 0.5f);
				}else if(box->isKinematic() == false){
					box->nudge(-nudgeVec);
				}else{
					sphere->nudge(nudgeVec);
				}
			}
		}
		delete direction;
	}
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject* obj1, PhysicsObject* obj2){
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if(box1 != nullptr && box2 != nullptr){
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);
		float pen = 0;
		int numContacts = 0;

		box1->checkBoxCorners(*box2, contact, numContacts, pen, norm);
		if(box2->checkBoxCorners(*box1, contact, numContacts, pen, norm) == true){
			norm = -norm;
		}
		if(pen > 0){
			box1->resolveCollision(box2, contact / (float)numContacts, &norm);
			glm::vec2 disp = pen * norm;

			//kinematic code
			if(box1->isKinematic() == false && box2->isKinematic() == false){
				box1->nudge(-disp * 0.5f);
				box2->nudge(disp * 0.5f);
			} else if(box1->isKinematic() == false){
				box1->nudge(-disp);
			} else{
				box2->nudge(disp);
			}

		}
		return true;
	}
	return false;
}