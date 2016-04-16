#ifndef ZBUFFER_H_INCLUDED
#define ZBUFFER_INCLUDED

void parametresTransformation(float *z, int *marge, float *e, float *offset, int height, int width, int nbLettres);
Lettre transformation(Lettre lettre, int i, int width, int height, int z, int marge, float e, float offset);
Lettre translation(Lettre lettre, Vecteur vecteur);
Lettre echelle(Lettre lettre, float coeff);
CvPoint3D32f barycentre(Lettre lettre);
Lettre deformation(Lettre lettre);
Lettre deformation_sin(Lettre lettre, char type);
CvPoint3D32f appliquerMatrice(Vecteur m[3], CvPoint3D32f q);
Lettre rotation(Lettre lettre, Vecteur angles);
Vecteur calculterTranslation(int width, int height, int marge, float z);
float calculOffsetX(float z, int width, int marge);

#endif // ZBUFFER_H_INCLUDED
