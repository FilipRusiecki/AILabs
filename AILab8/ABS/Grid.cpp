#include "Grid.h"

Grid::Grid(int size)
{
    gridSize = size;
    setupGrid(size);

}

Grid::~Grid()
{
}

void Grid::setupGrid(int size)
{
    nodes = new Node* [size];
    for (int i = 0; i < size; i++)
        nodes[i] = new Node[size];
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            //float outlineThickness = nodes[i][j].m_rectangle.getOutlineThickness();       // Depending on the direction of the outline, node size is different.
            float outlineThickness = 0;
            float r = outlineThickness + nodes[i][j].s_radius;// *1.25;
            nodes[i][j].setPos(startPos + sf::Vector2f((r * (float)i), (r * (float)j)));
        }
    }

}


void Grid::draw(sf::RenderWindow &t_window)
{
//    int counter = 0;      // Some debig to checj issues with drawing the grid cells due to outline thickness messing things up.
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            nodes[i][j].draw(t_window);
//            if (counter++ == 7)       
//                break;            // Set a breakpoint here to see whats going on.
        }
    }
}

float Grid::length(sf::Vector2f t_vect)
{

    float magn =  std::sqrt((t_vect.x * t_vect.x) + (t_vect.y * t_vect.y));
    return magn;
}

sf::Vector2f Grid::getGridLocation(int x, int y)
{
    //float outlineThickness = nodes[x][y].m_rectangle.getOutlineThickness();
    float outlineThickness = 0;
    float r = outlineThickness + nodes[x-1][y-1].s_radius;// *1.25;

    x--;    //Internal Grid starts at [0, 0]
    y--;

    sf::Vector2f localPos = startPos + sf::Vector2f((r/2 + (r * (float)x)), (r/2 + (r * (float)y)));

    return localPos;
}

int Grid::getGridCellX(sf::Vector2i location)
{
    int x = (location.x - startPos.x) / nodes[1][1].s_radius;
    x++;
    return x;
}
int Grid::getGridCellY(sf::Vector2i location)
{
    int y = (location.y - startPos.y) / nodes[1][1].s_radius;
    y++;
    return y;
}


