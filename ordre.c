#include <stdlib.h>
#include <stdio.h>
#include "ordre.h"
#include "stack.h"
#include "image.h"
#include "lecture.h"

void empile(stack* p,int taille_ancien_bloc) {
    push(p,taille_ancien_bloc);
}

void depile(stack* p) {
    int poub=pop(p);
}

void plus(stack* p) {
    int a = pop(p);
    int b = pop(p);
    push(p,b+a);
}

void moins(stack* p) {
    int a = pop(p);
    int b = pop(p);
    push(p,b-a);
}

void fois(stack* p) {
    int a = pop(p);
    int b = pop(p);
    push(p,b*a);
}

void divise(stack* p) {
    int a = pop(p);
    int b = pop(p);
    if (a==0){
        printf("attention division par 0 dans divise");
        exit(EXIT_FAILURE);
    }
    push(p,b/a);
}

void reste(stack* p) {
    int a = pop(p);
    int b = pop(p);
    if (a==0){
        printf("attention division par 0 dans reste");
        exit(EXIT_FAILURE);
    }
    push(p,b%a);
}

void non(stack* p) {
    if (pop(p)==0) {
        push(p,1);
    } else {
        push(p,0);
    }
}

void plus_grand(stack* p) {
    int a = pop(p);
    int b = pop(p);
    if (b>=a) {
        push(p,1);
    } else {
        push(p,0);
    }
}

void direction(stack* p, itineraire* db) {
    int a = pop(p);
    db->direction = (db->direction + a)%4;
}

void bord(stack* p, itineraire* db) {
    int a = pop(p);
    db->bord = (db->bord + a)%2;
}

void duplique(stack* p) {
    int a = pop(p);
    push(p,a);
    push(p,a);
}

void tourne(stack* p) {
    int n = pop(p);
    int d = pop(p);
    stack* pbis = initialize_stack(); //utilisation d'une pile intermédiare
    for (int i = 0; i < n; i++) {
        int y=pop(p);
        for (int j = 0; j < d-1; j++) {
            int x=pop(p);
            push(pbis,x);
        }
        push(p,y);
        for (int k = 0; k < d-1; k++) {
            int z=pop(pbis);
            push(p,z);
        }
    }
} // attention vérifier si le 2e élément de la pile est plus grand que 1

void in_nombre(stack* p) {
    int a;
    printf("Veuillez rentrer un entier : ");
    scanf("%d",&a);
    push(p,a);
}

void in_char(stack* p) {
    char a;
    printf("Veuillez rentrer un caractère : ");
    scanf("%c",&a);
    push(p,a);
}

void out_nombre(stack* p) {
    int a = pop(p);
    printf("%d",a);
}

void out_char(stack* p) {
    int a = pop(p);
    printf("%c",a);
}

int test_action(stack* p, int n) {
    return (p->top+1 >= n);
}
/*
    int m = 1;
    stack* pile_de_test = initialize_stack();
    for (int i = 0; i < n; i++) { // on test si on peut dépiler n fois la pile
        if is_empty(p) {
            m = 0;
        } else {
            push(pile_de_test,pop(p));
        }
    }
    for (int i = 0; i < n; i++) { // on re-rempli la pile
        if is_empty(pile_de_test) {} 
        else {
        push(p,pop(pile_de_test));
        }
    }
    return m;
}
*/

void action(calque* cal,int x0, int y0, int x1, int y1, stack* p, itineraire* db, int tb) {
    valeur v_depart = cal->tab[x0][y0];
    valeur v_arrive = cal->tab[x1][y1];
    int diff_c = (6+v_arrive.c-v_depart.c)%6;
    int diff_l = (3+v_arrive.l-v_depart.l)%3;
    if (diff_l == 0) {
        if (diff_c == 0) {}
        if (diff_c == 1) {
            if (test_action(p,2)) {
                plus(p);
            } else {}
        }
        if (diff_c == 2) {
            if (test_action(p,2)) {
                divise(p);
            } else {}
        }
        if (diff_c == 3) {
            if (test_action(p,2)) {
                plus_grand(p);
            } else {}
        }
        if (diff_c == 4) {
            if (test_action(p,1)) {
                duplique(p);
            } else {}
        }
        else {
            in_char(p);
        }
    }
    if (diff_l == 1) {
        if (diff_c == 0) {
            empile(p,tb);
        }
        if (diff_c == 1) {
            if (test_action(p,2)) {
                moins(p);
            } else {}
        }
        if (diff_c == 2) {
            if (test_action(p,2)) {
                reste(p);
            } else {}
        }
        if (diff_c == 3) {
            if (test_action(p,1)) {
                direction(p,db);
            } else {}
        }
        if (diff_c == 4) {
            if (test_action(p,2)) {
                int a = pop(p);
                int b = pop(p);
                if (test_action(p,b)) {
                    push(p,b);
                    push(p,a);
                    tourne(p);
                } else {
                    push(p,b);
                    push(p,a);
                }
            } else {}
        }
        else {
            if (test_action(p,1)) {
                out_nombre(p);
            } else {}
        }
    }
    else {
        if (diff_c == 0) {
            if (test_action(p,1)) {
                depile(p);
            } else {}
        }
        if (diff_c == 1) {
            if (test_action(p,2)) {
                fois(p);
            } else {}
        }
        if (diff_c == 2) {
            if (test_action(p,1)) {
                non(p);
            } else {}
        }
        if (diff_c == 3) {
            if (test_action(p,1)) {
                bord(p,db);
            } else {}
        }
        if (diff_c == 4) {
            in_nombre(p);
        }
        else {
            if (test_action(p,1)) {
                out_char(p);
            } else {}
        }
    }
}