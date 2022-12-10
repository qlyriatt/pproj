#include <time.h>
#include <random>
#include <iostream>

const int N = 100; 
const int M = 299;


int main()
{
    std::vector<int> v;
    std::srand(time(nullptr));
    
    for (int i = 0; i < N; i++)
    {
        v.push_back(1 + std::rand() % M);
        std::cout << i << " : " << v.at(i) << std::endl;
    }
    
    std::vector<int> count;
    count.resize(M + 1, 0);

    for (int i = 0; i < N; i++)
    {
        count.at(v.at(i))++;
    }

    std::vector<int> sorted_v;
    sorted_v.reserve(N);

    for (int j = 0; j < M + 1; j++)
    {
        while (count.at(j))
        {
            sorted_v.push_back(j);
            count.at(j)--;
        }
    }

    for (int i = 0; i < N; i++)
    {
        std::cout << i << " : " << sorted_v.at(i) << std::endl;        
    }
}
