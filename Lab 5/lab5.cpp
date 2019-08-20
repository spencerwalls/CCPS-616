/* Spencer Walls */
/* CCPS 616 */
/* Lab 5 */

#include <fstream>
#include <iostream>

int max(int a, int b) 
{
	return (a > b) ? a : b; 
}

int KS_bruteforce(int value[], int weight[], int size, int max_weight, int *total_weight, int optimal_permutation[])
{
	int permutation[size] = { 0 }; 
	int total_value = 0;

	for (int i = 0; ; i++)
	{
		int j = 0;
		int temp_weight = 0;
		int temp_value = 0;
		int k = 1;

		for (j = 0; j < size; j++)
		{
			permutation[j] += k;
			k = permutation[j] / 2;
			permutation[j] = permutation[j] % 2;
		}

		if (k)
		{
			break;
		}

		for (k = 0; k < size; k++)
		{
			if (permutation[k] == 1)
			{
				temp_weight += weight[k];
				temp_value += value[k];
			}
		}

		if (temp_value > total_value && temp_weight <= max_weight) 
		{
			total_value = temp_value;
			*total_weight = temp_weight;

			for (int i = 0; i < size; i++)
			{
				optimal_permutation[i] = permutation[i];
			}
		}
	}

	return total_value;
}

int KS_dynamic(int value[], int weight[], int size, int max_weight, int *total_weight, int optimal_permutation[])
{
	int i;
	int w;
	int mem_table[size + 1][max_weight + 1];

	for (i = 0; i <= size; i++) 
	{
		for (w = 0; w <= max_weight; w++) 
		{
			if (i == 0 || w == 0)
			{
				mem_table[i][w] = 0;
			}
			else if (weight[i - 1] <= w)
			{
				mem_table[i][w] = max(value[i - 1] + mem_table[i - 1][w - weight[i - 1]], mem_table[i - 1][w]);
			}
			else
			{
				mem_table[i][w] = mem_table[i - 1][w];
			}
		}
	}

	int total_value = 0;
	int total_value_temp = mem_table[size][max_weight];
	total_value = total_value_temp;

	w = max_weight;

	for (i = size; i > 0 && total_value_temp > 0; i--) 
	{
		if (total_value_temp == mem_table[i - 1][w])
		{
			continue;
		}
		else 
		{
			*total_weight += weight[i - 1];
			optimal_permutation[i - 1] = 1;

			total_value_temp -= value[i - 1];
			w = w - weight[i - 1];
		}
	}

	return total_value;
}

int main(int argc, char **argv)
{
	std::ifstream input_file(argv[1]);

	const int MAX_SIZE = 256;
	int array[MAX_SIZE];
	int integer_count = 0;

	while (input_file >> array[integer_count])
	{
		integer_count++;
	}

	int n = (integer_count - 1) / 2;

	input_file.clear();
	input_file.seekg(0, std::ios::beg);

	int max_weight = 0;
	input_file >> max_weight;

	int weight[n];
	int value[n];

	for (int i = 0; i < n; i++)
	{
		input_file >> weight[i];
	}

	for (int i = 0; i < n; i++)
	{
		input_file >> value[i];
	}

	int total_weight_BF = 0;
	int *total_weight_ptr = &total_weight_BF;

	int optimal_permutation_BF[n] = { 0 };

	int total_value_BF = KS_bruteforce(value, weight, n, max_weight, total_weight_ptr, optimal_permutation_BF);

	int last_item_index = 0;

	for (int i = 0; i < n; i++)
	{
		if (optimal_permutation_BF[i] == 1)
		{
			last_item_index = i;
		}
	}

	std::ofstream output_file;
	output_file.open("KS_output.txt");

	output_file << "Brute Force results:" << std::endl << std::endl << "Items:    ";

	for (int i = 0; i < n; i++)
	{
		if (optimal_permutation_BF[i] == 1 && (i != (last_item_index)))
		{
			output_file << "(" << weight[i] << ", " << value[i] << "), "; 
		}

		if (optimal_permutation_BF[i] == 1 && (i == (last_item_index)))
		{
			output_file << "(" << weight[i] << ", " << value[i] << ") ";
		}
	}

	output_file << std::endl << "Value:    " << total_value_BF << std::endl;
	output_file << "Weight:   " << total_weight_BF << std::endl << std::endl << std::endl;

	int optimal_permutation_DP[n] = { 0 };

	int total_weight_DP = 0;
	total_weight_ptr = &total_weight_DP;

	int total_value_DP = KS_dynamic(value, weight, n, max_weight, total_weight_ptr, optimal_permutation_DP);

	last_item_index = 0;

	for (int i = 0; i < n; i++)
	{
		if (optimal_permutation_DP[i] == 1)
		{
			last_item_index = i;
		}
	}

	output_file << "Dynamic Programming results:" << std::endl << std::endl << "Items:    ";

	for (int i = 0; i < n; i++)
	{
		if (optimal_permutation_DP[i] == 1 && (i != (last_item_index)))
		{
			output_file << "(" << weight[i] << ", " << value[i] << "), ";
		}

		if (optimal_permutation_DP[i] == 1 && (i == (last_item_index)))
		{
			output_file << "(" << weight[i] << ", " << value[i] << ") ";
		}
	}

	output_file << std::endl << "Value:    " << total_value_DP << std::endl;
	output_file << "Weight:   " << total_weight_DP;

	return 0; 
}