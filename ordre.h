#ifndef ORDRE_H_INCLUDED
#define ORDRE_H_INCLUDED
#include "stack.h"
#include "lecture.h"
#include "image.h"

/*
@requires un pointeur de pile, un entier
@assign peut allouer plus ou moins de mémoire à la pile
@ensure empile l'entier en argument sur la pile
*/
void empile(stack* p,int taille_ancien_bloc);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure dépile la pile
*/
void depile(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure depile les 2 dérniers éléments et empile leur somme
*/
void plus(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure dépile deux éléments et on empile la différence entre le second et le premier
*/
void moins(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile deux éléments et on empile leur produit
*/
void fois(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile deux éléments et on empile le quotient du second par le premier
*/
void divise(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile deux éléments et on empile le reste de la division entière du second par le premier
*/
void reste(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on empile 1 si l'élément vaut 0 et 0 sinon
*/
void non(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile deux éléments et on empile 1 si le second est plus grand que le premier, 0 sinon
*/
void plus_grand(stack* p);

/*
@requires un pointeur de pile et un entier
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on renvoie l'entier correspondant à la nouvelle direction à suivre
*/
void direction(stack* p, itineraire* db);

/*
@requires un pointeur de pile et un entier
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on renvoie l'entier correspondant au nouveau bord à suivre
*/
void bord(stack* p, itineraire* db);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on le rempile deux fois
*/
void duplique(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile deux éléments et on va faire "tourner" la pile jusqu'à la profondeur donnée par le second, autant de fois que le premier élément.
*/
void tourne(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on lit un entier sur l'entrée standard et on l'empile
*/
void in_nombre(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on lit un caractère sur l'entrée standard et on empile son code ASCII
*/
void in_char(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on l'affiche sur la sortie standard
*/
void out_nombre(stack* p);

/*
@requires un pointeur de pile
@assign peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure on dépile un élément et on affiche sur la sortie standard le caractère possédant ce code ASCII
*/
void out_char(stack* p);

/*
@requires un pointeur de pile
@assign rien
@ensure renvoie 0 si la pile contient strictement moins d'éléments que n, et 1 sinon
*/
int test_action(stack* p, int n);

/*
@requires un pointeur de calque, des correspondant aux coordonnées de départ et d'arriver, un pointeur de pile, un entier contenant la taille de l'ancien bloc
@assign renvoie vers une action a effectué, qui peut allouer plus ou moins de mémoire à la pile passé en argument
@ensure effectue l'action correspondante à la différence de luminosité eet de couleur du pixel de coordonnées "arrive" 
        et du pixel de coordonnée "départ"
*/
void action(calque* cal, int x0, int y0, int x1, int y1, stack* p, itineraire* db, int tb);


#endif // ORDRE_H_INCLUDED