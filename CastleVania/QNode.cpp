#include "QNode.h"


QNode::QNode(void)
{
	m_region = new Box(0, 0, 0, 0);
}

QNode::QNode(int level, Box * box)
{
	m_level = level;
	m_region = box;
	m_objects_list = new list<GameObject*>();

}



void QNode::Insert(GameObject* object)
{
	//Insert entity into corresponding nodes
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(object))
			m_nodes[0]->Insert(object);
		if (m_nodes[1]->IsContain(object))
			m_nodes[1]->Insert(object);
		if (m_nodes[2]->IsContain(object))
			m_nodes[2]->Insert(object);
		if (m_nodes[3]->IsContain(object))
			m_nodes[3]->Insert(object);

		return; // Return here to ignore rest.
	}

	//Insert entity into current quadtree
	if (this->IsContain(object))
		m_objects_list->push_back(object);

	//Split and move all objects in list into it’s corresponding nodes
	if (m_objects_list->size() > MAX_OBJECT_IN_REGION && m_level < MAX_LEVEL)
	{
		Split();

		while (!m_objects_list->empty())
		{
			if (m_nodes[0]->IsContain(m_objects_list->back()))
				m_nodes[0]->Insert(m_objects_list->back());
			if (m_nodes[1]->IsContain(m_objects_list->back()))
				m_nodes[1]->Insert(m_objects_list->back());
			if (m_nodes[2]->IsContain(m_objects_list->back()))
				m_nodes[2]->Insert(m_objects_list->back());
			if (m_nodes[3]->IsContain(m_objects_list->back()))
				m_nodes[3]->Insert(m_objects_list->back());

			m_objects_list->pop_back();
		}
	}
}

bool QNode::IsContain(GameObject* object)
{
	Box* bound = &object->GetBox();

	return !(bound->x + bound->w < m_region->x ||
		bound->y + bound->h < m_region->y ||
		bound->x > m_region->x + m_region->w ||
		bound->y > m_region->y + m_region->h);
}

void QNode::Split()
{
	m_nodes = new QNode*[4];

	m_nodes[0] = new QNode(m_level + 1,
		new Box(m_region->x, m_region->y, m_region->w / 2, m_region->h / 2));
	m_nodes[1] = new QNode(m_level + 1,
		new Box(m_region->x + m_region->w / 2, m_region->y, m_region->w / 2, m_region->h / 2));
	m_nodes[2] = new QNode(m_level + 1,
		new Box(m_region->x, m_region->y + m_region->h / 2, m_region->w / 2, m_region->h / 2));
	m_nodes[3] = new QNode(m_level + 1,
		new Box(m_region->x + m_region->w / 2,
			m_region->y + m_region->h / 2, m_region->w / 2, m_region->h / 2));
}

void QNode::Clear()
{
	//Clear all nodes
	if (m_nodes)
	{
		for (int i = 0; i < 4; i++)
		{
			m_nodes[i]->Clear();
			delete m_nodes[i];
		}
		delete[] m_nodes;
	}

	//Clear current quadtree
	m_objects_list->clear();

	delete m_objects_list;
}

void QNode::Retrieve(list<GameObject*>* return_objects_list, GameObject* object)
{
	if (m_nodes)
	{
		if (m_nodes[0]->IsContain(object))
			m_nodes[0]->Retrieve(return_objects_list, object);
		if (m_nodes[1]->IsContain(object))
			m_nodes[1]->Retrieve(return_objects_list, object);
		if (m_nodes[2]->IsContain(object))
			m_nodes[2]->Retrieve(return_objects_list, object);
		if (m_nodes[3]->IsContain(object))
			m_nodes[3]->Retrieve(return_objects_list, object);

		return; // Return here to ignore rest.
	}

	//Add all entities in current region into return_objects_list
	if (this->IsContain(object))
	{
		for (auto i = m_objects_list->begin(); i != m_objects_list->end(); i++)
		{
				return_objects_list->push_back(*i);
		}
	}
}

QNode::~QNode(void)
{
}
