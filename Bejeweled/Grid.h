//
//  Grid.h
//  Bejeweled
//
//  Created by Victor Cardozo on 15/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#ifndef __Bejeweled__Grid__
#define __Bejeweled__Grid__

#include <stdio.h>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

#include "Jewel.h"

class Grid
{
public:
    //Constructor
    Grid();
    
    //Returns grid.
    std::map<std::pair<int, int>, Jewel>& grid() { return m_grid; };
    
    //Provide intuitive mothod of accessing jewels in grid.
    Jewel& operator[](const std::pair<int, int>& key);
    
    //Populates grid with random jewels.
    void populate();
    
    //Check if jewels in grid give a combination.
    //returns bool indicating if any combinations were found.
    bool findCombinations();
    
    //Find jewels which need to drop.
    //returns vector with all keys to jewels to be dropped.
    std::vector<std::pair<int,int>> setDroppers();
    
    //Replace jewels combined with new jewels.
    //Returns keys of jewels being spawned
    std::vector<std::pair<int,int>> spawn();
    
private:
    //Verifies jewel can be created in grid position given.
    //'x' location on x-axis
    //'y' location on y-axis.
    //'color' indicates jewel color.
    bool verify(int x, int y, int color);
    
    //Checks jewels around jewel indicated, to see if there is a combination.
    //'key' is jewel indicating jewel to check for.
    bool matchAround(const std::pair<int,int>& key);
    
    //Grid
    std::map<std::pair<int, int>, Jewel> m_grid;
};

#endif /* defined(__Bejeweled__Grid__) */
