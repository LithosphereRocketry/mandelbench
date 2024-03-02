#include <SDL2/SDL.h>

size_t dim;

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL not initialized: %s", SDL_GetError());
        return -1;
    }

    if(argc < 2 || !strcmp(argv[1], "8")) {
        dim = 256;   
    } else {
        printf("Unrecognized size option: %s", argv[1]);
    }


    SDL_Window* window = SDL_CreateWindow("MandelView", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, dim, dim, SDL_WINDOW_SHOWN );
    if(!window) {
        printf("SDL window creation failed: %s", SDL_GetError());
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
    for(int y = 0; y < dim; y++) {
        for(int x = 0; x < dim; x += 4) {
            int c = getchar();
            char c_val;
            if(c >= 'a' && c <= 'f') {
                c_val = c - 'a' + 10;
            } else if(c >= 'A' && c <= 'F') {
                c_val = c - 'A' + 10;
            } else if(c >= '0' && c <= '9') {
                c_val = c - '0';
            } else {
                printf("Unrecognized character %c (0x%hhx)", c, c);
                return -1;
            }

            for(int i = 0; i < 4; i++) {
                if(c_val & (1 << (3 - i))) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                }
                SDL_RenderDrawPoint(renderer, x + i, y);
            }
        }
    }
    SDL_RenderPresent(renderer);
    int quit = 0;
    while(!quit) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }
        SDL_Delay(1);
    }
}