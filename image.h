#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

/* 
la strucure utilisé pour un pixel est un triplet de trois entiers compris entre 0 et 255
codant respectivement la valeur en rouge, en vert et en bleu
*/
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} pixel;

/*
la structure image permet de traduire un fichier ppm en une matrice de pixel (tab),
tout en conservant via h et w la hauteur et la largeur de l'image
*/
typedef struct{
	pixel** tab;
	int h;
    int w;
} image;

/*
@requires un chemin vers un fichier .ppm
@assign alloue de la mémoire pour stocker la hauteur et la largeur de l'image
        ainsi qu'une matrice contenant les informations relatives à chaque pixel de l'image
@ensures renvoie un pointeur vers un type image représentant le fichier .ppm passé en argument
*/
image* read_ppm(char* file_path);

/*
@requires une chaîne de caractère
@assign rien
@ensures renvoie 0 si la chaîne commence par le caractère "#" et un autre entier sinon
*/
int commentaire(char* b);

/*
@requires un pixel
@assign rien
@ensures renvoie la valeur en luminosité du pixel
*/
int luminance(pixel p);

/*
ce type va remplacer le code rgb des pixels :
l'entier "l" est compris entre 0 et 2 selon la luminosité :
    0 : clair
    1 : normal
    2 : foncé

l'entier "c" est compris entre 0 et 5 selon la couleur :
    0 : rouge
    1 : jaune
    2 : vert
    3 : cyan
    4 : bleu
    5 : magenta

Pour signifier qu'on a affaire à une couleur passante, le couple (l,c) vaut (-1,-1).
Pour signifier qu'on a affaire à une couleur bloquante, le couple (l,c) vaut (-2,-2).
*/
typedef struct {
    int l;
    int c;
} valeur;

/*
je définis ici le type calque, (comme une calque) contenant la hauteur et la largeur de l'image auxquels il est associé
mais, à la place ces pixels, il contient la valeur de ces pixels (défini avec le type ci-dessus)
*/
typedef struct {
    valeur** tab;
    int h;
    int w;
} calque;

/*
@requires un pointeur vers une image
@assign alloue de la mémoire pour un calque, et un valeur** qui est free à la fin
@ensures renvoie un pointeur vers un calque assigné à l'image passé en argument
*/
calque* traduction(image* img);

/*
@requires un pixel et une valeur
@assign de la mémoire pour 1 valeur
@ensures renvoie dans la valeur celle du pixel
*/
valeur associe(pixel p, valeur v);

#endif // IMAGE_H_INCLUDED