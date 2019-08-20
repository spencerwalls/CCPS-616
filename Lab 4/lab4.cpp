/* Spencer Walls */
/* CCPS 616 */
/* Lab 4 */

#include <fstream>
#include <algorithm>

struct interval 
{
	int start;
	int end;
};

bool compare_intervals(interval x, interval y)
{
	return (x.end < y.end);
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

	int number_of_intervals = (integer_count - 1) / 2;

	input_file.clear();
	input_file.seekg(0, std::ios::beg);

	interval bookings[number_of_intervals] = {};

	int N = 0;
	input_file >> N;

	for (int i = 0; i < number_of_intervals; i++)
	{
		input_file >> bookings[i].start;
	}

	for (int i = 0; i < number_of_intervals; i++)
	{
		input_file >> bookings[i].end;
	}

	std::sort(bookings, bookings + number_of_intervals, compare_intervals);

	std::ofstream output_file;
	output_file.open("selected_bookings.txt");

	bool flag_check[number_of_intervals] = {false};
	int count = 0;
	int i = 0;

	for (int n = 0; n < N; n++)
	{
		output_file << n + 1 << " ";
		for (int j = 0; j < number_of_intervals; j++)
		{
			if (flag_check[j] != true)
			{
				output_file << "(" << bookings[j].start << ", " << bookings[j].end << ") ";
				flag_check[j] = true;
				count++;
				i = j;
				break;
			}
		}
		for (int k = i + 1; k < number_of_intervals; k++)
		{
			if (bookings[k].start >= bookings[i].end && (flag_check[k] != true))
			{
				output_file << "(" << bookings[k].start << ", "
							<< bookings[k].end << ") ";
				flag_check[k] = true; 
				i = k;
				count++;
			}
		}

		output_file << std::endl;

		if (count == number_of_intervals)
		{
			break; 
		}
	}

	if (count < number_of_intervals)
	{
		for (int i = 0; i < number_of_intervals; i++)
		{
			if (flag_check[i] != true)
			{
				output_file << "(" << bookings[i].start << ", " << bookings[i].end << ") ";
			}
		}
	}

	return 0;
}