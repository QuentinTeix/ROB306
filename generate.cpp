#include <fstream>
#include <iostream>
#include <time.h>

int generate(int dimension)
{
    srand(time(NULL));
    std::ofstream fs("matrice.txt");

    if(!fs)
    {
        std::cerr<<"Cannot open the output file." << std::endl;
        return 1;
    }

    int l = (dimension-1)*dimension/2;
    int tab[dimension][dimension];

    for (int i=0; i<dimension; i++)
    for (int j=i; j<dimension; j++)
    {
        if (i==j) tab[i][j]=0;
        else
        {
            tab[i][j] = rand()%10;
            tab[j][i] = tab[i][j];
        }
    }

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j<dimension; j++)
        {
            fs << std::to_string(tab[i][j]) << "\n";
        }
    }
    fs.close();
    return 0;
}