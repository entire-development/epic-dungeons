#pragma once
#include <vector>
#include "cell/cell.h"

class Map
{
public:
    Map(int width, int height, int seed = 0);
    void generate_map(int seed);    
    private:
        Room* _start_room;
        int _width, _height;
};
