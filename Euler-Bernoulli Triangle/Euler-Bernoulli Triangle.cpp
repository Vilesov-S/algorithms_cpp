#include <iostream>
#include <vector>


int main()
{	
	std::cout << "Введите номер ряда = ";
	int n;
	std::cin >> n;
	n++;
	std::vector<std::vector<unsigned long long int>> tr(n, std::vector<unsigned long long int> (n, 0));
	tr[0][0] = 1;
	int i = 1, j = 0;
	
	int q = 1;
	bool trend = true; // true - вверх, false - вниз
	while (q < (n * (n + 1)/ 2))
	{
		if (trend)
		{
			if (j == 0) tr[i][j] = 0;
			else tr[i][j] = tr[i + 1][j - 1] + tr[i][j - 1];
			
			if (i - 1 >= 0)	{ i--; j++; }
			else { j++;	trend = false; }
		}
		else
		{
			if (i == 0) tr[i][j] = 0;
			else tr[i][j] = tr[i - 1][j + 1] + tr[i - 1][j];
			
			if (j - 1 >= 0) { i++; j--; }
			else { i++; trend = true; }
		}
		
		q++;
	}
	
	std::cout << "Последнее число в заданном ряду: ";
	if (trend) std::cout << tr[i - 1][j];
	else std::cout << tr[i][j - 1];
	
	std::cout << std::endl << "Треугольник: " << std::endl;;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			std::cout.width(n);
			std::cout << tr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}



