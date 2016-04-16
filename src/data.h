#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "captcha3d.h"

#define Z_CENTRE_PROJECTION 			600
#define PI								3.14159
#define DEFORMATION_SIN_AMPLITUDE		0.5
#define DEFORMATION_SIN_PERIODE			3.5
#define MAX_STR_LEN						5
#define CHAR_AUTH 						"abcdefghijklmnopqrstuvwxyz0123456789"

//Macros
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

typedef struct {
    float x;
    float y;
    float z;
} Vector3d;

typedef struct {
    float x;
    float y;
} Vector2d;

/**
 * \struct Face
 * \brief Face triangulaire
 *
 * Face triangulaire, a,b et c sont les identifiants des 3 points constituants la face.
 */
typedef struct {
    int a; /*!< identifiant point a du triangle*/
    int b; /*!< identifiant point b du triangle*/
    int c; /*!< identifiant point c du triangle*/
}
Face;

/**
 * \struct Lettre
 * \brief Description d'une lettre
 *
 * Une lettre est définie par un nombre de point, un tableau de points et un tableau de faces.
 */
typedef struct {
    int numPoints; /*!< nombre de points*/
    Vector3d points[500]; /*!< tableau des points*/
    int numFaces; /*!< nombre de faces*/
    Face faces[800]; /*!< tableau des faces*/
}
Lettre;

/**
 * \struct Lumiere
 * \brief Description d'une lumiere
 *
 * Une lumiere unidirectionnelle définie par des intensités et une direction.
 */
typedef struct {
    float ia; /*!< intensité ambiante */
    float ip; /*!< intensité */
    Vector3d direction; /*!< direction de la lumière*/
}
Lumiere;

/**
 * \struct Materiau
 * \brief Description d'une materiau
 *
 * Un materiau dispose de propriétés intrinsèques qui conditionnent l'interaction de la lumière avec l'objet.
 */
typedef struct {
    struct captcha3d_pixel couleur; /*!< couleur */
    float ka; /*!< coefficient ambiant */
    float kd; /*!< coefficient diffus */
    float ks; /*!< coefficient speculair */
    int n; /*!< exposant spéculaire*/
}
Materiau;

#include <opencv/cv.h>

/**
 * \struct PointProjete
 * \brief Description d'une point projete sur l'écran
 *
 * Un point projete sur l'écran est un point CvPoint qui dipose d'une intensité (correspondante à celle de son homologue 3D de l'espace)
 */
typedef struct {
    Vector2d p;
    float i;
}
PointProjete;

#endif
