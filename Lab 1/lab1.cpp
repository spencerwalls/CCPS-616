/* Spencer Walls */ 
/* C/C++ hybrid program including Mergesort, 
Selection sort, and MergSel sort implementations.
Experimental results are written to an output file
named 'CCPS616_Lab1_SpencerWalls.txt' as per
assignemnt requirements. */

#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void merge(int arr[], int l, int m, int r);
void merge_sort(int arr[], int l, int r); 
void random_array(int *arr, int size);
void selection_sort(int arr[], int n);
void selection_sort2(int arr[], int l, int r);
void mergeSel(int arr[], int l, int r, int threshold);
void swap(int *ptr1, int *ptr2); 
double sanity_check_merge(int size);
double sanity_check_selection(int size);
double sanity_check_mergesel(int size, int threshold);


/* Mergesort function */
void merge_sort(int arr[], int left, int right) 
{ 
    if (left < right) 
    { 
        int middle = left + (right - left) / 2; 
        merge_sort(arr, left, middle); 
        merge_sort(arr, middle + 1, right); 
        merge(arr, left, middle, right); 
    } 
} 

/* Merge function */ 
void merge(int arr[], int left, int middle, int right) 
{ 
    int i;
    int j;
    int k; 
    int n1 = middle - left + 1; 
    int n2 =  right - middle; 
 
    int left_arr[n1], right_arr[n2]; 
  
    for (i = 0; i < n1; i++)
    { 
        left_arr[i] = arr[left + i]; 
    }

    for (j = 0; j < n2; j++) 
    {
        right_arr[j] = arr[middle + 1+ j]; 
    }
  
    i = 0;  
    j = 0; 
    k = left;  

    while (i < n1 && j < n2) 
    { 
        if (left_arr[i] <= right_arr[j]) 
        { 
            arr[k] = left_arr[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = right_arr[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = left_arr[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = right_arr[j]; 
        j++; 
        k++; 
    } 
} 

/* Function that generates random numbers and 
stores them in an array that is passed as argument */
random_device rd;
default_random_engine generator(time(0));
void random_array(int *arr, int size)
{
	uniform_int_distribution<int> distribution(1, size * 4);

	for (int i = 0; i < size; i++)
	{
		arr[i] = distribution(generator);
	}
}

/* Sanity check function for Mergesort */
double sanity_check_merge(int size)
{
	double sum_of_times = 0;

    for (int i = 0; i < 10; i++) 
    {
	    int arr[size] = {};

	    random_array(arr, size);
	 
    	auto start = chrono::high_resolution_clock::now();

	    merge_sort(arr, 0, size - 1); 

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;

		sum_of_times += elapsed.count() * (1000);
	}	

	double average_time = sum_of_times / 10;
	return average_time;
}

/* Sanity check function for Selectionsort*/
double sanity_check_selection(int size)
{
	double sum_of_times = 0;

    for (int i = 0; i < 10; i++) 
    {
	    int arr[size] = {};

	    random_array(arr, size);
	  
    	auto start = chrono::high_resolution_clock::now();

	    selection_sort(arr, size); 

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;

		sum_of_times += elapsed.count() * (1000);
	}	

	double average_time = sum_of_times / 10;
	return average_time;
}

/* Sanity check function for MergeSel sort*/ 
/* This function is like the previous two sanity
checks however also prints example I/O for one 
of the iterations */
double sanity_check_mergesel(int size, int threshold)
{
	double sum_of_times = 0;

    for (int i = 0; i < 10; ++i) 
    {
	    int arr[size] = {};

	    random_array(arr, size);

		if (size == 5e2 && threshold == 7 && i == 0) // print example unsorted array 
		{
			printf("Example input (unsorted) array for MergeSel sort @ n = 5e2 and x = 7\n\n"); 
    		int k; 
    		for (k = 0; k < size; k++)
    		{ 
        		printf("%d ", arr[k]); 
        	}
		}		    
	  
    	auto start = chrono::high_resolution_clock::now();

	    mergeSel(arr, 0, size, threshold); 

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;

		sum_of_times += elapsed.count() * (1000);

		if (size == 5e2 && threshold == 7 && i == 0) // print example sorted array 
		{
			printf("\n\nExample output (sorted) array for MergeSel sort @ n = 5e2 and x = 7\n\n"); 
    		int k; 
    		for (k = 0; k < size; k++)
    		{
        		printf("%d ", arr[k]); 
    		}

    		printf("\n");
		}		
	}	

	double average_time = sum_of_times / 10;
	return average_time;
}

/* Swap function */
void swap(int *ptr1, int *ptr2)  
{  
    int temp = *ptr1;  
    *ptr1 = *ptr2;  
    *ptr2 = temp;  
}  
 
/* Selectionsort function */
void selection_sort(int arr[], int n)  
{  
    int i;
    int j;
    int min;  
   
    for (i = 0; i < n - 1; i++)  
    {  
        min = i;  
        for (j = i + 1; j < n; j++)
        {  
        	if (arr[j] < arr[min])
        	{  
            	min = j;
            }
  		}

        swap(&arr[min], &arr[i]);  
    }  
}  

/* Second Selectionsort implementation */
/* Only difference is that this one employs
specific array indices rather than simply 
the array size (this behaviour is required
for the MergeSel implementation) */
void selection_sort2(int arr[], int left, int right)  
{  
    int i;
    int j;
    int min;   
  
    for (i = left; i < right; i++)  
    {  
        min = i;  
        for (j = i + 1; j < (right + 1); j++)
        {  
        	if (arr[j] < arr[min])
        	{  
            	min = j;
            }
  		}

        swap(&arr[min], &arr[i]);  
    }  
}  

/* MergeSel function */
void mergeSel(int arr[], int left, int right, int threshold) 
{  
	if ((right - left) <= threshold)
	{
		selection_sort2(arr, left, right);
	}
	else
	{
		int middle = left + (right - left) / 2; 
		mergeSel(arr, left, middle, threshold); 
		mergeSel(arr, middle + 1, right, threshold); 
		merge(arr, left, middle, right); 
	}
}

int main() 
{ 
	/* Mergesort sanity checks */ 
	double avg_time_5e2_merge = sanity_check_merge(5e2);
	double avg_time_1e3_merge = sanity_check_merge(1e3);
	double avg_time_5e3_merge = sanity_check_merge(5e3);
	double avg_time_1e4_merge = sanity_check_merge(1e4);
	double avg_time_5e4_merge = sanity_check_merge(5e4);

	/* Selectionsort sanity checks */
	double avg_time_5e2_selection = sanity_check_selection(5e2);
	double avg_time_1e3_selection = sanity_check_selection(1e3);
	double avg_time_5e3_selection = sanity_check_selection(5e3);
	double avg_time_1e4_selection = sanity_check_selection(1e4);
	double avg_time_5e4_selection = sanity_check_selection(5e4);

	/* MergeSel sort sanity checks */
	/* Note that one block is present for each value of n, 
	whereby each respective block contains sanity checks for
	values of x ranging from 4 - 8. Thus, the sanity check
	function for MergeSel contains an additional argument
	for the value of x. */
	double avg_time_5e2_mergesel_4 = sanity_check_mergesel(5e2, 4); // n = 5e2
	double avg_time_5e2_mergesel_5 = sanity_check_mergesel(5e2, 5);
	double avg_time_5e2_mergesel_6 = sanity_check_mergesel(5e2, 6);
	double avg_time_5e2_mergesel_7 = sanity_check_mergesel(5e2, 7);
	double avg_time_5e2_mergesel_8 = sanity_check_mergesel(5e2, 8);

	double avg_time_1e3_mergesel_4 = sanity_check_mergesel(1e3, 4); // n = 1e3
	double avg_time_1e3_mergesel_5 = sanity_check_mergesel(1e3, 5);
	double avg_time_1e3_mergesel_6 = sanity_check_mergesel(1e3, 6);
	double avg_time_1e3_mergesel_7 = sanity_check_mergesel(1e3, 7);
	double avg_time_1e3_mergesel_8 = sanity_check_mergesel(1e3, 8);

	double avg_time_5e3_mergesel_4 = sanity_check_mergesel(5e3, 4); // n = 5e3
	double avg_time_5e3_mergesel_5 = sanity_check_mergesel(5e3, 5);
	double avg_time_5e3_mergesel_6 = sanity_check_mergesel(5e3, 6);
	double avg_time_5e3_mergesel_7 = sanity_check_mergesel(5e3, 7);
	double avg_time_5e3_mergesel_8 = sanity_check_mergesel(5e3, 8);

	double avg_time_1e4_mergesel_4 = sanity_check_mergesel(1e4, 4); // n = 1e4
	double avg_time_1e4_mergesel_5 = sanity_check_mergesel(1e4, 5);
	double avg_time_1e4_mergesel_6 = sanity_check_mergesel(1e4, 6);
	double avg_time_1e4_mergesel_7 = sanity_check_mergesel(1e4, 7);
	double avg_time_1e4_mergesel_8 = sanity_check_mergesel(1e4, 8);

	double avg_time_5e4_mergesel_4 = sanity_check_mergesel(5e4, 4); // n = 5e4
	double avg_time_5e4_mergesel_5 = sanity_check_mergesel(5e4, 5);
	double avg_time_5e4_mergesel_6 = sanity_check_mergesel(5e4, 6);
	double avg_time_5e4_mergesel_7 = sanity_check_mergesel(5e4, 7);
	double avg_time_5e4_mergesel_8 = sanity_check_mergesel(5e4, 8);

    // determine optimal x value (when n = 5e4)
	double array[5];
	array[0] = avg_time_5e4_mergesel_4;
	array[1] = avg_time_5e4_mergesel_5;
	array[2] = avg_time_5e4_mergesel_6;
	array[3] = avg_time_5e4_mergesel_7;
	array[4] = avg_time_5e4_mergesel_8;

	int min_x = 0; // get index of minimum time 
    for (int i = 1; i < 5; i++)
    {  
    	if (array[i] < array[min_x])
    	{  
        	min_x = i;
        }
	}

	ofstream myfile;
	myfile.open ("CCPS616_Lab1_SpencerWalls.txt");

	/* Sorry for the mess here, still getting used to C++ */
	myfile << fixed << showpoint << setprecision(3)
		   << "CCPS616 - Lab 1 – Spencer Walls\n" << "Each result is the average (in ms) of 10 trials\n\n"
		   << "n =" << "      " << "5e2" << right << setw(20) << "1e3" << right << setw(20) << "5e3" << right << setw(20) << "1e4" << right << setw(20)
		   << "5e4" << "\n" << "Sel" << "      " << avg_time_5e2_selection << setw(20) << avg_time_1e3_selection
		   << setw(20) << avg_time_5e3_selection << setw(20) << avg_time_1e4_selection << setw(20) << avg_time_5e4_selection << "\n"
		   << "Merge" << "    " << avg_time_5e2_merge << setw(20) << avg_time_1e3_merge << setw(20) << avg_time_5e3_merge << setw(20)
		   << avg_time_1e4_merge << setw(20) << avg_time_5e4_merge << "\n\n" << "MergeSel\n" << "x = 4" << "    " << avg_time_5e2_mergesel_4
		   << setw(20) << avg_time_1e3_mergesel_4 << setw(20) << avg_time_5e3_mergesel_4 << setw(20) << avg_time_1e4_mergesel_4 << setw(20) 
		   << avg_time_5e4_mergesel_4 << endl << "x = 5" << "    " << avg_time_5e2_mergesel_5 << setw(20) << avg_time_1e3_mergesel_5 << setw(20)
		   << avg_time_5e3_mergesel_5 << setw(20) << avg_time_1e4_mergesel_5 << setw(20) << avg_time_5e4_mergesel_5 << endl << "x = 6" << "    "
		   << avg_time_5e2_mergesel_6 << setw(20) << avg_time_1e3_mergesel_6 << setw(20) << avg_time_5e3_mergesel_6 << setw(20)
		   << avg_time_1e4_mergesel_6 << setw(20) << avg_time_5e4_mergesel_6 << endl <<  "x = 7" << "    " <<  avg_time_5e2_mergesel_7 << setw(20)
		   << avg_time_1e3_mergesel_7 << setw(20) << avg_time_5e3_mergesel_7 << setw(20) << avg_time_1e4_mergesel_7 << setw(20) << avg_time_5e4_mergesel_7
		   << endl <<  "x = 8" << "    " <<  avg_time_5e2_mergesel_8 << setw(20) << avg_time_1e3_mergesel_8 << setw(20)
		   << avg_time_5e3_mergesel_8 << setw(20) << avg_time_1e4_mergesel_8 << setw(20) << avg_time_5e4_mergesel_8 << "\n\n\n"		   
		   << "Based on this, MergeSel performed best (for n = 5e4) when x = " << min_x + 4;
	
	myfile.close();
	return 0; 
}