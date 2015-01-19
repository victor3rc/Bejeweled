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

const map<pair<int, int>, Jewel>& Grid::grid()
{
    return m_grid;
}

void Grid::populate()
{
    //Initial coordinates
    int init_x = (SCREEN_WIDTH-(GRID_SIZE*JEWEL_WIDTH)-(CUSHION*(GRID_SIZE-1)))/2;
    int init_y = (SCREEN_HEIGHT-(GRID_SIZE*JEWEL_HEIGHT)-(CUSHION*(GRID_SIZE-1)))/2;
    
    //Coordinates used to apply jewels
    int coord_x = init_x, coord_y = init_y;
    
    //Key for inserting into m_grid map.
    pair<int, int> key;
    
    //Value generated to identify jewel.
    int id;
    
    for(int x = 0; x < GRID_SIZE; ++x)
    {
        for(int y = 0; y < GRID_SIZE; ++y)
        {
            key = make_pair(x, y);
            
            id = rand() % 5;
            
            //Choose random jewel until acceptable.
            while(!verify(x, y, id))
            {
                id = rand() % 5;
            }
            
            //Create jewel.
            Jewel jewel;
            jewel.setPosition(coord_x, coord_y);
            jewel.setIdentifier(id);
            
            //Add jewel to grid.
            m_grid.insert(make_pair(key, jewel));
            
            //add cushion to coordinates.
            coord_x += JEWEL_WIDTH + CUSHION;
        }
        
        //update coordinates.
        coord_x = init_x;
        coord_y += JEWEL_HEIGHT + CUSHION;
    }
}

bool Grid::findCombinations(const pair<int, int>& swapped)
{
    //Count of adjacent jewels that match jewel given.
    int left = 0, right = 0, above = 0, below = 0;

    //Used as key to query adjacent jewel. Initially set to jewel to the left.
    pair<int,int> adjacent = make_pair(swapped.first, swapped.second-1);
    
    while(m_grid[swapped].value() == m_grid[adjacent].value() &&
          adjacent.second >= 0)
    {
        ++left;
        --adjacent.second;
    }
    
    //Set adjacent to jewel to the right.
    adjacent = make_pair(swapped.first, swapped.second+1);
    
    while(m_grid[swapped].value() == m_grid[adjacent].value() &&
          adjacent.second < 8)
    {
        ++adjacent.second;
        ++right;
    }
    
    //Set adjacent to jewel above.
    adjacent = make_pair(swapped.first-1, swapped.second);
    
    while(m_grid[swapped].value() == m_grid[adjacent].value() &&
          adjacent.first >= 0)
    {
        --adjacent.first;
        ++above;
    }
    
    //Set adjacent to jewel below.
    adjacent = make_pair(swapped.first+1, swapped.second);
    
    while(m_grid[swapped].value() == m_grid[adjacent].value() &&
          adjacent.first < 8)
    {
        ++adjacent.first;
        ++below;
    }
    
    //Combine if enough jewels are equal to their neighbours.
    if(left+right > 1)
    {
        combine(swapped, left, right, true);
        return true;
    }
    else if(above+below > 1)
    {
        combine(swapped, above, below, false);
        return true;
    }
    else
    {
        return false;
    }
    
    //printf("Jewel %i-%i: L=%i, R=%i, A=%i, B=%i\n", swapped.first, swapped.second, left, right, above, below);
}

Jewel& Grid::operator[](const pair<int, int>& key)
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

void Grid::combine(const pair<int,int>& key, int lower, int higher, bool x_axis)
{
    //Key to jewel to erase.
    pair<int,int> adjacent;
    
    m_grid[key].setDraw(false);
    
    //Erase number of jewels indicated.
    for(int i = 1; i < lower+1; ++i)
    {
        if(x_axis)
        {
            adjacent = make_pair(key.first, key.second-i);
        }
        else
        {
            adjacent = make_pair(key.first-i, key.second);
        }
        
        //Erase jewel.
        m_grid[adjacent].setDraw(false);
    }
    
    //Erase number of jewels indicated.
    for(int i = 1; i < higher+1; ++i)
    {
        if(x_axis)
        {
            adjacent = make_pair(key.first, key.second+i);
        }
        else
        {
            adjacent = make_pair(key.first+i, key.second);
        }
        
        m_grid[adjacent].setDraw(false);
    }
}

















