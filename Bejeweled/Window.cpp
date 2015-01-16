//
//  Window.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 15/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//
#include <stdio.h>
#include <SDL_image.h>

#include "Window.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const int JEWEL_DIMENSION = 70;
const int CUSHION = 15;

Window::Window()
{
    string background_path = "Images/Backdrop13.jpg";
    
    //Load background image.
    if(!loadImage(&m_background, background_path.c_str()))
    {
        printf("Cannot load image %s! SDL Error: %s\n", background_path.c_str(), SDL_GetError());
    }
    
    //Load jewels.
    loadJewels();
}

void Window::start()
{
    //Start up SDL and create window
    if(!init())
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Main loop flag
        bool quit = false;
        
        //Event handler
        SDL_Event e;
        
        //Populate grid
        m_grid.populate();
        
        //Add background image
        applySurface(0, 0, m_background, m_screenSurface);
        
        //Add jewels.
        applyJewels();
        
        //Update the surface
        SDL_UpdateWindowSurface(m_window);
        
        while(!quit)
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }
        }
        
    }
}

void Window::close()
{
    //Deallocate surface
    SDL_FreeSurface(m_background);
    m_background = NULL;
    
    //Destroy window
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

bool Window::init()
{
    //output flag
    bool output = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize window: %s\n", SDL_GetError() );
        output = false;
    }
    else
    {
        //Create window
        m_window = SDL_CreateWindow( "Bejeweled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if( m_window == NULL )
        {
            printf( "Cannot create Window: %s\n", SDL_GetError() );
            output = false;
        }
        else
        {
            //Get window surface
            m_screenSurface = SDL_GetWindowSurface(m_window);
        }
    }
    
    return output;
}

void Window::applySurface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    //rectangle used for coordinates.
    SDL_Rect rectangle;
    
    rectangle.x = x;
    rectangle.y = y;
    
    //Apply surface.
    SDL_BlitSurface(source, NULL, destination, &rectangle);
}

void Window::applyJewels()
{
    auto jewels = m_grid.grid();
    
    //Initial coordinates
    int init_x = (SCREEN_WIDTH-(m_grid.size()*JEWEL_DIMENSION)-(CUSHION*(m_grid.size()-1)))/2;
    int init_y = (SCREEN_HEIGHT-(m_grid.size()*JEWEL_DIMENSION)-(CUSHION*(m_grid.size()-1)))/2;
    
    //Coordinates used to apply jewels
    int coord_x = init_x, coord_y = init_y;
    
    for(int x = 0; x < m_grid.size(); ++x)
    {
        for(int y = 0; y < m_grid.size(); ++y)
        {
            int index = jewels[make_pair(x,y)];
            
            applySurface(coord_x, coord_y, m_jewels.at(index), m_screenSurface);

            //add cushion to coordinates.
            coord_x += JEWEL_DIMENSION + CUSHION;
        }
        
        //update coordinates.
        coord_x = init_x;
        coord_y += JEWEL_DIMENSION + CUSHION;
    }
}

bool Window::loadImage(SDL_Surface** obj, const string& path)
{
    //Output flag
    bool output = true;
    
    //Load splash image
    *obj = IMG_Load(path.c_str());
    
    if( obj == NULL )
    {
        printf( "Cannot load image %s: %s\n", path.c_str(), SDL_GetError() );
        output = false;
    }
    
    return output;
}

void Window::loadJewels()
{
    //Hardcoded.. change.
    for(int i = 1; i < 6; ++i)
    {
        string path = "Images/Color-" + to_string(i) + ".png";
        
        SDL_Surface* jewel = NULL;
        
        m_jewels.push_back(jewel);
        
        //Load image.
        if(!loadImage(&m_jewels.at(i-1), path))
        {
            printf("Cannot load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
    }
}






