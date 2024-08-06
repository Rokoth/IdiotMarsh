#pragma once
#include <tuple>
#include <array>
#include <string>

class MapManager
{	  
	int map_size = 10;
	int map_count = 100;

	struct current_position
	{
		current_position() {
			x = 0;
			y = 0;
		}
		current_position(int _x, int _y) : x(_x), y(_y) {}
		int x;
		int y;
	};

	struct map
	{
		map(std::string _name, int _x, int _y, std::array<std::array<int, 10>, 10> _points) 
			: name(_name), x(_x), y(_y), points(_points){};
		
		std::string name;
		int x;
		int y;
		std::array<std::array<int, 10>, 10> points;
	};

	std::array<std::array<map, 10>, 10> maps = {
				{
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()},
					{CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap(),CreateNewMap()}
				}
	};
	current_position _current_position = current_position(1, 1);
	current_position _current_map = current_position(1, 1);

	private:
		map CreateNewMap();

	public:
		MapManager();	

		int GetMapSize();
	    std::tuple<int, int> GetCurrentPosition();
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();
		std::array<std::array<int, 10>, 10> GetCurrentMap();
		

	protected:
};

