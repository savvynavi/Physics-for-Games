#include"StateManager.h"
#include"State.h"

StateManager::StateManager(unsigned int stateCount){
	m_registeredStates.resize(stateCount);
}

StateManager::~StateManager(){
	for(auto state : m_registeredStates){
		delete state;
	}
}

void StateManager::registerState(int id, State* state){
	m_registeredStates[id] = state;
}

void StateManager::pushState(int id){
	m_pushedStates.push_back(m_registeredStates[id]);
}

void StateManager::popState(){
	m_popState = true;
}

void StateManager::update(float deltaTime){
	while(m_popState == true){
		m_popState = false;

		//deactivate prev top
		m_stateStack.back()->exit();
		auto tmp = m_stateStack.back();
		m_stateStack.pop_back();
		tmp->onPopped();

		//activate state under prev top if exists
		if(m_stateStack.empty() == false){
			m_stateStack.back()->enter();
		}
	}

	for(auto pushedState : m_pushedStates){
		//deactivate prev top
		if(m_stateStack.empty() == false){
			m_stateStack.back()->exit();
		}

		//activate new top
		pushedState->onPushed();
		m_stateStack.push_back(pushedState);
		m_stateStack.back()->enter();
	}
	m_pushedStates.clear();

	for(auto state : m_stateStack){
		state->onUpdate(deltaTime);
	}
}

void StateManager::draw(){
	for(auto state : m_stateStack){
		state->onDraw();
	}
}

int StateManager::activeStateCount()const{
	return m_stateStack.size();
}

int StateManager::totalStateCount()const{
	return m_registeredStates.size();
}

State* StateManager::getTopState()const{
	return m_stateStack.back();
}

State* StateManager::getState(int id)const{
	return m_registeredStates[id];
}