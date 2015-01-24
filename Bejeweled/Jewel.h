//
//  Jewel.h
//  Bejeweled
//
//  Created by Victor Cardozo on 17/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#ifndef __Bejeweled__Jewel__
#define __Bejeweled__Jewel__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

const int GRID_SIZE = 8;

//Indicates pixels to be moved at a time during swap and drop.
const int SWAP_SPEED = 2;
const int DROP_SPEED = 2;

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int CUSHION = 10;

const int JEWEL_WIDTH = 70;
const int JEWEL_HEIGHT = 70;
const int SWAP_SCOPE = 20; //Distance in pixels mouse has to be dragged to activate swap.

//Jewel limit positions
const int LEFT_COLUMN = (SCREEN_WIDTH-(GRID_SIZE*JEWEL_WIDTH)-(CUSHION*(GRID_SIZE-1)))/2;
const int RIGHT_COLUMN = SCREEN_WIDTH-LEFT_COLUMN-JEWEL_WIDTH;
const int TOP_ROW = (SCREEN_HEIGHT-(GRID_SIZE*JEWEL_HEIGHT)-(CUSHION*(GRID_SIZE-1)))/2;
const int BOTTOM_ROW = SCREEN_HEIGHT-TOP_ROW-JEWEL_HEIGHT;

//The mouse button
class Jewel
{
public:
    //Initializes internal variables
    Jewel(int x, int y);
    Jewel();
    
    //Return original coordinates.
    const int& xOrig() { return m_x; };
    const int& yOrig() { return m_y; };
    
    //return current coordinates
    const int& x() { return m_position.x; };
    const int& y() { return m_position.y; };
    
    //Return target coordinates
    const int& xTarget() { return m_target.x; };
    const int& yTarget() { return m_target.y; };
    
    //Return jewel identifier value.
    const int& value() { return m_id; };
    
    //Return bool indicating if space vacant.
    const bool& vacant() { return m_vacant; };
    
    //Returns bool indicating if jewel is to be dropped, and how many spaces.
    const std::pair<bool,int>& drop() { return m_drop; };
    
    //Sets coordinates.
    void setPosition(int x, int y);
    
    //Set target position to drop to.
    void setDropTarget(int x, int y);
    
    //Sets jewel identifier value.
    void setIdentifier(int val);
    
    //Sets jewel to indicate if its space has been left blank.
    void setVacant(bool vacant);
    
    //Indicates if jewel is being dropped or not.
    void setDrop(bool drop, int spaces);
    
    //Indicates swapping has been finalised.
    void stopDragging();
    
    //Handles mouse event
    int handleEvent(SDL_Event* e);
    
private:
    //Updates mouse click location.
    void setClickLocation(int x, int y);
    
    //Find if swap has been activated by mouse drag.
    //'x' coordinate of where mouse was clicked.
    //'y' coordinate of where mouse was clicked.
    //returns int indicating jewel to be swapped with. 1 = left, 2 = right, 3 = above and 4 = below. 0 = no swap.
    int swapClick(int x, int y);
    
    //Top left position coordinates
    int m_x, m_y;
    
    //Current position and drop target coordinates
    SDL_Point m_position, m_target;
    
    //Jewel identifier value. Indicates jewel color
    //1 - Black, 2 - Gray, 3 - pink, 4 - Blue, 5 - orange, 0 - no jewel
    int m_id;
    
    //'m_drag' bool to indicated whether jewel is being clicked on.
    //'m_vacant' indicates if jewel space has been left vacant
    bool m_drag, m_vacant;
    
    //bool to indicate if jewel is to be dropped and integer indicating how many spaces it has to drop.
    std::pair<bool, int> m_drop;
    
    //Coordinates where mouse was clicked.
    int m_x_click, m_y_click;
    
};

#endif /* defined(__Bejeweled__Jewel__) */
