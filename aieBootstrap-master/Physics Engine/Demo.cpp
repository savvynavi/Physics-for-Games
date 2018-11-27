#include "Demo.h"
#include"StateManager.h"


Demo::Demo(StateManager* sm, PhysicsScene* physScene) : 
	m_sm(sm), m_physicsScene(physScene){
	m_input = aie::Input::getInstance();
}


Demo::~Demo(){

}

void Demo::onUpdate(float timeStep){
	m_physicsScene->update(timeStep);
	drawAtMouse();


	//change state back to main menu is escape pressed
	if(m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)){
		onExit();
		m_sm->popState();
		m_sm->pushState(MAIN_MENU);
	}else if(m_input->wasKeyPressed(aie::INPUT_KEY_R)){
		reset();
	}
}

void Demo::onDraw(){
	m_physicsScene->updateGizmos();
}

//resets all the objects when entering
void Demo::onEnter(){
	m_physicsScene->setGravity(glm::vec2(0, -10));
	startup();
}

//deletes all objects when exiting
void Demo::onExit(){
	m_physicsScene->clearAllActors();
}

//resets the scene
void Demo::reset(){
	onExit();
	onEnter();
}

//sets up the scene
void Demo::startup(){
	m_physicsScene->addActor(new Plane(glm::vec2(0, 1), -30));
	m_physicsScene->addActor(new Plane(glm::vec2(0.75f, -0.5f), 70));
	m_physicsScene->addActor(new Plane(glm::vec2(0.75f, 0.5f), -70));

	//creating a soft body 
	const int width = 5;
	const int height = 5;
	Sphere* spheres[width][height];
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			spheres[i][j] = new Sphere(glm::vec2((i * 3.0f), (j * 3.0f)), glm::vec2(0, 0), 5.0f, 1, glm::vec4(0.55, 0, 0.55, 1));
			m_physicsScene->addActor(spheres[i][j]);
		}
	}

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			float length = 0; 
			float springCoef = 100;
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

	//rope bridge
	int startX = -30;
	Sphere* ball1;
	Sphere* ball2;
	ball1 = new Sphere(glm::vec2(startX, 40), glm::vec2(0, 0), 1.0f, 1, glm::vec4(0.88, 0.35, 0.59, 1), 0.9f, true);
	m_physicsScene->addActor(ball1);
	int numBalls = 20;

	for(int i = 1; i < numBalls; i++){
		ball2 = new Sphere(glm::vec2(startX + (i * 2.0f), 40), glm::vec2(0, 0), 1.0f, 1, glm::vec4(0.88, 0.35, 0.59, 1), 0.9f, false);
		m_physicsScene->addActor(ball2);
		m_physicsScene->addActor(new Spring(ball1, ball2, 0, 100, 0.1f));
		ball1 = ball2;
		if(i == 19){
			ball1->setKinematic(true);
		}
	}
}

//draws a box at the mouse if clicked
void Demo::drawAtMouse(){
	m_input->getMouseXY(&m_mouseX, &m_mouseY);
	if(m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT)){
		m_physicsScene->addActor(new Sphere(gizmoCoords(glm::vec2(m_mouseX, m_mouseY)), glm::vec2(0, 0), 4, 2, glm::vec4(0.95, 0.77, 0.05, 1), 0.9f, false, 0, 0.3f, 0.3f));
	}
}

glm::vec2 Demo::gizmoCoords(glm::vec2 screenCoords){
	glm::vec2 screensize(1280, 720);
	float scale = 200 / screensize.x;
	m_gizmoCoordinates = glm::vec2(screenCoords.x - screensize.x / 2, screenCoords.y - screensize.y / 2);
	return m_gizmoCoordinates *= scale;
}