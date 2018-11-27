#include "NewtonsCradle.h"
#include"StateManager.h"
#include"Plane.h"
#include"Sphere.h"
#include"Box.h"

NewtonsCradle::NewtonsCradle(StateManager* sm, PhysicsScene* physScene) : 
	m_sm(sm), m_physicsScene(physScene){
	m_input = aie::Input::getInstance();

}

NewtonsCradle::~NewtonsCradle(){

}

void NewtonsCradle::onUpdate(float timeStep){
	m_physicsScene->update(timeStep);

	//change state back to main menu is escape pressed
	if(m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)){
		onExit();
		m_sm->popState();
		m_sm->pushState(MAIN_MENU);
	}
}

void NewtonsCradle::onDraw(){
	m_physicsScene->updateGizmos();
}

//resets all the objects when entering
void NewtonsCradle::onEnter(){
	setup();
}

//deletes all objects when exiting
void NewtonsCradle::onExit(){
	m_physicsScene->clearAllActors();
}

void NewtonsCradle::setup(){
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->addActor(new Plane(glm::vec2(-1, 0), 5));
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), 50));
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), -70));

	//right set
	m_physicsScene->addActor(new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(10, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.95, 0.77, 0.05, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(20, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(30, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.95, 0.77, 0.05, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(40, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));

	//left set
	m_physicsScene->addActor(new Sphere(glm::vec2(-10, -20), glm::vec2(20, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-20, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.95, 0.77, 0.05, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-30, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-40, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.95, 0.77, 0.05, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-50, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.88, 0.35, 0.59, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(-60, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.95, 0.77, 0.05, 1)));
}