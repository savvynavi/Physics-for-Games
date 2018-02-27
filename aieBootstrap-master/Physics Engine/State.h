#pragma once

enum States{
	MAIN_MENU,
	PINBALL
};

class State{
	friend class StateManager;
public:
	State();
	virtual ~State();
	bool isActive()const;
protected:
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw() = 0;

	void enter();
	void exit();

	virtual void onEnter();
	virtual void onExit();
	virtual void onPushed();
	virtual void onPopped();
private:
	bool m_active = false;
};