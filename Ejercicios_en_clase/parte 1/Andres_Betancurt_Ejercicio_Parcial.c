/*****************************************************************************/
/*****************************************************************************/
/*            Primer Examen Parcial - Curso de Estructura de Datos           */
/*                    Universidad Tecnológica de Pereira                     */
/*              Presentado por: Andrés Felipe Betancurt Rivera               */
/*                    Presentado a: Hugo Humberto Morales                    */
/*                        Ejercicio n° 2 - 60 Puntos                         */
/*****************************************************************************/
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct nodo{
  int posn;
  int money;
  struct nodo *sig;
  struct nodo *ant;
};

struct ganadores{
  int posn;
  int money;
  struct ganadores *sig;
};

struct prueba {
  char CoS;
  int red;
  int blue;
  struct prueba *sig;
};

struct nodo *creardoblecircular (int i, int n, int money)
{
  struct nodo *p, *q;
  int r;
  p = NULL;
  for (r=i ; r<=n; r++){
    q = (struct nodo *)malloc(sizeof(struct nodo));
    q->posn = r;
    q->money = money;
    if (p == NULL){
      q->sig = q;
      q->ant = q;
    }
    else {
      q->sig = p->sig;
      p->sig = q;
      q->ant = p;
      (q->sig)->ant = q;
    }
    p = q;
  }
  return p;
}

struct prueba *entradas (struct prueba *in,int CoS,int red,int blue)/*cola*/
{
  struct prueba *q;
  q= (struct prueba*)malloc (sizeof(struct nodo));
  q->CoS = CoS;
  q->red = red;
  q->blue = blue;
  if(in == NULL)
  {
  q->sig=q;
  in=q;
  }
  else{
  	q->sig = in->sig;
  	in->sig= q;
  	in=q;
  }
  return in;
}

struct ganadores *listaganadores (struct prueba **in, struct nodo **q)
{
  int i, d;
  struct ganadores *winers, *insertar;
  winers = NULL;
  struct prueba *E;
  /*---------------*/
  struct nodo *p, *r;
  p = (*q);
  r = p->sig;
  /*---------------*/
  while (r->sig != r) {
    E = (*in)->sig;
    if (E->CoS == 67){/*Cara s. horario*/
      for (i = 1; i<=(E->red); i++){
        p = r;
        r = r->sig;
      }
      d = (r->money)+(E->blue);
      if (d%2 == 0){/*si es par*/
        (*q) = r->sig;
        r->sig = (*q)->sig;
        r->ant = p->ant;
        (p->ant)->sig = r;
        ((*q)->sig)->ant = r;
        free (p);
        free (*q);
        r->money = d;
        p = r;
        r = r->sig;
      }
      if (d%2 == 1){/*si es impar*/
        (*q) = r;
        r = r->sig;
        insertar = (struct ganadores *)malloc(sizeof(struct ganadores));
        insertar->posn = (*q)->posn;
        insertar->money = d;
        if (winers == NULL){
          insertar->sig = insertar;
          winers = insertar;
        }
        else {
          insertar->sig = winers->sig;
          winers->sig = insertar;
          winers = insertar;
        }
        p->sig = r;
        r->ant = p;
        free (*q);
      }
    }
    if (E->CoS == 83){/*Sello s. antihorario*/
      for (i = 1; i<=(E->red); i++){
        p = r;
        r = r->ant;
      }
      d = (r->money)+(E->blue);
      if (d%2 == 0){/*si es par*/
        (*q) = r->ant;
        r->sig = p->sig;
        r->ant = (*q)->ant;
        ((*q)->ant)->sig = r;
        (p->sig)->ant = r;
        free (p);
        free (*q);
        p = r->ant;
        r->money = d;
      }
      if (d%2 == 1){/*si es impar*/
        (*q) = r;
        p = r;
        r = r->sig;
        insertar = (struct ganadores *)malloc(sizeof(struct ganadores));
        insertar->posn = (*q)->posn;
        insertar->money = d;
        if (winers == NULL){
          insertar->sig = insertar;
          winers = insertar;
        }
        if (winers != NULL){
          insertar->sig = winers->sig;
          winers->sig = insertar;
          winers = insertar;
        }
        p->sig = r;
        r->ant = p;
        free (*q);
      }
    }
    (*in)->sig = E->sig;
    free (E);
  }
  insertar = (struct ganadores *)malloc(sizeof(struct ganadores));
  insertar->posn = r->posn;
  insertar->money = r->money;
  if (winers == NULL){
    insertar->sig = insertar;
    winers = insertar;
  }
  if (winers != NULL){
    insertar->sig = winers->sig;
    winers->sig = insertar;
    winers = insertar;
  }
  return winers;
}

int main ()
{
  int n, m, red, blue, i;
  char CoS;
  struct nodo *p;
  p = NULL;
  struct ganadores *winers, *imprimir;
  winers = NULL;
  struct prueba *in;
  in = NULL;
  scanf ("%d %d", &n, &m);
  for (i = 1; i<n; i++){
    fflush (stdin);
    scanf ("%c %d %d", &CoS, &red, &blue);
    in = entradas (in, CoS, red, blue);
  }
  p = creardoblecircular (1, n, m);
  winers = listaganadores (&in, &p);
  imprimir = winers->sig;
  while (imprimir != winers){
    printf("%d %d\n", imprimir->posn, imprimir->money);
    imprimir = imprimir->sig;
    free (imprimir);
  }
  imprimir = NULL;
  printf("%d %d\n", winers->posn, winers->money);
  free (winers);
  return 0;
}
