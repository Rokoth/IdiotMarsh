#define _CRT_RAND_S
#include "MapManager.h"

MapManager ctor;
unsigned int    number;
errno_t         err;

MapManager::map MapManager::CreateNewMap()
{
	std::array<std::array<int, 10>, 10> points = {
				{
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
				}
	};
	return MapManager::map("emptyMap", 0, 0, points);
}

MapManager::MapManager()
{		
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::array<std::array<int, 10>, 10> points = {
				{
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0,0,0},
				}
			};
			for (int a = 0; a < 10; a++)
			{
				for (int b = 0; b < 10; b++)
				{
					err = rand_s(&number);
					if (err != 0)
					{
						printf_s("The rand_s function failed!\n");
					}
					unsigned int step = UINT_MAX / 10 * 9;
					if (number > step)
					{
						points[a][b] = 1;
					}					
				}
			}			
			maps[i][j] = map("map" + i + j, i, j, points);
		}
	}
}

std::array<std::array<int, 10>, 10> MapManager::GetCurrentMap()
{
	return maps[_current_map.x][_current_map.y].points;
}

std::tuple<int, int> MapManager::GetCurrentPosition()
{
	return std::make_tuple(_current_position.x, _current_position.y);
}

void MapManager::MoveUp()
{
	if (_current_position.y == 0)
	{
		if (_current_map.y > 0)
		{
			if (maps[_current_map.x][_current_map.y - 1].points[_current_position.x][9] == 0)
			{
				_current_map.y--;
				_current_position.y = 9;
			}
		}
	}
	else
	{		
		if (GetCurrentMap()[_current_position.x][_current_position.y - 1] == 0)
		{
			_current_position.y--;
		}
	}
}

void MapManager::MoveDown()
{
	if (_current_position.y == 9)
	{
		if (_current_map.y < 9)
		{
			if (maps[_current_map.x][_current_map.y + 1].points[_current_position.x][0] == 0)
			{
				_current_map.y++;
				_current_position.y = 0;
			}
		}
	}
	else
	{
		if (GetCurrentMap()[_current_position.x][_current_position.y + 1] == 0)
		{
			_current_position.y++;
		}
	}
}

void MapManager::MoveLeft()
{
	if (_current_position.x == 0)
	{
		if (_current_map.x > 0)
		{
			if (maps[_current_map.x-1][_current_map.y].points[9][_current_position.y] == 0)
			{
				_current_map.x--;
				_current_position.x = 9;
			}
		}
	}
	else
	{
		if (GetCurrentMap()[_current_position.x - 1][_current_position.y] == 0)
		{
			_current_position.x--;
		}
	}
}

void MapManager::MoveRight()
{
	if (_current_position.x == 9)
	{
		if (_current_map.x < 9)
		{
			if (maps[_current_map.x + 1][_current_map.y].points[0][_current_position.y] == 0)
			{
				_current_map.x++;
				_current_position.x = 0;
			}
		}
	}
	else
	{
		if (GetCurrentMap()[_current_position.x +1][_current_position.y] == 0)
		{
			_current_position.x++;
		}
	}
}

int MapManager::GetMapSize()
{
	return map_size;
}
