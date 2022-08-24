#ifndef GRAF_H
#define GRAF_H

typedef struct innie{
    float x;
    float y;
    struct innie * sljedeci;
}interval;


typedef struct cvor{
    int ind;
    float tezina;
    struct cvor* sljedeci;
} cvor;

typedef struct{
    cvor* u;
    interval * lista_intervala;
} lista_susjeda;

typedef struct{
    int n;
    lista_susjeda* sus;
} graf;


void add_list(cvor** l, int in, float tezina);
graf* create_graph(char lokacija[]);
void printc(cvor* l);
void printg(graf* g);
void add_list_int(interval** l, float li, float de);
void print(interval* l);
void nadji_naj(graf * g);
int prebroj(char lokacija[]);

#endif 