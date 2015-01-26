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
#include <CoreFoundation/CoreFoundation.h>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "Grid.h"

class Window
{
public:
    //Constructor
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
    
    //Grab and apply jewels to screen surface.
    void applyJewels();
    
    //Draw background and jewel objects.
    void drawGame();
    
    //Loads images to Surface object.
    //'obj' object to load image to.
    //'path' image path
    //returns bool indicating if image has been loaded.
    bool loadImage(SDL_Surface** obj, const std::string& path);
    
    //Loads jewel images.
    void loadJewels();
    
    //Carry out swap of two adjacent jewels
    //'swapper' is key to jewel actively being swapped
    //'event' indicates which direction the swap was requested
    //'1' left, '2' right, '3' above, '4' below.
    void swapJewels(std::pair<int,int>& swapper, const int event);
    
    void performSwap(const std::pair<int,int>& swapper, const std::pair<int,int>& swapped);
    
    //Updates grid containing jewels, swapping two jewels indicated.
    //'lower' jewel to be swapped.
    //'higher' jewel to be swapped.
    void gridSwap(std::pair<int, int> lower, std::pair<int, int> higher);
    
    //Initialise jewels on screen.
    void initialAnimation();
    
    //Perform animation of jewel swap.
    //'jewel' is jewel where swap was activated.
    //Returns bool indicating if jewel needs to be re-rendered
    bool swapAnimation(std::pair<int, int> jewel);
    
    //Flicker jewels which have been combined before substituting them.
    void flickerAnimation();
    
    //Function used to update and drop jewels after combination.
    //'spawn' indicating if jewels have just been spawned.
    void dropAnimation(bool spawn);
    
    //The window.
    SDL_Window* m_window;
    
    //The surface contained by the window
    SDL_Surface* m_screenSurface = NULL;
    
    //The bakground image
    SDL_Surface* m_background = NULL;
    
    //The jewels
    std::vector<SDL_Surface*> m_jewels;
    
    //Sound effects
    Mix_Chunk* m_soundSwap = NULL;
    Mix_Chunk* m_soundCombine = NULL;
    Mix_Chunk* m_soundSpawn = NULL;
    Mix_Chunk* m_soundNoSwap = NULL;
    Mix_Chunk* m_soundStart = NULL;
    
    //Jewels grid.
    Grid m_grid;
    
    //Key used in jewels map to indicate jewel which should be drawn on top.
    std::pair<int, int> m_top_jewel;
};

#endif /* defined(__Bejeweled__Window__) */
