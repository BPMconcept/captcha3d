#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "data.h"
#include "illumination.h"

#define max(a,b) (a>=b?a:b)

struct captcha3d_color randomColor()
{
    struct captcha3d_color couleur;

    couleur.red = rand() % 256;
    couleur.green = rand() % 256;
    couleur.blue = rand() % 256;
    couleur.alpha = 255;

    return couleur;
}

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
struct captcha3d_color couleurAffichage(Triangle face, Material materiau, Light lumiere, Letter lettre)
{
    struct captcha3d_color color;
    float coeff;
    Vector3d normale = normaleFace(face, lettre.points);
    coeff = intensite(lettre, lumiere, materiau, normale);

    color.red = coeff * materiau.couleur.red <= 255 ? coeff * materiau.couleur.red : 255;
    color.green = coeff * materiau.couleur.green <= 255 ? coeff * materiau.couleur.green : 255;
    color.blue = coeff * materiau.couleur.blue <= 255 ? coeff * materiau.couleur.blue : 255;

    return color;
}

/**
 * \fn void intensiteAuxPoints(float tab[], Vecteur normales[], Lettre lettre, Lumiere lumiere, Materiau materiau)
 * \brief Calcul des intensités aux points d'une lettre pour le modèle de Gouraud
 *
 * \param tab[] Contiendra les intensités
 * \param normales[] Contient les vecteurs normaux
 * \param lettre Lettre en cours
 * \param lumiere Lumière de l'environnement
 * \param materiau Matériau de la lettre
 */
void intensiteAuxPoints(float tab[], Vector3d normales[], Letter lettre, Light lumiere, Material materiau)
{
    Vector3d lux = normaliser(lumiere.direction);
    int i;
    float angleDiffus;

    //Calcul de l'intensité à chaque point de la lettre
    for (i = 0; i < lettre.numPoints; i++) {
        angleDiffus = max(0, angleDiffusion(lux, normales[i]));
        tab[i] = ((lumiere.ia) * (materiau.ka) + (lumiere.ip) * (materiau.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));
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
float intensite(Letter lettre, Light lumiere, Material materiau, Vector3d normale)
{
    Vector3d lux = normaliser(lumiere.direction);
    float angleDiffus;

    //Calcul de l'intensité à chaque point de la lettre
    angleDiffus = max(0, angleDiffusion(lux, normale));
    return ((lumiere.ia) * (materiau.ka) + (lumiere.ip) * (materiau.kd) * angleDiffus) / ((lumiere.ip) + (lumiere.ia));

}

/**
 * \fn Vecteur normaleFace(Face face,CvPoint3D32f points[])
 * \brief Calcul du vecteur normale à une face
 *
 * \param face Face en cours
 * \param points[] Tableau de points
 * \return Vecteur normal
 */
Vector3d normaleFace(Triangle face, Vector3d points[])
{
    Vector3d n;
    Vector3d p1, p2, p3;

    p1 = points[face.a];
    p2 = points[face.b];
    p3 = points[face.c];

    //Calcul du produit vectoriel pour avoir la normale
    n.x = -((p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y));
    n.y = -((p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z));
    n.z = -((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));

    return normaliser(n);
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

/**
 * \fn Vecteur normaliser(Vecteur vecteur)
 * \brief Normalise un vecteur
 *
 * \param vecteur Vecteur à normaliser
 * \return vecteur normalisé
 */
Vector3d normaliser(Vector3d vecteur)
{
    Vector3d vecteurNormal = vecteur;
    float norme;
    norme = sqrt((vecteur.x) * (vecteur.x) + (vecteur.y) * (vecteur.y) + (vecteur.z) * (vecteur.z));

    vecteurNormal.x /= norme;
    vecteurNormal.y /= norme;
    vecteurNormal.z /= norme;

    return vecteurNormal;
}

/**
 * \fn void normalesAuxPoints(Vecteur tab[],Lettre lettre)
 * \brief Fonction qui calcule les normales à chaque points de la lettre
 *
 * \param tab Tableau qui recevra les normales
 * \param lettre Lettre pour laquelle il faut calculer les normales
 */
void normalesAuxPoints(Vector3d tab[], Letter lettre)
{
    Vector3d n;
    Triangle face;
    int i;
    initialiserTableauNormales(tab, lettre.numPoints);

    for (i = 0; i < lettre.numFaces; i++) {
        face = lettre.faces[i];
        //Calcul de la normale à la face
        n = normaleFace(lettre.faces[i], lettre.points);

        //Ajout de cette normale à chacun des points de la face
        tab[face.a] = additionerVecteurs(tab[face.a], n);
        tab[face.b] = additionerVecteurs(tab[face.b], n);
        tab[face.c] = additionerVecteurs(tab[face.c], n);

    }

    //On normalise les normales
    for (i = 0; i < lettre.numPoints; i++) {
        tab[i] = normaliser(tab[i]);
    }
}

/**
 * \fn Vecteur additionerVecteurs(Vecteur n1, Vecteur n2)
 * \brief Aditionne deux vecteurs
 *
 * \param n1 Premier vecteur à additioner
 * \param n2 Deuxième vecteur à additioner
 * \return Vecteur total
 */
Vector3d additionerVecteurs(Vector3d n1, Vector3d n2)
{
    Vector3d n;
    n.x = n1.x + n2.x;
    n.y = n1.y + n2.y;
    n.z = n1.z + n2.z;

    return n;
}

/**
 * \fn void initialiserTableauNormales(Vecteur tab[],int taille)
 * \brief Initialise un tableau avec la normale nulle
 *
 * \param tab Tableau à initialiser
 * \param taille Taille du tableau
 */
void initialiserTableauNormales(Vector3d tab[], int taille)
{
    Vector3d nul;
    int i;

    nul.x = 0;
    nul.y = 0;
    nul.z = 0;

    for (i = 0; i < taille; i++) {
        tab[i] = nul;
    }
}

