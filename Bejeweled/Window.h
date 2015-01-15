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
    
private:
    //Initialises window.
    bool init();
    
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
