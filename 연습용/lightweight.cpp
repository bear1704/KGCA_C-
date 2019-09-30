#include <iostream>


#ifdef case2
enum class Terrain
{
	TERRAIN_GLASS,
	TERRAIN_HILL,
	TERRAIN_RIVER,
};

class World
{
public:
	World();
	~World();
private:
	Terrain tiles_[100][100];

public:
	int tiles(int x, int y);
};


int World::tiles(int x, int y)
{
	switch (tiles_[x][y])
	{
		case Terrain::TERRAIN_GLASS: return 1;
		case Terrain::TERRAIN_HILL: return 2;
		case Terrain::TERRAIN_RIVER: return 3;
	}
}
#endif


enum class TerrainType
{
	TERRAIN_GLASS,
	TERRAIN_HILL,
	TERRAIN_RIVER,
};


class Terrain
{
public:
	TerrainType type;

	//etc..
};

#ifdef case1
class World
{
public:
	World();
	~World();
private:
	Terrain tiles_[100][100];

public:
	int tiles(int x, int y);
};

int World::tiles(int x, int y)
{
	if (tiles_[x][y].type == TerrainType::TERRAIN_GLASS) {}
	else if (tiles_[x][y].type == TerrainType::TERRAIN_HILL) {}
	else if (tiles_[x][y].type == TerrainType::TERRAIN_RIVER) {}
}
#endif

#ifdef case3

class Terrain
{
	Terrain();
	~Terrain();
};

class World
{
private: 
	Terrain* tiles_[100][100];


	Terrain grass_terrain_;
	Terrain hill_terrain_;
	Terrain river_terrain_;

public:
	void Generate();
};

void World::Generate()
{
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			if (rand() % 3 == 0)
				tiles_[x][y] = &grass_terrain_;
			else if (rand() % 3 == 1)
				tiles_[x][y] = &hill_terrain_;
			else
				tiles_[x][y] = &river_terrain_;
		}
	}
}

#endif