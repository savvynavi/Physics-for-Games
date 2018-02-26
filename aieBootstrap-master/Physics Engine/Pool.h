#pragma once
#include<list>
#include<Gizmos.h>
#include"PhysicsScene.h"
#include"Plane.h"
#include"Sphere.h"
#include"Box.h"

class Pool{
public:
	Pool(PhysicsScene* physScene);
	~Pool();
	void reset();
private:
	Box* m_lSide;
	Box* m_rSide;
	Box* m_lTop;
	Box* m_rTop;
	Box* m_lBottom;
	Box* m_rBottom;

	//std::list<Sphere*> m_reds;
	PhysicsScene* m_physScene;

};

