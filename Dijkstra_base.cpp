#include<iostream>
#include <fstream>
#include<climits>
#include "generate.cpp"

using namespace std;

const int DIMENSION = 5;

int TAB[DIMENSION][DIMENSION];

int miniDist(int distance[], bool Tset[], int DIMENSION) // finding minimum distance
{
    int minimum=INT_MAX,ind;          
    for(int k=0;k<DIMENSION;k++) {
        if(Tset[k]==false && distance[k]<=minimum) {
            minimum=distance[k];
            ind=k;}}
    return ind;
}

void DijkstraAlgo(int src) // adjacency matrix 
{
    int distance[DIMENSION]; // // array to calculate the minimum distance for each node                             
    bool Tset[DIMENSION];// boolean array to mark visited and unvisited for each node
    for(int k = 0; k<DIMENSION; k++) {
        distance[k] = INT_MAX;
        Tset[k] = false;}

    distance[src] = 0;   // Source vertex distance is set 0               
    for(int k = 0; k<DIMENSION; k++) {
        int m=miniDist(distance,Tset, DIMENSION); 
        Tset[m]=true;
        for(int k = 0; k<DIMENSION; k++) {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && TAB[m][k] && distance[m]!=INT_MAX && distance[m]+TAB[m][k]<distance[k])
                distance[k]=distance[m]+TAB[m][k];}}

    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<DIMENSION; k++) { 
        char str=65+k; 
        cout<<str<<"\t\t\t"<<distance[k]<<endl;}
}

int main()
{
    ifstream fs("C:/Users/qteix/OneDrive/Bureau/ENSTA/3A/ROB306-SEE/Projet/matrice.txt");
    generate(DIMENSION);
    if (fs)
    {
        string line;
        int i=0, j=0;

        int DIMENSION;
        if (getline(fs, line)) DIMENSION = stoi(line);
        else printf("Problème de lecture 1");


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
        for (int i=0; i<DIMENSION; i++)
        {
            for (int j=0; j<DIMENSION; j++) std::cout << TAB[i][j] << " ";
            std::cout << std::endl;

        }
        DijkstraAlgo(0);
    }
    else
    {
        printf("Problème de lecture");
    }
    
    return 0;                           
}