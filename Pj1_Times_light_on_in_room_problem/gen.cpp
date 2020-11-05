#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <time.h>

using namespace std;



int main(){
  
	int n;
	vector<pair<int,int>> vec;
	int a,b;
	cin >> n;

	srand(time(NULL));
	for (int i = 0; i < n; ++i){
		a = (rand()%10000)+1;
		b = a+rand()%(100)+1;
		vec.push_back(make_pair(a,b));
	}
	
	cout<<n<<endl;
	for (int i = 0; i < n; ++i){
		cout<<vec[i].first<<" "<<vec[i].second<<endl;
	}

	return 0;
}

