//Codigo compilado y hecho en replit(editor web de texto)

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

template <class T>
class nodo
{
  public:

  T valor;
  nodo<T>** next;
  nodo(int v,int level)
  {
    valor = v;
    next = new nodo<T> *[level+1];
    memset(next, 0, sizeof(nodo*)* (level + 1));
  }
};

template <class T>
class SL
{
  int level_max, level;
  float P;//Probabilidad
  nodo<T> *head;

  public:
  SL(int level_max,float P)
  {
    head=new nodo<T>(-1,level_max);
    level=0;
    this->level_max=level_max;
    this->P=P;
  }

  void print()
  {
    cout<<"\n -----SKIP LIST-----  "<<"\n";
    for (int i=0;i<=level;i++)
    {
      nodo<T> *node = head->next[i];
      cout << "Level " << i << ":  ";
      while (node != NULL)
      {
        cout << node->valor<<" ";
        node = node->next[i];
      }
      cout << "\n";
    }
  }

  float randoom()
  {
  	return (float)rand()/RAND_MAX;
  }
  int Choose_lvl()
  {
    /*int lvl = 0;
    float temp = randoom();
    while (temp < P)
    {
      cout<<"this"<<temp<<endl;
      lvl++;
      temp = randoom();
    }*/
    static bool tmp = true;
    if (tmp)
    {
        srand((unsigned)time(NULL));
        tmp = false;
    }
    int lvl = (int)(log(randoom()) / log(1.-P));
    if(lvl>level_max)
    {
      return level_max;
    }
    return lvl;
  }

  void add(T v)
  {
    nodo<T>* update[level_max + 1];
    nodo<T>* x=head;
    memset(update, 0, sizeof(nodo<T>*)* (level_max + 1));
    for (int i = level;i >= 0;i--)
    {
      while (x->next[i]->valor < v && x->next[i] != NULL)
      {
        x = x->next[i];
      }
      update[i] = x;
    }
    x = x->next[0];

    if(x->valor == v && x!=NULL)x->valor=v;
    else
    {
      int new_level = Choose_lvl();
      if (new_level > level)
      {
        for (int i = level + 1;i < new_level+1;i++)
        {
          update[i] = head;
        }
        level = new_level;
      }

      x = new nodo<T>(v,new_level);

      for (int i = 0;i < new_level+1;i++)
      {
        x->next[i] = update[i]->next[i];
        update[i]->next[i] = x;
      }

    }
  }

  void del(T v)
  {
    nodo<T>* update[level_max + 1];
    nodo<T>* x=head;
    memset(update, 0, sizeof(nodo<T>*)* (level_max + 1));
    for (int i = level;i >= 0;i--)
    {
      while (x->next[i]->valor < v && x->next[i] != NULL)
      {
        x = x->next[i];
      }
      update[i] = x;
    }

    x = x->next[0];

    if(x->valor == v)
    {
      for (int i = 0;i < level+1;i++)
      {
        if (update[i]->next[i] != x)break;
        update[i]->next[i] = x->next[i];
      }
      delete x;
      while (level > 0 && head->next[level] == NULL)
      {
        level--;
      }
    }
  }

  bool find(T v)
  {
    nodo<T>* x=head;
    for (int i = level;i >= 0;i--)
      {
      //if(x->valor == v && x!=NULL){return 1;break;}
      while (x->next[i]->valor < v)
      {
        x = x->next[i];
      }
    }
    x = x->next[0];
    if(x->valor == v && x!=NULL)return 1;
      //cout<<"Se encontro numero."<<endl;
    else return 0;//cout<<"No se encontro numero."<<endl;

  }

};
int main(){
    //1000 datos
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();

    SL <int> A(3,0.5);
    /**/srand(time(NULL));
    for(int i=1; i<=50; i++){
    A.add(1+rand()%100);
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
          << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;       //cout << 1+rand()%100 << endl;

    //SL <int> A(3,0.5);
    /*
    A.add(6);
    A.add(5);
    A.add(7);
    A.add(2);
    A.add(9);
    //cout<<A.Choose_lvl();
    A.print();
    A.del(7);
    A.print();
    if(A.find(7))cout<<"Se encontro numero."<<endl;
    else cout<<"No se encontro numero."<<endl;
    //A.find(7);*/

}
