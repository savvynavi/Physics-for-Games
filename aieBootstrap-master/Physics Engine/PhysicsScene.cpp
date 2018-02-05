#include<iostream>

#include "PhysicsScene.h"
#include"PhysicsObject.h"
#include"Rigidbody.h""

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
	static std::list<PhysicsObject*> dirty;

	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while(accumulatedTime >= m_timeStep){
		for(auto pActor : m_actors){
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}

	//check for colisions
	for(auto pActor : m_actors){
		for(auto pOther : m_actors){
			if(pActor == pOther){
				continue;
			}
			if(std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() && std::find(dirty.begin(), dirty.end(), pOther) != dirty.end()){
				continue;
			}

			Rigidbody* pRigidbody = dynamic_cast<Rigidbody*>(pActor);
			if(pRigidbody->checkCollision(pOther) == true){
				pRigidbody->applyForceToActor(dynamic_cast<Rigidbody*>(pOther), pRigidbody->getVelocity() * pRigidbody->getMass());
				dirty.push_back(pRigidbody);
				dirty.push_back(pOther);
			}
		}
	}
	dirty.clear();
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