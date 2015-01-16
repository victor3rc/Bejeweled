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

const int GRID_SIZE = 6;

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
            
            //Generate jewel until acceptable.
            while(!verify(x, y, index))
            {
                index = (rand() % 5);
            }
            
            //insert into grid
            m_grid.insert(make_pair(key, index));
        }
    }
}

bool Grid::verify(int x, int y, int index)
{
    //return flag.
    bool output = true;
    
    //check jewels to the left aren't the same
    if(x > 1)
    {
        //jewels to check
        pair<int,int> left1, left2;

        //grab their value
        left1 = make_pair(x-1, y);
        left2 = make_pair(x-2, y);

        if(m_grid[left1] == index && m_grid[left2] == index)
        {
            return false;
        }
    }
    
    //check jewels above aren't the same
    if(y > 1)
    {
        //jewels to check
        pair<int,int> above1, above2;
        
        //grab their value
        above1 = make_pair(x, y-1);
        above2 = make_pair(x, y-2);
        
        if(m_grid[above1] == index && m_grid[above2] == index)
        {
            return false;
        }
    }
    
    
    return output;
}



