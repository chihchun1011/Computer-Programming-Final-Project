#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

#ifndef __getinput_h__
#define __getinput_h__
class LTexture
{
	public:
		LTexture();
		~LTexture();

		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );

		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        void renderTexture(int x, int y, int w, int h);

		int getWidth();
		int getHeight();

	private:

		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

#endif


