#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "color.h"
#include "data.h"
#include "illumination.h"

#define max(a,b) (a>=b?a:b)

static float lightning_angle(Vector3d L, Vector3d N)
{
    return -((L.x) * (N.x) + (L.y) * (N.y) + (L.z) * (N.z));
}

static float letter_intensity(Light lumiere, Material materiau, Vector3d normale)
{
    Vector3d lux = vector_normalize(&lumiere.direction);
    float angleDiffus;

    angleDiffus = max(0, lightning_angle(lux, normale));
    return ((lumiere.ia) * (materiau.ka) + (lumiere.ip) * (materiau.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));
}

struct Color color_random()
{
    struct Color couleur;

    couleur.red = rand() % 256;
    couleur.green = rand() % 256;
    couleur.blue = rand() % 256;
    couleur.alpha = 255;

    return couleur;
}

struct Color color_gouraud(float coeff, struct Color couleur)
{
    couleur.red = coeff * couleur.red <= 255 ? coeff * couleur.red : 255;
    couleur.green = coeff * couleur.green <= 255 ? coeff * couleur.green : 255;
    couleur.blue = coeff * couleur.blue <= 255 ? coeff * couleur.blue : 255;

    return couleur;
}

void color_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material material)
{
    Vector3d lux = vector_normalize(&lumiere.direction);
    float angleDiffus;

    for (size_t i = 0; i < letter->pointsNumber; i++) {
        angleDiffus = max(0, lightning_angle(lux, normales[i]));
        tab[i] = ((lumiere.ia) * (material.ka) + (lumiere.ip) * (material.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));
    }
}
