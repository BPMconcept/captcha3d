/**
 * \file main.c
 * \brief Main du captcha 3D
 * \author Marc Blanc-Patin et Bernier Paul
 * \version 1.0.0
 * \date 19 mai 2011
 *
 * Module principal du captcha 3D
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include "data.h"
#include "zbuffer.h"
#include "transformations.h"
#include "illumination.h"
#include "param.h"
#include "main.h"

/**
 * \fn int main(int argc, char *argv[])
 * \brief Fonction main du programme Captcha3d
 *
 * \param argc Nombre de paramètres passés
 * \param argv[] Tableau des paramètres passés
 * 
 */
int main(int argc, char *argv[])
{
	// Vérification des paramètres
	if (!checkParams(argc,argv)) return EXIT_FAILURE;
	
	// Création de l'image
	int width = (100+cfg_aliasing)*cfg_width/100;
	int height = (100+cfg_aliasing)*cfg_height/100;
  	IplImage *img = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 4);
  	IplImage *img_final = cvCreateImage(cvSize(cfg_width,cfg_height),img->depth,img->nChannels);
  	
  	 //Seed pour nombres aléatoires
	srand(time(NULL)*getpid());
  	
  	// Génération de la couleur des lettres
  	CvScalar couleur = couleurAleatoire();
  	
  	// Affichage du fond d'écran
  	if (cfg_degrade == 1)
  	{
		degrade(img, width, height, couleur);
	}
	else
	{
		cvSet(img,cfg_background,0);
	}
  		
	// Lancement du Z-Buffer
	generer(img,width,height,cfg_str,couleur);
	
	// Redimensionnement à la taille voulue
	if(cfg_aliasing > 0)
		cvResize(img,img_final,CV_INTER_LINEAR);

	
	// Enregistrement de l'image
	if (cfg_window == 0)
	{
		(cfg_aliasing > 0) ? cvSaveImage(cfg_output,img_final,0) : cvSaveImage(cfg_output,img,0);
	}
	// Ou affichage dans une fenêtre
	else
	{
		cvNamedWindow("Captcha3D",0); 
		(cfg_aliasing > 0) ? cvShowImage("Captcha3D",img_final) : cvShowImage("Captcha3D",img);
		cvWaitKey(0);
	}	
	
    return EXIT_SUCCESS;
}


