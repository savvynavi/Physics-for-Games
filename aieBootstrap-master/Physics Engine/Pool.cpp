#include "Pool.h"

#define BOARD_XPOS 90
#define BOARD_YPOS 40

Pool::Pool(PhysicsScene* physScene) : 
	m_physScene(physScene){
	//instantiate board
	m_lSide = new Box(glm::vec2(-BOARD_XPOS, -5), glm::vec2(0, 0), 1, 5, 80, glm::vec4(0.25f, 1, 0, 1), 0, 0);
	m_rSide = new Box(glm::vec2(BOARD_XPOS, -5), glm::vec2(0, 0), 1, 5, 80, glm::vec4(0.25f, 1, 0, 1), 0, 0);

	m_lTop = new Box(glm::vec2(-BOARD_XPOS + 45, BOARD_YPOS), glm::vec2(0, 0), 1, 45, 5, glm::vec4(0.25f, 1, 0, 1), 0, 0);
	m_rTop = new Box(glm::vec2(0, BOARD_YPOS), glm::vec2(0, 0), 1, 100, 5, glm::vec4(0.25f, 1, 0, 1), 0, 0);
	m_lBottom = new Box(glm::vec2(0, BOARD_YPOS), glm::vec2(0, 0), 1, 100, 5, glm::vec4(0.25f, 1, 0, 1), 0, 0);
	m_rBottom = new Box(glm::vec2(0, BOARD_YPOS), glm::vec2(0, 0), 1, 100, 5, glm::vec4(0.25f, 1, 0, 1), 0, 0);


	//add to scene
	m_lSide->setKinematic(true);
	m_physScene->addActor(m_lSide);	
	m_rSide->setKinematic(true);
	m_physScene->addActor(m_rSide);
	m_lTop->setKinematic(true);
	m_physScene->addActor(m_lTop);
	//m_rTop->setKinematic(true);
	//m_physScene->addActor(m_rTop);
	//m_lBottom->setKinematic(true);
	//m_physScene->addActor(m_lBottom);
	//m_rBottom->setKinematic(true);
	//m_physScene->addActor(m_rBottom);
	
	//reset();
}


Pool::~Pool(){

}

//draws up table with balls in starting positions
void Pool::reset(){

}