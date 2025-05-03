#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void main_loop()
{
    // Clear screen to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw red square
    SDL_Rect rect = {100, 100, 200, 200};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Red Square",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_SHOWN);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#endif

    while (true)
    {
        main_loop();
        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
