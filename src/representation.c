//#include <stdio.h>
//#include <stdbool.h>
//#include "SDL.h"
//#include "doom_nukem.h"
//#include "math.h"
//
//
////void	apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend)
////{
////    SDL_Rect pos;
////
////    pos.x = x;
////    pos.y = y;
////    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
////    SDL_RenderCopy(rend, tex, NULL, &pos);
////}
//
////Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//#define POINTS_COUNT 2
//
////static SDL_Point points[POINTS_COUNT] = {
////        {100, 100},
////        {100, 300},
//////        {140, 240},
//////        {120, 200}
////};
//
//void representation()
//{
//    int wx1 = 70;
//    int wy1 = 70;
//    int wx2 = 200;
//    int wy2 = 200;
//
//
//
//    double tx1;
//    double tx2;
//    double tz1;
//    double tz2;
//    double ty1;
//    double ty2;
//
//
//    double px = 50;
//    double py = 100;
//    double angle = 0.0;
//
//    if (SDL_Init(SDL_INIT_VIDEO) == 0 ) {
//        t_sdl_main sdl;
//        if (SDL_CreateWindowAndRenderer(640, 480, 0, &sdl.window, &sdl.renderer) == 0) {
//            sdl.done = SDL_FALSE;
//
//            while (!sdl.done)
//            {
//                tx1 = wx1 - px;
//                ty1 = wy1 - py;
//                tx2 = wx2 - px;
//                ty2 = wy2 - py;
//                tz1 = tx1 * cos(angle) + ty1 * sin(angle);
//                tz2 = tx2 * cos(angle) + ty2 * sin(angle);
//                tx1 = tx1 * sin(angle) - ty1 * cos(angle);
//                tx2 = tx2 * sin(angle) - ty2 * cos(angle);
//
//                SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//                SDL_RenderClear(sdl.renderer);
//
//                SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
////                SDL_RenderDrawLines(sdl.renderer, points, POINTS_COUNT);
//                /* Transormed map */
//
////                SDL_RenderDrawLine(sdl.renderer, wx1, wy1, wx2, wy2);
//                SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//                SDL_RenderDrawLine(sdl.renderer, 50 - tx1, 50 - tz1, 50 - tx2, 50 - tz2);
//                SDL_RenderDrawPoint(sdl.renderer, 50, 50);
//
//                /* Absolute map
//                SDL_RenderDrawLine(sdl.renderer, wx1, wy1, wx2, wy2);
//                SDL_SetRenderDrawColor(sdl.renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//                SDL_RenderDrawLine(sdl.renderer, px, py, cos(angle) * 5 + px, sin(angle) * 5 + py);
//                SDL_RenderDrawPoint(sdl.renderer, px, py);
//                */
//                 SDL_RenderPresent(sdl.renderer);
//
//                while (SDL_PollEvent(&sdl.event))
//                {
//                    if (sdl.event.key.keysym.sym == 'w')
//                    {
//                        px += cos(angle);
//                        py += sin(angle);
//                    }
//                    if (sdl.event.key.keysym.sym == 's')
//                    {
//                        px -= cos(angle);
//                        py -= sin(angle);
//                    }
//                    if (sdl.event.key.keysym.sym == 'd')
//                    {
//                        angle -= 0.5;
//                    }
//                    if (sdl.event.key.keysym.sym == 'a')
//                    {
//                        angle += 0.5;
//                    }
//                    if ((sdl.event.type == SDL_QUIT) ||
//                            sdl.event.type == SDL_KEYDOWN &&
//                                    (SDL_SCANCODE_ESCAPE == sdl.event.key.keysym.scancode)){
//                        sdl.done = SDL_TRUE;
//                    }
//                }
//            }
//
//        }
//        if (sdl.renderer) {
//            SDL_DestroyRenderer(sdl.renderer);
//        }
//        if (sdl.window) {
//            SDL_DestroyWindow(sdl.window);
//        }
//    }
//    SDL_Quit();
//}
