/*Implemente un generador que permita generar aleatoriamente un conjunto de actividades donde
se pueda especificar el total de actividades, n; el tiempo de inicio y término aleatorias dentro de
un rango con parámetros [si, fi]. Note que las actividades generadas deben ser válidas, es decir si < fi
.(0.5 puntos)*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

int main()
{
	int n, s, f;
	cout<<"Ingrese cantidad de actividades, rango del tiempo de inicio y tiempo final: "<<endl;
	cin>>n>>s>>f;
	srand(time(NULL));

	FILE *fp = fopen("randInput.txt", "w");

	fprintf(fp, "%d\n", n);
	int valS, valF;
	for (int i = 0; i < n; ++i){
		valS = s + rand()%(f-s);
		valF = (valS+1) + rand()%(f-valS); 
		fprintf(fp, "%d %d\n", valS, valF);
	}

	fclose(fp);
	cout<<"Guardado en randInput.txt"<<endl;
	return 0;
}