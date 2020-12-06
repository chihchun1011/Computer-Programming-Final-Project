#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include "move.hpp"
#include "getinput.hpp"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern LTexture harrytexture;

Dot::Dot(int px, int py, int vx, int vy)
{
    mPosX = px;
    mPosY = py;

    mVelX = vx;
    mVelY = vy;
}

void Dot::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move()
{
    mPosX += mVelX;
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY;
    }
}

void Dot::render()
{
	harrytexture.render( mPosX, mPosY );
}

int Dot::getPosX(){ return mPosX;}
int Dot::getPosY(){ return mPosY;}

Particle::Particle()
{
    mPosX = 900;
    mPosY = rand() % 500;

    mVelX = -(rand() % 3 +3);
    mVelY = 0;

    DOT_WIDTH = 100;
    DOT_HEIGHT = 60;

    //goldentexture.loadFromFile( "SA.png" );

    cclips[0].x = 0;
    cclips[0].y = 0;
    cclips[0].w = 128;
    cclips[0].h = 85;

    cclips[1].x = 128;
    cclips[1].y = 0;
    cclips[1].w = 128;
    cclips[1].h = 85;

    cclips[2].x = 256;
    cclips[2].y = 0;
    cclips[2].w = 128;
    cclips[2].h = 85;

    cclips[3].x = 384;
    cclips[3].y = 0;
    cclips[3].w = 128;
    cclips[3].h = 85;

}

Particle::Particle(int PosX, int PosY, int w, int h)
{
    mPosX = 900;
    mPosY = (rand() % 350) + 200;

    mVelX = rand() % 2 + 3 ;
    mVelY = rand() % 2 + 3 ;

    DOT_WIDTH = w;
    DOT_HEIGHT = h;

}

void Particle::move()
{
    mPosX += mVelX;
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
    {
        mPosX -= mVelX;
    }
}

void Particle::randommove()
{
    mPosX += mVelX;

    mPosY += mVelY;

    if(mPosY>690){
        mVelY=-(rand()%4)-3;
    }
    if(mPosY<20){
        mVelY=rand()%4+3;
    }
    if(mPosX<10){
        mVelX=rand()%4+3;
    }
    if(mPosX>920){
        mVelX=-(rand()%4)-3;
    }

    if( ( mPosX < 0 ) || ( mPosX + 96 > SCREEN_WIDTH))
    {
        mPosX -= mVelX;
    }

    if( ( mPosY < 0 ) || ( mPosY + 60 > SCREEN_HEIGHT ))
    {
        mPosY -= mVelY;
    }
}

void Particle::render(LTexture* mTexture)
{
	mTexture->render( getPosX(), getPosY() , getclip(getMode()));
}

void Particle::render2(LTexture* mTexture)
{
	mTexture->renderTexture( mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT);
}

bool Particle::isDead()
{
    return mPosX < 10;;
}

void Particle::free(LTexture* mTexture)
{
	mTexture->free();
}

int Particle::getPosX(){ return mPosX;}
int Particle::getPosY(){ return mPosY;}
int Particle::getVelX(){ return mVelX;}


bool checkCollision( Particle& a, Particle& b )
{
    if(a.getPosY() - b.getPosY() > 0 && a.getPosY() - b.getPosY() < 60 && a.getVelX() == b.getVelX())
    {
        return true;
    }
    else if(b.getPosY() - a.getPosY() > 0 && b.getPosY() - a.getPosY() < 60 && a.getVelX() == b.getVelX())
    {
        return true;
    }
    return false;
}

bool checkharrycollision( Particle& a, Dot* b){

    if (a.getPosX() - b->getPosX() > 10 && a.getPosX() - b->getPosX() < b->DOT_WIDTH + 30 &&
        b->getPosY() - a.getPosY() > a.DOT_HEIGHT - b->DOT_HEIGHT && b->getPosY() - a.getPosY() < a.DOT_HEIGHT)
    {
        return true;
    }

    return false;
}

bool blueballCollision( Particle& a, Dot* b )
{
    int cX, cY;
    if( a.getPosX() < b->getPosX() )
    {
        cX = b->getPosX();
    }
    else if( a.getPosX() > b->getPosX() + b->DOT_WIDTH )
    {
        cX = b->getPosX() + b->DOT_WIDTH;
    }
    else
    {
        cX = a.getPosX();
    }
    if( a.getPosY() < b->getPosY() )
    {
        cY = b->getPosY();
    }
    else if( a.getPosY() > b->getPosY() + b->DOT_HEIGHT )
    {
        cY = b->getPosY() + b->DOT_HEIGHT;
    }
    else
    {
        cY = a.getPosY();
    }

    if( distanceSquared( a.getPosX(), a.getPosY(), cX, cY ) < (a.DOT_WIDTH/2-40) * (a.DOT_WIDTH/2-40) )
    {
        return true;
    }
    return false;
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

void Particle::nextstage(){
    static const int period_1=T;
    static const int period_2=T;
    static const int period_3=T;
    static const int period_4=T;

    switch(mode){
        case c1:
            if(nextstage_lastmode==c1){
                nextstage_lefttime--;
                if(nextstage_lefttime<=0){
                    nextstage_lefttime=period_2;
                    mode=c1;
                }
            }
            else{
                nextstage_lefttime=period_1;
            }
            break;
        case c2:
            if(nextstage_lastmode==c2){
                nextstage_lefttime--;
                if(nextstage_lefttime<=0){
                    nextstage_lefttime=period_3;
                    mode=c2;
                }
            }
            else{
                nextstage_lefttime=period_2;
            }
            break;
        case c3:
            if(nextstage_lastmode==c3){
                nextstage_lefttime--;
                if(nextstage_lefttime<=0){
                    nextstage_lefttime=period_4;
                    mode=c3;
                }
            }
            else{
                nextstage_lefttime=period_3;
            }
            break;
        case c4:
            if(nextstage_lastmode==c4){
                nextstage_lefttime--;
                if(nextstage_lefttime<=0){
                    nextstage_lefttime=period_1;
                    mode=c1;
                }
            }
            else{
                nextstage_lefttime=period_4;
            }
            break;
    }
    nextstage_lastmode=mode;
}

SDL_Rect* Particle::getclip(int mode){
    int a=c1;
    int period=T;
    switch(mode){
        case c1:
            if(getclip_lastmode==c1){
                getclip_lefttime--;

                if(getclip_lefttime<=0){
                    getclip_lefttime=period;
                    a=(lastclip==clip4?clip1:lastclip+1);
                }
                else
                    a=lastclip;
            }
            else{
                getclip_lefttime=period;
                a=clip1;
            }
            break;
        case c2:
            a=clip2;
            break;
        case c3:
            a=clip3;
            break;
        case c4:
            a=clip4;
            break;

    }

    getclip_lastmode=mode;
    lastclip=a;
    return &cclips[a];
}

int Particle::getMode()
{
    return mode;
}


