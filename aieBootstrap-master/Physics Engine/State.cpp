#include"State.h"

State::State(){

}

State::~State(){

}

bool State::isActive()const{
	return m_active;
}

void State::enter(){
	m_active = true;
	onEnter();
}

void State::exit(){

}

void State::onEnter(){

}

void State::onExit(){

}

void State::onPushed(){

}

void State::onPopped(){

}