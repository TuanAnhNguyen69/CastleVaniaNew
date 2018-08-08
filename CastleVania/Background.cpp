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
		quadtreeFileName = "Resource/map/lv-2.1Quadtree.txt";

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
		G_MapWidth = col * 32;
		G_MapHeight = row * 32;
		int tileID;
		listTile = new std::map<int, Tile*>();
		int value = 0;
		for (int rowIndex = 1; rowIndex <= row; rowIndex++)
		{
			for (int colIndex = 1; colIndex <= col; colIndex++, value++) {
				map >> tileID;
				posX = (colIndex - 1) * 32;
				posY = G_MapHeight - (rowIndex - 1) * 32;
				listTile->insert(pair<int, Tile*>(value, new Tile(tileID, posX, posY)));
			}
		}
	}

		map.close();
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