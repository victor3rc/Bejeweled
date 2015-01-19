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
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int GRID_SIZE = 8;

//Indicates pixels to be moved at a time during swap.
const int SWAP_SPEED = 5;

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
    Jewel();
    
    //Return coordinates.
    int x() { return m_position.x; };
    int y() { return m_position.y; };
    
    //Return jewel identifier value.
    int value() { return m_id; };
    
    //Return bool to indicate if jewel can be rendered.
    bool render() { return m_render; };
    
    //Sets coordinates.
    void setPosition(int x, int y);
    
    //Sets jewel identifier value.
    void setIdentifier(int val);
    
    //Used to indicate if jewel is to be rendered or not.
    void setDraw(bool render);
    
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
    int swap(int x, int y);
    
    //Top left position
    SDL_Point m_position;
    
    //Jewel identifier value.
    int m_id;
    
    //bool to indicated whether jewel is being clicked on.
    bool m_drag;
    
    //bool to indicate if jewel is to be rendered.
    bool m_render;
    
    //Coordinates where mouse was clicked.
    int m_x_click, m_y_click;
    
};

#endif /* defined(__Bejeweled__Jewel__) */
