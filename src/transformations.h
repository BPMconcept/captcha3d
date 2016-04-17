#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_H_INCLUDED

#include "data.h"

void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres);
Letter transformation(Letter lettre, int i, int width, int height, int z, int marge, float e, float offset);
Letter translation(Letter lettre, Vector3d vecteur);
Letter echelle(Letter lettre, float coeff);
Vector3d barycentre(Letter lettre);
Letter deformation(Letter lettre);
Letter deformation_sin(Letter lettre, char type);
Vector3d appliquerMatrice(Vector3d m[3], Vector3d q);
Letter rotation(Letter lettre, Vector3d angles);
Vector3d calculterTranslation(int width, int height, int marge, float z);
float calculOffsetX(float z, int width, int marge);

#endif
