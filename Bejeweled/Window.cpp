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
        
        //Draw background and jewels.
        drawGame();
        
        while(!quit)
        {
            //Key to consult jewels.
            pair<int, int> swapper, swapped;
            
            //indicates when there is a swap
            bool swap = false;
            
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                
                //int to indicate which jewel to swap.
                int swap_event = 0;
                
                //Handle events in jewels
                for(int x = 0; x < m_grid.size(); ++x)
                {
                    for(int y = 0; y < m_grid.size(); ++y)
                    {
                        swapper = make_pair(x, y);
                        
                        //Find out which jewel to swap for
                        swap_event = m_grid[swapper].handleEvent(&e);
                        
                        //Redraw if swap event relevant.
                        if(swap_event != 0)
                        {
                            //Set jewel clicked on as top jewel.
                            m_top_jewel = swapper;
                            
                            swap = true;
                            
                            switch(swap_event)
                            {
                                case 1:
                                    //Swap left.
                                    swapped = make_pair(swapper.first, swapper.second-1);
                                    swapAnimation(swapped, swapper, true);
                                    combine(swapped, swapper, true);
                                    goto restart;
                                case 2:
                                    //Swap right.
                                    swapped = make_pair(swapper.first, swapper.second+1);
                                    swapAnimation(swapper, swapped, true);
                                    combine(swapper, swapped, true);
                                    goto restart;
                                case 3:
                                    //Swap above.
                                    swapped = make_pair(swapper.first-1, swapper.second);
                                    swapAnimation(swapped, swapper, false);
                                    combine(swapped, swapper, false);
                                    goto restart;
                                case 4:
                                    //Swap below
                                    swapped = make_pair(swapper.first+1, swapper.second);
                                    swapAnimation(swapper, swapped, false);
                                    combine(swapper, swapped, false);
                                    goto restart;
                                default:
                                    swap = false;
                                    continue;
                            }
                        }
                    }
                }
                
                restart:
                continue;
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
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
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
    map<pair<int, int>, Jewel> jewels = m_grid.grid();
    
    for(auto& jewel : jewels)
    {
        if(jewel.first != m_top_jewel)
        {
            //apply jewel in place, if available.
            if(jewel.second.value() != -1 )//render())
            {
                applySurface(jewel.second.x(), jewel.second.y(), m_jewels[jewel.second.value()], m_screenSurface);
            }
        }
    }
    
    //apply jewel to appear on top of all other jewels last.
    applySurface(jewels[m_top_jewel].x(), jewels[m_top_jewel].y(), m_jewels[jewels[m_top_jewel].value()], m_screenSurface);
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

void Window::drawGame()
{
    //Add background image
    applySurface(0, 0, m_background, m_screenSurface);
    
    //Add jewels to screen surface.
    applyJewels();
    
    //Update the surface
    SDL_UpdateWindowSurface(m_window);
}

void Window::swapAnimation(pair<int, int> lower, pair<int, int> higher, bool horizontal)
{
    //Original coordinates of jewel doing the swapping.
    int x_orig = m_grid[higher].x(), y_orig = m_grid[higher].y();
    
    //While swap has not been completed yet.
    while(((m_grid[lower].x() != x_orig && horizontal) ||
          ((m_grid[lower].y() != y_orig) && !horizontal )))
    {
        //Swap
        if(horizontal)
        {
            m_grid[lower].setPosition(m_grid[lower].x() + SWAP_SPEED, y_orig);
            m_grid[higher].setPosition(m_grid[higher].x() - SWAP_SPEED, y_orig);
        }
        else
        {
            m_grid[lower].setPosition(x_orig, m_grid[lower].y() + SWAP_SPEED);
            m_grid[higher].setPosition(x_orig, m_grid[higher].y() - SWAP_SPEED);
        }

        //Update game.
        drawGame();
    }
    
    indicateSwap(lower, higher);
}

void Window::indicateSwap(std::pair<int, int> lower, std::pair<int, int> higher)
{
    //Swap jewels in grid container also.
    Jewel temp = m_grid[lower];
    m_grid[lower] = m_grid[higher];
    m_grid[higher] = temp;
    
    m_grid[lower].stopDragging();
    m_grid[higher].stopDragging();
}

void Window::combine(const pair<int,int>& swapper, const pair<int,int>& swapped, int x_axis)
{
    //indicates if combinations were made
    bool combined = false;
    
    //Check for new combinations for both jewels swapped.
    if(m_grid.findCombinations(swapped))
    {
        combined = true;
        
        drawGame();
    }
    
    if(m_grid.findCombinations(swapper))
    {
        combined = true;
        
        drawGame();
    }
    
    //If no combinations were found, swap jewels back.
    if(combined == false)
    {
        if(x_axis)
        {
            swapAnimation(swapper, swapped, true);
        }
        else
        {
            swapAnimation(swapper, swapped, false);
        }
    }
    else
    {
        updateJewels();
    }
}

void Window::updateJewels()
{
    auto droppers = m_grid.findDroppers();
    
    //Drop jewels.
    dropAnimation(droppers);
}

void Window::dropAnimation(vector<pair<int, int>> &droppers)
{
    //Indicates if jewels are still dropping.
    bool dropping = false;
    
    do
    {
        //Cycle through jewels in gid
        for(auto& jewel : m_grid.grid())
        {
            if(jewel.second.drop())
            {
                jewel.second.setPosition(jewel.second.x(),
                                         jewel.second.y() + DROP_SPEED);
                //printf("%i-%i: %i tar %i\n", jewel.first.first, jewel.first.second, jewel.second.y(), jewel.second.yTarget());
                if(jewel.second.y() >= jewel.second.yTarget())
                {
                    //reset jewel
                    jewel.second.setDrop(false);
                }
                else
                {
                    dropping = true;
                }
            }
        }
        
        drawGame();
    }while(dropping);
}

















