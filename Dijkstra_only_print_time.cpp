#include<iostream>
#include <fstream>
#include<climits>
#include <chrono>

#include "generate.cpp"


using namespace std;

const int DIMENSION = 719;
int TAB[DIMENSION][DIMENSION];


int miniDist(int distance[], bool Tset[], int DIMENSION) // finding minimum distance
{
    int minimum=INT_MAX,ind;
              
    for(int k=0;k<DIMENSION;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            ind=k;
        }
    }
    return ind;
}

void DijkstraAlgo(int src) // adjacency matrix 
{
    int distance[DIMENSION]; // // array to calculate the minimum distance for each node                             
    bool Tset[DIMENSION];// boolean array to mark visited and unvisited for each node
    
     
    for(int k = 0; k<DIMENSION; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<DIMENSION; k++)                           
    {
        int m=miniDist(distance,Tset, DIMENSION); 
        Tset[m]=true;
        for(int k = 0; k<DIMENSION; k++)
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && TAB[m][k] && distance[m]!=INT_MAX && distance[m]+TAB[m][k]<distance[k])
                distance[k]=distance[m]+TAB[m][k];
        }
    }
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    generate(DIMENSION);
    
    ifstream fs("C:/Users/qteix/OneDrive/Bureau/ENSTA/3A/ROB306-SEE/Projet/matrice.txt");

    if (fs)
    {
        string line;
        int i=0, j=0;

        while(getline(fs, line))
        {
            if (i<DIMENSION && j<DIMENSION) TAB[i][j] = stoi(line);
            else printf("Problème de taille");
            i++;
            if (i==DIMENSION)
            {
                i=0;
                j++;
            }
        }
        std::chrono::steady_clock::time_point begin_dij = std::chrono::steady_clock::now();
        DijkstraAlgo(0);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Dijkstra Execution Time = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin_dij).count() << "[micro_sec]" << std::endl;
        std::cout << "Total Execution Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[micro_sec]" << std::endl;
    }
    else
    {
        printf("Problème de lecture");
    }
    
    
    return 0;                           
}