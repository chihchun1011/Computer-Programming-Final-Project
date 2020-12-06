#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "getinput.hpp"

class Particle
{
	public:

        int DOT_WIDTH, DOT_HEIGHT;
		Particle();
		Particle(int , int, int, int);
		void render(LTexture* );
		void render2(LTexture* );
		bool isDead();
		void move();
		void randommove();
		void shiftColliders();
		void free(LTexture* );
		int getPosX();
		int getPosY();
		int getVelX();

		void nextstage();

        SDL_Rect* getclip(int);
        static const int T=4;
        int lastclip;
        SDL_Rect cclips[4];
        int getMode();


	private:
		int mPosX, mPosY;
		int mVelX, mVelY;

		int mode = c1;
        int nextstage_lastmode,nextstage_lefttime;
        int getclip_lefttime,getclip_lastmode;
        enum cmode{
        c1,
        c2,
        c3,
        c4,
    };

        enum clips{
        clip1,
        clip2,
        clip3,
        clip4,
    };
};

class Dot
{
    public:
		static const int DOT_WIDTH = 240;
		static const int DOT_HEIGHT = 174;

		static const int DOT_VEL = 10;

		Dot();
		Dot(int, int, int, int);

		void handleEvent( SDL_Event& e );
		void move();
		void render();
		int getPosX();
		int getPosY();

    private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};

bool checkCollision( Particle& , Particle&  );
bool checkharrycollision( Particle& , Dot* );
bool blueballCollision( Particle& , Dot*  );
double distanceSquared( int x1, int y1, int x2, int y2 );

