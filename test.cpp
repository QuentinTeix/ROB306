#include "generate.cpp"

template <size_t rows, size_t cols>
void process_2d_array_template(int (&array)[rows][cols])
{
    std::cout << __func__ << std::endl;
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < cols; ++j)
            std::cout << array[i][j] << '\t';
        std::cout << std::endl;
    }
}

void process_pointer_2_pointer(int **array, size_t rows, size_t cols)
{
    std::cout << __func__ << std::endl;
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < cols; ++j)
            std::cout << array[i][j] << '\t';
        std::cout << std::endl;
    }
}

int main()
{
    int rows = 2, cols = 5;
    int **tab;
    for (int i=0; i<2; i++) for (int j=0; j<5; j++) tab[i][j] = i+j;
    process_pointer_2_pointer(tab, rows, cols);
    return 0;
}