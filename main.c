#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "image.h"
#include "ordre.h"
#include "lecture.h"

int main(int argc,char* argv[]){
    if ( argc != 2 ){
        printf("Veuillez vérifier qu'un unique argument a bien été mis en paramètre");
        exit(0);
    }
    image* cc = read_ppm(argv[1]);
    calque* cal = traduction(cc);
    stack* pile=initialize_stack();
    itineraire* db = malloc(sizeof(itineraire));
    db->direction = 0;
    db->bord = 0;
    suivant(cal,0,0,db,0,pile);
    //printf("%d, %d\n",cal->tab[0][cal->w/2].l,cal->tab[0][cal->w/2].c);
    //printf("%d, %d\n",cal->tab[0][0].l,cal->tab[0][0].c);
    return 0;
}