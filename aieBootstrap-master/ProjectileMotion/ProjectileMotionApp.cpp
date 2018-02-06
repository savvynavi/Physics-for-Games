#include "ProjectileMotionApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

ProjectileMotionApp::ProjectileMotionApp() {

}

ProjectileMotionApp::~ProjectileMotionApp() {

}

bool ProjectileMotionApp::startup() {
	
	aie::Gizmos::create(255U, 255U, 65536U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.01f);
	
	glm::vec2 startPosition(-40,0);
	setUpContinuourDemo(startPosition, 45.0f, 40.0f, -10.0f);

	return true;
}

void ProjectileMotionApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void ProjectileMotionApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ProjectileMotionApp::draw() {

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

void ProjectileMotionApp::setUpContinuourDemo(glm::vec2 startPos, float inclination, float speed, float gravity){
	float time = 0;
	float timeStep = 0.05f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
	float x0 = startPos.x;
	float y0 = startPos.y;
	aie::Gizmos::add2DCircle(glm::vec2(x0, y0), radius, segments, colour);

	while(time <= 5){
		//calc x, y pos of projectie at time 

		float x = x0 + (speed * time);
		float y = y0 + (speed * time) + (0.5f * gravity * time * time);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		time += timeStep;
	}
}