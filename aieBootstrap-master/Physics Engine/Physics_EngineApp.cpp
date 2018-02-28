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
	m_physicsScene->setTimestep(0.01f);
	m_physicsScene->setGravity(glm::vec2(0, -10));

	m_sm = new StateManager(2);
	m_pinball = new Pinball(m_physicsScene, m_sm, m_font);
	m_mainMenu = new MainMenu(m_2dRenderer, m_sm, m_font, this);

	m_sm->registerState(PINBALL, m_pinball);
	m_sm->registerState(MAIN_MENU, m_mainMenu);
	m_sm->pushState(PINBALL);


	m_mousePos = glm::vec2();

	//cradleSetUp();
	//frictionExampleSetup();
	//contactForceTest();
	//springTest();
	//pool();
	//pinball();
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

	//m_physicsScene->update(deltaTime); 
	//m_physicsScene->updateGizmos();


	//adds box to scene at point clicked
	//if(input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)){
	//	m_physicsScene->addActor(new Box(m_mouseWorldCoord, glm::vec2(0, 0), 0, 5.0f, 4, 4, glm::vec4(0, 0, 1, 1), 0, 0));
	//}
}

void Physics_EngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();


	m_sm->draw();
	// draw your stuff here!
	static float aspectRatio = 16 / 9.0f;
	//draws circle at mousepoint
	//aie::Gizmos::add2DCircle(m_mouseWorldCoord, 1, 16, glm::vec4(1, 1, 1, 1));

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

//converts mouseposition into screen coordinates
void Physics_EngineApp::mouseToWorld(){
	aie::Input* input = aie::Input::getInstance();
	input->getMouseXY(&m_mouseX, &m_mouseY);

	glm::vec2 screenSize(1280, 720);
	float scale = 200 / screenSize.x;
	m_mouseWorldCoord = glm::vec2(m_mouseX - screenSize.x / 2, m_mouseY - screenSize.y / 2);
	m_mouseWorldCoord *= scale;
}

//sets up a newtons cradle
void Physics_EngineApp::cradleSetUp(){
	//m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimestep(0.001f);

	m_plane1 = new Plane(glm::vec2(-1, 0), 5);
	m_plane2 = new Plane(glm::vec2(1, 0), 50);

	m_ball1 = new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1));
	m_ball2 = new Sphere(glm::vec2(10, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	m_ball3 = new Sphere(glm::vec2(20, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1));
	m_ball4 = new Sphere(glm::vec2(30, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 0, 1));
	m_ball5 = new Sphere(glm::vec2(40, 15), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 1, 0, 1));

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
	//m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, 0));
	m_physicsScene->setTimestep(0.01f);

	m_plane1 = new Plane(glm::vec2(-0.5f, -0.5f), 5);
	m_plane2 = new Plane(glm::vec2(1, 0), 50);
	m_plane3 = new Plane(glm::vec2(0, 1), 30);

	m_ball1 = new Sphere(glm::vec2(0, 15), glm::vec2(10, 0), 4.0f, 2, glm::vec4(0.75f, 0, 1, 1), 0.9f, false, 0, 0.3f, 0.3f);
	m_ball2 = new Sphere(glm::vec2(10, 15), glm::vec2(-5, 10), 4.0f, 4, glm::vec4(1, 0.5f, 0, 1), 0.9f, false, 0, 0.3f, 0.3f);
	m_ball3 = new Sphere(glm::vec2(20, 15), glm::vec2(-20, 50), 4.0f, 8, glm::vec4(1, 1, 0, 1), 0.9f, false, 0, 0.3f, 0.3f);

	m_box1 = new Box(glm::vec2(5, 20), glm::vec2(0, -10), 0, 16.0f, 5, 5, glm::vec4(1, 0, 1, 1));

	m_physicsScene->addActor(m_ball1);
	m_physicsScene->addActor(m_ball2);
	m_physicsScene->addActor(m_ball3);

	m_physicsScene->addActor(m_plane1);
	m_physicsScene->addActor(m_plane2);
	m_physicsScene->addActor(m_plane3);

	m_physicsScene->addActor(m_box1);

}

