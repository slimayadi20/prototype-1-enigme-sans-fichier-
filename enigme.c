/**
* @file enigme.c
*@author slimayadi
*@brief enigme sans fichier
*@date 11 juin 2020
*@version 1.1
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
/**
* @brief init enigme .
* @param enigme *e 

* @return nothing
*/
void init_enigme(enigme * e)
{

    e->back_enigme=IMG_Load("1.png");
    e->pos_back_enigme.x=150;
    e->pos_back_enigme.y=100;
   
    e->obj[0].img=IMG_Load("2.png");
    e->obj[1].img=IMG_Load("3.jpg");
    e->obj[2].img=IMG_Load("4.jpg");
    e->obj[3].img=IMG_Load("5.jpg");
   
    e->obj[0].pos.x=200;
    e->obj[0].pos.y=150;
    e->obj[1].pos.x=200;
    e->obj[1].pos.y=385;
    e->obj[2].pos.x=520;
    e->obj[2].pos.y=385;
    e->obj[3].pos.x=840;
    e->obj[3].pos.y=385;
    e->resolu=-1;
    e->running=1;


}
/**
* @brief init input  .
* @param input *inp

* @return nothing
*/
void init_input(input *inp)
{
	inp->s.click=-1;
	inp->c.echap=-1;

}

/**
* @brief afficher enigme .
* @param enigme *e *ecran input inp 

* @return nothing 
*/
void afficher_enigme(enigme *e,SDL_Surface *ecran,input inp)
{
    
	TTF_Font *police = NULL;
        SDL_Color couleuur = {108, 204,0};
	SDL_Rect positionT ; 
	SDL_Surface  *text = NULL;
        SDL_BlitSurface(e->back_enigme,NULL,ecran,&e->pos_back_enigme);
	for (int i=0;i<4;i++)
    {
    	SDL_BlitSurface(e->obj[i].img,NULL,ecran,&e->obj[i].pos);
    }

	

	if(e->resolu==1)
{
	police = TTF_OpenFont("angelina.TTF",60);
	TTF_SetFontStyle(police, TTF_STYLE_BOLD);
	
	text = TTF_RenderText_Blended(police,"c la bonne reponse",couleuur);
	positionT.x= 300;
	positionT.y=200;
            SDL_Delay(600);
 	e->running=0;
            SDL_Delay(600);

}


	

	SDL_BlitSurface(text, NULL, ecran, &positionT);

	TTF_CloseFont(police);

}
/**
* @brief get input   .
* @param input *inp enigme e sdl rect *posevent

* @return entier continuer 
*/
int get_input(input *inp,enigme e,SDL_Rect *posevent)				
{
	SDL_Event event;
	int continuer=1;
	SDL_WaitEvent(&event);

       		 switch	(event.type)

       			 {

				case SDL_QUIT:

				continuer = 0;
		
				break;

            case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
                {
		case SDLK_ESCAPE: 
			continuer=0;

		break;
		}
		break;

		
			
			case SDL_MOUSEBUTTONDOWN:

				if (event.button.button == SDL_BUTTON_LEFT)
					{
					inp->s.click=1;
					posevent->x=event.button.x ;
					posevent->y=event.button.y ;
  					}
        			
			break;
			case SDL_MOUSEBUTTONUP:

				if (event.button.button == SDL_BUTTON_LEFT)
					{
					inp->s.click=-1;
  					}
        			
			break;
			}	

		
			
return continuer;
}
/**
* @brief deplacer souris  .
* @param input inp objet *flecche sdl rect posevent

* @return nothing 
*/
void deplacer(input inp,objet *fleche,SDL_Rect posevent)
{
	
	if(inp.s.click==1)
	{
		fleche->pos.x=posevent.x ;
		fleche->pos.y=posevent.y ;
	}

}
/**
* @brief calculer centre rayeon  .
* @param enigme *e

* @return nothing
*/
void calculer_centre_rayon (enigme *e)
{
	int X,Y;
	for (int i=0; i<4; i++)
	{
    		X=e->obj[i].pos.x+ (e->obj[i].img->w)/2 ;
    		Y=e->obj[i].pos.y+ (e->obj[i].img->h)/2 ;
    		e->obj[i].rayon=sqrt(pow(X-e->obj[i].pos.x, 2) + pow(Y-e->obj[i].pos.y, 2)) ;
	}

}
/**
* @brief calculer distance  .
* @param enigme *e

* @return nothing 
*/
void calculer_distance (enigme *e)
{	
	for (int i=1;i<4;i++)
	{
    		e->obj[i].distance=sqrt(pow((e->obj[0].pos.x) - (e->obj[i].pos.x),2) + pow ((e->obj[0].pos.y) - (e->obj[i].pos.y), 2)) ;
	}

}
/**
* @brief verifier collision  .
* @param enigme e entier *collision

* @return nothing
*/
void verif_collision (enigme e,int *collision)
{

	float somme ;
	for (int i=1;i<4;i++)
	{
		somme=e.obj[0].rayon + e.obj[i].rayon;
		if(e.obj[i].distance<=somme)
{
        		*collision= i ;

}
	}
}
/**
* @brief resoudre enigme   .
* @param enigme *e entier *collision mix music *musique

* @return nothing
*/
void resoudre_enigme(enigme *e,int *collision, Mix_Music *musique)
{ 
    int previous_volume;
    Mix_Volume(1, MIX_MAX_VOLUME/2);
    Mix_Chunk *son;
    son = Mix_LoadWAV("Button.wav");
    previous_volume=Mix_VolumeChunk(son, MIX_MAX_VOLUME/2);

	 verif_collision (*e,&(*collision));


	if(*collision==3)
{
		 e->resolu=1;
			Mix_PlayChannel(1, son, 0);
}						
	else 
{
		e->resolu=0;
			Mix_PlayChannel(1, son, 0);						
}
    	
}


/**
* @brief liberer la memoire  .
* @param enigme *e

* @return nothing
*/
void liberate_memory (enigme *e)
{
	for( int i=0;i<4;i++)
	{
		SDL_FreeSurface(e->obj[i].img) ;
	}
    SDL_FreeSurface (e->back_enigme) ;
   
}
