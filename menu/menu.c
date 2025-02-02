#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1366 //you can change this and the others if zou want but make sure zou choose the right aspect ratio bc the photo ,don-t come crzing to bitches
#define SCREEN_HEIGHT 768
#define FONT_SIZE 40
#define MENU_ITEMS 4

// Menu options for dummies
enum MenuOptions { NEW_GAME, LOAD_GAME, SETTINGS, QUIT };

const char *menuText[MENU_ITEMS] = {"New Game", "Load Game", "Settings", "Quit"};

int main(int argc, char *argv[]) {
    // Initialize SDL and SDL_Mixer so zou can hear the fucking buttons
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    // Set up the screen with the desired resolution depending on zour laptop screen but I alreadz defined it up so idk don-t ask me
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_Surface *background = IMG_Load("menu_background.png");  // Background image that took 4 hours to find
    
    // Load font (make sure "TheCentrion.ttf" is in the same directory and I mean it it took me to days to notice that the font name was set to the centrion instead of thecentrion when I downloaded it)
    TTF_Font *font = TTF_OpenFont("TheCenturion.ttf", FONT_SIZE);
    SDL_Color white = {255, 255, 255};  // Color for unselected text youssef I tried bro I didn-t studz paint so everz color was like shit
    SDL_Color red = {255, 0, 0};       // Color for selected text (red in case zou didn-t know like the elden ring death screen :( )
    if (!font) {
    		printf("Error loading font: %s\n", TTF_GetError());
    return 1;  // Exit if font cannot be loaded 1 means e have a serious problem fam 0 means zou are good to go my nigga
}

    
    // Load sound effects (make sure they are in the same directory and zou better not change them bitch)
    Mix_Chunk *moveSound = Mix_LoadWAV("move.wav");
    Mix_Chunk *selectSound = Mix_LoadWAV("select.wav");
    
    SDL_Event event;
    bool running = true;
    int selected = 0;  // Initially selected menu item
    
    // Game loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;  // Close the program when the quit event is cumming
            } else if (event.type == SDL_KEYDOWN) {
                // Keyboard navigation don-t worry I used arrows
                if (event.key.keysym.sym == SDLK_DOWN) {
                    selected = (selected + 1) % MENU_ITEMS;
                    Mix_PlayChannel(-1, moveSound, 0);  // Play sound when moving down though there is a delay bc it-s linux what did you expect
                } else if (event.key.keysym.sym == SDLK_UP) {
                    selected = (selected - 1 + MENU_ITEMS) % MENU_ITEMS;
                    Mix_PlayChannel(-1, moveSound, 0);  // Play sound when moving up
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    Mix_PlayChannel(-1, selectSound, 0);  // Play selection sound
                    if (selected == QUIT) {
                        running = false;  // Exit if Quit is selected or close terminal if you want your pc to crash
                    }
                }
            }
        }
        
        // Clear the screen and draw the background
        SDL_BlitSurface(background, NULL, screen, NULL);
        
        // Render each menu item with their position
        for (int i = 0; i < MENU_ITEMS; i++) {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuText[i], (i == selected) ? red : white);
            SDL_Rect textPos = {1100, 300 + i * 60, 0, 0};  // Position of each text item
            SDL_BlitSurface(textSurface, NULL, screen, &textPos);
            SDL_FreeSurface(textSurface);  // Free the text surface after rendering
        }
        
        // Update the screen with the new drawing if you know you know youssef
        SDL_Flip(screen);
        
        // setting fps to 100 so I can flex whitout my pc exploding
        SDL_Delay(100);
    }
    
    // Clean up resources (i didn-t use that quit we learned in the video though idk why but it didn-t feel right to me)
    SDL_FreeSurface(background);
    TTF_CloseFont(font);
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(selectSound);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    
    return 0;
}

