//
//  main.cpp
//  Bejeweled
//
//  Created by Victor Cardozo on 14/01/2015.
//  Copyright (c) 2015 Victor Cardozo. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>

#include "Window.h"

int main(int argc, char** argv)
{
    Window win;
    
    win.start();
    win.close();
    
    return 0;
}
