#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

void draw_poly4(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 150, 0, 255, 255);
	SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
	SDL_RenderDrawLine(renderer,x2,y2,x3,y3);
	SDL_RenderDrawLine(renderer,x3,y3,x4,y4);
	SDL_RenderDrawLine(renderer,x4,y4,x1,y1);
}

int main(void) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	draw_poly4(20,20,160,40,160,120,20,140,renderer);
	SDL_RenderPresent(renderer);
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}