#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define nmax 10
/*#---Funcoes---#*/
/*-------------------------------------------*/
FILE *openSafe(char arquivo[]);
double modulo(double x);
void pegaMatriz(FILE *arquivo, int n, double a[][nmax]);
void pegaVetor(FILE *arquivo,int n, double intch[nmax]);
void multiploLinha(int n,int l , int x, int m,    double A[][nmax]);
void trocaLinha(int n , int x, int m,   double a[][nmax]);
int lucol(double a[][nmax], int n, int intch[]);
int lurow(double a[][nmax], int n, int intch[]);
/*-------------------------------------------*/
/*
Como usar: digite o nome do arquivo que tenha 
a matriz com vetor B assim como foi explicado
na descrição do EP1.....(continua)
*/
int main(int argc, char** argv) {
  
   FILE *arquivo;
   int n;

   double A[nmax][nmax]; 
   double b[nmax];


   int i;
   int x,y;
  
   arquivo = openSafe(argv[1]);
   fscanf(arquivo,"%d",&n);
   pegaMatriz(arquivo, n, A);
   pegaVetor(arquivo, n, b);

  
   /*Imprime matriz Apenas teste*/
   for(x = 0; x < n; x++) {
   	   for(y = 0; y < n; y ++)
   	   	printf("%f ",A[x][y]);

       printf("\n"); 
   }
   
   printf("\n");
   for(x = 0; x < n; x++)
      printf("%f\n",b[x]);
   
   fclose(arquivo);
   return 0;
}
/*Corpo das funcoes*/

/* openSafe(char arquivo[])
Recebe um ponteiro para FILE e devolve um outro
se não houver arquivo nulo na entrada
*/
FILE *openSafe(char arquivo[]) {
    FILE * f;
    f = fopen(arquivo,"r");  
    if (f == NULL) {
   	  printf("Falha para abrir arquivo\n");
          exit(EXIT_FAILURE); 
  }
   return f;    
}
/*-------------------------------------------*/

/* pegaMatriz(FILE *arquivo, int n):
Preenche a matriz
*/
void pegaMatriz(FILE *arquivo, int n, double a[][nmax]) {
   int i, j;
   for (i = 0; i < n; i++){
     for (j=0; j < n; j++)
       fscanf(arquivo, "%lf", &a[i][j]);
   }
}
/*-------------------------------------------*/

/* pegaVetor(FILE *arquivo,int n):
Recebe um ponteiro para tipo FILE e devolve
um vetor do tipo   double
*/
void pegaVetor(FILE *arquivo, int n, double intch[]) {
   int i;
   for (i = 0; i < n; i++) { 
      fscanf(arquivo,"%lf",&intch[i]);
   }
}
/*-------------------------------------------*/
/* 
multiploLinha
Recebe ponteiro para uma matriz de tamanho n*n
e soma l * linha x na linha m 
*/

void multiploLinha(int n,int l, int x,int m, double A[][nmax]) {
   int w;
   for (w = 0; w < n; w++) {
      A[m][w] = A[m][w] + (l * (A[x][w])); 

   }
}
/* mod */
double modulo(double x) {
  if(x < 0)
    return (-1 * x);
  else
    return x;
}

void trocaLinha(int n, int x, int m, double a[][nmax]) {
   double aux;
   int i;
   for (i = 0; i < n; i++) {
     aux  = a[x][i] ;
     a[x][i] = a[m][i];
     a[m][i] = aux;
   }
}


int lucol(double a[][nmax], int n, int intch[])
{
  int i, j, k, maxk;
  for (k = 0; k < n; k++)
  {
    /*retorna índice do máximo*/
    maxk = 0;
    for (i = k + 1; i < n; i++)
       if (modulo(a[i][k]) > a[maxk][k])
         maxk = i;
    

    if (a[k][maxk] = 0)
      return -1; /*É singular*/ 
    else
    {
      intch[k] = maxk; /*Guardamos a mudança de row*/

      if (maxk != k)
      {
         //trocar a linha a[k][] por a[maxk][]
         trocaLinha(n, k, maxk, a); 
      }

      if (a[k][k] == 0)
         return (-1);

      for (i = k + 1; i < n; i++) /*Calcula os multiplicadores*/
         a[i][k] = a[i][k] / a[k][k];

      for (j = k + 1; i < n; i++) /*Subtrai a linha k a[i][k] vezes da linha i*/
         for (i = k + 1; j < n; j++)
            a[i][j] = a[i][j] - a[i][k] * a[k][j];
    }
      
  }

}


int lurow(double a[][nmax], int n, int intch[])
{
  int i, j, k, maxk;
  for (k = 0; k < n; k++)
  {
    /*retorna índice do máximo*/
    maxk = 0;
    for (i = k + 1; i < n; i++)
       if (modulo(a[i][k]) > a[maxk][k])
	       maxk = i;
    

    if (a[k][maxk] = 0)
      return -1; /*É singular*/ 
    else
    {
      intch[k] = maxk; /*Guardamos a mudança de row*/

      if (maxk != k)
      {
	   //trocar a linha a[k][] por a[maxk][]
    	   trocaLinha(n, k, maxk, a); 
      }

      if (a[k][k] == 0)
	       return (-1);

      for (i = k + 1; i < n; i++) /*Calcula os multiplicadores*/
	       a[i][k] = a[i][k] / a[k][k];

      for (i = k + 1; i < n; i++) /*Subtrai a linha k a[i][k] vezes da linha i*/
	       for (j = k + 1; j < n; j++)
	          a[i][j] = a[i][j] - a[i][k] * a[k][j];
    }
      
  }

}

