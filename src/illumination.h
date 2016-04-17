#ifndef ILLUMINATION_H_INCLUDED
#define ILLUMINATION_H_INCLUDED

#include "data.h"
#include "vector.h"

struct captcha3d_color randomColor();
void compute_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material materiau);
float angleDiffusion(Vector3d L, Vector3d N);
void compute_normal_vectors(Vector3d tab[], const Letter *letter);
void initialiserTableauNormales(Vector3d tab[], int taille);
struct captcha3d_color couleurAffichageGouraud(float coeff, struct captcha3d_color couleur);
Vector3d face_normal_vector(const Triangle *face, const Vector3d points[]);
struct captcha3d_color couleurAffichage(const Triangle *face, Material materiau, Light lumiere, const Letter *letter);

#endif
