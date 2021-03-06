#include "MainMenu.h"
#include"Physics_EngineApp.h"
#include"StateManager.h"

#define OFFSET 1280 / 2 - 120

MainMenu::MainMenu(aie::Renderer2D* renderer, StateManager* sm, aie::Font* font, Physics_EngineApp* app) : m_renderer(renderer), m_sm(sm), m_font(font){
	m_input = aie::Input::getInstance();
	m_menuSelector = 0;
	m_selectorHeight = 510;
	this->m_app = app;
}


MainMenu::~MainMenu(){

}

void MainMenu::onUpdate(float timeStep){
	
	if(m_input->wasKeyPressed(aie::INPUT_KEY_SPACE)){
		if(m_menuSelector == 0){
			m_sm->popState();
			onExit();
			m_sm->pushState(PINBALL);
			onEnter();
		} else if(m_menuSelector == 1){
			m_sm->popState();
			onExit();
			m_sm->pushState(PHYS_DEMO);
			onEnter();
		}else if(m_menuSelector == 2){
			m_sm->popState();
			onExit();
			m_sm->pushState(CRADLE);
			onEnter();
		}else if(m_menuSelector == 3){
			m_sm->popState();
			m_sm->pushState(INSTRUCTIONS);
			onEnter();
		} else if(m_menuSelector == 4){
			m_sm->popState();
			m_app->quit();
		}
	}

	//moving the selector up/down
	if(m_input->wasKeyPressed(aie::INPUT_KEY_DOWN) && m_menuSelector < 4){
		m_selectorHeight -= 50;
		m_menuSelector++;
	}
	if(m_input->wasKeyPressed(aie::INPUT_KEY_UP) && m_menuSelector > 0){
		m_selectorHeight += 50;
		m_menuSelector--;
	}
}

void MainMenu::onDraw(){
	m_renderer->drawText(m_font, "Pinball", OFFSET, 510);
	m_renderer->drawText(m_font, "Physics Demo", OFFSET, 460);
	m_renderer->drawText(m_font, "Newtons Cradle", OFFSET, 410);
	m_renderer->drawText(m_font, "Instructions", OFFSET, 360);
	m_renderer->drawText(m_font, "Quit to Desktop", OFFSET, 310);
	m_renderer->drawText(m_font, ">", OFFSET - 30, m_selectorHeight);
}