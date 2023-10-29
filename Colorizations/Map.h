#pragma once

#include <raylib.h>
#include <iostream>

namespace Colorizations {
	namespace Map {
		class Civilization{
		public:
			Color color;
			int money;
		};

		typedef enum { SUB_PLAINS, SUB_HILLS, SUB_TUNDRA, SUB_DESERT, SUB_MOUNTAINS, SUB_FARMING, SUB_ENTERTAINMENT, SUB_INDUSTRIAL, SUB_RESIDENTIAL, SUB_DOWNTOWN, SUB_OTHER } TileType;

		class Tile {
		public:
			TileType type;
			int civilization;
		};

	}
}