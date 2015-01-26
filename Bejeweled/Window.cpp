//
//  Window.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 15/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//
#include <stdio.h>
#include <SDL_image.h>
#include <CoreFoundation/CoreFoundation.h>

#include "Window.h"

using namespace std;

Window::Window()
{
    //Start up SDL and create window
    if(!init())
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        CFURLRef appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("Backdrop13"), CFSTR("jpg"), NULL);
        CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
        const char* background = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("woosh"), CFSTR("wav"), NULL);
        filePathRef = CFURLCopyPath(appUrlRef);
        const char* swap = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("blop"), CFSTR("wav"), NULL);
        filePathRef = CFURLCopyPath(appUrlRef);
        const char* combine = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("bubble"), CFSTR("wav"), NULL);
        filePathRef = CFURLCopyPath(appUrlRef);
        const char* spawn = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("boo"), CFSTR("wav"), NULL);
        filePathRef = CFURLCopyPath(appUrlRef);
        const char* noSwap = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        //Load background image.
        if(!loadImage(&m_background, background))
        {
            printf("Cannot load image %s! SDL Error: %s\n", background, SDL_GetError());
        }
        
        //Load jewels.
        loadJewels();
        
        //Load sound effects
        m_soundSwap = Mix_LoadWAV(swap);
        m_soundCombine = Mix_LoadWAV(combine);
        m_soundSpawn = Mix_LoadWAV(spawn);
        m_soundNoSwap = Mix_LoadWAV(noSwap);
        
        // Release references
        CFRelease(filePathRef);
        CFRelease(appUrlRef);
    }
}

void Window::start()
{
    //Event handler
    SDL_Event e;
    
    //Populate grid
    m_grid.populate();
    
    //Draw background and jewels.
    drawGame();
    
    //Key to consult jewels.
    pair<int, int> swapper;
    
    //indicates when there is a swap
    bool dropped = false;
    
    //Handle events on queue
    while(SDL_WaitEvent(&e) != 0)
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            break;
        }
        
        //int to indicate which jewel to swap.
        int swap_event = 0;
        
        //Handle events in jewels
        for(int x = 0; x < GRID_SIZE; ++x)
        {
            for(int y = 0; y < GRID_SIZE; ++y)
            {
                swapper = make_pair(x, y);
                
                //Find out which jewel to swap for
                swap_event = m_grid[swapper].handleEvent(&e);
                
                //If jewel has been dragged to swap
                if(swap_event != 0)
                {
                    dropped = false;
                    
                    //Carry out swap
                    swapJewels(swapper, swap_event);
                    
                    //If combinations were made, drop jewels
                    while(m_grid.findCombinations())
                    {
                        //Flicker jewels before disappearing.
                        flicker();
                        
                        //Play combination swap.
                        Mix_PlayChannel(-1, m_soundCombine, 0);
                        SDL_Delay(100);
                        
                        dropJewels(false);
                        SDL_Delay(500);
                        
                        dropped = true;
                    }
                    
                    //if not dropped, swap back
                    if(!dropped)
                    {
                        //Play no swap sound.
                        Mix_PlayChannel(-1, m_soundNoSwap, 0);
                        
                        //swap_event needs to change to indicate opposite direction.
                        //Change hardcoded bits?
                        if(swap_event == 1 || swap_event == 3)
                        {
                            swapJewels(swapper, ++swap_event);
                        }
                        else
                        {
                            swapJewels(swapper, --swap_event);
                        }
                    }
                    //else, spawn new jewels.
                    else
                    {
                        Mix_PlayChannel(-1, m_soundSpawn, 0);
                        
                        //Spawn new jewels.
                        dropJewels(true);
                    }
                }
            }
        }
    }
}

