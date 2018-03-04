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

	m_physicsScene->addActor(new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(10, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(20, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(30, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1)));
	m_physicsScene->addActor(new Sphere(glm::vec2(40, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1)));
}