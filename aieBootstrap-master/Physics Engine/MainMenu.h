#pragma once
#include"State.h"
#include"Renderer2D.h"
#include"Input.h"
#include"Font.h"

class Physics_EngineApp;
class StateManager;

class MainMenu : public State{
public:
	MainMenu(aie::Renderer2D* renderer, StateManager* sm, aie::Font* font, Physics_EngineApp* app);
	~MainMenu();
	void onUpdate(float timeStep);
	void onDraw();
private:
	aie::Renderer2D* m_renderer;
	aie::Input* m_input;
	aie::Font* m_font;
	StateManager* m_sm;
	Physics_EngineApp* m_app;
	int m_menuSelector;
	float m_selectorHeight;
};

