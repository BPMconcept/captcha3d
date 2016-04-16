#ifndef ILLUMINATION_H_INCLUDED
#define ILLUMINATION_H_INCLUDED

#include "data.h"

void degrade(IplImage *img, int width, int height, CvScalar couleurHaute);
struct captcha3d_pixel couleurAleatoire();
void intensiteAuxPoints(float tab[], Vector3d normales[], Lettre lettre, Lumiere lumiere, Materiau materiau);
Vector3d normaliser(Vector3d vecteur);
float angleDiffusion(Vector3d L, Vector3d N);
void normalesAuxPoints(Vector3d tab[], Lettre lettre);
Vector3d additionerVecteurs(Vector3d n1, Vector3d n2);
void initialiserTableauNormales(Vector3d tab[], int taille);
struct captcha3d_pixel couleurAffichageGouraud(float coeff, struct captcha3d_pixel couleur);
Vector3d normaleFace(Face face, CvPoint3D32f points[]);
struct captcha3d_pixel couleurAffichage(Face face, Materiau materiau, Lumiere lumiere, Lettre lettre);
float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau, Vector3d normale);

#endif
