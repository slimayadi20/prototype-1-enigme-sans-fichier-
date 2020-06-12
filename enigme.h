
#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <SDL/SDL_mixer.h>
/**
* @struct clavier 
* @brief struct for clavier

*/
typedef struct clavier
{
	int haut;
	int bas;
	int droite;
	int gauche;
	int echap;
}clavier; 
/**
* @struct souris 
* @brief struct for souris

*/
typedef struct souris 
{
	int click;
	SDL_Rect pos;
}souris;

/**
* @struct input 
* @brief struct for input

*/
typedef struct input
{
	clavier c;
	souris s;
}input;

/**
* @struct objet 
* @brief struct for object

*/
typedef struct objet
{
	SDL_Surface *img;
	SDL_Rect pos;
	int rayon;
	float distance;
}objet;
/**
* @struct enigme 
* @brief struct for enigme

*/
typedef struct enigmeS
{
	SDL_Surface * back_enigme;
	SDL_Rect pos_back_enigme;
	objet obj[4];
	int running;
	int resolu;

	
}enigme;

void init_enigme(enigme * e);
void init_input(input *inp);
void afficher_enigme(enigme *e,SDL_Surface *ecran,input inp);
int get_input(input *inp,enigme e,SDL_Rect *posevent);
void deplacer(input inp,objet *fleche,SDL_Rect posevent);
void calculer_centre_rayon (enigme *e);
void calculer_distance (enigme *e);
void verif_collision (enigme e,int *collision);
void resoudre_enigme(enigme *e,int *collision, Mix_Music *musique);
void liberate_memory (enigme *e);

#endif
