#include "ImageUtil.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::string;
using std::cout;
using std::endl;

bool ImageUtil::loadImage(const char *fileName, string &s)
{
    SDL_Surface* img = IMG_Load(fileName);
    if( !img ){
        cout << "Load Image " << fileName << " failed: "
             << IMG_GetError() << endl;
        return false;
    }
    s = (char*)img->pixels;
    SDL_FreeSurface(img);

    return true;
}
