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

Jewel& Grid::operator[](const pair<int, int>& key)
{
    return m_grid[key];
}

void Grid::populate()
{
    //Initial coordinates
    int init_x = (SCREEN_WIDTH-(GRID_SIZE*JEWEL_WIDTH)-(CUSHION*(GRID_SIZE-1)))/2;
    int init_y = (SCREEN_HEIGHT-(GRID_SIZE*JEWEL_HEIGHT)-(CUSHION*(GRID_SIZE-1)))/2;
    
    //Coordinates used to apply jewels and value to identify color.
    int coord_x = init_x, coord_y = init_y, id;
    
    //Key for inserting into m_grid map.
    pair<int, int> key;
    
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
            
            //Create jewel and set its id.
            Jewel jewel(coord_x, coord_y);
            jewel.setColor(id);
            
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
            if(matchAround(current) && !m_grid[current].vacant())
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

vector<pair<int,int>> Grid::setDroppers()
{
    //Jewels to be dropped.
    vector<pair<int,int>> output;
    
    //Keys to query values for current jewel being examined, and the one above.
    pair<int,int> current, above;
    
    //Cycle through columns.
    for(int y = GRID_SIZE-1; y >= 0; --y)
    {
        for(int x = GRID_SIZE-1; x >= 0; --x)
        {
            current = make_pair(x, y);
            
            //If jewel is set as vacant
            if(m_grid[current].vacant())
            {
                int i = 1;
                
                above = make_pair(x-i, y);
                
                //while jewel above is not out of the grid and vacant
                while(x >= 0 && m_grid[above].vacant())
                {
                    ++i;
                    above = make_pair(x-i, y);
                    
                    //If found a jewel to drop and still inside the grid.
                    if (!m_grid[above].vacant() && x-i >= 0)
                    {
                        break;
                    }
                }
                
                //If not reached the top row and jewel above is not already vacant
                if(x-i >= 0 && !m_grid[above].vacant())
                {
                    //Set position and color of lower jewel to match jewel above.
                    m_grid[current].setPosition(m_grid[above].x(), m_grid[above].y());
                    m_grid[current].setColor(m_grid[above].color());
                    
                    //set jewel to drop.
                    m_grid[above].setVacant(true);
                    m_grid[current].setVacant(false);
                    
                    //Indicate jewel has been inserted in current key and needs to drop
                    output.push_back(current);
                }
                else
                {
                    //Indicate jewel has already flickered.
                    m_grid[current].setColor(-1);
                }
            }
        }
    }
    
    return output;
}

vector<pair<int,int>> Grid::spawn()
{
    //vector containing jewels to be spawned.
    vector<pair<int,int>> output;
    
    //key for jewel being looked at.
    pair<int,int> current;
    
    //Cycle through jewels in grid, through columns.
    for(int y = 0; y < GRID_SIZE; ++y)
    {
        for(int x = 0; x < GRID_SIZE; ++x)
        {
            current = make_pair(x, y);
            
            if(m_grid[current].vacant())
            {
                //Indicate current jewel is being spawned;
                output.push_back(current);
                
                //Move jewel to spawning position.
                m_grid[current].setPosition(m_grid[current].x(), 0);
                
                //Find color to spawn.
                m_grid[current].setColor(rand() % 5);
                
                while (matchAround(current))
                {
                    m_grid[current].setColor(rand() % 5);
                }
                
                //Not vacant any longer.
                m_grid[current].setVacant(false);
            }
            else
            {
                //proceed to next column if found a non-vacant jewel spot
                break;
            }
        }
    }
    
    return output;
}

bool Grid::verify(int x, int y, int color)
{
    //return flag.
    bool output = true;
    
    pair<int,int> adjacent1, adjacent2;
    
    //check jewels to the left aren't the same
    if(x > 1)
    {
        //grab their value
        adjacent1 = make_pair(x-1, y);
        adjacent2 = make_pair(x-2, y);
        
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
        {
            return false;
        }
    }
    
    //check jewels above aren't the same
    if(y > 1)
    {
        //grab their value
        adjacent1 = make_pair(x, y-1);
        adjacent2 = make_pair(x, y-2);
        
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
        {
            return false;
        }
    }
    
    return output;
}

bool Grid::matchAround(const std::pair<int, int>& key)
{
    //color of jewel.
    int color = m_grid[key].color();
    
    //keys to adjacent jewels to check combinations for.
    pair<int,int> adjacent1, adjacent2;
    
    //Check if jewel given is the one in the middle of horizontal combination
    if(key.second != 0 && key.second != 7)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first, key.second-1);
        adjacent2 = make_pair(key.first, key.second+1);
        
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
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
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
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
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
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
        
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one below in a combination
    if(key.first >= 2)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first-1, key.second);
        adjacent2 = make_pair(key.first-2, key.second);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
        {
            return true;
        }
    }
    
    //Check if jewel given is the one above in a combination
    if(key.first <= 5)
    {
        //Jewels directly left and right
        adjacent1 = make_pair(key.first+1, key.second);
        adjacent2 = make_pair(key.first+2, key.second);
        
        //Jewel given is the one in the middle of combination
        if(m_grid[adjacent1].color() == color && m_grid[adjacent2].color() == color)
        {
            return true;
        }
    }
    
    return false;
}















