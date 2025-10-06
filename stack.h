#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct{
    int top;
    int* array;
    int size;
}stack;

/*
@requires un pointeur vers une pile et un entier qui sera sa nouvelle taille
@assign alloue de la mémoire pour la création d'un tableau de taille new_size
        libère la mémoire et supprime tableau initial de la pile
@ensures la taille de la pile à été modifié
*/
void resize(stack* p,int new_size);

/*
@requires rien
@assign alloue de la mémoire pour une pile
@ensures une pile vide
*/
stack* initialize_stack();

/*
@requires un pointeur vers une pile et un entier
@assign si la pile à suffisement de mémoire pour ajouter un élément, rien
        sinon on double la mémoire allouer à la pile
@ensures la pile s'est vu ajouter à son sommet l'élément en argument
*/
void push(stack* p,int e);

/*
@requires un pointeur de pile
@assign rien
@ensures renvoie vrai si la pile est vide, faux sinon
*/
int is_empty(stack* p);

/*
@requires un pointeur vers une pile
@assign si le sommet est au tier du tableau, on reduit de moitié la mémoire alloué à la pile
@ensures si la pile est vide, la fonction retourne -1, sinon elle retourne le sommet de la pile tout en le supprimant de celle-ci
*/
int pop(stack* p);

/*
@requires un pointeur de pile
@assign rien
@ensures affiche la pile dans la sortie standard
*/
void printp(stack* p);

#endif // STACK_H_INCLUDED
