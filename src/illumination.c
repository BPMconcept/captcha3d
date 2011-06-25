/**
 * \file illumination.c
 * \brief Modèle d'illumination
 * \author Marc Blanc-Patin et Bernier Paul
 * \version 1.0.0
 * \date 23 mai 2011
 *
 * Set de fonctions qui permettent de gérer l'illumination des scènes 3D
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <math.h>

#include "data.h"
#include "illumination.h"

#define max(a,b) (a>=b?a:b)

/**
 * \fn void degrade(IplImage *img, int width, int height, CvScalar couleurHaute)
 * \brief Affiche un fond d'écran dégardé sur l'image en paramètre
 *
 * \param img Image à modifier
 * \param width Largeur de l'image
 * \param height Hauteur de l'image
 * \param couleurHaute Couleur du texte
 */
void degrade(IplImage *img, int width, int height, CvScalar couleurHaute)
{
	int i,j,amplitude=200;
	CvScalar couleurBasse = cvScalar(0,0,0,0), couleurInter = cvScalar(0,0,0,255);

	couleurBasse.val[0]=min(max(couleurHaute.val[0] + (rand() % amplitude - amplitude/2),0),255);
	couleurBasse.val[1]=min(max(couleurHaute.val[1] + (rand() % amplitude - amplitude/2),0),255);
	couleurBasse.val[2]=min(max(couleurHaute.val[2] + (rand() % amplitude - amplitude/2),0),255);
	couleurBasse.val[3]=couleurHaute.val[3];
				
	for(i=0;i<height;i++)
	{
		couleurInter.val[0]=couleurHaute.val[0]+i*(couleurBasse.val[0]-couleurHaute.val[0])/(height-1);
		couleurInter.val[1]=couleurHaute.val[1]+i*(couleurBasse.val[1]-couleurHaute.val[1])/(height-1);
		couleurInter.val[2]=couleurHaute.val[2]+i*(couleurBasse.val[2]-couleurHaute.val[2])/(height-1);

		for(j=0;j<width;j++)
		{
			cvSet2D(img,i,j,couleurInter);
		}
	}
}

/**
 * \fn CvScalar couleurAleatoire()
 * \brief Retourne une couleur aléatoire
 * 
 */
CvScalar couleurAleatoire()
{
	CvScalar couleur;
	couleur.val[0] = rand() % 256;
	couleur.val[1] = rand() % 256;
	couleur.val[2] = rand() % 256;
	couleur.val[3] = 255;
	return couleur;
}

/**
 * \fn CvScalar couleurAffichageGouraud(float coeff, CvScalar couleur)
 * \brief Calcul de la couleur en fonction de la lumière pour le modèle de Gouraud
 *
 * \param coeff Multiplicateur
 * \param couleur Couleur initiale
 * \return Couleur pour Gouraud
 */
CvScalar couleurAffichageGouraud(float coeff, CvScalar couleur)
{
	CvScalar couleurAffichee=couleur;
	couleurAffichee.val[0]*=coeff;
	couleurAffichee.val[1]*=coeff;
	couleurAffichee.val[2]*=coeff;
	
	return couleurAffichee;
}

/**
 * \fn CvScalar couleurAffichage(Face face, Materiau materiau, Lumiere lumiere,Lettre lettre)
 * \brief Calcul de la couleur d'une face
 *
 * \param face Face en cours de la lettre
 * \param materiau Matériau de la lettre
 * \param lumiere Lumière de l'environnement
 * \param lettre Lettre en cours
 * \return Couleur pour Gouraud
 */
CvScalar couleurAffichage(Face face, Materiau materiau, Lumiere lumiere,Lettre lettre)
{
	float coeff;
	CvScalar couleurAffichee=materiau.couleur;
	Vecteur normale=normaleFace(face,lettre.points);
	
	coeff=intensite(lettre, lumiere,materiau,normale);
	
	couleurAffichee.val[0]*=coeff;
	couleurAffichee.val[1]*=coeff;
	couleurAffichee.val[2]*=coeff;
	
	return couleurAffichee;
}

/**
 * \fn void intensiteAuxPoints(float tab[], Vecteur normales[], Lettre lettre, Lumiere lumiere, Materiau materiau)
 * \brief Calcul des intensités aux points d'une lettre pour le modèle de Gouraud
 *
 * \param tab[] Contiendra les intensités
 * \param normales[] Contient les vecteurs normaux
 * \param lettre Lettre en cours
 * \param lumiere Lumière de l'environnement
 * \param materiau Matériau de la lettre
 */
void intensiteAuxPoints(float tab[], Vecteur normales[], Lettre lettre, Lumiere lumiere, Materiau materiau)
{
	Vecteur lux=normaliser(lumiere.direction);
	int i;
	float angleDiffus;

	//Calcul de l'intensité à chaque point de la lettre
	for(i=0;i<lettre.numPoints;i++)
	{
		angleDiffus=max(0,angleDiffusion(lux,normales[i]));
		tab[i]=((lumiere.ia)*(materiau.ka)+(lumiere.ip)*(materiau.kd)*angleDiffus)/((lumiere.ip)+(lumiere.ia));
	}
}

