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
	m_physicsScene->setTimestep(0.001f);
	m_physicsScene->setGravity(glm::vec2(0, -10));

	m_sm = new StateManager(4);
	m_pinball = new Pinball(m_physicsScene, m_sm, m_2dRenderer, m_font);
	m_mainMenu = new MainMenu(m_2dRenderer, m_sm, m_font, this);
	m_demo = new Demo(m_sm, m_physicsScene);
	m_cradle = new NewtonsCradle(m_sm, m_physicsScene);

	m_sm->registerState(PINBALL, m_pinball);
	m_sm->registerState(MAIN_MENU, m_mainMenu);
	m_sm->registerState(PHYS_DEMO, m_demo);
	m_sm->registerState(CRADLE, m_cradle);
	m_sm->pushState(MAIN_MENU);

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

	//mouseToWorld();

	m_sm->update(deltaTime);

}

void Physics_EngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_sm->draw();
	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// done drawing sprites
	m_2dRenderer->end();
}