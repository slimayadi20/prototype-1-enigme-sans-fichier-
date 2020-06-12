/**
* @file main.c
* @brief Testing Program.
* @author slimayadi
* @version 1.1
* @date june 11 2020
*
* Testing program for enigme
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <math.h>
#include "enigme.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
int main()
{
	SDL_Surface *ecran;
	enigme e;
	SDL_Rect posevent;
	int continuer=1;
	int v=-1;
        Mix_Music *musique;
        Mix_Chunk *son;
	input inp;
        TTF_Init();
	e.running=1;
	ecran = SDL_SetVideoMode(1200,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF) ;
	init_enigme(&e);
	init_input(&inp);




	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
 	 {printf("%s",Mix_GetError()); }
          	
	   musique=Mix_LoadMUS("music2.mp3");
           Mix_PlayMusic(musique,-1);



	while (continuer)
	{
		
	continuer=get_input(&inp,e,&posevent);
	calculer_centre_rayon(&e);
	deplacer(inp,&(e.obj[0]),posevent);
	calculer_distance(&e);
	resoudre_enigme(&e,&v,musique);
	init_input(&inp);
	afficher_enigme(&e,ecran,inp);

	if (e.running==0)
			continuer=0;
		SDL_Flip(ecran);
	


	}
			
				
	TTF_Quit();
	SDL_FreeSurface(ecran);
	liberate_memory (&e);
	SDL_Quit ();
return EXIT_SUCCESS ;
}