/**
 * \fn float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau,Vecteur normale)
 * \brief Calcul des intensités d'une lettre
 *
 * \param lettre Lettre en cours
 * \param lumiere Lumière de l'environnement
 * \param materiau Matériau de la lettre
 * \param normale Vecteur normal
 */
float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau,Vecteur normale)
{
	Vecteur lux=normaliser(lumiere.direction);
	float angleDiffus;

	//Calcul de l'intensité à chaque point de la lettre
	angleDiffus=max(0,angleDiffusion(lux,normale));
	return ((lumiere.ia)*(materiau.ka)+(lumiere.ip)*(materiau.kd)*angleDiffus)/((lumiere.ip)+(lumiere.ia));
	
}

/**
 * \fn Vecteur normaleFace(Face face,CvPoint3D32f points[])
 * \brief Calcul du vecteur normale à une face
 *
 * \param face Face en cours
 * \param points[] Tableau de points
 * \return Vecteur normal
 */
Vecteur normaleFace(Face face,CvPoint3D32f points[])
{
	Vecteur n;
	CvPoint3D32f p1,p2,p3;
	
	p1=points[face.a];
	p2=points[face.b];
	p3=points[face.c];

	//Calcul du produit vectoriel pour avoir la normale
	n.x=-((p2.y-p1.y)*(p3.z-p1.z)-(p2.z-p1.z)*(p3.y-p1.y));
	n.y=-((p2.z-p1.z)*(p3.x-p1.x)-(p2.x-p1.x)*(p3.z-p1.z));
	n.z=-((p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x));
		
	return normaliser(n);
}

/**
 * \fn float angleDiffusion(Vecteur L, Vecteur N)
 * \brief Calcul de l'angle de diffusion
 *
 * \param L Vecteur lumière
 * \param N Vecteur normal
 * \return angle
 */
float angleDiffusion(Vecteur L, Vecteur N)
{
	//Produit scalaire pour obtenir l'angle
	return -((L.x)*(N.x)+(L.y)*(N.y)+(L.z)*(N.z));
}

/**
 * \fn Vecteur normaliser(Vecteur vecteur)
 * \brief Normalise un vecteur
 *
 * \param vecteur Vecteur à normaliser
 * \return vecteur normalisé
 */
Vecteur normaliser(Vecteur vecteur)
{
	Vecteur vecteurNormal=vecteur;
	float norme;
	norme=sqrt((vecteur.x)*(vecteur.x)+(vecteur.y)*(vecteur.y)+(vecteur.z)*(vecteur.z));
		
	vecteurNormal.x/=norme;
	vecteurNormal.y/=norme;
	vecteurNormal.z/=norme;

	return vecteurNormal;
}

/**
 * \fn void normalesAuxPoints(Vecteur tab[],Lettre lettre)
 * \brief Fonction qui calcule les normales à chaque points de la lettre
 *
 * \param tab Tableau qui recevra les normales
 * \param lettre Lettre pour laquelle il faut calculer les normales
 */
void normalesAuxPoints(Vecteur tab[],Lettre lettre)
{
    Vecteur n;
    Face face;
    int i;
    initialiserTableauNormales(tab,lettre.numPoints);

    for(i=0;i<lettre.numFaces;i++)
    {
        face=lettre.faces[i];
        //Calcul de la normale à la face
		n=normaleFace(lettre.faces[i],lettre.points);

		//Ajout de cette normale à chacun des points de la face
        tab[face.a]=additionerVecteurs(tab[face.a],n);
        tab[face.b]=additionerVecteurs(tab[face.b],n);
        tab[face.c]=additionerVecteurs(tab[face.c],n);

    }

    //On normalise les normales
    for(i=0;i<lettre.numPoints;i++)
    {
        tab[i]=normaliser(tab[i]);
    }
}

/**
 * \fn Vecteur additionerVecteurs(Vecteur n1, Vecteur n2)
 * \brief Aditionne deux vecteurs
 *
 * \param n1 Premier vecteur à additioner
 * \param n2 Deuxième vecteur à additioner
 * \return Vecteur total
 */
Vecteur additionerVecteurs(Vecteur n1, Vecteur n2)
{
    Vecteur n;
    n.x=n1.x+n2.x;
    n.y=n1.y+n2.y;
    n.z=n1.z+n2.z;

    return n;
}

/**
 * \fn void initialiserTableauNormales(Vecteur tab[],int taille)
 * \brief Initialise un tableau avec la normale nulle
 *
 * \param tab Tableau à initialiser
 * \param taille Taille du tableau
 */
void initialiserTableauNormales(Vecteur tab[],int taille)
{
    Vecteur nul;
    int i;

    nul.x=0;
    nul.y=0;
    nul.z=0;

    for(i=0;i<taille;i++)
    {
        tab[i]=nul;
    }
}

