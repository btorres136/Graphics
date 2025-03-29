#include "map.hpp"

Map::Map()
{
    //m_map = new int[64];
}

Map::~Map()
{
    if(map_)
    {
        delete map_;
        map_ = 0;
    }
}

void Map::RenderMap(SDL_Renderer* renderer)
{

}