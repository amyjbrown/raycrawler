// Main file!
#include <iostream>
#include "SDL2/SDL.h"
#include "myinclude/myinclude.hpp"

using namespace std;

// Global Defines
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define frameRate 17 // 17 milliseconds per frame for 60FPS

// World map, array of ints
int worldMap[mapWidth][mapHeight] = 
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};
//function to create a Color value
Uint32 Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha=255){
  return (red << 24) | (green << 16) | (blue << 8) | alpha;
}
//function update value in array
void blit_pixel(Uint32* parray, int x, int y, Uint32 color){
  parray[y * screenWidth + x] = color;
}


SDL_Renderer* init(){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) 
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return nullptr;
    }
    // Crate window with appropriate size
    SDL_Window* window = SDL_CreateWindow(
      "Raytracing :)",
      SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
      screenWidth, screenHeight,
      0
    );
    if (window == nullptr) 
    {
      SDL_Log("Unable to create window: %s", SDL_GetError()); 
      return nullptr;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(
      window,
      -1,
      0
    );

    if (renderer == nullptr) 
    {
      SDL_Log("Unable to create renderer: %s", SDL_GetError()); 
      return nullptr;
    }
    // Clear the screen to PureGreen
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //SDL_RenderFillRect(renderer, nullptr);
    //SDL_RenderPresent(renderer);
    return renderer;
}

void shutdown(){
  SDL_Quit();
  exit(3);
}

int main( int argc, char* argv[] )
{
    //SDL init
    auto renderer = init();
    if (renderer == nullptr) shutdown();

    
    SDL_Texture* texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      screenWidth, screenHeight
    );

    // Player Position (x,y)
    double posX = 22, posY = 12;
    // Player Direction Vector
    double dirX = -1, diyY = 0;
    // the 2d raycaster version of camera plane, here camera line
    double planeX = 0, planeY = 0.66;

    double time = 0; // current time frame
    double oldTime = 0;
 
    printf("Hello world, we done!\n");
    // it goes (y, x) instead of x, y
    Uint32* pixel_array = (Uint32*) malloc(sizeof(Uint32) * screenWidth * screenHeight);
    memset(pixel_array, 0, sizeof(Uint32) * screenHeight * screenWidth);

    SDL_Event poll_event; 
    while(true) {
      // Update Info
      while(SDL_PollEvent(&poll_event)){
        if (poll_event.type == SDL_QUIT) {
          SDL_Log("Exit detected, leaving...");
          shutdown();
        }
      }
      // Update screen texture
      for(Uint32 y = 0; y < screenHeight; y++){
        for(Uint32 x = 0; x < screenWidth; x++){
          blit_pixel(pixel_array,
            x, y,
            Color(0x77, 0x77, 0x77));
        }
      }
      // write texture to renderer, update screen, and render update
      // SDL_RenderPresent(renderer);

    }

    SDL_Quit();
    return 0;
}