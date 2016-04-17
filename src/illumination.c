#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "data.h"
#include "illumination.h"

#define max(a,b) (a>=b?a:b)

static float intensite(Light lumiere, Material materiau, Vector3d normale);

/**
 * \fn CvScalar couleurAffichageGouraud(float coeff, CvScalar couleur)
 * \brief Calcul de la couleur en fonction de la lumière pour le modèle de Gouraud
 *
 * \param coeff Multiplicateur
 * \param couleur Couleur initiale
 * \return Couleur pour Gouraud
 */
struct captcha3d_color couleurAffichageGouraud(float coeff, struct captcha3d_color couleur)
{
    couleur.red = coeff * couleur.red <= 255 ? coeff * couleur.red : 255;
    couleur.green = coeff * couleur.green <= 255 ? coeff * couleur.green : 255;
    couleur.blue = coeff * couleur.blue <= 255 ? coeff * couleur.blue : 255;

    return couleur;
}

/**
 * \fn CvScalar couleurAffichage(Face face, Materiau materiau, Lumiere lumiere,Lettre lettre)
 * \brief Calcul de la couleur d'une face
 *
 * \param face Face en cours de la lettre
 * \param materiau Matériau de la lettre
 * \param lumiere Lumière de l'environnement
 * \param lettre Lettre en cours
 * \return Couleur pour Gouraud
 */
struct captcha3d_color couleurAffichage(const Triangle *face, Material materiau, Light lumiere, const Letter *letter)
{
    struct captcha3d_color color;
    float coeff;
    Vector3d normale = face_normal_vector(face, letter->points);
    coeff = intensite(lumiere, materiau, normale);

    color.red = coeff * materiau.couleur.red <= 255 ? coeff * materiau.couleur.red : 255;
    color.green = coeff * materiau.couleur.green <= 255 ? coeff * materiau.couleur.green : 255;
    color.blue = coeff * materiau.couleur.blue <= 255 ? coeff * materiau.couleur.blue : 255;

    return color;
}

void compute_light_intensity(float tab[], Vector3d normales[], const Letter *letter, Light lumiere, Material material)
{
    Vector3d lux = normalize(&lumiere.direction);
    float angleDiffus;

    for (size_t i = 0; i < letter->pointsNumber; i++) {
        angleDiffus = max(0, angleDiffusion(lux, normales[i]));
        tab[i] = ((lumiere.ia) * (material.ka) + (lumiere.ip) * (material.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));
    }
}

/**
 * \fn float intensite(Lettre lettre, Lumiere lumiere, Materiau materiau,Vecteur normale)
 * \brief Calcul des intensités d'une lettre
 *
 * \param lettre Lettre en cours
 * \param lumiere Lumière de l'environnement
 * \param materiau Matériau de la lettre
 * \param normale Vecteur normal
 */
float intensite(Light lumiere, Material materiau, Vector3d normale)
{
    Vector3d lux = normalize(&lumiere.direction);
    float angleDiffus;

    //Calcul de l'intensité à chaque point de la lettre
    angleDiffus = max(0, angleDiffusion(lux, normale));
    return ((lumiere.ia) * (materiau.ka) + (lumiere.ip) * (materiau.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));

}

/**
 * \fn float angleDiffusion(Vecteur L, Vecteur N)
 * \brief Calcul de l'angle de diffusion
 *
 * \param L Vecteur lumière
 * \param N Vecteur normal
 * \return angle
 */
float angleDiffusion(Vector3d L, Vector3d N)
{
    //Produit scalaire pour obtenir l'angle
    return -((L.x) * (N.x) + (L.y) * (N.y) + (L.z) * (N.z));
}



