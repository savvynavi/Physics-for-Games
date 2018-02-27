#pragma once
#include<vector>

class State;

class StateManager{
public:
	StateManager(unsigned int stateCount);
	~StateManager();

	void registerState(int id, State* state);
	void pushState(int id);
	void popState();

	void update(float deltaTime);

	void draw();

	int activeStateCount()const;
	int totalStateCount()const;
	State* getTopState()const;
	State* getState(int id)const;
private:
	std::vector<State*> m_pushedStates;
	bool m_popState = false;

	std::vector<State*> m_stateStack;
	std::vector<State*> m_registeredStates;
};