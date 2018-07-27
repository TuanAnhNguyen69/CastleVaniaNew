#ifndef _QNODE_H_
#define _QNODE_H_

#include "Tile.h"

#include <list>
using namespace std;

class QNode
{
public:
	int left;
	int top;
	int width;
	int height;
	bool hasNode;
	list<int> listObject;
	QNode *leftTop;
	QNode *rightTop;
	QNode *leftBottom;
	QNode *rightBottom;

	void Insert(int key);
	QNode(void);
	QNode(int, int, int, int, bool, list<int>);
	QNode(const QNode &);
	~QNode(void);
};

#endif