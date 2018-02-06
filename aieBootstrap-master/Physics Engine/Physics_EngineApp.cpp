#include "Physics_EngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include<Gizmos.h>

Physics_EngineApp::Physics_EngineApp() {

}

Physics_EngineApp::~Physics_EngineApp() {

}

bool Physics_EngineApp::startup() {
	//increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65536U, 65535U);


	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimestep(0.1f);

	//m_plane = new Plane();

	Sphere* ball1 = new Sphere(glm::vec2(-4, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1), true);
	Sphere* ball2 = new Sphere(glm::vec2(4, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1), true);
	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	ball1->applyForceToActor(ball2, glm::vec2(2, 0));

	return true;
}

void Physics_EngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Physics_EngineApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Physics_EngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}