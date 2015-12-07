#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*uses sdl libraries from srcfolder*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define WHEIGHT             700
#define WWIDTH             1100
#define TILESIZE             64

#define H WHEIGHT / TILESIZE
#define W WWIDTH / TILESIZE

/* FORWARD DEDCLARATIONS */
struct display;
typedef struct display Display;

struct entity;
typedef struct entity entity;

struct cell;
typedef struct cell cell;
