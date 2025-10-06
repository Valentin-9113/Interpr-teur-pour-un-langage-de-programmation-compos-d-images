#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "lecture.h"
#include "ordre.h"

int egal_valeur(valeur v1, valeur v2) {
    return (v1.l == v2.l && v1.c == v2.c);
}

lcoord* initialize_lcoord(calque* cal) {
    lcoord* list = malloc(sizeof(lcoord*));
    list->taille = (cal->w)*(cal->h);
    list->l = malloc((list->taille)*sizeof(coord));
    list->compteur = 0;
    return list;
}

void bloc(calque* cal, int x, int y, valeur v, int** traite, lcoord* list) {
    traite[x][y]=1; // on à bien traité ce pixel
    coord c;
    c.x = x;
    c.y = y;
    list->l[list->compteur] = c;
    list->compteur = list->compteur + 1;
    //action sur les voisins
    int xs = ((cal->h)+x+1)%(cal->h); // xs pour x-sud, l'indice de la ligne sous celle considéré (en prenant bien en compte que l'image est un tore!)
    int xn = ((cal->h)+x-1)%(cal->h); // xs pour x-nord, l'indice de la ligne au dessus de celle considéré (en prenant bien en compte que l'image est un tore!)
    int yo = ((cal->w)+y-1)%(cal->w); // yo pour y-ouest, l'indice de la colonnes à gauche de celle considéré (en prenant bien en compte que l'image est un tore!)
    int ye = ((cal->w)+y+1)%(cal->w); // yo pour y-est, l'indice de la colonnes à droite de celle considéré (en prenant bien en compte que l'image est un tore!)
    // on relance l'algorithme sur les voisins
    if (egal_valeur(cal->tab[x][yo], v) && traite[x][yo] != 1) {
        bloc(cal,x,yo,v,traite,list); //ouest
    }
    if (egal_valeur(cal->tab[x][ye], v) && traite[x][ye] != 1) {
        bloc(cal,x,ye,v,traite,list); //est
    }
    if (egal_valeur(cal->tab[xs][y], v) && traite[xs][y] != 1) {
        bloc(cal,xs,y,v,traite,list); //sud
    }
    if (egal_valeur(cal->tab[xn][y], v) && traite[xn][y] != 1) {
        bloc(cal,xn,y,v,traite,list); //nord
    } else {}
}

coord recherche_du_pixel_de_depart(calque* cal, lcoord* list, itineraire* db) {
    coord init = list->l[0]; // init servira à déterminé une information sur la position de la frontière recherché dans l'image, pour ensuite remplir liste_bis
    lcoord* list_bis = initialize_lcoord(cal); // liste_bis sera la liste des pixels candidats, se trouvant sur la frontière de la direction considéré
// sud
    if (db->direction == 1){
        // on récupère les coordonnées d'un des pixels de la frontière sud dans "init"
        for (int i = 0; i < list->compteur; i++) { // on parcourt list->l
            coord p_tmp = list->l[i];
            int xs = ((cal->h)+p_tmp.x+1)%(cal->h);
            // xs pour x-sud, ligne au sud de celui considéré
            if ((p_tmp.x > init.x) && !(egal_valeur(cal->tab[p_tmp.x][p_tmp.y],cal->tab[xs][p_tmp.y]))) {
                init = list->l[i];
            }
        }
        // on récupère l'ensemble des pixels de la frontière sud dans list_bis
        for (int j = 0; j < list->compteur; j++) {
            int xs = ((cal->h)+list->l[j].x+1)%(cal->h);
            if (list->l[j].x == init.x && !(egal_valeur(cal->tab[list->l[j].x][list->l[j].y],cal->tab[xs][list->l[j].y]))) {
                list_bis->l[list_bis->compteur] = list->l[j];
                list_bis->compteur = list_bis->compteur +1;
            }
        }
        // parmi la liste des candidats, recherche de celui étant le plus à babord ou à tribord
        if (db->bord == 1) { // tribord, recherche du pixel le plus à gauche dans liste_bis->l, liste des pixels candidats
            coord min = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].y < min.y) {
                    min = list_bis->l[n];
                }
            }
            return min;
        } else { // babord, recherche du pixel le plus à droite dans liste_bis->l, liste des pixels candidats
            coord max = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].y > max.y) {
                    max = list_bis->l[n];
                }
            }
            return max;
        }
    }

