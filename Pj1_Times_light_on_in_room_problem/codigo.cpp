#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;


int nlogn(vector<pair<int,int>> vec){

	int count=vec.size();

	if(count==0){ 
		return 0;
	}
	//cout<<"--Print Pairs--"<<endl;
	/*
	for (int i = 0; i < count; ++i)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<endl;
	}*/

	
	// Ordenar vector de pares
	sort(vec.begin(),vec.end());     // Sort de C++ es O(nlog(n))


	
	//sort es nlogn
	
	/*
	cout<<"--Sorted Pairs--"<<endl;
	for (int i = 0; i < count; ++i)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<endl;
	}
	*/

	//cout<<"--Start code--"<<endl;

	int max=vec[0].second;
	int flicks=1;
	for (int i = 1; i < count; ++i)               // Esto es O(n)
	{
		if((vec[i-1].second <= vec[i].first) && (vec[i].first >= max)){
			flicks++;
			max = vec[i].second;
			//cout<<"Flick "<<vec[i].first<<" "<<vec[i].second<<endl;
		}
		else if (vec[i].second > max){
			max = vec[i].second;
		}
	}
	return flicks;

	// Como el sort de C++ es O(nlog(n)) y lo que sigue es O(n)
	// Podemos decir que la complejidad nos queda f(n) = O(nlog(n)) + O(n)

	// Con ello se ve trivial que la complejidad del algoritmo es
	//                                  nlog(n)

}


int n2(vector<pair<int,int>> vec){
	int count = vec.size();
	pair<int,int> aux;

	//cout<<"--Print Pairs--"<<endl;
	/*for (int i = 0; i < count; ++i)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<endl;
	}*/

	if(count==0){ 
		return 0;
	}
	


	for (int i = 0; i < count; ++i)          // Selection Sort para los pares
	{
		for (int j = i; j < count; ++j)
		{
			if (vec[j].first <= vec[i].first && vec[j].second < vec[i].second)
			{
				aux = vec[j];
				vec[j] = vec[i];
				vec[i] = aux;
			}
			else if (vec[j].first < vec[i].first)
			{
				aux = vec[j];
				vec[j] = vec[i];
				vec[i] = aux;
			}
		}
	}

	/*cout<<"--Sorted Pairs--"<<endl;
	for (int i = 0; i < count; ++i)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<endl;
		}*/


	//cout<<"--Start code--"<<endl;
	
	int max=vec[0].second;
	int flicks=1;
	for (int i = 1; i < count; ++i)       // Esto es O(n)
	{
		if((vec[i-1].second <= vec[i].first) && (vec[i].first >= max)){
			flicks++;
			max = vec[i].second;
			//cout<<"Flick "<<vec[i].first<<" "<<vec[i].second<<endl;
		}
		else if (vec[i].second > max){
			max = vec[i].second;
		}
	}
	return flicks;

	// Por lo tanto nuestro algoritmo tiene complejidad:
	// f(n) = O(n²) + O(n)
	//
	// => f(n) = O(n²)    // Siendo esta la complejidad del algoritmo

}


int main()
{
	int n;
	vector<pair<int,int>> vec;
	vector<pair<int,int>> vec2;
	int a,b;
	cin >> n;
	
	for (int i = 0; i < n; ++i)       // Creamos 2 vectores con los pares generados
	{
		cin>>a>>b;
		vec.push_back(make_pair(a,b));
		vec2.push_back(make_pair(a,b));
	}

	auto start = chrono::high_resolution_clock::now();

	int flicks = nlogn(vec);       // Llamada de la función nlogn

	auto finish = chrono::high_resolution_clock::now();
	auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();

	cout << "Time: " << d << " ns " << endl;    // Imprimir tiempo de demora
	
	cout<< "Flicks with nlogn " << flicks << endl;   // Imprimir encendido de luces

	start = chrono::high_resolution_clock::now();
	
	flicks = n2(vec2);             // Llamada de la funcion n2
	
	finish = chrono::high_resolution_clock::now();
	d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();

	cout << "Time: " << d << " ns " << endl;  // Imprimir tiempo de ejecucion
	
	cout << "Flicks with n2 " << flicks << " ns " << endl;   // Imprimir encendido de luces
	
	return 0;
}
