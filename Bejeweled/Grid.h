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
    Grid();
    
    //Populates grid with random jewels.
    void populate();
    
    //Returns grid.
    const std::map<std::pair<int, int>, Jewel> grid();
    
    //Returns grid size.
    const int size() { return GRID_SIZE; };
    
    //Provide intuitive mothod of accessing jewels in grid.
    Jewel& operator[](const std::pair<int, int>& key);
    
private:
    //Verifies jewel can be created in grid position given.
    //'x' location on x-axis
    //'y' location on y-axis.
    //'id' indicates jewel type.
    bool verify(int x, int y, int index);
    
    //Grid
    std::map<std::pair<int, int>, Jewel> m_grid;
};

#endif /* defined(__Bejeweled__Grid__) */
