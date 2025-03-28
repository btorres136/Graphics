#include "Map.hpp"

Map::Map()
{
    //m_map = new int[64];
}

Map::~Map()
{
    if(m_map)
    {
        delete m_map;
        m_map = 0;
    }
}

void Map::renderMap(SDL_Renderer* renderer)
{

}