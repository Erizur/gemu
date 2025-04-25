#include <stdio.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

static void render(SDL_Renderer* const renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (float i = 0; i < WINDOW_WIDTH; ++i) {
        SDL_RenderPoint(renderer, i, i);
    }

    SDL_RenderPresent(renderer);
}

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_CreateWindowAndRenderer("gemu", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    bool exit = false;

    while (!exit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    exit = true;
                    break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    switch (event.key.key) {
                        case SDLK_UP: {
                            SDL_Log("up");
                            break;
                        }
                        default: {
                            SDL_Log("some other key");
                        }
                    }
                    break;
                }
                default: {
                }
            }

            SDL_DelayNS(1e9 / 60);
        }

        render(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
