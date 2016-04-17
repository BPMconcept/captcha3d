#ifndef ILLUMINATION_H_INCLUDED
#define ILLUMINATION_H_INCLUDED

#include "data.h"
#include "vector.h"
#include "letter.h"

void compute_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material materiau);
float angleDiffusion(Vector3d L, Vector3d N);
struct captcha3d_color couleurAffichageGouraud(float coeff, struct captcha3d_color couleur);
struct captcha3d_color couleurAffichage(const Triangle *face, Material materiau, Light lumiere, const Letter *letter);

#endif
