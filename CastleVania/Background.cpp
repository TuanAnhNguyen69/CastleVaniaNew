#include "Background.h"

BackgroundController::BackgroundController(void)
{
	tree = NULL;
	listTile = NULL; // => list object, tất cả tile 
	nodes = NULL; //  số node 
	currentTiles = NULL; 
}

BackgroundController::BackgroundController(int level)
{
	string tileFileName;
	string quadtreeFileName;


	switch (level)
	{
	case 1:
		tileFileName = "Resource/map/lv-2.txt";
		quadtreeFileName = "Resource/map/lv-2Quadtree.txt";

		break;
	case 2:
		tileFileName = "Resource\\map\\Level2.txt";
		break;
	default:
		break;
	}
	
	ifstream map(tileFileName);

	currentTiles = new list<int>();

	if (map.is_open())
	{
		float posX, posY;
		int col, row;
		int count;
		map >> count;

		switch (level)
		{
		case 1:
			bgSprite = new GSprite(new GTexture("Resource\\map\\lv-2.bmp", count, 1, count), 1000);
			break;
		case 2:
			bgSprite = new GSprite(new GTexture("Resource\\map\\Level2.png", count, 1, count), 1000);
			break;
		default:
			break;
		}

		map >> row >> col;
		G_MapWidth = col * 16;
		G_MapHeight = row * 16;
		int tileID;
		listTile = new std::map<int, Tile*>();
		int value = 0;
		for (int rowIndex = 1; rowIndex <= row; rowIndex++)
		{
			for (int colIndex = 1; colIndex <= col; colIndex++, value++) {
				map >> tileID;
				posX = (colIndex - 1) * 16;
				posY = G_MapHeight - (rowIndex - 1) * 16;
				listTile->insert(pair<int, Tile*>(value, new Tile(tileID, posX, posY)));
			}
		}
	}

		map.close();
		LoadQuadTreeFromFile(quadtreeFileName);
}

void BackgroundController::GetAvailableTiles(int viewportX, int viewportY)
{
	currentTiles->clear();
	for (int index = 0; index < listTile->size(); index++) {
		if (listTile->find(index)->second->posX > viewportX && listTile->find(index)->second->posY < viewportY) {
			currentTiles->push_back(index);
		}
	}
}

void BackgroundController::LoadQuadTreeFromFile(string quadtreeFileName)
{
	ifstream map(quadtreeFileName);
	Load(&map, tree);
	map.close();
}

void BackgroundController::Load(ifstream *map, QNode *& _nodeTree)
{
	int width, height, numberOfNode, numberOfObject;
	float posX, posY;

	*map >> posX >> posY >> width >> height >> numberOfNode >> numberOfObject;
	int objectIndex = 0;
	list<int> *_objOfNode = new list<int>();

	for (int index = 0; index < numberOfObject; index++)
	{
		*map >> objectIndex;
		_objOfNode->push_back(objectIndex);
	}

	_nodeTree = new QNode(posX, posY, width, height, numberOfNode != 0, *_objOfNode);
	if (_nodeTree->hasNode) {
		Load(map, _nodeTree->leftTop);
		Load(map, _nodeTree->rightTop);
		Load(map, _nodeTree->leftBottom);
		Load(map, _nodeTree->rightBottom);
	}
}

void BackgroundController::Draw(GCamera *camera)
{
	for (list<int>::iterator _itBegin = currentTiles->begin(); _itBegin != currentTiles->end(); ++_itBegin)
	{
		Tile* obj = listTile->find(*_itBegin)->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);
		bgSprite->DrawIndex(obj->idTile, t.x, t.y);
	}
}

BackgroundController::~BackgroundController(void)
{
}