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

	//cradleSetUp();
	//frictionExampleSetup();
	//boxTest();
	//contactForceTest();
	springTest();
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

//sets up a newtons cradle
void Physics_EngineApp::cradleSetUp(){
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimestep(0.001f);

	m_plane1 = new Plane(glm::vec2(-1, 0), 5);
	m_plane2 = new Plane(glm::vec2(1, 0), 50);

	m_ball1 = new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1), 0, 0, 0);
	m_ball2 = new Sphere(glm::vec2(10, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1), 0, 0, 0);
	m_ball3 = new Sphere(glm::vec2(20, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1), 0, 0, 0);
	m_ball4 = new Sphere(glm::vec2(30, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1), 0, 0, 0);
	m_ball5 = new Sphere(glm::vec2(40, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1), 0, 0, 0);

	m_physicsScene->addActor(m_ball1);
	m_physicsScene->addActor(m_ball2);
	m_physicsScene->addActor(m_ball3);
	m_physicsScene->addActor(m_ball4);
	m_physicsScene->addActor(m_ball5);
	
	m_physicsScene->addActor(m_plane1);
	m_physicsScene->addActor(m_plane2);

}

//test for friction (change lin/ang drag from 0 to get drag effects)
void Physics_EngineApp::frictionExampleSetup(){
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimestep(0.01f);

	m_plane1 = new Plane(glm::vec2(-0.5f, -0.5f), 5);
	m_plane2 = new Plane(glm::vec2(1, 0), 50);
	m_plane3 = new Plane(glm::vec2(0, 1), 30);

	m_ball1 = new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 2, glm::vec4(0.75f, 0, 1, 1), 0, 0.3f, 0.3f);
	m_ball2 = new Sphere(glm::vec2(10, 15), glm::vec2(-5, 10), 4.0f, 4, glm::vec4(1, 0.5f, 0, 1), 0, 0.3f, 0.3f);
	m_ball3 = new Sphere(glm::vec2(20, 15), glm::vec2(-20, 50), 4.0f, 8, glm::vec4(1, 1, 0, 1), 0, 0.3f, 0.3f);

	m_box1 = new Box(glm::vec2(5, 20), glm::vec2(0, -10), 16.0f, 5, 5, glm::vec4(1, 0, 1, 1), 0, 0);

	m_physicsScene->addActor(m_ball1);
	m_physicsScene->addActor(m_ball2);
	m_physicsScene->addActor(m_ball3);

	m_physicsScene->addActor(m_plane1);
	m_physicsScene->addActor(m_plane2);
	m_physicsScene->addActor(m_plane3);

	m_physicsScene->addActor(m_box1);

}

void Physics_EngineApp::boxTest(){
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.001f);

	m_box1 = new Box(glm::vec2(0, 20), glm::vec2(0, -10), 16.0f, 10, 10, glm::vec4(1, 0, 1, 1), 0, 0);
	m_box2 = new Box(glm::vec2(0, -5), glm::vec2(0, 0), 16.0f, 10, 10, glm::vec4(0.75f, 0, 1, 1), 0, 0);
	
	m_box3 = new Box(glm::vec2(-20, 0), glm::vec2(10, 0), 16.0f, 10, 10, glm::vec4(1, 0, 1, 1), 0, 0);
	m_box4 = new Box(glm::vec2(20, 0), glm::vec2(-10, 0), 16.0f, 10, 10, glm::vec4(0.75f, 0, 1, 1), 0, 0);

	m_ball1 = new Sphere(glm::vec2(30, 15), glm::vec2(-10, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0, 0, 0);

	m_plane1 = new Plane(glm::vec2(0, 1), -10);

	m_physicsScene->addActor(m_box1);
	m_physicsScene->addActor(m_box2);
	//m_physicsScene->addActor(m_box3);
	//m_physicsScene->addActor(m_box4);

	//m_physicsScene->addActor(m_ball1);
	m_physicsScene->addActor(m_plane1);
}

void Physics_EngineApp::contactForceTest(){
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.001f);

	m_box1 = new Box(glm::vec2(0, 0), glm::vec2(0, 0), 16.0f, 5, 5, glm::vec4(1, 0, 1, 1), 0, 0);
	m_box2 = new Box(glm::vec2(0, 10), glm::vec2(0, 0), 16.0f, 5, 5, glm::vec4(0.75f, 0, 1, 1), 0, 0);
	m_box3 = new Box(glm::vec2(0, 40), glm::vec2(0, 0), 16.0f, 5, 5, glm::vec4(1, 0, 1, 1), 0, 0);

	m_box4 = new Box(glm::vec2(-20, 0), glm::vec2(0, 0), 16.0f, 5, 5, glm::vec4(1, 0, 1, 1), 0, 0);
	m_box5 = new Box(glm::vec2(-20, 20), glm::vec2(0, 0), 16.0f, 5, 5, glm::vec4(0, 1, 0.5f, 1), 0, 0);


	m_ball1 = new Sphere(glm::vec2(1, 20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0, 0, 0);
	m_ball2 = new Sphere(glm::vec2(0, 30), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 1, 1), 0, 0, 0);
	
	m_ball3 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 1, 1), 0, 0, 0);
	m_ball4 = new Sphere(glm::vec2(20, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 1, 1), 0, 0, 0);
	
	m_ball5 = new Sphere(glm::vec2(-20, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 1, 1), 0, 0, 0);

	m_ball1->setKinematic(true);
	m_box4->setKinematic(true);

	m_plane1 = new Plane(glm::vec2(0, 1), -30);

	m_physicsScene->addActor(m_box1);
	m_physicsScene->addActor(m_box2);
	m_physicsScene->addActor(m_box3);
	m_physicsScene->addActor(m_box4);
	m_physicsScene->addActor(m_box5);

	m_physicsScene->addActor(m_ball1);
	m_physicsScene->addActor(m_ball2);
	m_physicsScene->addActor(m_ball3);
	m_physicsScene->addActor(m_ball4);
	m_physicsScene->addActor(m_ball5);


	m_physicsScene->addActor(m_plane1);
}

void Physics_EngineApp::springTest(){
	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.01f);

	int startX = -50;
	Sphere* ball1;
	Sphere* ball2;

	ball1 = new Sphere(glm::vec2(startX, 40), glm::vec2(0, 0), 1.0f, 2, glm::vec4(0, 1, 1, 1), 0, 0.3f, 0);
	ball1->setKinematic(true);
	m_physicsScene->addActor(ball1);
	int numBalls = 10;

	for(int i = 0; i < numBalls; i++){
		ball2 = new Sphere(glm::vec2(startX + (i * 6), 40), glm::vec2(0, 0), 1.0f, 2, glm::vec4(0, 1, 1, 1), 0, 0.3f, 0);
		m_physicsScene->addActor(ball2);
		m_physicsScene->addActor(new Spring(ball1, ball2, 5, 10, 0.1f));
		ball1 = ball2;
		//if( i == 9){
		//	ball1->setKinematic(true);
		//}
	}


	//make spheres
	//for(int x = 0; x <= width; x++){
	//	for(int y = 0; y <= height; y++){
	//		sphere = new Sphere(glm::vec2(x * 5, y * 5), glm::vec2(0, 0), 4.0f, 1, glm::vec4(1, 0, 1, 1), 0, 0, 0);
	//		m_physicsScene->addActor(sphere);
	//		m_physicsScene->addActor(new Spring());
	//	}
	//}

	//m_plane1 = new Plane(glm::vec2(0, 1), -10);
	//m_physicsScene->addActor(m_plane1);
}