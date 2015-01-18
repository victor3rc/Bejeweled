//
//  Jewel.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 17/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#include "Jewel.h"

Jewel::Jewel()
{}

void Jewel::setPosition( int x, int y )
{
    m_position.x = x;
    m_position.y = y;
}

void Jewel::setValue(int val)
{
    m_value = val;
}

void Jewel::handleEvent( SDL_Event* e )
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
        else if( y < m_position.y )
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

                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    printf("pressed %i-%i\n", this->x(), this->y());
                    break;
                    
                case SDL_MOUSEBUTTONUP:

                    break;
            }
        }
    }
}