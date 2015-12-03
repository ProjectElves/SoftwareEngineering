#include <stdbool.h>
#include <math.h>
#include "entity.h"

#define MILLISECONDDELAY     20

struct display {
    SDL_bool finished;
    SDL_Window *win;
    SDL_Surface *temp;
    SDL_Texture *images[256];
    SDL_Texture *background;
    SDL_Renderer *renderer;
    SDL_Event event;
    Uint32 colour;
    //declare the music file
    Mix_Music *music;
    Mix_Chunk *zap;
};


// Create a new display object.
Display *newDisplay();
void loadPhoto(Display *d, char *s, int i);
//Splashes photo without loading it again
void splashPhoto(Display *d);
//draws entity
void drawEntities(Display *d, cell grid[H][W]);
//Set drawing colour
void setColour(Display *d, int r, int g, int b, int a);
// Update the window on screen, after delaying for the (rest of) the given time.
void drawFrame(Display *d, int milliseconds);
// Return true if the quit button has been pressed.
bool quitEvent(Display *d);
//Gets whatever error message SDL gives and it prits it with the input *s
void fail(char *s);
/*My own delay function*/
void myDelay(int ms);
void closeDisplay(Display *d);
