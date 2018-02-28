#include "Pinball.h"
#include"StateManager.h"

Pinball::Pinball(PhysicsScene* physScene, StateManager* sm, aie::Font* font) : 
	m_physicsScene(physScene), m_sm(sm), m_font(font){
	m_input = aie::Input::getInstance();
	mouseDrag = false;
	board();
}


Pinball::~Pinball(){
}

//draws the pinball board out
void Pinball::board(){
	//m_physicsScene->addActor(new Sphere(gizmoCoords(glm::vec2(1280, 720)), glm::vec2(0, 0), 5, 5, glm::vec4(1, 1, 1, 1), 0, 0, 0));
	//play bounds
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), 50));
	m_physicsScene->addActor(new Plane(glm::vec2(1, 0), -90));

	m_physicsScene->addActor(new Box(gizmoCoords(glm::vec2(850, 250)), glm::vec2(0, 0), 0, 1, 3, 80, glm::vec4(1, 1, 1, 1), 0.8f, true));
	m_physicsScene->addActor(new Box(gizmoCoords(glm::vec2(910, 50)), glm::vec2(0, 0), 0, 5, 15, 20, glm::vec4(1, 1, 1, 1), 0.8f, true));

	//corner + roof
	m_physicsScene->addActor(new Box(gizmoCoords(glm::vec2(900, 650)), glm::vec2(0, 0), 1, 1, 3, 30, glm::vec4(1, 1, 1, 1), 0.8f, true));
	m_physicsScene->addActor(new Box(gizmoCoords(glm::vec2(450, 700)), glm::vec2(0, 0), 0, 1, 120, 3, glm::vec4(1, 1, 1, 1), 0.8f, true));

	
	//bumpers
	m_physicsScene->addActor(new Sphere(gizmoCoords(glm::vec2(350, 300)), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 3, true));
	m_physicsScene->addActor(new Sphere(gizmoCoords(glm::vec2(550, 300)), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 3, true));
	m_physicsScene->addActor(new Sphere(gizmoCoords(glm::vec2(450, 500)), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0.75f, 0, 1, 1), 3, true));

	m_physicsScene->addActor(new Box(gizmoCoords(glm::vec2(120, 670)), glm::vec2(0, 0), 0.75f, 1, 30, 3, glm::vec4(0.75f, 0, 1, 1), 3, true));


	//paddles
	m_leftPaddle = new Box(gizmoCoords(glm::vec2(300, 50)), glm::vec2(0, 0), 1, 1, 3, 30, glm::vec4(1, 1, 1, 1), 0.5f, true);
	m_rightPaddle = new Box(gizmoCoords(glm::vec2(600, 50)), glm::vec2(0, 0), -1, 1, 3, 30, glm::vec4(1, 1, 1, 1), 0.5f, true);
	m_physicsScene->addActor(m_leftPaddle);
	m_physicsScene->addActor(m_rightPaddle);

	//ball
	m_ball = new Sphere(gizmoCoords(glm::vec2(910, 60)), glm::vec2(0, 0), 10.0f, 4, glm::vec4(0, 1, 0.5f, 1), 0.9f, false, 0, 0.2f, 0.2f);
	m_physicsScene->addActor(m_ball);
}

//converts gizmo coordinates(where (0, 0) is the screen centre), to screen coordinates(where (0, 0) is the bottom left corner)
glm::vec2 Pinball::gizmoCoords(glm::vec2 screenCoords){
	glm::vec2 screensize(1280, 720);
	float scale = 200 / screensize.x;
	m_gizmoCoordinates = glm::vec2(screenCoords.x - screensize.x / 2, screenCoords.y - screensize.y / 2);
	return m_gizmoCoordinates *= scale;
}

void Pinball::onUpdate(float timeStep){
	addForceMouse();
	//m_leftPaddle->setAngularVelocity(2);

	//left paddle movement
	if(m_input->isKeyDown(aie::INPUT_KEY_LEFT)){
		m_leftPaddle->setAngularVelocity(2);
		//m_leftPaddle->setRotat
	}else{
		m_leftPaddle->setAngularVelocity(-2);
	}

	//stopping the rotation when paddle is at max angle
	if(m_leftPaddle->getRotation() < -2 ){
		m_leftPaddle->setAngularVelocity(0);
	}

	//right paddle
	if(m_input->isKeyDown(aie::INPUT_KEY_RIGHT)){
		m_rightPaddle->setAngularVelocity(-2);
	} else{
		m_rightPaddle->setAngularVelocity(0);

	}

	//update all physics objects
	m_physicsScene->update(timeStep);

	//change state back to main menu is escape pressed
	if(m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)){
		m_sm->popState();
		m_sm->pushState(MAIN_MENU);
		onEnter();
	}
}

void Pinball::onDraw(){
	//mouse pointer
	aie::Gizmos::add2DCircle(m_mousePosCurrent, 1, 16, glm::vec4(1, 1, 1, 1));

	//draw all gizmos
	m_physicsScene->updateGizmos();
}

void Pinball::addForceMouse(){
	//grabbing mouse position
	m_input->getMouseXY(&m_mouseX, &m_mouseY);
	if(m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)){
		m_mousePosDragged = gizmoCoords(glm::vec2(m_mouseX, m_mouseY));
		aie::Gizmos::add2DLine(m_mousePosCurrent, m_mousePosDragged, glm::vec4(0, 1, 1, 1));
	} else{
		m_mousePosCurrent = gizmoCoords(glm::vec2(m_mouseX, m_mouseY));
	}

	//detects when the mouse pointer is on top of the ball (colour change indicates)	
	float dist = sqrt(pow((m_mousePosCurrent.x - m_ball->getPosition().x), 2) + pow((m_mousePosCurrent.y - m_ball->getPosition().y), 2));
	if(dist < m_ball->getRadius()){
		m_ball->setColour(glm::vec4(1, 0, 0, 1));
		if(m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)){
			mouseDrag = true;
			m_ball->applyForce(-2.5f * (m_mousePosDragged - m_mousePosCurrent), m_mousePosCurrent - m_ball->getPosition());
		}
	} else{
		m_ball->setColour(glm::vec4(0, 1, 0.5f, 1));
	}
}