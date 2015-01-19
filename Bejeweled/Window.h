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
    
    //Draw background and jewel objects.
    void drawGame();
    
    //Perform swap of two jewels in direction indicated.
    //'lower' is jewel to the left on horizontal swap or above in a vertical swap.
    //'higher' is jewel to the right on horizontal swap or below in a vertical swap.
    //'horizontal' indicates horizontal (true) or vertical (false) swap.
    void swapAnimation(std::pair<int, int> lower, std::pair<int, int> higher, bool horizontal);
    
    //Updates grid containing jewels, swapping two jewels indicated.
    //'lower' jewel to be swapped.
    //'higher' jewel to be swapped.
    void indicateSwap(std::pair<int, int> lower, std::pair<int, int> higher);
    
    //Check for jewels combinations in neighbouring jewels.
    //'swapper' is first jewel swapped
    //'swapped' is the jewel swapped for.
    //'x_axis' indicates if swap was performed on x-axis (true) or y-axis (false)
    void combine(const std::pair<int,int>& swapper, const std::pair<int,int>& swapped, int x_axis);
    
    //Function used to update jewels after combination.
    void updateJewels();
    
    //Drop jewels who have no jewels below.
    //'droppers' are the jeys to the jewels to be dropped.
    void dropAnimation(std::vector<std::pair<int,int>>& droppers);
    
    //The window.
    SDL_Window* m_window;
    
    //The surface contained by the window
    SDL_Surface* m_screenSurface = NULL;
    
    //The bakground image
    SDL_Surface* m_background = NULL;
    
    //The 1st jewel
    std::vector<SDL_Surface*> m_jewels;
    
    //Jewels grid.
    Grid m_grid;
    
    //Key used in jewels map to indicate jewel which should be drawn on top.
    std::pair<int, int> m_top_jewel;
};

#endif /* defined(__Bejeweled__Window__) */
