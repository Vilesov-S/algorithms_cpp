#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


void write_result(vector<unsigned int> &sieve, int quantity_elements)
{
    int quant = 0;
    ofstream result_file;
    result_file.open("result.txt", ios::out);
    for (int i = 0; i < quantity_elements; i++)
        if (sieve[i])
        {
            quant++;
            result_file << i << " ";
        }
    result_file << endl << "Quantity simple numbers: " << quant;
    result_file.close();
}


void eratosthen_sieve(int quantity_elements, bool write_to_file = false)
{
    vector<unsigned int> sieve(quantity_elements, 1);
    sieve[0] = 0;
    sieve[1] = 0;
    __int64 j;
    for (__int64 prime_number = 2; prime_number <= int(sqrt(quantity_elements)); prime_number++)
        if (sieve[prime_number])
        {
            for (j = prime_number * prime_number; j < quantity_elements; j += prime_number)
            {
                sieve[j] = 0;
            }
        }

    if (write_to_file) write_result(sieve, quantity_elements);
}

int main(int argc, char *argv[])
{
	//setlocale(LC_ALL, "ru_RU.UTF-8");
	int quantity_elements = stoi(argv[1]);
	bool write_to_file = bool(stoi(argv[2]));
	eratosthen_sieve(quantity_elements, write_to_file);
}
