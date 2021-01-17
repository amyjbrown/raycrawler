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
      SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_STREAMING,
      screenWidth, screenHeight
    );
 
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
    // Player Position (x,y)
    double posX = 22, posY = 12;
    // Player Direction Vector
    double dirX = -1, dirY = 0;
    // the 2d raycaster version of camera plane, here camera line
    double planeX = 0, planeY = 0.66;

    double time = 0; // current time frame
    double oldTime = 0;


    for(int x = 0; x < screenWidth; x++) {
        //calculate ray position and direction
        double cameraX = 2 * x / double(screenWidth) - 1; //x-coordinate in camera space
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX=int(posX), mapY=int(posY);
        double sideDistX, sideDistY;
        double deltaDistX = std::abs(1 / rayDirX);
        double deltaDistY = std::abs(1 / rayDirY);
        double perpWallDist;
        // what dirction to step in: x or y (either +1 or -1)
        int stepX, stepY;
        int hit = 0; // was theer a wall hit
        int side; // was a NS EW wall hit 

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        } 
        //DDA algorithim
        while (hit==0) {
            // jump to next map square, OR in x direaction or Y
            if (sideDistX < sideDistY) {
                sideDistX 
            }
        }
    }

      // write texture to renderer, update screen, and render update
      // SDL_RenderPresent(renderer);
    SDL_UpdateTexture(texture, NULL, pixel_array, 640 * sizeof (Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    }

    SDL_Quit();
    return 0;
}