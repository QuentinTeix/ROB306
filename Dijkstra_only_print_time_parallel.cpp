#include<iostream>
#include <fstream>
#include<climits>
#include <chrono>
#include <omp.h>

#include "generate.cpp"


using namespace std;

const int dimension = 700;
int TAB[dimension][dimension];


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
# pragma omp parallel
# pragma omp for nowait
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

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    int dimension;
    printf("Enter a dimension : ");
    scanf ("%d",&dimension);

    int **tab = (int**)malloc(dimension*sizeof(char*));
    for (int i=0; i<dimension; i++)
    {
        int *ligne = (int*)malloc(dimension*sizeof(int));
        tab[i] = ligne;
    }


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

    std::cout << "Dijkstra Execution Time = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin_dij).count() << "[micro_sec]" << std::endl;
    std::cout << "Dijkstra Execution Time = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin_dij).count() << "[sec]" << std::endl;
    std::cout << "Total Execution Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[micro_sec]" << std::endl;
    std::cout << "Total Execution Time = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "[sec]" << std::endl;

    // Libération des mallocs
    for (int i=0; i<dimension; i++) free(tab[i]);
    free(tab);
    
    return 0;
}