// est
    if (db->direction == 0){
        // on récupère les coordonnées d'un des pixels de la frontière est dans "init"
        for (int i = 0; i < list->compteur; i++) { // on parcours la list->l
            coord p_tmp = list->l[i];
            int ye = ((cal->w)+p_tmp.y+1)%(cal->w); // ye pour y-est ; la collone à droite de celle qu'on considère
            if ((p_tmp.y > init.y) && !(egal_valeur(cal->tab[p_tmp.x][p_tmp.y],cal->tab[p_tmp.x][ye]))) {
                init = list->l[i];
            }
        }
        // on récupère l'ensemble des pixels de la frontière est dans list_bis
        for (int j = 0; j < list->compteur; j++) {
            int ye = ((cal->w)+list->l[j].y+1)%(cal->w); // ye pour y-est ; la colonne à droite de celle qu'on considère
            if (list->l[j].y == init.y && !(egal_valeur(cal->tab[list->l[j].x][list->l[j].y],cal->tab[list->l[j].x][ye]))) {
                list_bis->l[list_bis->compteur] = list->l[j];
                list_bis->compteur = list_bis->compteur +1;
            }
        }
        // parmi la liste des candidats, recherche de celui étant le plus à babord ou à tribord
        if (db->bord == 1) { // tribors, recherche du pixel à l'indice de ligne maximale dans liste_bis->l, liste des pixels candidats
            coord max = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].x > max.x) {
                    max = list_bis->l[n];
                }
            }
            return max;
        } else { // babord, recherche du pixel à l'indice de ligne minimale dans liste_bis->l, liste des pixels candidats
            coord min = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].x < min.x) {
                    min = list_bis->l[n];
                }
            }
            return min;
        }
    }
// nord
    if (db->direction == 3){
        // on récupère les coordonnées d'un des pixels de la frontière nord dans "init"
        for (int i = 0; i < list->compteur; i++) { // on parcourt list->l
            coord p_tmp = list->l[i];
            int xn = ((cal->h)+p_tmp.x-1)%(cal->h); // xn pour x-nord, la ligne au nord de celle considéré
            if ((p_tmp.x < init.x) && !(egal_valeur(cal->tab[p_tmp.x][p_tmp.y],cal->tab[xn][p_tmp.y]))) {
                init = list->l[i];
            }
        }
        // on récupère l'ensemble des pixels de la frontière ouest dans list_bis
        for (int j = 0; j < list->compteur; j++) {
            int xn = ((cal->h)+list->l[j].x-1)%(cal->h); // xn pour x-nord, la ligne au nord de celle considéré
            if (list->l[j].x == init.x && !(egal_valeur(cal->tab[list->l[j].x][list->l[j].y],cal->tab[xn][list->l[j].y]))) {
                list_bis->l[list_bis->compteur] = list->l[j];
                list_bis->compteur = list_bis->compteur +1;
            }
        }
        // parmi la liste des candidats, recherche de celui étant le plus à babord ou à tribord
        if (db->bord == 1) { // tribord, recherche du pixel à l'indice de collone maximal dans liste_bis->l, liste des pixels candidats
            coord max = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].y > max.y) {
                    max = list_bis->l[n];
                }
            }
            return max;
        } else { // babord, recherche du pixel à l'indice de colonne minimale dans liste_bis->l, liste des pixels candidats
            coord min = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].y < min.y) {
                    min = list_bis->l[n];
                }
            }
            return min;
        }
    }
