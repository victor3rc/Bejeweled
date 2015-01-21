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

map<pair<int, int>, Jewel>& Grid::grid()
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
            jewel.setVacant(false);
            
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

bool Grid::findCombinations()
{
    //flag indicating if there were any combinations
    bool output = false;
    
    //Current key to jewel being looked at
    pair<int,int> current;
    
    for(int x = 0; x < GRID_SIZE; ++x)
    {
        for(int y = 0; y < GRID_SIZE; ++y)
        {
            current = make_pair(x, y);
    
            //if jewel is part of a combination.
            if(matchAround(current))
            {
                //Set as vacant.
                m_grid[current].setVacant(true);
                
                //indicate combination.
                output = true;
            }
        }
    }
    
    return output;
}

vector<pair<int,int>> Grid::findDroppers()
{
    //Jewels to be dropped.
    vector<pair<int,int>> output;
    
    //Keys to query values for current jewel being examined, and the one above.
    pair<int,int> current, above;
    
    int targetX = 0, targetY = 0;
    
    //Cycle through columns.
    for(int y = GRID_SIZE-1; y >= 0; --y)
    {
        //indicates if there's an empty space
        bool hole = false;
        
        //Indicates number of drops in this column
        int spaces_dropped = 0;
        
        for(int x = GRID_SIZE-1; x >= 0; --x)
        {
            current = make_pair(x, y);
            
            //If jewel space empty and hole hasn't been declared yet
            if(!hole && m_grid[current].vacant())
            {
                //set drop target.
                targetX = m_grid[current].x();
                targetY = m_grid[current].y();
                
                hole = true;
            }
            //If hole has been detected and there is a jewel in space
            else if(hole && !m_grid[current].vacant())
            {
                //update spaces dropped
                ++spaces_dropped;
                
                //set drop target and indicate jewel is meant to drop.
                m_grid[current].setDropTarget(targetX, targetY);
                m_grid[current].setDrop(true, spaces_dropped);
                
                //Check if space has been left vacant.
                if((GRID_SIZE-spaces_dropped) < 0)
                {
                    m_grid[current].setVacant(true);
                }
                
                //update drop target.
                targetY -= JEWEL_HEIGHT + CUSHION;
            }
        }
    }
   
    return output;
}

void Grid::moveJewel(const pair<int,int>& moved, const pair<int,int>& space)
{
    //Make jewel in space = moved jewel.
    m_grid[space] = m_grid[moved];
    
    //Indicate that space is now occupied.
    m_grid[space].setVacant(false);
    
    //Indicate jewels are not dropping anymore.
    m_grid[moved].setDrop(false, 0);
    m_grid[space].setDrop(false, 0);
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
    
    m_grid[key].setVacant(true);
    
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
        m_grid[adjacent].setVacant(true);
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
        
        //Erase jewel
        m_grid[adjacent].setVacant(true);
    }
}

void Grid::dropAbove(pair<int, int> current)
{
//    pair<int,int> above;
//    
//    while(current.first >= 0)
//    {
//        above = make_pair(current.first - 1, current.second);
//        
//        //Set jewel above to drop. Set its drop target also.
//        m_grid[above].setDrop(true);
//        m_grid[above].setDropTarget(m_grid[current].xTarget(),
//                                    m_grid[current].yTarget() - JEWEL_HEIGHT - CUSHION);
//        
//        --current.first;
//    }
}

bool Grid::matchAround(const std::pair<int, int>& key)
{
    //color of jewel.
    int color = m_grid[key].value();
    
    //keys to adjacent jewels to check combinations for.
    pair<int,int> adjacent1, adjacent2;
    
    //Check if jewel given is the one in the middle of horizontal combination
    if(key.second != 0 && key.second != 7)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first, key.second-1);
        adjacent2 = make_pair(key.first, key.second+1);
        
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one on the right of a combination
    if(key.second >= 2)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first, key.second-1);
        adjacent2 = make_pair(key.first, key.second-2);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one on the left of a combination
    if(key.second <= 5)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first, key.second+1);
        adjacent2 = make_pair(key.first, key.second+2);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one in the middle of vertical combination
    if(key.first != 0 && key.first != 7)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first-1, key.second);
        adjacent2 = make_pair(key.first+1, key.second);
        
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one above in a combination
    if(key.first >= 2)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first-1, key.second);
        adjacent2 = make_pair(key.first-2, key.second);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one below in a combination
    if(key.first <= 5)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first+1, key.second);
        adjacent2 = make_pair(key.first+2, key.second);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].value() == color && m_grid[adjacent2].value() == color)
        {
            return true;
        }
    }
    
    return false;
}















