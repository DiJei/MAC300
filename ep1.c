#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define nmax 10
/*#---Funcoes---#*/
/*-------------------------------------------*/
FILE *openSafe(char arquivo[]);
double modulo(double x);
double **pegaMatriz(FILE *arquivo, int n);
double *pegaVetor(FILE *arquivo,int n);
void multiploLinha(int n,int l , int x, int m,   double **A);
void trocaLinha(int n , int x, int m,   double **A);
int lucol(double a[][nmax], int n, int intch[]);
int lurow(double a[][nmax], int n, int intch[]);
int sscol(int n, double A[][nmax], int p[], double b[]);
int ssrow(int n, double A[][nmax], int p[], double b[]);
/*-------------------------------------------*/
/*
Como usar: digite o nome do arquivo que tenha 
a matriz com vetor B assim como foi explicado
na descrição do EP1.....(continua)
*/
int main(int argc, char** argv) {
  
   FILE *arquivo;
   int n;

   double **A; 
   double *b;


   int i;
   int x,y;
  
   arquivo = openSafe(argv[1]);
   fscanf(arquivo,"%d",&n);
   A = pegaMatriz(arquivo, n);
   b = pegaVetor(arquivo, n);

  
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
Recebe um ponteiro para FILE e devolve um ponteiro
para uma matriz nxn tipo double
*/
double **pegaMatriz(FILE *arquivo, int n) {
   int x,y;
   double **A;
   A = malloc( n * sizeof (  double *));
   int i;
   for (i = 0; i < n; i++)
      A[i] = malloc( n * sizeof (  double));
   
   for (i = 0; i < (n * n); i++){
      fscanf(arquivo,"%d %d",&x,&y);
      fscanf(arquivo,"%f",&A[x][y]);
   }
   return A;
}
/*-------------------------------------------*/

/* pegaVetor(FILE *arquivo,int n):
Recebe um ponteiro para tipo FILE e devolve
um vetor do tipo   double
*/
double *pegaVetor(FILE *arquivo,int n) {
   double *b; 
   int x,i;
   b = malloc( n * sizeof (  double));
   for (i = 0; i < n; i++) { 
      fscanf(arquivo,"%d",&x);
       fscanf(arquivo,"%f",&b[x]);
   }
   return b;
}
/*-------------------------------------------*/
/* multiploLinha(int n,   double **A):
Recebe ponteiro para uma matriz de tamanho n*n
e soma l * linha x na linha m 
*/

void multiploLinha(int n,int l, int x,int m, double A[nmax][]) {
   int w
   for (int w = 0; w < n; w++) {
      &A[m][w] = &A[m][w] + (l * (&A[x][w])); 

   }
}
/* mod */
double modulo(double x) {
  if(x < 0)
    return (-1 * x);
  else
    return x;
}

void trocaLinha(int n, int x, int m, double a[nmax][]) {
   float aux;
   for (i = 0; i < n; i++) {
      aux  = A[x][i] 
      A[x][i] = A[m][i]
      A[m][i] = aux
   }
}


int lucol(double a[][nmax], int n, int intch[])
{
   int i, j, k;
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
   int i, j, k;
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

/*  Programa do livro pagina 100  */
int sscol(int n, double A[][nmax], int p[], double b[]) {
   int m,j,i;
   for (k = 0; k < n - 1; k++){
      m = p[k] 
      trocaLinha(1,b[k],b[m],A);
   }
   for (j = 0; j < n - 1; j++) 
      for (i = j + 1; i < n; i++)
         b[i] = b[i] - A[i][j]*b[j]  
   
   for (j = n; j > 1; j--) {
    if (A[j][j] == 0)
      return -1;
   
    b[j] = b[j]/A[j][j]
    for (i = 0;i < j -1;; i ++)
      b[i] = b[i] - A[i][j]*b[j]
   }

}

/* Na não sei se ta certo... */
int ssrow(int n, double A[][nmax], int p[], double b[]) {


}
