#include <iostream>
#include <fstream>

/*
// input stream : read from file
int main(void)
{
	std::ifstream fin; // output, normal file
	char item[20];
	float cost;

	fin.open("Inventory.txt", std::ios::in);
	if (!fin)
	{
		std::cout << "Cannot open Inventory.txt file." << std::endl;
		return (1);
	}

	fin >> item >> cost;
	std::cout << item << " " << cost << std::endl;
	fin >> item >> cost;
	std::cout << item << " " << cost << std::endl;
	fin >> item >> cost;
	std::cout << item << " " << cost << std::endl;

	fin.close();
	return (0);
}
*/
// output stream: write to file
int main(void)
{
	std::ofstream out; // output, normal file

	out.open("Inventory.txt", std::ios::app);
	if (!out)
	{
		std::cout << "Cannot open Inventory.txt file." << std::endl;
		return (1);
	}

	out << "Radios\t\t" << 39.95 << std::endl;
	out << "Tosters\t\t" << 19.95 << std::endl;
	out << "Mixtures\t" << 24.80 << std::endl;

	out.close();
	return (0);
}