// ouest
    else {
        // on récupère les coordonnées d'un des pixels de la frontière ouest dans "init"
        for (int i = 0; i < list->compteur; i++) { // on parcours la list->l
            coord p_tmp = list->l[i];
            int yo = ((cal->w)+p_tmp.y-1)%(cal->w); // yo pour y-ouest ; la colonne à gauche de celle qu'on considère
            if ((p_tmp.y < init.y) && !(egal_valeur(cal->tab[p_tmp.x][p_tmp.y],cal->tab[p_tmp.x][yo]))) {
                init = list->l[i];
            }
        }
        // on récupère l'ensemble des pixels de la frontière est dans list_bis
        for (int j = 0; j < list->compteur; j++) {
            int yo = ((cal->w)+list->l[j].y-1)%(cal->w); // yo pour y-ouest ; la colonne à gauche de celle qu'on considère
            if (list->l[j].y == init.y && !(egal_valeur(cal->tab[list->l[j].x][list->l[j].y],cal->tab[list->l[j].x][yo]))) {
                list_bis->l[list_bis->compteur] = list->l[j];
                list_bis->compteur = list_bis->compteur +1;
            }
        }
        // parmi la liste des candidats, recherche de celui étant le plus à babord ou à tribord
        if (db->bord == 0) { // tribord, recherche du pixel à l'indice de ligne minimale dans liste_bis->l, liste des pixels candidats
            coord min = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].x < min.x) {
                    min = list_bis->l[n];
                }
            }
            return min;
        } else { // babord, recherche du pixel à l'indice de ligne maximale dans liste_bis->l, liste des pixels candidats
            coord max = list_bis->l[0];
            for (int n = 0; n < list_bis->compteur; n++) {
                if (list_bis->l[n].x > max.x) {
                    max = list_bis->l[n];
                }
            }
            return max;
        }
    }
}

