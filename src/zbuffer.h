#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_INCLUDED

#include "param.h"

void generer(struct captcha3d_image *image, char string[], CvScalar couleur);
void zBufferGouraud(struct captcha3d_image *image, CvMat* buffer, Lettre lettre, Materiau materiau);
void zBuffer(IplImage *img, CvMat* buffer, Lettre lettre, Materiau materiau, int width, int height);
Materiau selectionMateriau();
void ligne(int *xdebut, int *xfin, IplImage *temp, int y, int limite1, int limite2);
PointProjete projeter(CvPoint3D32f p, CvPoint3D32f cp, float intensite);
float profondeur(int x, int y, CvPoint3D32f a, CvPoint3D32f b, CvPoint3D32f c, CvPoint3D32f cp);
void ordonnerProjetes(PointProjete *p1, PointProjete *p2, PointProjete *p3);
void echanger(PointProjete *p1, PointProjete *p2);
Lettre descriptionLettre(char c);


#endif // ZBUFFER_H_INCLUDED
