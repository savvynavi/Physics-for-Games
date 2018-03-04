#include "Pinball.h"
#include"StateManager.h"

#define MAX_VELOCITY 150
#define LIVES 3

Pinball::Pinball(PhysicsScene* physScene, StateManager* sm, aie::Renderer2D* renderer, aie::Font* font) :
	m_physicsScene(physScene), m_sm(sm), m_renderer(renderer), m_font(font){
	m_input = aie::Input::getInstance();
	mouseDrag = false;
}

Pinball::~Pinball(){

}

//draws the pinball board out
void Pinball::board(){
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
	m_ball = new Sphere(gizmoCoords(glm::vec2(910, 60)), glm::vec2(0, 0), 10.0f, 4, glm::vec4(0, 1, 1, 1), 0.9f, false, 0, 0.2f, 0.2f);
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
	paddleMovement();

	//limit ball veloocity so it doesn't go to space
	if(m_ball->getVelocity().x >= MAX_VELOCITY){
		m_ball->setVelocity(glm::vec2(MAX_VELOCITY, m_ball->getVelocity().y));
	}
	if(m_ball->getVelocity().y >= MAX_VELOCITY){
		m_ball->setVelocity(glm::vec2(m_ball->getVelocity().x, MAX_VELOCITY));
	}

	//update all physics objects
	m_physicsScene->update(timeStep);

	//change state back to main menu is escape pressed
	if(m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)){
		onExit();
		m_sm->popState();
		m_sm->pushState(MAIN_MENU);
	}
}

void Pinball::onDraw(){
	//mouse pointer
	aie::Gizmos::add2DCircle(m_mousePosCurrent, 1, 16, glm::vec4(1, 1, 1, 1));
	
	//drawing lives in
	m_renderer->drawText(m_font, "Lives", 1000, 200);
	for(int i = 0; i < m_lives; i++){
		aie::Gizmos::add2DCircle(glm::vec2(60 + (i * 6.0f), -30), 2, 12, glm::vec4(0, 1, 1, 1));
	}

	//if the ball falls off the bottom of the screen, you lose a life and the ball resets itself
	if(m_ball->getPosition().y < -60){
		m_lives--;
		//if you run out of lives, displays text and stops spawning ball
		if(m_lives >= 0){
			resetBall();
		} else{
			m_renderer->drawText(m_font, "Out of lives - hit R to restart", 1280 / 2 - 400, 400);
			if(m_input->wasKeyPressed(aie::INPUT_KEY_R)){
				m_lives = LIVES;
				resetBall();
			}
		}
	}
	//draw all gizmos
	m_physicsScene->updateGizmos();
}

void Pinball::onEnter(){
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_lives = LIVES;
	m_score = 0;
	board();
}

void Pinball::onExit(){
	m_physicsScene->clearAllActors();
}

void Pinball::paddleMovement(){

	//left paddle movement
	if(m_input->isKeyDown(aie::INPUT_KEY_LEFT)){
		m_leftPaddle->setAngularVelocity(4);
		//if paddle is greater than the max angle, it stops rotation
		if(m_leftPaddle->getRotation() > 2){
			m_leftPaddle->setAngularVelocity(0);
		}
	}else{
		m_leftPaddle->setAngularVelocity(-6);
		//if paddle less than min anlge, stops rotation
		if(m_leftPaddle->getRotation() < 1){
			m_leftPaddle->setAngularVelocity(0);
		}
	}
	//right paddle
	if(m_input->isKeyDown(aie::INPUT_KEY_RIGHT)){
		m_rightPaddle->setAngularVelocity(-4);
		if(m_rightPaddle->getRotation() < -2){
			m_rightPaddle->setAngularVelocity(0);
		}
	}else{
		m_rightPaddle->setAngularVelocity(6);
		if(m_rightPaddle->getRotation() > -1){
			m_rightPaddle->setAngularVelocity(0);
		}
	}
}

//resets the ball back to start
void Pinball::resetBall(){
	m_physicsScene->removeActor(m_ball);
	delete m_ball;
	m_ball = new Sphere(gizmoCoords(glm::vec2(910, 60)), glm::vec2(0, 0), 10.0f, 4, glm::vec4(0, 1, 1, 1), 0.9f, false, 0, 0.2f, 0.2f);
	m_physicsScene->addActor(m_ball);
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
		if(m_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)){
			mouseDrag = true;
			m_ball->applyForce(-2.5f * (m_mousePosDragged - m_mousePosCurrent), m_mousePosCurrent - m_ball->getPosition());
		}
	} 
}