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

//#ifdef __APPLE__
//#include "CoreFoundation/CoreFoundation.h"
//#endif
//
//// ----------------------------------------------------------------------------
//// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
//#ifdef __APPLE__
//CFBundleRef mainBundle = CFBundleGetMainBundle();
//CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
//char path[PATH_MAX];
//if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
//{
//    // error!
//}
//CFRelease(resourcesURL);
//
//chdir(path);
//std::cout << "Current Path: " << path << std::endl;
//#endif
//// ----------------------------------------------------------------------------

int main(int argc, char** argv)
{
    Window win;
    
    win.start();
    win.close();
    
    return 0;
}
