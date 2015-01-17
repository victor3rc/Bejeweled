//
//  Window.h
//  Bejeweled
//
//  Created by Victor Cardozo on 15/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#ifndef __Bejeweled__Window__
#define __Bejeweled__Window__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "Grid.h"

class Window
{
public:
    Window();
    
    //Opens window.
    void start();
    
    //Closes window.
    void close();
    
    int width() { return SCREEN_WIDTH; };
    int height() { return SCREEN_HEIGHT; };
    
private:
    //Initialises window.
    bool init();
    
    //Applies surface on specified destination.
    //'x' is x-axis coordinates.
    //'y' is y-axis coordinates.
    //'source' is surface to be applied.
    //'destination' is surface to be applied to.
    void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
    
    //Grab and apply jewels.
    void applyJewels();
    
    //Loads images to Surface object.
    //'obj' object to load image to.
    //'path' image path
    bool loadImage(SDL_Surface** obj, const std::string& path);
    
    //Loads jewel images.
    void loadJewels();
    
    //The window.
    SDL_Window* m_window;
    
    //The window renderer
    SDL_Renderer* m_renderer = NULL;
    
    //The surface contained by the window
    SDL_Surface* m_screenSurface = NULL;
    
    //The bakground image
    SDL_Surface* m_background = NULL;
    
    //The 1st jewel
    std::vector<SDL_Surface*> m_jewels;
    
    SDL_Surface* m_jewel = NULL;
    
    //Jewels grid.
    Grid m_grid;
};

#endif /* defined(__Bejeweled__Window__) */
