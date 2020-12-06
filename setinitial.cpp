#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL_mixer.h>
#include "setinitial.hpp"
#include "getinput.hpp"

extern LTexture Inputtexture;
extern LTexture Outputtexture;
extern LTexture Scoretexture;
extern Mix_Music *gMusic;
extern Mix_Chunk *wrong;
extern Mix_Chunk *rightanswer;
extern Mix_Chunk *click;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font *gFont;

extern const int SCREEN_WIDTH = 1024;
extern const int SCREEN_HEIGHT = 768;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "HarryPotter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				int imgFlags2 = IMG_INIT_JPG;
				if( !( IMG_Init( imgFlags2 ) & imgFlags2 ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	gFont = TTF_OpenFont( "resource/lazy.ttf", 44 );

	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render the prompt
		SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };
		if( !Inputtexture.loadFromRenderedText( "V:", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
		if( !Outputtexture.loadFromRenderedText( "V:", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
		if( !Scoretexture.loadFromRenderedText( "00000000", textColor ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}

		gMusic = Mix_LoadMUS( "resource/bgmusic.mp3" );
        if( gMusic == NULL )
        {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        rightanswer = Mix_LoadWAV( "resource/right.wav" );
        if( rightanswer == NULL )
        {
            printf( "Failed to load right sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        wrong = Mix_LoadWAV( "resource/wrong.wav" );
        if( wrong == NULL )
        {
            printf( "Failed to load wrong sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        click = Mix_LoadWAV( "resource/click.wav" );
        if( click == NULL )
        {
            printf( "Failed to load wrong sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
	}

	return success;
}

void close()
{
    Mix_FreeMusic( gMusic );
	gMusic = NULL;

	TTF_CloseFont( gFont );
	gFont = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
