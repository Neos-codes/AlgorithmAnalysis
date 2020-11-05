#include <iostream>
#include <vector>

using namespace std;

void knapsack01(int n, int capacity, vector<int> weights, vector<int> values){
	int table[n+1][capacity+1];

	//fill first row of the table with zeroes
	for (int j = 0; j <= capacity; ++j){
		table[0][j]=0;
	}

	for (int i = 1; i <= n; ++i){
		for (int j = 0; j <= capacity; ++j){
			//cout<<"1";
			if (weights[i-1] > j){
				//item does not fit
				table[i][j] = table[i-1][j];
				//take previous optimal solution
			}
			else{
				//item fits
				if ((values[i-1] + table[i-1][j-weights[i-1]]) > table[i-1][j]){
					//take object because it improves the prev solution
					table[i][j] = values[i-1] + table[i-1][j-weights[i-1]];
				}
				else{
					//object does not improve solution
					table[i][j] = table[i-1][j];
				}
			}
		}
	}
	//now that the optimal solution has been foind
	//decode which items were picked


	//cout<<"\n";
	/*for (int i = 0; i <= capacity; ++i)
	{
		cout<<i<<" ";
	}
	cout<<"\n";*/
	//prints table
	/*for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= capacity; ++j){
			cout<<table[i][j]<<" ";
		}
		cout<<endl;
	}*/


	int result[n];
	int j = capacity;
	for (int i = n; i > 0; --i){
		if (table[i][j] > table[i-1][j]){
			//cout<<table[i][j];
			//cout<<"YES weight "<<weights[i-1]<<" | value "<<values[i-1]<<endl;
			j = j-weights[i-1];
			result[i-1]=1;
		}
		else{
			//cout<<"NO weight "<<weights[i-1]<<" | value "<<values[i-1]<<endl;
			result[i-1]=0;
		}
	}

	cout<<n<<" "<<capacity<<" ";
	for (int i = 0; i < n; ++i)
	{
		cout<<result[i]<<" ";
	}
	cout<<endl;

}

void leerArchivo(int *n, int *c, vector<int> *weight, vector<int> *values){

  char name[20];
  int temp1, temp2;

  // Leer nombre archivo
  cout << "Ingrese el nombre del archivo con extension. Ej: input1.txt" << endl;
  scanf("%s", name);
  getchar();
  
  FILE *fp = fopen(name, "r");

  //Leer cantidad de objetos y capacidad de mochila
  fscanf(fp, "%d %d", n, c);
  //cout << "n: " << *n << " c: " << *c << endl;

  // Leer pesos y valores
  for(int i = 0; i < *n; i++){
    fscanf(fp, "%d %d", &temp1, &temp2);
    weight -> push_back(temp1);
    values -> push_back(temp2);
  }
  


}

int main(){
	
	int n;
	int capacity;
	vector<int> weights;
	vector<int> values;

	leerArchivo(&n, &capacity, &weights, &values);

	// Imprimir vectores   SANITY CHECK
	/*
	for (int i = 0; i < n; ++i){
	  cout<< weights.at(i) <<" "<<values.at(i) << " " << "\n";
	  }*/

	//cout<<"\nStarting\n";
	knapsack01(n,capacity, weights, values);
	
	return 0;
}
