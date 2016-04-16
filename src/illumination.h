#ifndef ILLUMINATION_H_INCLUDED
#define ILLUMINATION_H_INCLUDED

#include "data.h"

void degrade(IplImage *img, int width, int height, CvScalar couleurHaute);
struct captcha3d_color couleurAleatoire();
void intensiteAuxPoints(float tab[], Vector3d normales[], Letter lettre, Light lumiere, Material materiau);
Vector3d normaliser(Vector3d vecteur);
float angleDiffusion(Vector3d L, Vector3d N);
void normalesAuxPoints(Vector3d tab[], Letter lettre);
Vector3d additionerVecteurs(Vector3d n1, Vector3d n2);
void initialiserTableauNormales(Vector3d tab[], int taille);
struct captcha3d_color couleurAffichageGouraud(float coeff, struct captcha3d_color couleur);
Vector3d normaleFace(Triangle face, Vector3d points[]);
struct captcha3d_color couleurAffichage(Triangle face, Material materiau, Light lumiere, Letter lettre);
float intensite(Letter lettre, Light lumiere, Material materiau, Vector3d normale);

#endif
