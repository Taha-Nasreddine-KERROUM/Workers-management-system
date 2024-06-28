#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MADMAX 100

typedef struct {
    int h;
    int s;
    int m;
} tim;

typedef struct {
    char *name;
    tim ariv;
    tim leav;
    tim work;
} stf;


int tosec ( stf e ) {
    int arv = e.ariv.h * 3600 + e.ariv.m * 60 + e.ariv.s;
    int out = e.leav.h * 3600 + e.leav.m * 60 + e.leav.s;
    return out - arv;
}

void calc ( stf *mpl, int n ){
    for ( stf *p = mpl; p < mpl + n; ++p ) {
        int t = tosec(*p);
        p -> work.h = t / 3600;
        t %= 3600;
        p -> work.m = t / 60;
        t %= 60;
        p -> work.s = t;
    }
}

void desplay ( stf *mpl, int n ) {
    for ( stf *p = mpl; p < mpl + n; ++p ) {
        printf(" employee %ld %s:\n", p - mpl + 1, p->name);
        printf(" arrival time: %02dh:%02dm:%02ds\n", p->ariv.h, p->ariv.m, p->ariv.s);
        printf(" checkingout time: %02dh:%02dm:%02ds\n", p->leav.h, p->leav.m, p->leav.s);
        printf(" working time: %02dh:%02dm:%02ds\n", p->work.h, p->work.m, p->work.s);
    }
}

void read ( stf *mpl, int n ){
    for ( stf *p = mpl; p < mpl + n; ++p ) {
        p->name = (char *)malloc(MADMAX);
        if (p->name == NULL) {
            puts(" one of the employees' name memory allocation failed");
            exit(EXIT_FAILURE);
        }
        
        printf(" employee %d's name: ", p - mpl + 1);
        scanf("%s", p->name);
        p->name = ( char* ) realloc ( p->name, strlen(p->name) );
        if ( p->name == NULL ) {
            puts(" one of the employees name's memory re-allocation failed");
            exit(EXIT_FAILURE);
        }
        
        printf(" %s's arrival time: \n", p->name);
        printf("\thour: ");
        scanf("%d", &p->ariv.h);
        printf("\tminute: ");
        scanf("%d", &p->ariv.m);
        printf("\tsecond: ");
        scanf("%d", &p->ariv.s);
        
        printf(" %s's checkingout time: \n", p->name);
        printf("\thour: ");
        scanf("%d", &p->leav.h);
        printf("\tminute: ");
        scanf("%d", &p->leav.m);
        printf("\tsecond: ");
        scanf("%d", &p->leav.s);
    }
}

int main()
{
    stf *emple;
    int n;
    printf(" yo, how many employees we're dealing with: ");
    scanf("%d%*c", &n);
    emple = ( stf* ) malloc ( n * sizeof(stf) );
    if ( emple == NULL ) {
        puts(" employees's memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    read(emple, n);
    calc(emple, n);
    desplay(emple, n);
    
    for (stf *p = emple; p < emple + n; ++p) {
        free(p->name);
        p->name = NULL;
    }
    free(emple);
    emple = NULL;
    return 0;
}