void suivant(calque* cal, int x_0, int y_0, itineraire* db, int fin, stack* p) {

    //condition de sortie du programme
    if (fin == 8) {
        printf("  - fin du programme\n");
        exit(EXIT_SUCCESS);
    }


    valeur v_actuelle = cal->tab[x_0][y_0];
    // on est sur une couleur bloquante
    if (v_actuelle.l == -2) {
        printf("l'algorithme s'est retrouvé à traiter une couleur bloquante, erreur\n");
        exit(EXIT_FAILURE);
    }
    // on est sur une couleur codante
    if (v_actuelle.l >= 0) {
        int** traite = malloc((cal->h)*sizeof(int*)); // création d'un tableau d'entier rempli de 0 pour les appels recursifs
        for (int i = 0; i < cal->h; i++) {
            traite[i] = calloc((cal->w),sizeof(int));
        }
        lcoord* blc = initialize_lcoord(cal);
        bloc(cal,x_0,y_0,v_actuelle,traite,blc); // blc contient désormais toutes les coordonnées de tous les pixels appartenant au bloc de x_0 y_0
        coord d = recherche_du_pixel_de_depart(cal, blc, db);
        int x = d.x;
        int y = d.y;
        int taille_bloc = blc->compteur;

        //sud
        if (db->direction == 1) { 
            int xs = ((cal->h)+x+1)%(cal->h);
            int pass = 0; // compteur indiquant le nombre de fois que l'on passe sur une couleur passante avant d'atteidre la prochaine couleur codante/bloquante
            
            while (cal->tab[xs][y].l == -1) { // on passe les couleurs passantes, il ne faut pas qu'il y ait une bande sinon la boucle while ne s'arrête pas
                xs = ((cal->h)+xs+1)%(cal->h);
                pass = pass + 1;
            }


            if (cal->tab[xs][y].l == -2) { // on arrive sur une couleur bloquante
                if (pass > 0) {
                    db->direction = (db->direction + 1)%4; // changement de direction
                    suivant (cal,((cal->h)+xs-1)%(cal->h),y,db,0,p);
                } else {
                    if (fin%2 == 0) {
                        db->bord = (db->bord+1)%2;
                    } else {
                        db->direction = (db->direction + 1)%4;
                    }
                    suivant (cal,x,y,db,fin+1,p);
                } // on relance en chnageant bord et direction de façon alterné
            } else { // on arrive sur une couleur codante
                if (pass > 0) {
                    suivant (cal,xs,y,db,0,p);
                } else {
                    action(cal,x_0,y_0,xs,y,p,db,taille_bloc);
                    suivant (cal,xs,y,db,0,p);
                }
            }
        }


         //est
        if (db->direction == 0) { 
            int ye = ((cal->w)+y+1)%(cal->w);
            int pass = 0; // compteur indiquant le nombre de fois que l'on passe sur une couleur passante avant d'atteidre la prochaine couleur codante/bloquante
            
            while (cal->tab[x][ye].l == -1) { // on passe les couleurs passantes
                ye = ((cal->w)+ye+1)%(cal->w); //il ne faut pas qu'il y ait une bande sinon la boucle while ne s'arrête pas
                pass = pass + 1;
            }


            if (cal->tab[x][ye].l == -2) { // on arrive sur une couleur bloquante
                if (pass > 0) { 
                    db->direction = (db->direction + 1)%4;
                    suivant (cal,x,((cal->w)+ye-1)%(cal->w),db,0,p);
                     // on relance à partir du dernier pixel passant en changeant la direction
                } else {
                    if (fin%2 == 0) {
                        db->bord = (db->bord+1)%2;
                    } else {
                        db->direction = (db->direction + 1)%4;
                    }
                    suivant (cal,x,y,db,fin+1,p); // on relance en chnageant bord et direction de façon alterné
                }
            } else { // on arrive sur une couleur codante
                if (pass > 0) {
                    suivant (cal,x,ye,db,0,p); // et on remet fin à 0
                } else {
                    action(cal,x_0,y_0,x,ye,p,db,taille_bloc);
                    suivant (cal,x,ye,db,0,p);
                }
            }
        }


        //nord
        if (db->direction == 3) { 
            int xn = ((cal->h)+x-1)%(cal->h);
            int pass = 0; // compteur indiquant le nombre de fois que l'on passe sur une couleur passante avant d'atteidre la prochaine couleur codante/bloquante
            
            while (cal->tab[xn][y].l == -1) { // on passe les couleurs passantes, l'image étant un tore, la boucle while ne peut tourner indefiniment
                xn = ((cal->h)+xn-1)%(cal->h);
                pass = pass + 1;
            }


            if (cal->tab[xn][y].l == -2) { // on arrive sur une couleur bloquante
                if (pass > 0) { // et on remet fin à 0 // couleur bloquante
                    db->direction = (db->direction + 1)%4;
                    suivant (cal,((cal->h)+xn-1)%(cal->h),y,db,0,p); // on relance à partir du dernier pixel passant en changeant la direction
                } else {
                    if (fin%2 == 0) {
                        db->bord = (db->bord+1)%2;
                    } else {
                        db->direction = (db->direction + 1)%4;
                    }
                    suivant (cal,x,y,db,fin+1,p); // on relance en chnageant bord et direction de façon alterné
                } 
            } else { // on arrive sur une couleur codante
                if (pass > 0) {
                    suivant (cal,xn,y,db,0,p); // et on remet fin à 0
                } else {
                    action(cal,x_0,y_0,xn,y,p,db,taille_bloc);
                    suivant (cal,xn,y,db,0,p);
                }
            }
        }

         //ouest
        else { 
            int yo = ((cal->w)+y-1)%(cal->w);
            int pass = 0; // compteur indiquant le nombre de fois que l'on passe sur une couleur passante avant d'atteidre la prochaine couleur codante/bloquante
            
            while (cal->tab[x][yo].l == -1) { // on passe les couleurs passantes
                yo = ((cal->w)+yo-1)%(cal->w); //il ne faut pas qu'il y ait une bande sinon la boucle while ne s'arrête pas
                pass = pass + 1;
            }


            if (cal->tab[x][yo].l == -2) { // on arrive sur une couleur bloquante
                if (pass > 0) { // et on remet fin à 0 // couleur bloquante
                    db->direction = (db->direction + 1)%4;
                    suivant (cal,x,((cal->w)+yo-1)%(cal->w),db,0,p); // on relance à partir du dernier pixel passant en changeant la direction
                } else {
                    if (fin%2 == 0) {
                        db->bord = (db->bord+1)%2;
                    } else {
                        db->direction = (db->direction + 1)%4;
                    }
                    suivant (cal,x,y,db,fin+1,p); // on relance en chnageant bord et direction de façon alterné
                } 
            } else { // on arrive sur une couleur codante
                if (pass > 0) {
                    suivant (cal,x,yo,db,0,p); // et on remet fin à 0
                } else {
                    action(cal,x_0,y_0,x,yo,p,db,taille_bloc);
                    suivant (cal,x,yo,db,0,p);
                }
            }
        }
    }

    else { // on est sur une couleur passante, il faut continuer dans la direction jusqu'à trouver une couleur bloquante ou codante

        //sud
        if (db->direction == 1) { 
            int xs = ((cal->h)+x_0+1)%(cal->h);
            while (cal->tab[xs][y_0].l == -1) { // on passe les couleurs passantes
                xs = ((cal->h)+xs+1)%(cal->h);
            }
            if (cal->tab[xs][y_0].l == -2) { // on arrive sur une couleur bloquante
                db->direction = (db->direction + 1)%4;
                suivant (cal,((cal->h)+xs-1)%(cal->h),y_0,db,0,p);
            } // on relance à partir du dernier pixel passant en changeant la direction
            else { // on arrive sur une couleur codante
                suivant (cal,xs,y_0,db,0,p); // et on remet fin à 0
            }
        }

        //est
        if (db->direction == 1) { 
            int ye = ((cal->w)+y_0+1)%(cal->w);
            while (cal->tab[x_0][ye].l == -1) { // on passe les couleurs passantes
                ye = ((cal->w)+ye+1)%(cal->w);
            }
            if (cal->tab[x_0][ye].l == -2) { // on arrive sur une couleur bloquante
                db->direction = (db->direction + 1)%4;
                suivant (cal,x_0,((cal->w)+ye-1)%(cal->w),db,0,p);
            } // on relance à partir du dernier pixel passant en changeant la direction
            else { // on arrive sur une couleur codante
                suivant (cal,x_0,ye,db,0,p); // et on remet fin à 0
            }
        }

        //nord
        if (db->direction == 2) { 
            int xn = ((cal->h)+x_0-1)%(cal->h);
            while (cal->tab[xn][y_0].l == -1) { // on passe les couleurs passantes
                xn = ((cal->h)+xn-1)%(cal->h);
            }
            if (cal->tab[xn][y_0].l == -2) { // on arrive sur une couleur bloquante
                db->direction = (db->direction + 1)%4;
                suivant (cal,((cal->h)+xn+1)%(cal->h),y_0,db,0,p);
            } // on relance à partir du dernier pixel passant en changeant la direction
            else { // on arrive sur une couleur codante
                suivant (cal,xn,y_0,db,0,p); // et on remet fin à 0
            }
        }

        //ouest
        else { 
            int yo = ((cal->w)+y_0-1)%(cal->w);
            while (cal->tab[x_0][yo].l == -1) { // on passe les couleurs passantes
                yo = ((cal->w)+yo-1)%(cal->w);
            }
            if (cal->tab[x_0][yo].l == -2) { // on arrive sur une couleur bloquante
                db->direction = (db->direction + 1)%4;
                suivant (cal,x_0,((cal->w)+yo+1)%(cal->w),db,0,p);
            } // on relance à partir du dernier pixel passant en changeant la direction
            else { // on arrive sur une couleur codante
                suivant (cal,x_0,yo,db,0,p); // et on remet fin à 0
            }
        }
    }
}

