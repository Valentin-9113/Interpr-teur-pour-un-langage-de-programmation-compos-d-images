#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"

image* read_ppm(char* file_path){
	FILE* f = fopen(file_path, "r");
	int w;
    int h;
    // utilisation d'un buffer pour la lecture des premières lignes
    int buff_size = 128; 
	char buffer[buff_size];


    //lecture de la 1ère ligne, test du type de fichier
    fgets(buffer, buff_size, f);
    while (commentaire(buffer)==0){
        fgets(buffer, buff_size, f);
    } //condition d'arrêt, il y a un nombre finit de commentaire dans un .ppm, on va forcément sortir de la boncle à un moment
    if(strcmp(buffer, "P6\n")){
		printf("Le fichier n'est pas au bon format\n");
		exit(0);
	}


    //lecture de la 2e ligne, récupération des variables h et w
    fgets(buffer, buff_size, f);
    while (commentaire(buffer)==0){
        fgets(buffer, buff_size, f);
    } //condition d'arrêt, il y a un nombre finit de commentaire dans un .ppm, on va forcément sortir de la boncle à un moment
    sscanf(buffer, "%d %d", &w, &h);


    //lecture de la 3e ligne contenant des informations sur un pixel
    fgets(buffer, buff_size, f);
    while (commentaire(buffer)==0){
        fgets(buffer, buff_size, f);
    } //condition d'arrêt, il y a un nombre finit de commentaire dans un .ppm, on va forcément sortir de la boncle à un moment


    //création d'un tableau de tableau de pixels pour y stocker les informations du fichier à lire
    pixel** tab_tmp = malloc(h * sizeof(pixel*)); 
	for(int i = 0; i < h; i++){
		tab_tmp[i] = malloc(w * sizeof(pixel));
	}


    //lecture de l'image du fichier .ppm, remplissage du tableau et 
    for(int j = 0; j < h; j++){
        fread(tab_tmp[j], sizeof(pixel), w, f);
    }
    image* img = malloc(sizeof(image));
	img->tab = tab_tmp;
	img->w = w;
	img->h = h;
    fclose(f);
    return img;
}

int commentaire(char* b){
    return strncmp(b,"#",1);
}

int luminance(pixel p){
    return 0.202*p.r+0.707*p.g+0.071*p.b;
}


calque* traduction(image* img){
    //printf("debut");
    calque* cal = malloc(sizeof(calque));
    // alloue de la mémoire pour un calque de valeur, visuellement superposable à l'image
    int h = img->h;
    int w = img->w;
    //printf("iciii");
    valeur** tab_tmp = malloc(h * sizeof(valeur*)); 
	for(int i = 0; i < h; i++){
		tab_tmp[i] = malloc(w * sizeof(valeur));
	}
    for(int x = 0; x < h; x++){
        for(int y = 0; y < w; y++){
            valeur v;
            //printf("at %d %d",x,y);
            //printf(" -> (%d,%d,%d)",img->tab[x][y].r,img->tab[x][y].g,img->tab[x][y].b);
            tab_tmp[x][y] = associe(img->tab[x][y],v);
            //printf(" -> (%d,%d)\n",tab_tmp[x][y].l,tab_tmp[x][y].c);
        }
    }
    cal->tab = tab_tmp;
    cal->h = h;
    cal->w = w;
    //printf("fin\n");
    return cal;
}

valeur associe(pixel p, valeur v) {
    if (p.r == 255 && p.g == 128 && p.b == 128) {
        v.l=0;
        v.c=0;
        return v;
    } //up rouge clair
    if (p.r == 255 && p.g == 0 && p.b == 0 ) {
        v.l=1;
        v.c=0;
        return v;
    } //up rouge
    if (p.r == 128 && p.g == 0 && p.b == 0) {
        v.l=2;
        v.c=0;
        return v;
    } // up rouge foncé
    if (p.r == 255 && p.g == 255 && p.b == 128 ) {
        v.l=0;
        v.c=1;
        return v;
    } // up jaune clair
    if (p.r == 255 && p.g == 255 && p.b == 0 ) {
        v.l=1;
        v.c=1;
        return v;
    } // up jaune
    if (p.r == 128 && p.g == 128 && p.b == 0 ) {
        v.l=2;
        v.c=1;
        return v;
    } // up jaune foncé
    if (p.r == 128 && p.g == 255 && p.b == 128 ) {
        v.l=0;
        v.c=2;
        return v;
    } // up vert clair
    if (p.r == 0 && p.g == 255 && p.b == 0 ) {
        v.l=1;
        v.c=2;
        return v;
    } // up vert
    if (p.r == 0 && p.g == 128 && p.b == 0) {
        v.l=2;
        v.c=2;
        return v;
    } // up vert foncé
    if (p.r == 128 && p.g == 255 && p.b == 255 ) {
        v.l=0;
        v.c=3;
        return v;
    } // up cyan clair
    if (p.r == 0 && p.g == 255 && p.b == 255 ) {
        v.l=1;
        v.c=3;
        return v;
    } // up cyan
    if (p.r == 0 && p.g == 128 && p.b == 128 ) {
        v.l=2;
        v.c=3;
        return v;
    } // up cyan foncé
    if (p.r == 128 && p.g == 128 && p.b == 255) {
        v.l=0;
        v.c=4;
        return v;
    } // up bleu clair
    if (p.r == 0 && p.g == 0 && p.b == 255 ) {
        v.l=1;
        v.c=4;
        return v;
    } // up bleu
    if (p.r == 0 && p.g == 0 && p.b == 128 ) {
        v.l=2;
        v.c=4;
        return v;
    } // up bleu foncé
    if (p.r == 255 && p.g == 128 && p.b == 255 ) {
        v.l=0;
        v.c=5;
        return v;
    } // up magenta clair
    if (p.r == 255 && p.g == 0 && p.b == 255 ) {
        v.l=1;
        v.c=5;
        return v;
    } // up magenta
    if (p.r == 128 && p.g == 0 && p.b == 128 ) {
        v.l=2;
        v.c=5;
        return v;
    } // up magenta foncé
    if (luminance(p) < 128 ) {
        v.l=-2;
        v.c=-2;
        return v;
    } // up couleur bloquante
    else {
        v.l=-1;
        v.c=-1;
        return v;
    }
}