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

class Grid
{
public:
    Grid();
    
    //Populates grid with random jewels.
    void populate();
    
    //Returns grid.
    const std::map<std::pair<int, int>, int> grid();
    
    //Returns grid size.
    int size();
    
private:
    //Verifies jewel can be created in index given.
    //'x' position of creation on x-axis
    //'y' position of creation on y-axis.
    //'index' indicates jewel type.
    bool verify(int x, int y, int index);
    
    //Grid
    std::map<std::pair<int, int>, int> m_grid;
};

#endif /* defined(__Bejeweled__Grid__) */
