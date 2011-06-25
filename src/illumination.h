#ifndef ILLUMINATION_H_INCLUDED
#define ILLUMINATION_INCLUDED

void degrade(IplImage *img, int width, int height, CvScalar couleurHaute);
CvScalar couleurAleatoire();
void intensiteAuxPoints(float tab[], Vecteur normales[], Lettre lettre, Lumiere lumiere, Materiau materiau);
Vecteur normaliser(Vecteur vecteur);
float angleDiffusion(Vecteur L, Vecteur N);
void normalesAuxPoints(Vecteur tab[],Lettre lettre);
Vecteur additionerVecteurs(Vecteur n1, Vecteur n2);
void initialiserTableauNormales(Vecteur tab[],int taille);
CvScalar couleurAffichageGouraud(float coeff, CvScalar couleur);
Vecteur normaleFace(Face face,CvPoint3D32f points[]);
CvScalar couleurAffichage(Face face, Materiau materiau, Lumiere lumiere,Lettre lettre);
float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau,Vecteur normale);

#endif // ILLUMINATION_H_INCLUDED
