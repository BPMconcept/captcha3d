#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <opencv/cv.h>

#include "data.h"
#include "param.h"

///**
// * \fn int checkParams(int argc, char *argv[])
// * \brief Fonction qui analyse les paramètres passés en argument du main
// *
// * \param argc Argc du main
// * \param argv Argv du main
// * \return Succès ou échec
// */
//int checkParams(int argc, char *argv[])
//{
//    // Initialisation des variables globales
//    initGlobalParams();

//    if (argc <= 1) {
//        fprintf(stderr, "Utilisation: captcha3d [OPTION]\n");
//        fprintf(stderr, "Génère un captcha 3D à partir d'une chaine de caractère\n");
//        fprintf(stderr, "\t-b\tCouleur du fond d'écran R V B A (défaut blanc)\n");
//        fprintf(stderr, "\t-d\tActiver les déformations\n");
//        fprintf(stderr, "\t-f\tMode fenêtre (désactivé par défaut)\n");
//        fprintf(stderr, "\t-g\tActive le dégradé en fond\n");
//        fprintf(stderr, "\t-h\tHauteur de l'image (défaut: 150)\n");
//        fprintf(stderr, "\t-o\tChemin vers l'image à générer\n");
//        fprintf(stderr, "\t-q\tQualité de l'anti-aliasing (défaut: 0)\n");
//        fprintf(stderr, "\t-s\tChaine de caractère à afficher\n");
//        fprintf(stderr, "\t-w\tForcer la largeur de l'image\n");
//        return 0;
//    }

//    int i;
//    for (i = 0; i < argc; i++) {
//        // Chaine de caractère à afficher
//        if (strcmp(argv[i], "-s") == 0) {
//            cfg_str = argv[i + 1];
//            i++;
//            continue;
//        }

//        // Chemin de sortie du fichier, avec l'extension
//        if (strcmp(argv[i], "-o") == 0) {
//            cfg_output = argv[i + 1];
//            i++;
//            continue;
//        }

//        // Largeur de l'image
//        if (strcmp(argv[i], "-w") == 0) {
//            cfg_width = atoi(argv[i + 1]);
//            i++;
//            continue;
//        }

//        // Hauteur de l'image
//        if (strcmp(argv[i], "-h") == 0) {
//            cfg_height = atoi(argv[i + 1]);
//            i++;
//            continue;
//        }

//        // Mode fenêtre
//        if (strcmp(argv[i], "-f") == 0) {
//            cfg_window = 1;
//            continue;
//        }

//        // Choix de la couleur du background
//        if (strcmp(argv[i], "-b") == 0) {
//            cfg_background = cvScalar(atoi(argv[i + 3]), atoi(argv[i + 2]), atoi(argv[i + 1]), atoi(argv[i + 4]));
//            i += 4;
//            continue;
//        }

//        // Qualité de l'antialiasing
//        if (strcmp(argv[i], "-q") == 0) {
//            cfg_aliasing = atoi(argv[i + 1]);
//            i++;
//            continue;
//        }

//        // Déformations sinusoidales
//        if (strcmp(argv[i], "-d") == 0) {
//            cfg_deform_sin = 1;
//            continue;
//        }

//        // Activation du dégradé
//        if (strcmp(argv[i], "-g") == 0) {
//            cfg_degrade = 1;
//            continue;
//        }
//    }

//    // Test de caractères non pris en compte
//    if (!checkChar(cfg_str)) {
//        fprintf(stderr, "Présence d'un caractère non géré par le programme\n");
//        return 0;
//    }

//    // Champ -s non renseigné
//    if (strlen(cfg_str) == 0) {
//        fprintf(stderr, "Chaine de caractère à afficher obligatoire\n");
//        return 0;
//    }

//    // Champ -o non renseigné en mode image
//    if (strlen(cfg_output) == 0 && cfg_window == 0) {
//        fprintf(stderr, "Chemin vers l'image à générer obligatoire\n");
//        return 0;
//    }

//    // Largeur à calculer automatiquement
//    if (cfg_width == 0) {
//        cfg_width = cfg_height * strlen(cfg_str) * 2 / 3;
//    }

//    // Test de largeur suffisante
//    if (cfg_width < cfg_height) {
//        fprintf(stderr, "Largeur trop petite par rapport à la hauteur demandée\n");
//        return 0;
//    }

//    // Test de la valeur de cfg_aliasing
//    if (cfg_aliasing < 0 || cfg_aliasing > 100) {
//        fprintf(stderr, "Valeur de l'anti-aliasing trop élevée (max 100)\n");
//        return 0;
//    }


//    // Test de la longueur de la chaine
//    if (strlen(cfg_str) > MAX_STR_LEN) {
//        fprintf(stderr, "Chaine de caractère trop grande (max MAX_STR_LEN)\n");
//        return 0;
//    }

//    return 1;
//}

///**
// * \fn void initGlobalParams()
// * \brief Initialisation des paramètres globaux
// *
// */
//void initGlobalParams()
//{
//    cfg_str = "";
//    cfg_output = "";

//    // Déformations
//    cfg_deform_sin = 0;

//    // Taille
//    cfg_width = 0;
//    cfg_height = 150;

//    // Qualité anti aliasing
//    cfg_aliasing = 0;

//    // Mode non fenêtré
//    cfg_window = 0;

//    // Background blanc
//    cfg_background = cvScalar(255, 255, 255, 255);

//    // Dégardé désactivé
//    cfg_degrade = 0;
//}


///**
// * \fn int checkParams(int argc, char *argv[])
// * \brief Fonction qui teste si une chaine contient un caractère non géré par le captcha
// *
// * \param string Chaine de caractère
// * \return Succès ou échec
// */
//int checkChar(char *string)
//{
//    int i, test = 1;
//    for (i = 0; i < strlen(string); i++) {
//        if (strchr(CHAR_AUTH, string[i]) == 0) {
//            test = 0;
//        }
//    }
//    return test;
//}