void Physics_EngineApp::contactForceTest(){
	//m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.001f);

	m_box1 = new Box(glm::vec2(0, 0), glm::vec2(0, 0), 0, 16.0f, 5, 5, glm::vec4(1, 0, 1, 1));
	m_box2 = new Box(glm::vec2(0, 10), glm::vec2(0, 0), 0, 16.0f, 5, 5, glm::vec4(0.75f, 0, 1, 1));
	m_box3 = new Box(glm::vec2(0, 40), glm::vec2(0, 0), 0, 16.0f, 5, 5, glm::vec4(1, 0, 1, 1));

	m_box4 = new Box(glm::vec2(-20, 0), glm::vec2(0, 0), 0, 16.0f, 5, 5, glm::vec4(1, 0, 1, 1), 0.9f, true);
	m_box5 = new Box(glm::vec2(-20, 20), glm::vec2(0, 0), 0, 16.0f, 5, 5, glm::vec4(0, 1, 0.5f, 1));


	m_ball1 = new Sphere(glm::vec2(1, 20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0.9f, true);
	m_ball2 = new Sphere(glm::vec2(0, 30), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 1, 1));
	
	m_ball3 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 1, 1));
	m_ball4 = new Sphere(glm::vec2(20, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 1, 1));
	
	m_ball5 = new Sphere(glm::vec2(-20, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 1, 1, 1));

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
	//m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.001f);

	//bridge
	int startX = -50;
	Sphere* ball1;
	Sphere* ball2;

	m_plane1 = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->addActor(m_plane1);

	//ball1 = new Sphere(glm::vec2(startX, 40), glm::vec2(0, 0), 1.0f, 2, glm::vec4(0, 1, 1, 1), 0, 0.3f, 0);
	//ball1->setKinematic(true);
	//m_physicsScene->addActor(ball1);
	//int numBalls = 10;

	//for(int i = 1; i < numBalls; i++){
	//	ball2 = new Sphere(glm::vec2(startX + (i * 6.0f), 40), glm::vec2(0, 0), 1.0f, 2, glm::vec4(0, 1, 1, 1), 0, 0.3f, 0);
	//	m_physicsScene->addActor(ball2);
	//	m_physicsScene->addActor(new Spring(ball1, ball2, 0, 10, 0.1f));
	//	ball1 = ball2;
	//	if(i == 9){
	//		ball1->setKinematic(true);
	//	}
	//}

	//softbody
	const int width = 5;
	const int height = 5;
	Sphere* spheres[width][height];
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			spheres[i][j] = new Sphere(glm::vec2((i * 3.0f), (j * 3.0f)), glm::vec2(0, 0), 5.0f, 1, glm::vec4(0, 1, 1, 1));
			m_physicsScene->addActor(spheres[i][j]);
		}
	}

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			float length = 0;
			float springCoef = 10;
			//horizontal springs
			if(i < width - 1){
				m_physicsScene->addActor(new Spring(spheres[i][j], spheres[i + 1][j], length, springCoef, 0.1f));
			}
			//vertical springs
			if(j < height - 1){
				m_physicsScene->addActor(new Spring(spheres[i][j], spheres[i][j + 1], length, springCoef, 0.1f));
			}
			//diagonal springs
			if(i < width - 1 && j < height - 1){
				m_physicsScene->addActor(new Spring(spheres[i][j], spheres[i + 1][j + 1], length, springCoef, 0.1f));
				m_physicsScene->addActor(new Spring(spheres[i][j + 1], spheres[i + 1][j], length, springCoef, 0.1f));
			}
			//bend springs
			if(i < width - 2){
				m_physicsScene->addActor(new Spring(spheres[i][j], spheres[i + 2][j], length, springCoef, 0.1f));
			}
			if(j < height - 2){
				m_physicsScene->addActor(new Spring(spheres[i][j], spheres[i][j + 2], length, springCoef, 0.1f));
			}
		}
	}

}

void Physics_EngineApp::pool(){

}

void Physics_EngineApp::pinball(){
	//m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimestep(0.01f);

	//m_pinball = new Pinball(m_physicsScene);

	////bumper test, setting elasticity to 10 pushes back ball with more force than it had on collision
	//m_ball1 = new Sphere(glm::vec2(1, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0, 0, 0);
	//m_ball1->setKinematic(true);
	//m_physicsScene->addActor(m_ball1);
	//m_ball1->setElasticity(10);

	//m_ball3 = new Sphere(glm::vec2(10, 30), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0, 0, 0);
	//m_ball3->setKinematic(true);
	//m_physicsScene->addActor(m_ball3);
	//m_ball3->setElasticity(10);

	////test ball
	//m_ball2 = new Sphere(glm::vec2(3, 30), glm::vec2(0, 0), 5.0f, 4, glm::vec4(0.75f, 0, 1, 1), 0, 0, 0);
	//m_physicsScene->addActor(m_ball2);
	//m_ball2->setElasticity(0.9f);
}