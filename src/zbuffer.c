#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "data.h"
#include "arial.h"
#include "zbuffer.h"
#include "transformations.h"
#include "illumination.h"

static Material selectionMateriau();
static void ligne(int *xdebut, int *xfin, IplImage *temp, int y, int limite1, int limite2);
static Projection projeter(Vector3d p, Vector3d cp, float intensite);
static float profondeur(int x, int y, Vector3d a, Vector3d b, Vector3d c, Vector3d cp);
static void ordonnerProjetes(Projection *p1, Projection *p2, Projection *p3);
static void echanger(Projection *p1, Projection *p2);

void zBufferGouraud(struct captcha3d_image *image, CvMat* buffer, Letter lettre, Material materiau)
{
    IplImage *temp = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 3);

    Triangle face;
    int i, j, k;
    int xDebut, xFin, xLimiteG, xLimiteD, xMilieu;
    Vector2d triangleARemplir[3];
    float z, zbuff;
    float ia, ib, ip, alpha, beta, gamma;
    float d1, d2, d3;

    Vector3d normales[500];
    float intensites[500];

    //Définition lumière
    Light lumiere = {0.2, 0.9, {0, 0, 1}};

    //Définition du centre de projection
    Vector3d cp;
    cp.x = image->width / 2;
    cp.y = image->height / 2;
    cp.z = -Z_CENTRE_PROJECTION;

    // Calcul des normales aux points
    normalesAuxPoints(normales, lettre);

    // Calcul de l'intensité aux points
    intensiteAuxPoints(intensites, normales, lettre, lumiere, materiau);

    for (i = 0; i < lettre.numFaces; i++) {
        cvSet(temp, cvScalar(255, 255, 255, 0), 0);
        face = lettre.faces[i];

        //Obtention des points 3D de la face
        Vector3d p1 = lettre.points[face.a];
        Vector3d p2 = lettre.points[face.b];
        Vector3d p3 = lettre.points[face.c];

        //Obtention des intensités de chaque point
        float i1 = intensites[face.a];
        float i2 = intensites[face.b];
        float i3 = intensites[face.c];

        //Obtention des points projetés
        Projection pp1 = projeter(p1, cp, i1);
        Projection pp2 = projeter(p2, cp, i2);
        Projection pp3 = projeter(p3, cp, i3);

        //Ordonnancement des projetés
        ordonnerProjetes(&pp1, &pp2, &pp3);

        triangleARemplir[0] = pp1.p;
        triangleARemplir[1] = pp2.p;
        triangleARemplir[2] = pp3.p;
        //Remplissage du triangle
        cvFillConvexPoly(temp, triangleARemplir, 3, CV_RGB(0, 0, 0), 8, 0);

        //Détermination de la boite englobant le triangle
        xLimiteG = min(min(pp1.p.x, pp2.p.x), pp3.p.x);
        xLimiteD = max(max(pp1.p.x, pp2.p.x), pp3.p.x);

        // Calcul de xMilieu pour connaitre la configuration du triangle (brisure à gauche ou à droite)
        if (pp3.p.y != pp1.p.y) {
            xMilieu = (pp3.p.x - pp1.p.x) * (pp2.p.y - pp1.p.y) / (pp3.p.y - pp1.p.y) + pp1.p.x;
        } else {
            xMilieu = pp2.p.x;
        }


        for (k = pp1.p.y; k <= pp3.p.y; k++) {
            xDebut = -1;
            xFin = -1;
            //Calcul des bornes de la ligne
            ligne(&xDebut, &xFin, temp, k, xLimiteG, xLimiteD);

            int xLimBeta = (pp2.p.x > xMilieu) ? xFin : xDebut;
            int xLimAlpha = (pp2.p.x > xMilieu) ? xDebut : xFin;

            for (j = xDebut; j <= xFin; j++) {
                //Calcul de la profondeur du point dans l'espace correspondant
                z = profondeur(j, k, p1, p2, p3, cp);
                //Récupération de la valeur du zbuffer
                zbuff = CV_MAT_ELEM(*buffer, float, j, k);

                //Si le z est plus petit que celui du buffer, ou que le buffer est encore à 0
                if (z <= zbuff || zbuff == 0) {
                    //On calcule l'intensité du point considéré
                    d1 = sqrt((pp1.p.x - pp3.p.x) * (pp1.p.x - pp3.p.x) + (pp1.p.y - pp3.p.y) * (pp1.p.y - pp3.p.y));
                    d2 = sqrt((pp1.p.x - pp2.p.x) * (pp1.p.x - pp2.p.x) + (pp1.p.y - pp2.p.y) * (pp1.p.y - pp2.p.y));
                    d3 = sqrt((pp2.p.x - pp3.p.x) * (pp2.p.x - pp3.p.x) + (pp2.p.y - pp3.p.y) * (pp2.p.y - pp3.p.y));

                    if (d1 != 0) {
                        alpha = sqrt((pp1.p.x - xLimAlpha) * (pp1.p.x - xLimAlpha) + (pp1.p.y - k) * (pp1.p.y - k)) / d1;
                    } else {
                        alpha = 0;
                    }

                    ia = alpha * pp3.i + (1 - alpha) * pp1.i;


                    if (k <= pp2.p.y) {
                        //Première partie du triangle
                        if (d2 != 0) {
                            beta = sqrt((pp1.p.x - xLimBeta) * (pp1.p.x - xLimBeta) + (pp1.p.y - k) * (pp1.p.y - k)) / d2;
                        } else {
                            beta = 0;
                        }
                        ib = beta * pp2.i + (1 - beta) * pp1.i;
                    } else {
                        //Deuxième partie du triangle
                        if (d3 != 0) {
                            beta = sqrt((pp2.p.x - xLimBeta) * (pp2.p.x - xLimBeta) + (pp2.p.y - k) * (pp2.p.y - k)) / d3;
                        } else {
                            beta = 0;
                        }
                        ib = beta * pp3.i + (1 - beta) * pp2.i;
                    }

                    //Calcul final de l'intensité
                    if (xFin != xDebut) {
                        gamma = (float) (xFin - j) / (xFin - xDebut);
                        ip = (pp2.p.x > xMilieu) ? gamma * ia + (1 - gamma) * ib : gamma * ib + (1 - gamma) * ia;
                    } else {
                        ip = ia;
                    }

                    //Application de la couleur et mise à jour du zbuffer
//                    cvSet2D(img, height - k, j, couleurPixel);
                    struct captcha3d_color *pixel = captcha3d_image_get(image, j, image->height - k);

                    *pixel = couleurAffichageGouraud(ip, materiau.couleur);

                    CV_MAT_ELEM(*buffer, float, j, k) = z;
                }
            }
        }
    }
}

