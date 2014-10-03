#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define nmax 10
int lurow(double a[][nmax], int n, int intch[], int flag)
{
  int i, j, k, maxk;
  for (k = 0; k < n; k++)
  {
    /*retorna índice do máximo*/
    maxk = 0;
    for (i = k + 1; i < n; i++)
    {
      if (a[i][k] > a[maxk][k])
	maxk = i;
    }

    if (a[k][maxk] = 0)
      return -1; /*É singular*/ 
    else
    {
      intch[k] = maxk; /*Guardamos a mudança de row*/

      if (maxk != k)
      {
	//trocar a linha a[k][] por a[maxk][] funçao ja feita
	printf("não trava na hora de compilar");
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
int main()
{
  printf("benis\n");
  return(0);
}
