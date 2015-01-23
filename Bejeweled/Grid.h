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
    std::map<std::pair<int, int>, Jewel>& grid();
    
    //Check if jewels in grid give a combination.
    //returns bool indicating if any combinations were found.
    bool findCombinations();
    
    //Find jewels which need to drop.
    //returns vector with all keys to jewels to be dropped.
    std::vector<std::pair<int,int>> setDroppers();
    
    //Move jewel to a new position in grid.
    //'moved' is key to jewel to be moved.
    //'space' is key to space to be moved into.
    void moveJewel(const std::pair<int,int>& moved, const std::pair<int,int>& space);
    
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
    
    //Combines jewels in lower and higher indexes to the one given.
    //'key' is key of jewel to be combined in grid.
    //'lower' is the number of jewels lower in the relevant index that are to be combined.
    //'higher' is the number of jewels higher in the relevant index that are to be combined.
    //'x_axis' indicates if jewels to combine are in x-axis (true) or y-axis (false).
    void combine(const std::pair<int,int>& key, int lower, int higher, bool x_axis);
    
    //Check if jewels jewel given need to be dropped also.
    //'current' is key to jewel which check will be carried on.
    void dropAbove(std::pair<int, int> current);
    
    //Checks jewels around jewel given, to see if there is a combination.
    //'key' is jewel indicating jewel to check for.
    bool matchAround(const std::pair<int,int>& key);
    
    //Grid
    std::map<std::pair<int, int>, Jewel> m_grid;
};

#endif /* defined(__Bejeweled__Grid__) */
