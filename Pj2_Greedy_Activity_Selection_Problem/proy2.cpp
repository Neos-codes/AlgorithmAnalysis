#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;


class room{
public:
  int id;
  bool asigned;
  vector<int> actVec;
  room(){
    asigned = false;
    //actVec = NULL;
    
    
  }
};

class activity{
public:
  room* r;
  int id;
  int start;
  int finish;
  activity(int id){
    this -> id = id;
  }
};

class event{
public:
  bool type;	
  //type 
  //true si es start
  //false si es finish
  int time;	
  int id;	
  activity *a;
  event(bool type, int time, activity *a){
    this -> a = a;
    this -> type = type;
    this -> time = time;
  }		
};

bool ValueCmp(event const & a, event const & b)
{
  //comparador para ordenar eventos segun tiempo mayor o menor y dar prioridad a los eventos de finish
  if(a.time < b.time){
    //Si el tiempo de A es menor que B
    return true;
  }
  else if (a.time == b.time){
    if (a.type && b.type){
      return false;
    }
    else if (a.type && !b.type){
      return false;
    }
    else if (!a.type && b.type){
      return true;
    }
    else{
      return true;
    }
  }
  
  return false;
  
  
  
  
  //return a.time < b.time;
}

vector<room*> calcMin(vector<int> start, vector<int> finish, int tam, int *aux){
  
  stack<room*> freeRooms;
  vector<room*> vector1;
  vector<room*> personas;
  //contains all free rooms
  room *auxRoom;
  for (int i = 0; i < tam; ++i){
    //create all needed rooms
    auxRoom = new room();
    auxRoom -> id = i;
    freeRooms.push(auxRoom);
    vector1.push_back(auxRoom);
  }
  
  vector<event> eventVector;
  activity *auxAct;
  event *auxEvent;
  
  int j=0;
  for (int i = 0; i < tam; ++i){
    
    auxAct = new activity(i);
    
    auxAct->start = start[i];
    auxAct->finish = finish[i];
    
    auxEvent = new event(true,start[i],auxAct);
    auxEvent->id=j;
    j++;
    eventVector.push_back(*auxEvent);
    auxEvent = new event(false,finish[i],auxAct);
    auxEvent->id=j;
    j++;
    eventVector.push_back(*auxEvent);
    
  }

  cout<<"\n------------------------------------\nComenzando, estos son los eventos."<<endl;
  cout<<"Primero mostramos el id del evento y su tiempo\nDespues el tipo, el cual es 1 si es inicio y 0 si es final.\n";
  cout<<"Despues se printea el ID de la actividad asociada\n----------\n\n";
  
  for (int i = 0; i < (2*tam); ++i){
    cout<<"Event "<<eventVector[i].id<<" of time "<<eventVector[i].time<<" and type "<<eventVector[i].type<<" of act id "<<eventVector[i].a->id<<endl;
    //cout<<"Said activity @ "<<eventVector[i].a->start<<" - "<<eventVector[i].a->finish<<endl;
  }
  
  
  sort(eventVector.begin(),eventVector.end(), ValueCmp);
  //Ordena el vector en tiempo nlogn segun el tiempo de los eventos y da prioridad a finish por sobre start
  
  cout<<"\nHemos ordenado los eventos, printeamos los eventos ordenados: "<<endl<<endl;
  
  for (int i = 0; i < (2*tam); ++i){
    //Printeamos todo despues de ordenar eventos
    cout<<"Event "<<eventVector[i].id<<" of time "<<eventVector[i].time<<" and type "<<eventVector[i].type<<" of act id "<<eventVector[i].a->id<<endl;
  }
  
  cout<<"\nVeremos cuantas personas necesitamos: \n\n";

  room *r;
  for (int i = 0; i < (2*tam); ++i){
    if (eventVector[i].type == false){
      //Si el evento es de tipo finish
      freeRooms.push(eventVector[i].a->r); 
      cout<<"Persona de id "<<eventVector[i].a->r->id<<" esta desocupada de actividad "<<eventVector[i].a->id <<" y vuelve al stack."<<endl;
    }
    else{
      r = freeRooms.top();
      freeRooms.pop();
      r->asigned = true;
      
      r->actVec.push_back(eventVector[i].a->id);
      
      eventVector[i].a->r = r;
      
      cout<<"Persona de id "<<eventVector[i].a->r->id<<" realiza actividad "<<eventVector[i].a->id<<" y es popeada."<<endl;
      //cout<<"Voy a pushear "<<eventVector[i].a->id<<" a "<<eventVector[i].a->r->id<<endl;
      
    }
  }

  cout<<"\nAhora vamos a mostrar las personas que realizaron actividades y los ID de estas\n\n";

  int count = 0;
  for (int i = 0; i < tam; ++i){
    r = freeRooms.top();
    freeRooms.pop();
    if (r->asigned){
      cout<<"Persona de ID "<<r->id<<" realizo las actividades ";
      for (int i = 0; i < r->actVec.size(); ++i){
	      cout<<r->actVec[i]<<" ";
      }
      cout<<endl;
      personas.push_back(r);
      count++;
    }
  }
  
  cout<<endl;
  /*for (int i = 0; i < tam; ++i){
    
    cout<<"Room of id "<<vector1[i]->id<<" status: "<<vector1[i]->asigned<<endl;
  }*/

  *aux = count;
  
  return personas;
  
}

void leerArchivo(int *n, vector<int> *start, vector<int> *finish){

  char name[20];
  int temp1, temp2;

  cout << "Ingrese el nombre del archivo con extension. Ej: input1.txt" << endl;
  scanf("%s", name);
  getchar();

  FILE *fp = fopen(name, "r");

  fscanf(fp, "%d", n);
  cout << "\nSe registraron " << *n << " actividades"<<endl;

  for(int i = 0; i < *n; i++){
    fscanf(fp, "%d %d", &temp1, &temp2);
    start -> push_back(temp1);
    finish -> push_back(temp2);
  }

  fclose(fp);
  
}

int main(){
  int n;
  int n_colores;
  char name[20];
  vector<room *> personas;
  vector<int> start, finish;

  leerArchivo(&n, &start, &finish);
  
  
  /* for (int i = 0; i < n; ++i){
    cout << start[i] << " " << finish[i]  <<endl;
    }*/
  
  personas = calcMin(start,finish,n, &n_colores);

  cout<<"\nID de personas que nos ha retornado la funcion: "<<endl;
  for(int i = 0; i < personas.size(); i++)
    cout << personas[i]->id<<" ";

  cout << "\nNecesitamos " << n_colores <<" personas"<< endl;
  
  return 0;
}
