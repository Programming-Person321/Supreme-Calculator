#include "include/utilities.hpp"
#include "include/window.hpp"

SDL_Texture* createBackground(){
      int width, height;
      SDL_GetRendererOutputSize(renderer, &width, &height);

      SDL_Texture* image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
      SDL_SetRenderTarget(renderer, image);

      int ** noise = new int*[width];
      for(int i = 0; i < width; i++){
      noise[i] = new int[height];
      }

      for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
            bool x (i > 0);
            bool y (j > 0);

            if(x && y) {
                  int avx = (noise[i-1][j] + noise[i][j-1])/2;
                  noise[i][j] = {avx + ((rand()%3)-2)};
            }else if(x){
                  int avx = (noise[i-1][j]);
                  noise[i][j] = {avx + ((rand()%3)-2)};
            }else if(y){
                  int avx = (noise[i][j-1]);
                  noise[i][j] = {avx + ((rand()%3)-2)};
            }else      {
                  noise[i][j] = {(rand()%255)};
            }

            noise[i][j] = noise[i][j]%255;

            SDL_SetRenderDrawColor(renderer, noise[i][j], noise[i][j], noise[i][j], 255);
            SDL_RenderDrawPoint(renderer, i, j);
      }
      }

      for(int i = width; i > 0;){
            delete[] noise[--i];
      }
      delete[] noise;

      SDL_SetRenderTarget(renderer, NULL);
      return image;
}