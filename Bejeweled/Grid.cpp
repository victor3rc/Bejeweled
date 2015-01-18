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

Grid::Grid()
{
    //seed random generator.
    srand(time(NULL));
}

const map<pair<int, int>, Jewel> Grid::grid()
{
    return m_grid;
}

void Grid::populate()
{
    //Initial coordinates
    int init_x = (SCREEN_WIDTH-(GRID_SIZE*JEWEL_DIMENSION)-(CUSHION*(GRID_SIZE-1)))/2;
    int init_y = (SCREEN_HEIGHT-(GRID_SIZE*JEWEL_DIMENSION)-(CUSHION*(GRID_SIZE-1)))/2;
    
    //Coordinates used to apply jewels
    int coord_x = init_x, coord_y = init_y;
    
    //Key for inserting into m_grid map.
    pair<int, int> key;
    
    //Value generate to identify jewel.
    int identifier;
    
    for(int x = 0; x < GRID_SIZE; ++x)
    {
        for(int y = 0; y < GRID_SIZE; ++y)
        {
            key = make_pair(x, y);
            
            identifier = rand() % 5;
            
            //Choose random jewel until acceptable.
            while(!verify(x, y, identifier))
            {
                identifier = rand() % 5;
            }
            
            //Create jewel.
            Jewel jewel;
            jewel.setPosition(coord_x, coord_y);
            jewel.setValue(identifier);
            
            //Add jewel to grid.
            m_grid.insert(make_pair(key, jewel));
            
            //add cushion to coordinates.
            coord_x += JEWEL_DIMENSION + CUSHION;
        }
        
        //update coordinates.
        coord_x = init_x;
        coord_y += JEWEL_DIMENSION + CUSHION;
    }
}

Jewel Grid::operator[](const pair<int, int>& key)
{
    return m_grid[key];
}

bool Grid::verify(int x, int y, int id)
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

        if(m_grid[left1].value() == id && m_grid[left2].value() == id)
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
        
        if(m_grid[above1].value() == id && m_grid[above2].value() == id)
        {
            return false;
        }
    }
    
    
    return output;
}



