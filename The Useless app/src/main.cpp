#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


int main(int argc, char **argv) 
{
    int Running = true;
    bool showMessage = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Screen initializers
    SDL_Window *window = SDL_CreateWindow("The useless app",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = IMG_Load("sprites/LeverSpriteSheet.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Event ev;
    SDL_Color Black = {0, 0, 0};


    //Animation rectangles Initializers
    SDL_Rect srcrect = { 0, 0, 280, 380 };
    SDL_Rect dsrect = { 0, 0, 280, 380 };

    Uint32 startTime = SDL_GetTicks(); // Record the start time
    const int frameTime = 10; // Time in milliseconds per frame
    int spriteFrame = 0;

    SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255); //set Background color
    SDL_RenderClear(renderer);
    
    if(!image)
    {
        std::cerr << "SDL_Image Initialization failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() != 0) 
    {
        std::cerr << "SDL_ttf Initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    TTF_Font * Sans = TTF_OpenFont("fonts/Sans.ttf", 24);
    if (!window) 
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        TTF_CloseFont(Sans);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    if (!renderer) 
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_CloseFont(Sans);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    if (!Sans) 
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, "   This   app   is   Useless", Black);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = 300;
    Message_rect.h = 100;

    // Render the text texture on the window
    SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);
    // Update the window
    SDL_RenderPresent(renderer);
    SDL_Delay(100);

    while (Running) 
    {
        while (SDL_PollEvent(&ev)) 
        {
            if (ev.type == SDL_QUIT)
                Running = false;
            
            else if (ev.type == SDL_MOUSEBUTTONUP)
            {
                // Calculate the time elapsed since the start
                 Uint32 elapsedTime = SDL_GetTicks() - startTime;

                // Calculate the current frame based on elapsed time and frame time
                spriteFrame = (elapsedTime / frameTime) % 2; // Change 2 to the number of frames you have

            }
        }
         // Calculate the time elapsed since the start
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        // Update the source rectangle to display the correct frame
        srcrect.x = spriteFrame * 280;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcrect, &dsrect);
        SDL_RenderCopy(renderer, Message, nullptr, &Message_rect);
        SDL_RenderPresent(renderer);
        
    }

    // Clean up and exit
    SDL_DestroyTexture(Message);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(Sans);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();


    return 0;
}
