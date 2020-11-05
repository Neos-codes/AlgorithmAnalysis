#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

void valKnap01(int n, int capacity, vector<pair<int,int>> objects){

	//cout<<"Starting...\n\nSorting objects\n\n";
	//sort(objects.begin(), objects.end());
	//No hace falta sortear los objetos

	//cout<<"Sorted objects: \n";

	int totalValue=0;
	for (int i = 0; i < n; ++i){
		//cout<<"Weight "<<objects[i].first<<" | Val "<<objects[i].second<<" "<<"\n";
		totalValue += objects[i].second; 
	}
	//cout<<"Total value of objects: "<<totalValue<<"\n";

	//Create table that will hold solutions to subproblems
	int table[n+1][totalValue+1];

	/*for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= totalValue; ++j){
			table[i][j] = INT_MAX;
		}	
	}*/

	for (int i = 0; i <= totalValue; ++i){
		table[0][i] = INT_MAX;	
	}
	for (int i = 0; i <= n; ++i){
		table[i][0] = INT_MAX;	
	}

	/**/
	int peso=0;
	int valor=0;
	int valGen=0;
	int pesoGen=0;
	int valAux;
	int pesoAux;
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= totalValue; ++j){
			peso = objects[i-1].first;
			valor = objects[i-1].second;
			//cout<<"Peso "<<peso<<" | Valor "<<valor<<" | i = "<<i<<" | j = "<<j<<"\n";
			if (j < valor){
				table[i][j]=table[i-1][j];
				//cout<<"SE COPIA ANT"<<endl;
			}
			else{
				if (table[i-1][j-valor] != INT_MAX){
					pesoGen = table[i-1][j-valor];
					valGen = j-valor;
					//cout<<"1 ARRIBA EN "<<j-valor<<" HAY PESO "<<pesoGen<<" VALOR "<<valGen<<endl;
				}
				else{
					pesoGen = 0;
					valGen = 0;
					//cout<<"2 ARRIBA EN "<<j-valor<<" HAY PESO "<<pesoGen<<" VALOR "<<valGen<<endl;
				}
				valAux = valGen + valor;
				pesoAux = pesoGen + peso;
				//cout<<"valAux "<<valAux<<" | pesoAux "<<pesoAux<<endl;
				if (pesoAux > capacity){
					//cout<<"Capacidad sobrepasada"<<endl;
					//deberia ser el valor anterior
					//table[i][j] = INT_MAX;
					table[i][j] = table[i-1][j];
					continue;
				}
				if ((valAux == j) /*&& table[i-1][j] != INT_MAX*/){
					if (pesoAux <= table[i-1][j]){
					//estabamos comparando valor con peso
					//if (valAux <= table[i-1][j]){
						table[i][j] = pesoAux;
					}
					else{
						table[i][j] = table[i-1][j];
					}
				}
				else{
					//deberia ser el valor anterior
					//table[i][j] = INT_MAX;
					table[i][j] = table[i-1][j];
				}
			}
		}
	}




	cout<<"\n";
	/*for (int i = 0; i <= totalValue; ++i)
	{
		cout<<i<<" ";
	}
	cout<<"\n";*/
	/*for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= totalValue; ++j){
			if (table[i][j] == INT_MAX){
				cout<<"- ";
			}
			else{
				cout<<table[i][j]<<" ";
			}
			
		}
		cout<<"\n";
		}*/


	int search = 0;
	while(1){
		if (table[n][totalValue-search] != INT_MAX){
			//se encontro el valor en pos tanto
			//cout<<"MAX ES "<<table[n][totalValue-search]<<" en pos "<<totalValue-search<<endl;
			break;
		}
		else{
			search++;
		}
	}

	int result[n];
	int searchPos = totalValue - search;
	//search for the final result
	for (int i = n; i > 0; --i){
		if (table[i][searchPos] == table[i-1][searchPos]){
			result[i-1]=0;
			continue;
		}
		else{
			//cout<<table[i][searchPos];
			//cout<<" weight "<<objects[i-1].first<<" | value "<<objects[i-1].second<<endl;
			searchPos = searchPos - objects[i-1].second;
			result[i-1]=1;
		}
	}


	cout<<n<<" "<<capacity<<" ";
	for (int i = 0; i < n; ++i)
	{
		cout<<result[i]<<" ";
	}
	cout<<endl;

}

void leerArchivo(int *n, int *c, vector<pair<int,int>> *objects){

  char name[20];
  int temp1, temp2;
  pair<int,int> temp;

  // Leer nombre archivo
  cout << "Ingrese el nombre del archivo para input con extension. Ej: input1.txt\n (Max 20 char)" << endl;
  scanf("%s", name);
  getchar();

  FILE *fp = fopen(name, "r");

  // Leer cantidad de objetos y capacidad de mochila
  fscanf(fp, "%d %d", n, c);
  //cout << "n: " << *n << " c: " << *c << endl;

  // Leer pesos y valores
  for(int i = 0; i < *n; i++){
    fscanf(fp, "%d %d", &temp1, &temp2);
    temp = make_pair(temp1, temp2);
    objects ->push_back(temp);
  }

}



int main(){
	//Pide la cantida de objetos, seguido de la capacidad de la mochila
	//Luego pide cada objeto sucesivamente tomando su 
	int n;
	int capacity;
	vector<pair<int,int>> objects;

	leerArchivo(&n, &capacity, &objects);

	/*for (int i = 0; i < n; ++i){
	  cout<<"Weight "<<objects[i].first<<" | Val "<<objects[i].second<<" "<<"\n";
	}*/


	valKnap01(n,capacity, objects);
	
	return 0;
}
