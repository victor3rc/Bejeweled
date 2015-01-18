//
//  Jewel.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 17/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#include "Jewel.h"

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

bool Jewel::handleEvent( SDL_Event* e )
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
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    
                    if(m_drag)
                    {
                        //Move with mouse
                        setPosition(x-m_x_click, y-m_y_click);
                    }
                    
                    return true;
                    
                case SDL_MOUSEBUTTONDOWN:
                    
                    setClickLocation(x, y);
                    
                    m_drag = true;
                    
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    m_drag = false;
                    break;
            }
        }
    }
    
    return false;
}

void Jewel::setClickLocation(int x, int y)
{
    m_x_click = x - m_position.x;
    m_y_click = y - m_position.y;
}






