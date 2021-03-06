#include <iostream>
#include <fstream>
#include <climits>
#include <chrono>
#include <omp.h>
#include "generate.cpp"

using namespace std;

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

int DijkstraAlgo(int dimension, int src) // adjacency matrix 
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

        #pragma omp parallel for
        for(int k = 0; k<dimension; k++)
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && tab(m,k) && distance[m]!=INT_MAX && distance[m]+tab(m,k)<distance[k])
                distance[k]=distance[m]+tab(m,k);
        }
    }
    return distance[dimension-1];
}

int Dijkstra(int dimension, double* temps1)
{
    std::chrono::steady_clock::time_point begin_dij = std::chrono::steady_clock::now();
    int dist = DijkstraAlgo(dimension,0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    *temps1 = (double)(std::chrono::duration_cast<std::chrono::microseconds> (end - begin_dij).count()) / 1000000;
    return dist;
}


int main(int argc, char *argv[])
{
    //////////// CHOIX DIMENSION //////////////
    int dimension;
    if (argc <= 1)
    {
        printf("Enter a dimension : ");
        scanf ("%d",&dimension);
    }
    else dimension = stoi(argv[1]);
    std::cout << "Chosen dimension : " << dimension << std::endl;

    //////////// APPEL DIJKSTRA /////////////////
    double temps1;
    int dist = Dijkstra(dimension, &temps1);
    std::cout << "Dijkstra Execution Time = " << temps1 << " [sec]" << std::endl;
    std::cout << "Last Distance (Expectation,Result) = (" << dimension - 1 << "," << dist << ")" << std::endl;   // V??rification du code --> R??sultat = Dimension-1

    return 0;
}