/**
 * \fn Materiau selectionMateriau()
 * \brief Renvoie un matériau de couleur aléatoire
 *
 * \return Materiau de couleur aléatoire
 */
Material selectionMateriau()
{
    Material materiau = {{255, 255, 255, 255}, 0.3, 0.9, 30};

    materiau.couleur.red = rand() % 256;
    materiau.couleur.green = rand() % 256;
    materiau.couleur.blue = rand() % 256;

    return materiau;
}

/**
 * \fn void ligne(int *xDebut, int *xFin, IplImage *temp,int y, int limite1, int limite2)
 * \brief Fonction qui permet d'obtenir le début et la fin d'une ligne colorée
 *
 * \param xDebut abscisse du début de la ligne
 * \param xFin abscisse de la fin de la ligne
 * \param temp image surlaquelle est dessinée le triangle projeté
 * \param y ordonnée à laquelle on cherche la ligne
 * \param limite1 limite gauche de recherche
 * \param limite2 limite droite de recherche
 */
void ligne(int *xDebut, int *xFin, IplImage *temp, int y, int limite1, int limite2)
{
    int x;
    CvScalar couleurRemplissage;

    for (x = limite1; x <= limite2; x++) {
        couleurRemplissage = cvGet2D(temp, y, x);

        if (couleurRemplissage.val[0] == 0 && couleurRemplissage.val[1] == 0 && couleurRemplissage.val[2] == 0) {
            if (*xDebut == -1) {
                *xDebut = x;
            } else {
                *xFin = x;
            }
        }
    }
    if (*xFin == -1) {
        *xFin = *xDebut;
    }
}

/**
 * \fn PointProjete projeter(CvPoint3D32f p, CvPoint3D32f cp, float intensite)
 * \brief Fonction qui renvoie le projeté sur l'écran (z=0) d'un point de l'espace associé à l'intensité de ce point
 *
 * \param p point de l'espace dont on veut le projeté
 * \param cp 2e centre de projection
 * \param intensite intensité du point de l'espace
 *
 * \return Point projeté sur l'écran
 */
