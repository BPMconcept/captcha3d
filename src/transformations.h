#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_INCLUDED

#include "data.h"

void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres);
Lettre transformation(Lettre lettre, int i, int width, int height, int z, int marge, float e, float offset);
Lettre translation(Lettre lettre, Vector3d vecteur);
Lettre echelle(Lettre lettre, float coeff);
Vector3d barycentre(Lettre lettre);
Lettre deformation(Lettre lettre);
Lettre deformation_sin(Lettre lettre, char type);
Vector3d appliquerMatrice(Vector3d m[3], Vector3d q);
Lettre rotation(Lettre lettre, Vector3d angles);
Vector3d calculterTranslation(int width, int height, int marge, float z);
float calculOffsetX(float z, int width, int marge);

#endif
