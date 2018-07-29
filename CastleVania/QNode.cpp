#include "QNode.h"


QNode::QNode(void)
{
	left = 0;
	top = 0;
	width = 0;
	height = 0;
	hasNode = false;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
}

QNode::QNode(int _left, int _top, int _width, int _height, bool _hasNode, list<int> _list)
{
	left = _left;
	top = _top;
	width = _width;
	height = _height;
	hasNode = _hasNode;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
	listObject = _list;
}

void QNode::Insert(int key)
{
	listObject.push_back(key);
}

QNode::QNode(const QNode& _node)
{
	left = _node.left;
	top = _node.top;
	width = _node.width;
	height = _node.height;
	leftTop = _node.leftTop;
	leftBottom = _node.leftBottom;
	rightTop = _node.rightTop;
	rightBottom = _node.rightBottom;
	listObject = _node.listObject;
	hasNode = leftTop != NULL;
}

//bool QNode::IsContain(GameObject* entity)
//{
//	Rect* bound = entity->GetBoundingBox();
//
//	return !(bound->x + bound->width < m_region->x ||
//		bound->y + bound->height < m_region->y ||
//		bound->x > m_region->x + m_region->width ||
//		bound->y > m_region->y + m_region->height);
//}

QNode::~QNode(void)
{
}
