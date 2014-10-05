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

   double A[nmax][nmax]; 
   double b[nmax];
   int p[nmax];

   int i;
   int x,y;
  
   arquivo = openSafe(argv[1]);
   fscanf(arquivo,"%d",&n);
   pegaMatriz(arquivo, n, A);
   pegaVetor(arquivo, n, b);

  
   /*Imprime matriz e vetor  Apenas teste*/
   for(x = 0; x < n; x++) {
   	   for(y = 0; y < n; y ++)
   	   	printf("%f ",A[x][y]);

       printf("\n"); 
   }
   printf("\n");
   for(x = 0; x < n; x++)
      printf("%f\n",b[x]);
   /*--------------------*/
   
   
   /*Acha a decomposicao LU por coluna
   e imprime
   printf("Decomposicao LU coluna:\n");
   lucol(A,n,p);
   for(x = 0; x < n; x++) {
      for(y = 0; y < n; y ++)
         printf("%f ",A[x][y]);
       printf("\n"); 
   }
   /*Agora resolve por coluna e imprime
   printf("Solucao Coluna: \n");
   sscol(n,A,p,b);
   for(x = 0; x < n; x++)
      printf("%f\n",b[x]);

    printf("\n");

   /*Acha a decomposicao LU por linha
   e imprime*/
   printf("Decomposicao LU linha:\n");
   lurow(A,n,p);
   for(x = 0; x < n; x++) {
      for(y = 0; y < n; y ++)
         printf("%f ",A[x][y]);
       printf("\n"); 
   }
   /*Agora resolve por linha e imprime*/
   printf("Solucao linha: \n");
   ssrow(n,A,p,b);
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
   int i,x,y;
   for (i = 0; i < (n * n); i++){
       fscanf(arquivo, "%d %d", &x, &y);
       fscanf(arquivo, "%lf", &a[x][y]);
   }
}
/*-------------------------------------------*/

/* pegaVetor(FILE *arquivo,int n):
Recebe um ponteiro para tipo FILE e devolve
um vetor do tipo   double
*/
void pegaVetor(FILE *arquivo, int n, double intch[]) {
   int i,x;
   for (i = 0; i < n; i++) { 
      fscanf(arquivo,"%d",&x);
      fscanf(arquivo,"%lf",&intch[x]);
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
    maxk = k;
    for (i = k; i < n; i++)/*antes: i = k + 1 agora i = k*/
    {
       if (modulo(a[i][k]) > modulo(a[maxk][k]))
         maxk = i;
    }
    
    if (a[maxk][k] == 0)
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

      for (i = k + 1; i < n; i++)
      { 
         a[i][k] = a[i][k] / a[k][k];
         for (j = k + 1; j < n; j++)
            a[i][j] = a[i][j] - a[i][k] * a[k][j];
      }
      
    }
      
  }

}


int lurow(double a[][nmax], int n, int intch[])
{
  int i, j, k, maxk;
  for (k = 0; k < n; k++)
  {
    /*retorna índice do máximo*/
    maxk = k;
    for (i = k; i < n; i++)
    {
      if (modulo(a[i][k]) > modulo(a[maxk][k]))
	       maxk = i;
    }

    if (a[maxk][k] == 0)
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
      {
	a[i][k] = a[i][k] / a[k][k];
	for (j = k + 1; j < n; j++)
	  a[i][j] = a[i][j] - a[i][k] * a[k][j];
      }
    }
      
  }

}

/*  Programa do livro pagina 100  */
int sscol(int n, double A[][nmax], int p[], double b[]) {
   int k,j,i;
   int aux;
   for (k = 0; k < (n - 1); k++){ /*ate (n-1)*/
      if (p[k] != k) /*troca a linha do vetor b*/
      {
        aux = b[k];
	b[k] = b[p[k]];
	b[p[k]] = aux;
      }
   }
   for (j = 0; j < n - 1; j++) 
      for (i = j + 1; i < n; i++)
	       b[i] = b[i] - A[i][j]*b[j];
   
   for (j = n; j > -1; j--) {
    if (A[j][j] == 0)
      return -1;
   
    b[j] = b[j]/A[j][j];
    for (i = 0;i < j -1; i ++)
      b[i] = b[i] - A[i][j]*b[j];
   }

}

/* Orientado a linha */
int ssrow(int n, double A[][nmax], int p[], double b[]) 
{
  int m, j ,i;
  int aux;
  /*Acerta as mudanças de linha*/
  for (i = 0; i < n; i++)
  {
    if (p[i] != i)
    {
      aux = b[i];
      b[i] = b[p[i]];
      b[p[i]] = aux;
    }
  }
  /*Sistema triangular superior*/
  for (i = n - 1; i > -1; i--)
  {
    for (j = n - 1; j > i; j--)
    {
      b[i] = b[i] - A[i][j]*b[j];
    }
    if (A[i][i] == 0)
      return (-1); /*Singular...*/
    b[i] = b[i]/A[i][i];
  }
  /*Sistema triangular inferior com diagonais = 1*/
  for (j = 1; j < n; j++)
  {
    for (i = 0; i < j; i++)
    {
      b[j] = b[j] - A[i][j] * b[i];
    }
    /*Como a diagonal = 1, não precisa da segunda parte*/
  }
  return (0);
}
