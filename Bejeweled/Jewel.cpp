//
//  Jewel.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 17/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#include "Jewel.h"

using namespace std;

Jewel::Jewel()
{
    m_drag = false;
}

void Jewel::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;
}

void Jewel::setIdentifier(int val)
{
    m_id = val;
}

void Jewel::stopDragging()
{
    m_drag = false;
}

int Jewel::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        
        //Check if mouse is in button
        bool inside = true;
        
        //Mouse is left of the button
        if( x < m_position.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > m_position.x + JEWEL_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        if( y < m_position.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > m_position.y + JEWEL_HEIGHT )
        {
            inside = false;
        }
        
        //Mouse is inside button
        if(inside)
        {
            //Set mouse over sprite
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                    
                    if(m_drag)
                    {
                        //Check for a swap, only if mouse is being dragged.
                        return swap(x, y);
                    }
                    
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    
                    if(e->button.button == SDL_BUTTON_LEFT)
                    {
                        setClickLocation(x, y);
                        m_drag = true;
                    }
                    
                    break;
            }
        }
    }
    
    return 0;
}

void Jewel::setClickLocation(int x, int y)
{
    m_x_click = x;
    m_y_click = y;
}

int Jewel::swap(int x, int y)
{
    //Swap left
    if(x < m_x_click - SWAP_SCOPE && m_position.x > LEFT_COLUMN)
    {
        return 1;
    }
    //Swap right.
    else if (x > m_x_click + SWAP_SCOPE && m_position.x < RIGHT_COLUMN)
    {
        return 2;
    }
    //Swap above.
    else if(y < m_y_click - SWAP_SCOPE && m_position.y > TOP_ROW)
    {
        return 3;
    }
    //Swap below.
    else if(y > m_y_click + SWAP_SCOPE && m_position.y < BOTTOM_ROW)
    {
        return 4;
    }
    
    //No swap.
    return 0;
}













