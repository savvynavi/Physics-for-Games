#include "MainMenu.h"
#include"Physics_EngineApp.h"
#include"StateManager.h"

#define OFFSET 1280 / 2 - 120

MainMenu::MainMenu(aie::Renderer2D* renderer, StateManager* sm, aie::Font* font, Physics_EngineApp* app) : m_renderer(renderer), m_sm(sm), m_font(font){
	m_input = aie::Input::getInstance();
	m_menuSelector = 0;
	m_selectorHeight = 400;
	this->m_app = app;
}


MainMenu::~MainMenu(){

}

void MainMenu::onUpdate(float timeStep){
	
	if(m_input->wasKeyPressed(aie::INPUT_KEY_SPACE)){
		if(m_menuSelector == 0){
			m_sm->popState();
			m_sm->pushState(PINBALL);
			onEnter();
		}else if(m_menuSelector == 1){
			m_sm->popState();
			m_app->quit();
		}
	}

	//moving the selector up/down
	if(m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && m_menuSelector < 1){
		m_selectorHeight -= 100;
		m_menuSelector++;
	}
	if(m_input->wasKeyPressed(aie::INPUT_KEY_UP) && m_menuSelector > 0){
		m_selectorHeight += 100;
		m_menuSelector--;
	}
}

void MainMenu::onDraw(){
	m_renderer->drawText(m_font, "Pinball", OFFSET, 400);
	m_renderer->drawText(m_font, "Quit to Desktop", OFFSET, 300);
	m_renderer->drawText(m_font, ">", OFFSET - 30, m_selectorHeight);
}