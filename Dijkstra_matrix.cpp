#include<iostream>
#include <fstream>
#include<climits>
#include <chrono>

#include "generate.cpp"


using namespace std;

const int dimension = 700;
int TAB[dimension][dimension];

int tab(int i, int j)
{
    int nb = 1+(j-i-1)*2;
    if (i==j) return 0;
    else return ((nb>0)?nb:-(nb+2));
}

int miniDist(int distance[], bool Tset[], int dimension) // finding minimum distance
{
    int minimum=INT_MAX,ind;
              
    for(int k=0;k<dimension;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            ind=k;
        }
    }
    return ind;
}

void DijkstraAlgo(int ** tab, int dimension, int src) // adjacency matrix 
{
    int distance[dimension]; // // array to calculate the minimum distance for each node                             
    bool Tset[dimension];// boolean array to mark visited and unvisited for each node
     
    for(int k = 0; k<dimension; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<dimension; k++)
    {
        int m=miniDist(distance,Tset, dimension);
        Tset[m]=true;
        for(int k = 0; k<dimension; k++)
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && tab[m][k] && distance[m]!=INT_MAX && distance[m]+tab[m][k]<distance[k])
                distance[k]=distance[m]+tab[m][k];
        }
    }
}

void Dijkstra(int dimension, double* temps1, double* temps2)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int **tab = (int**)malloc(dimension*sizeof(char*));
    for (int i=0; i<dimension; i++)
    {
        int *ligne = (int*)malloc(dimension*sizeof(int));
        tab[i] = ligne;
    }

    // Creation of the matrix
    for (int i=0; i<dimension; i++) for (int j=i; j<dimension; j++)
    {
        if (i==j) tab[i][j]=0;
        else
        {
            tab[i][j] = rand()%10;
            tab[j][i] = tab[i][j];
        }
    }

    std::chrono::steady_clock::time_point begin_dij = std::chrono::steady_clock::now();
    DijkstraAlgo(tab,dimension,0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    *temps1 = (double)(std::chrono::duration_cast<std::chrono::microseconds> (end - begin_dij).count()) / 1000000;
    *temps2 = (double)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000;

    // Libération des mallocs
    for (int i=0; i<dimension; i++) free(tab[i]);
    free(tab);
}

int main(int argc, char *argv[])
{
    int dimension;
    if (argc <= 1)
    {
        printf("Enter a dimension : ");
        scanf ("%d",&dimension);
    }
    else dimension = stoi(argv[1]);

    std::cout << "Chosen dimension : " << dimension << std::endl;

    double temps1, temps2;
    Dijkstra(dimension, &temps1, &temps2);

    std::cout << "Dijkstra Execution Time = " << temps1 << " [sec]" << std::endl;
    std::cout << "Total Execution Time = " << temps2 << " [sec]" << std::endl;

    return 0;
}