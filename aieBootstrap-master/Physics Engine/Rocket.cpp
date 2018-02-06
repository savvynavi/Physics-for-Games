#include "Rocket.h"

Rocket::Rocket(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour, PhysicsScene* physScene) :
	Sphere(position, velocity, mass, radius, colour, false), m_physScene(physScene){
	m_input = aie::Input::getInstance();
}


Rocket::~Rocket(){

}

void Rocket::fixedUpdate(glm::vec2 gravity, float timeStep){
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;

	//rocket stuff
	if(m_input->isKeyDown(aie::INPUT_KEY_SPACE)){
		if(this->getMass() > 5.0f){
			this->setMass(this->getMass() - 0.04f);
			Sphere* tmpParticle = new Sphere(glm::vec2(this->getPosition().x, this->getPosition().y - this->getRadius() - 1.01f), glm::vec2(0, 0), 2.0f, 1, glm::vec4(1, 0, 1, 0.5f), false);
			m_physScene->addActor(tmpParticle);
			this->applyForceToActor(tmpParticle, glm::vec2(0, -5));
		}
	}
}