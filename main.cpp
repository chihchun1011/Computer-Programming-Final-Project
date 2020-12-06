#include "getinput.hpp"
#include "setinitial.hpp"
#include "spelloutput.hpp"
#include "move.hpp"
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>


using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
Mix_Music *gMusic = NULL;
Mix_Chunk *wrong = NULL;
Mix_Chunk *rightanswer = NULL;
Mix_Chunk *click = NULL;

LTexture background3;
LTexture Inputtexture;
LTexture Outputtexture;
LTexture Scoretexture;
LTexture timetexture;
LTexture harrytexture;
LTexture blueballtexture;
LTexture lifetexture;
LTexture lifebgtexture;
LTexture goldentexture;
Particle* particles[ 8 ];
Particle* blueball[ 2 ];


int main( int argc, char* args[] )
{
    bool quit = false;
    while (!quit){
    srand(time(0));
    bool start = false;

    bool end = false;
    bool level1end = false;
    bool restart = true;
    bool inside = false;
    Uint32 getTime = 20;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
        while (restart == true)
        {
            Mix_PlayMusic( gMusic, -1 );
            restart = false;
		    SDL_Event e;
		    background3.loadFromFile("resource/cover01.jpg");
		    int x, y;
		    while (start == false && !quit && restart == false)
            {

                SDL_GetMouseState( &x, &y );
                while( SDL_PollEvent( &e ) != 0 ) //Handle events on queue
				{
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && inside == true)
                    {
                        start = true;
                        Mix_PlayChannel( -1, click, 0 );
                    }
				}
				if (x > 400 && y > 420)
                {
                    background3.loadFromFile("resource/cover02.jpg");
                    inside = true;
                }
                else
                {
                    inside = false;
                    background3.loadFromFile("resource/cover01.jpg");
                }


                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //Clear screen
                SDL_RenderClear( gRenderer );

                background3.renderTexture(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_RenderPresent( gRenderer );
            }
            background3.free();
            start = false;

            //intro1
            while (start == false && !quit && restart == false)
            {
                background3.loadFromFile("resource/Qintro.jpg");

                while( SDL_PollEvent( &e ) != 0 )
				{
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        start = true;
                        Mix_PlayChannel( -1, click, 0 );
                    }
				}
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //Clear screen
                SDL_RenderClear( gRenderer );

                background3.renderTexture(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_RenderPresent( gRenderer );
            }
            background3.free();
            start = false;

            //level 2 start
            std::stringstream timeText2;
            std::stringstream scoretext2;

            SDL_Color textColor2 = { 0, 0, 0, 255 };
            Dot harry(0, 600, -2, +4);
            harrytexture.loadFromFile("resource/harry.png");
            blueballtexture.loadFromFile("resource/blueball.png");
            background3.loadFromFile("resource/bg2.jpg");
            lifetexture.loadFromFile("resource/blood.png");
            lifebgtexture.loadFromFile("resource/bloodbg.png");
            goldentexture.loadFromFile( "resource/SA.png" );
            int nowparticles = 1;
            int particlenum[8] = {0};
            int blueballnum[2] = {0};
            Uint32 mstarttime2 = SDL_GetTicks();
            int time2=30;
            int tempscore2 = 0;
            int realscore2 = 0;
            int blood = 500;

            int scrollingOffset = 0;
            while( !quit && !level1end && restart == false && (time2 -(SDL_GetTicks() - mstarttime2)/1000)>0)
            {
                for( int i = 0; i < nowparticles ; ++i )
                {
                    if (particlenum[ i ] == 0)
                    {
                        particles[ i ] = new Particle();
                        particlenum[ i ] = 1;
                    }
                }
                for(int i=0 ; i<2 ; ++i)
                {
                    if(blueballnum [i]  ==0)
                    {
                        blueball [i]= new Particle(0, 0, 60, 60);
                        blueballnum[i]=1;
                    }
                }

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        else if (e.type == SDL_KEYDOWN)
                        {
                            if (e.key.keysym.sym == SDLK_e) {level1end = true;}
                            else if (e.key.keysym.sym == SDLK_c)
                            {
                                for (int i = 0; i < 8; i++)
                                {
                                    if (particlenum [ i ] != 0 && checkharrycollision( *particles[ i ], &harry ))
                                    {
                                        delete  particles[ i ];
                                        particlenum[ i ] = 0;
                                        nowparticles --;
                                        tempscore2+=20;
                                        getTime+=3;
                                    }
                                }
                            }
                        }
                        harry.handleEvent( e );
                    }

                    harry.move();

                    for( int i = 0; i < 8; ++i )
                    {
                        if (particlenum[ i ] != 0)
                        particles[ i ]->move();
                    }

                    for( int i = 0; i < 2; ++i )
                    {
                        if (blueballnum [ i ] != 0)
                        blueball[ i ]->randommove();
                    }
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    background3.renderTexture( scrollingOffset, 0, 2730, SCREEN_HEIGHT );
                    background3.renderTexture( scrollingOffset + 2730, 0, 2730, SCREEN_HEIGHT );

                    timetexture.render( ( SCREEN_WIDTH - timetexture.getWidth() ) / 2 +320 , ( SCREEN_HEIGHT - timetexture.getHeight() ) / 2 -300);
                    Scoretexture.render( 0, 0 );

                    if (blueballCollision(*blueball[ 0 ], &harry))
                    {
                        harrytexture.loadFromFile("resource/harryfaded.png");
                        delete [] blueball[ 0 ];
                        blueballnum[ 0 ] = 0;
                        blood -= 100;

                    }
                    else if (blueballCollision(*blueball[ 1 ], &harry))
                    {
                        harrytexture.loadFromFile("resource/harryfaded.png");
                        delete [] blueball[ 1 ];
                        blueballnum[ 1 ] = 0;
                        blood -=100;
                    }
                    else
                    {
                        harrytexture.loadFromFile("resource/harry.png");
                    }

                    if (blood == 0)break;

                    --scrollingOffset;
                    if( scrollingOffset < -2730 )
                    {
                        scrollingOffset = 0;
                    }

                    for( int i = 0; i < 8; ++i )
                    {
                        if (particlenum[ i ] != 0)
                        {
                           if( particles[ i ]->isDead() )
                            {
                                delete [] particles[ i ];
                                particlenum[ i ] = 0;
                                nowparticles --;
                            }

                            for (int j = 0; j < 8; j++)
                            {
                                if ( particlenum[ j ] != 0 && particlenum[ i ] != 0 && checkCollision(*particles[ i ], *particles[ j ]) && j != i)
                                {
                                    delete [] particles[ i ];
                                    particlenum[ i ] = 0;
                                    nowparticles --;

                                }
                            }
                        }

                    }

                    for( int i = 0; i < 8; ++i )
                    {
                        if (particlenum[ i ] != 0)
                        {
                            particles[ i ]->nextstage();
                            particles[ i ]->render( &goldentexture );
                        }
                    }

                    for( int i = 0; i < 2; ++i )
                    {
                        if (blueballnum [ i ] != 0)
                        blueball[ i ]->render2( &blueballtexture );
                    }

                    lifebgtexture.renderTexture(220, 0, 480, 100);
                    lifetexture.renderTexture(220, 0, blood, 100);
                    harry.render();

                    if (nowparticles < 2 ) nowparticles += (rand() % 2) + 1;

                if (tempscore2 != 0)
                {
                    scoretext2.str( "" );
                    realscore2 ++;
                    scoretext2 << turntochar(realscore2);
                    tempscore2 --;
                }
                else
                {
                    scoretext2.str( "" );
                    scoretext2 << turntochar(realscore2);
                }

                if( !Scoretexture.loadFromRenderedText( scoretext2.str().c_str(), textColor2 ) )
				{
					printf( "Unable to render score texture!\n" );
				}

                timeText2.str( "" );
				timeText2 << "Time left " << time2 -(SDL_GetTicks() - mstarttime2)/1000 ;

				if( !timetexture.loadFromRenderedText( timeText2.str().c_str(), textColor2 ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				SDL_RenderPresent( gRenderer );

                }

                lifetexture.free();
                lifebgtexture.free();
                blueballtexture.free();
                harrytexture.free();
                goldentexture.free();
                background3.free();
                level1end = false;
            // level 2 end

            //levelintro
            int mode = 1;
            background3.loadFromFile("resource/afterQuidditch.jpg");
            while (start == false && !quit && restart == false)
            {
                while( SDL_PollEvent( &e ) != 0 )
				{
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && mode == 2)
                    {
                        start = true;
                        Mix_PlayChannel( -1, click, 0 );
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && mode == 1)
                    {
                        background3.loadFromFile("resource/spellintro.jpg");
                        mode = 2;
                        Mix_PlayChannel( -1, click, 0 );
                    }
				}
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                background3.renderTexture(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_RenderPresent( gRenderer );
            }
            background3.free();
            start = false;

            // level 3 start
            Uint32 mstarttime3 = SDL_GetTicks();
            int tempscore = 0;
            int realscore = tempscore2 + realscore2;
            bool win = false;

			SDL_Color textColor = { 0xFF, 0xFF, 0xFF, 0xFF };

			string outputText = findspell();
			string inputText = "V:";

			Outputtexture.loadFromRenderedText( outputText.c_str(), textColor );
            Inputtexture.loadFromRenderedText( inputText.c_str(), textColor );
            background3.loadFromFile("resource/finalmission.jpg");

			SDL_StartTextInput();

			std::stringstream timeText;
			std::stringstream scoretext;

			while( !quit && (getTime -(SDL_GetTicks() - mstarttime3)/1000) != 0 && restart == false && win == false)
			{
				bool renderText = false;

				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
					{
						if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 2 )
						{
							inputText.erase(inputText.length()-1, 1);
							renderText = true;
						}
						if (e.key.keysym.sym == SDLK_RETURN){
                            if (comparison(outputText, inputText))
                            {
                                tempscore +=50;
                                outputText = findspell();
                                inputText = "V:";
                                Mix_PlayChannel( -1, rightanswer, 0 );
                                background3.loadFromFile("resource/right.jpg");
                                Outputtexture.loadFromRenderedText( outputText.c_str(), textColor );
                                Inputtexture.loadFromRenderedText( inputText.c_str(), textColor );
                                break;
                            }
                            else if (!comparison(outputText, inputText))
                            {
                                if (outputText == "V:expelliarmus" && inputText == "H:alohomora")
                                {
                                    win = true;
                                    break;
                                }

                                Mix_PlayChannel( -1, wrong, 0 );
                                tempscore+=0;
                                outputText = findspell();
                                inputText = "V:";
                                background3.loadFromFile("resource/wrong.jpg");
                                Outputtexture.loadFromRenderedText( outputText.c_str(), textColor );
                                Inputtexture.loadFromRenderedText( inputText.c_str(), textColor );
                                break;

                            }

						}
					}
					else if( e.type == SDL_TEXTINPUT )
					{
                        inputText += e.text.text;
                        renderText = true;
					}
				}

				if( renderText )
				{

					if( inputText != "" )
					{
						Inputtexture.loadFromRenderedText( inputText.c_str(), textColor );
					}
					else
					{
						Inputtexture.loadFromRenderedText( " ", textColor );

					}
				}

				timeText.str( "" );
				timeText << "Time left " << getTime -(SDL_GetTicks() - mstarttime3)/1000 ;
				if (tempscore != 0)
                {
                    scoretext.str( "" );
                    realscore ++;
                    scoretext << turntochar(realscore);
                    tempscore --;
                }
                else
                {
                    scoretext.str( "" );
                    scoretext << turntochar(realscore);
                }

				if( !timetexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				if( !Scoretexture.loadFromRenderedText( scoretext.str().c_str(), textColor ) )
				{
					printf( "Unable to render score texture!\n" );
				}
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //Clear screen
				SDL_RenderClear( gRenderer );

				background3.renderTexture(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				Outputtexture.render( 300, 250);
				Inputtexture.render( 650, 400 );
				Scoretexture.render( 0, 0 );
				timetexture.render( ( SCREEN_WIDTH - timetexture.getWidth() ) / 2 +140 , ( SCREEN_HEIGHT - timetexture.getHeight() ) / 2 -200);


				SDL_RenderPresent( gRenderer );
			}

			SDL_StopTextInput();
			timetexture.free();
            Inputtexture.free();
            Outputtexture.free();
            Mix_PauseMusic();
            //level3end

            while ( !quit && !end && restart == false)
            {
                while( SDL_PollEvent( &e ) != 0 )
				{
                    if( e.type == SDL_QUIT ){quit = true;}
                    else if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_e)
                        {
                            end = true;
                            close();
                            return 0;
                        }
                        else if (e.key.keysym.sym == SDLK_r)
                        restart = true;
                    }
				}

                if (tempscore + realscore >= 1250 || win == true){background3.loadFromFile("resource/win.jpg");}
                else {background3.loadFromFile("resource/lose.jpg");}

                scoretext.str( "" );
                scoretext << turntochar(realscore + tempscore);

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                background3.renderTexture(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                Scoretexture.render( 0, 0 );
                SDL_RenderPresent( gRenderer );

            }
            Scoretexture.free();
            Mix_ResumeMusic();
        }
		}
	}
    }
	close();

	return 0;
}