Projection projeter(Vector3d p, Vector3d cp, float intensite)
{
    //Equation du plan de projection z=0
    Projection projete;
    Vector2d point;

    point.x = floor((p.x - cp.x) * (-cp.z) / (p.z - cp.z) + cp.x);
    point.y = floor((p.y - cp.y) * (-cp.z) / (p.z - cp.z) + cp.y);

    projete.p = point;
    projete.i = intensite;

    return projete;
}

/**
 * \fn float profondeur(int x,int y,CvPoint3D32f a, CvPoint3D32f b, CvPoint3D32f c, CvPoint3D32f cp)
 * \brief Fonction qui calcul la composante z du point appartenant au triangle définit par les points a,b et c, et dont le projeté est en (x,y) sur l'écran
 *
 * \param x abscisse du projeté
 * \param y ordonnée du projeté
 * \param a 1er point décrivant la face triangulaire
 * \param b 2e point décrivant la face triangulaire
 * \param c 3e point décrivant la face triangulaire
 * \param cp centre de projection
 *
 * \return Profondeur du point appartenant au triangle définit par les points a,b et c, et dont le projeté est en (x,y) sur l'écran
 */
float profondeur(int x, int y, Vector3d a, Vector3d b, Vector3d c, Vector3d cp)
{
    float t;

    t = (cp.x * a.y * c.z - cp.x * a.y * b.z - cp.x * b.y * c.z + cp.x * b.z * c.y - cp.x * a.z * c.y + cp.x * a.z * b.y - cp.y * c.x * b.z - cp.y * a.x * c.z + cp.y * b.x * c.z - cp.y * b.x * a.z + cp.y * a.x * b.z + cp.y * c.x * a.z + cp.z * a.x * c.y - cp.z * b.x * c.y + cp.z * b.x * a.y - cp.z * c.x * a.y + cp.z * c.x * b.y - cp.z * a.x * b.y + b.y * a.x * c.z - b.z * a.x * c.y + a.y * c.x * b.z - a.y * b.x * c.z + a.z * b.x * c.y - b.y * c.x * a.z)
        /
        (-cp.x * a.y * b.z + cp.x * a.y * c.z - cp.x * b.y * c.z + cp.x * b.z * c.y - cp.x * a.z * c.y + cp.x * a.z * b.y - cp.y * a.x * c.z + cp.y * b.x * c.z - cp.y * c.x * b.z - cp.y * b.x * a.z + cp.y * a.x * b.z + cp.y * c.x * a.z + cp.z * a.x * c.y + cp.z * c.x * b.y - cp.z * c.x * a.y - cp.z * b.x * c.y + cp.z * b.x * a.y - cp.z * a.x * b.y + x * a.y * b.z - x * a.y * c.z + x * b.y * c.z - x * b.z * c.y - x * a.z * b.y + x * a.z * c.y + c.x * b.z * y + a.x * c.z * y - b.x * c.z * y - a.x * b.z * y + b.x * a.z * y - c.x * a.z * y);

    return -cp.z * t + cp.z;
}

/**
 * \fn void ordonnerProjetes(PointProjete *p1,PointProjete *p2,PointProjete *p3)
 * \brief Fonction qui trie 3 points projetés dans l'ordre croissant de leu composante y
 *
 * \param p1 1er point projeté à trier
 * \param p2 2e point projeté à trier
 * \param p3 3e point projeté à trier
 */
void ordonnerProjetes(Projection *p1, Projection *p2, Projection *p3)
{
    if ((*p1).p.y > (*p2).p.y) {
        echanger(p1, p2);
    }
    if ((*p2).p.y > (*p3).p.y) {
        echanger(p2, p3);
    }
    if ((*p1).p.y > (*p2).p.y) {
        echanger(p1, p2);
    }
}


/**
 * \fn void echanger(PointProjete *p1,PointProjete *p2)
 * \brief Fonction qui échange deux points projetés
 *
 * \param p1 1er point projeté que l'on veut échanger
 * \param p2 2e point projeté que l'on veut échanger
 */
void echanger(Projection *p1, Projection *p2)
{
    Projection temp;
    temp.p = (*p1).p;
    temp.i = (*p1).i;
    (*p1).p = (*p2).p;
    (*p1).i = (*p2).i;
    (*p2).p = temp.p;
    (*p2).i = temp.i;
}

