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
    int value() { return m_value; };
    
    //Sets coordinates.
    void setPosition(int x, int y);
    
    //Sets jewel identifier value.
    void setValue(int val);
    
    //Handles mouse event
    void handleEvent( SDL_Event* e );
    
private:
    //Top left position
    SDL_Point m_position;
    
    //Jewel identifier value.
    int m_value;
    
    const int JEWEL_WIDTH = 70;
    const int JEWEL_HEIGHT = 70;
};

#endif /* defined(__Bejeweled__Jewel__) */
