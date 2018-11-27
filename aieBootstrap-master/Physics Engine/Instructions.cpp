#include "Instructions.h"
#include"StateManager.h"


Instructions::Instructions(PhysicsScene* physScene, StateManager* sm, aie::Renderer2D* renderer, aie::Font* font) :
	m_physicsScene(physScene), m_sm(sm), m_renderer(renderer), m_font(font){
	m_input = aie::Input::getInstance();
	m_font2 = new aie::Font("../bin/font/consolas.ttf", 20);
}


Instructions::~Instructions(){

}
//m_renderer->drawText(m_font, "", 950, 150);

void Instructions::onUpdate(float timeStep){
	//change state back to the main menu if escape is pressed
	if(m_input->wasKeyPressed(aie::INPUT_KEY_ESCAPE)){
		onExit();
		m_sm->popState();
		m_sm->pushState(MAIN_MENU);
	}
}

void Instructions::onDraw(){
	m_renderer->drawText(m_font, "Pinball", 50, 650);
	m_renderer->drawText(m_font2, "This application allows you to play a game of pinball (minus the score), where you have 3 lives until", 100, 600);
	m_renderer->drawText(m_font2, "gameover. Use the left and right arrows to move the paddles to hit the ball, which can be pushed out", 100, 570);
	m_renderer->drawText(m_font2, "of the starting area by clicking on the ball and then dragging in the opposite direction you want it", 100, 540);
	m_renderer->drawText(m_font2, "to go. When you're out of lives you can hit R to restart the game.", 100, 510);
	
	m_renderer->drawText(m_font, "Physics Demo", 50, 400);
	m_renderer->drawText(m_font2, "This creates a small scene with a rope bridge, a soft body and several planes all being affected by ", 100, 370);
	m_renderer->drawText(m_font2, "gravity. Holding down the right mouse button will spawn spheres at the mouse point, which will", 100, 340);
	m_renderer->drawText(m_font2, "interact with the things in the scene. Hit R at any time to reset the scene.", 100, 310);

	m_renderer->drawText(m_font, "Hit ESCAPE to go back to the main menu from any scene", 150, 150);
}

void Instructions::onEnter(){

}

void Instructions::onExit(){

}
