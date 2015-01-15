//
//  Grid.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 15/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//
#include <time.h>

#include "Grid.h"

using namespace std;

const int GRID_SIZE = 5;

Grid::Grid()
{
    //seed random generator.
    srand(time(NULL));
}

const map<pair<int, int>, int> Grid::grid()
{
    return m_grid;
}

int Grid::size()
{
    return GRID_SIZE;
}

void Grid::populate()
{
    //Key for m_grid.
    pair<int, int> key;

    //Index to choose jewels.
    int index;
    
    for(int x = 0; x < GRID_SIZE; ++x)
    {
        for(int y = 0; y < GRID_SIZE; ++y)
        {
            //generate key for m_grid.
            key = make_pair(x, y);
            
            //Random index for picking jewels.
            index = (rand() % 5);
            
            //insert into grid
            m_grid.insert(make_pair(key, index));
        }
    }
}