void Window::close()
{
    //Deallocate background;
    SDL_FreeSurface(m_background);
    m_background = NULL;
    
    //Deallocate screen
    SDL_FreeSurface(m_screenSurface);
    m_screenSurface = NULL;
    
    //deallocate jewels
    for(auto& jewel : m_jewels)
    {
        SDL_FreeSurface(jewel);
        jewel = NULL;
    }
    
    //Free sound effects
    Mix_FreeChunk(m_soundSwap);
    Mix_FreeChunk(m_soundCombine);
    Mix_FreeChunk(m_soundSpawn);
    Mix_FreeChunk(m_soundNoSwap);
    
    //Destroy window
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    
    //Close the mixer
    Mix_CloseAudio();
    
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
        
        //Initialise sound effects
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
        {
            output = false;
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
    map<pair<int, int>, Jewel> grid = m_grid.grid();
    
    for(auto& jewel : grid)
    {
        if(jewel.first != m_top_jewel)
        {
            //apply jewel in place, if available.
            if(!jewel.second.vacant())
            {
                if(jewel.first.first >= 0)
                {
                    applySurface(jewel.second.x(), jewel.second.y(), m_jewels[jewel.second.color()], m_screenSurface);
                }
            }
        }
    }
    
    //apply jewel to appear on top of all other jewels last.
    applySurface(grid[m_top_jewel].x(), grid[m_top_jewel].y(), m_jewels[grid[m_top_jewel].color()], m_screenSurface);
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
    CFURLRef appUrlRef;
    CFStringRef filePathRef;
    
    //Hardcoded.. change.
    for(int i = 1; i < 6; ++i)
    {
        CFStringRef relativePath = CFStringCreateWithFormat(NULL, NULL, CFSTR("Color-%d"), i);
        appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(), relativePath, CFSTR("png"), NULL);
        filePathRef = CFURLCopyPath(appUrlRef);
        string path = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
        
        SDL_Surface* jewel = NULL;
        
        m_jewels.push_back(jewel);
        
        //Load image.
        if(!loadImage(&m_jewels.at(i-1), path))
        {
            printf("Cannot load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
    }
    
    // Release references
    CFRelease(filePathRef);
    CFRelease(appUrlRef);
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

bool Window::swapAnimation(pair<int, int> jewel)
{
    //Original fixed coordinates of jewel doing the swapping.
    int x_orig = m_grid[jewel].xOrig(), y_orig = m_grid[jewel].yOrig();
    
    //flag to indicate if swap needs to be rendered
    bool output = false;
    
    //swap on horizontal axis
    if(m_grid[jewel].x() != x_orig)
    {
        if(m_grid[jewel].x() < x_orig)
        {
            m_grid[jewel].setPosition(m_grid[jewel].x() + SWAP_SPEED, y_orig);
        }
        else
        {
            m_grid[jewel].setPosition(m_grid[jewel].x() - SWAP_SPEED, y_orig);
        }
        
        output = true;
    }
    else if(m_grid[jewel].y() != y_orig)
    {
        if(m_grid[jewel].y() < y_orig)
        {
            m_grid[jewel].setPosition(x_orig, m_grid[jewel].y() + SWAP_SPEED);
        }
        else
        {
            m_grid[jewel].setPosition(x_orig, m_grid[jewel].y() - SWAP_SPEED);
        }
        
        output = true;
    }
    
    return output;
}

void Window::indicateSwap(std::pair<int, int> lower, std::pair<int, int> higher)
{
    //swap jewel colors.
    int tempColor = m_grid[lower].color();
    m_grid[lower].setColor(m_grid[higher].color());
    m_grid[higher].setColor(tempColor);
    
    //Indicate they are not being dragged any longer.
    m_grid[lower].stopDragging();
    m_grid[higher].stopDragging();
    
    //indicate jewels are located in each other's fixed position.
    m_grid[lower].setPosition(m_grid[higher].xOrig(), m_grid[higher].yOrig());
    m_grid[higher].setPosition(m_grid[lower].xOrig(), m_grid[lower].yOrig());
}

void Window::dropJewels(bool spawn)
{
    //Find jewels to be dropped.
    vector<pair<int,int>> droppers;
    
    if(spawn)
    {
        droppers = m_grid.spawn();
    }
    else
    {
        droppers = m_grid.setDroppers();
    }
    
    bool dropping;
    
    //if found no droppers redraw game in case jewels were combined at the top rows (i.e. no droppers)
    if(droppers.size() == 0)
    {
        drawGame();
    }
    else
    {
        do
        {
            dropping = false;
            
            for(auto& jewel : droppers)
            {
                if(m_grid[jewel].y() < m_grid[jewel].yOrig())
                {
                    //Adjust coordinates for jewel to drop
                    m_grid[jewel].setPosition(m_grid[jewel].x(), m_grid[jewel].y() + DROP_SPEED);
                    
                    //indicating jewels are dropping
                    dropping = true;
                }
            }
            
            //Re-render if still dropping.
            if(dropping)
            {
                drawGame();
            }
            
        }while(dropping);
    }
}

void Window::swapJewels(std::pair<int, int>& swapper, const int event)
{
    pair<int,int> swapped;
    
    //swap jewels in grid.
    //update m_position.
    switch(event)
    {
        case 1:
            //Swap left.
            swapped = make_pair(swapper.first, swapper.second-1);
            break;
        case 2:
            //Swap right.
            swapped = make_pair(swapper.first, swapper.second+1);
            break;
        case 3:
            //Swap above.
            swapped = make_pair(swapper.first-1, swapper.second);
            break;
        case 4:
            //Swap below
            swapped = make_pair(swapper.first+1, swapper.second);
            break;
    }
    
    performSwap(swapped, swapper);
    
    //Set jewel clicked on as top jewel.
    m_top_jewel = swapper;
    
    //Update swapper to indicate where its jewel is on the grid.
    swapper.first = swapped.first;
    swapper.second = swapped.second;
}

void Window::performSwap(const std::pair<int, int> &swapper, const std::pair<int, int> &swapped)
{
    //swap jewels in grid, updating current position.
    indicateSwap(swapper, swapped);
    
    bool render;
    
    //play swap sound
    Mix_PlayChannel(-1, m_soundSwap, 0);
    SDL_Delay(100);
    
    //while swap needs to be rendered.
    do
    {
        drawGame();
        
        render = false;
        
        if(swapAnimation(swapper))
        {
            render = true;
        }
        
        if(swapAnimation(swapped))
        {
            render = true;
        }
        
    }while(render);
}

void Window::flicker()
{
    //jewel being analysed.
    pair<int,int> current;
    
    //jewels in grid to be flickered.
    vector<pair<int,int>> flickered;
    
    //Cycle through jewels to find the ones meant to be flickered.
    for(int x = 0; x < GRID_SIZE; ++x)
    {
        for(int y = 0; y < GRID_SIZE; ++y)
        {
            current = make_pair(x, y);
            
            if(m_grid[current].vacant())
            {
                flickered.push_back(current);
            }
        }
    }
    
    //Flicker jewels selected
    for(int i = 0; i < FLICKER; ++i)
    {
        for(auto& jewel : flickered)
        {
            if(m_grid[jewel].vacant())
            {
                m_grid[jewel].setVacant(false);
            }
            else
            {
                m_grid[jewel].setVacant(true);
            }
        }
        
        //Re-render after each flick.
        drawGame();
        SDL_Delay(50);
    }
    
    //Reset jewels
    for(auto& jewel : flickered)
    {
        if(!m_grid[jewel].vacant())
        {
            m_grid[jewel].setVacant(true);
        }
    }
}













