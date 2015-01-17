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

const int GRID_SIZE = 6;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int JEWEL_DIMENSION = 70;
const int CUSHION = 15;

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
    
private:
    //Verifies jewel can be created in index given.
    //'x' position of creation on x-axis
    //'y' position of creation on y-axis.
    //'index' indicates jewel type.
    bool verify(int x, int y, int index);
    
    //Grid
    std::map<std::pair<int, int>, Jewel> m_grid;
};

#endif /* defined(__Bejeweled__Grid__) */
