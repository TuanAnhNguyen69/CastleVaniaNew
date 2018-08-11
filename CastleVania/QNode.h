#ifndef _QNODE_H_
#define _QNODE_H_

#include "Tile.h"
#include "GameObject.h"
#include <list>
using namespace std;

#define MAX_LEVEL                3
#define MAX_OBJECT_IN_REGION     10

class QNode
{
private:
	int m_level;
	Box* m_region;
	list<GameObject*>* m_objects_list;
	QNode** m_nodes;
public:
	QNode();
	QNode(int level, Box* box);
	~QNode();
	void Split();
	void Insert(GameObject* object);
	bool IsContain(GameObject* object);
	void Retrieve(list<GameObject*> *return_objects_list, GameObject* object);	
	void Clear();
};

#endif