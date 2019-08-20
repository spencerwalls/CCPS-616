/* Spencer Walls */ 
/* CCPS 616 */
/* Lab 2 */

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std; 

string mult4(string x, string y);
string mult3a(string x, string y);
string mult3b(string x, string y);
string random_numeric_string(int len);
string add(string x, string y);
string subtract(string x, string y);
double time_mult4(int len);
double time_mult3b(int len);
double time_mult3a(int len);

/* mult4 function */
string mult4(string x, string y) 
{ 
    int n1 = x.size(); 
    int n2 = y.size(); 

    if (n1 == 0 || n2 == 0)
    { 
    	return "0"; 
	}

    vector<int> product(n1 + n2, 0);  
    int idx_n1 = 0;  
    int idx_n2 = 0;  
  
    for (int i = n1 - 1; i >= 0; i--) 
    { 
        int carry = 0; 
        int n1 = x[i] - '0'; 
        idx_n2 = 0;  
                        
        for (int j = n2 - 1; j >= 0; j--) 
        { 
            int n2 = y[j] - '0'; 
            int sum = n1 * n2 + product[idx_n1 + idx_n2] + carry;  
            carry = sum / 10; 
            product[idx_n1 + idx_n2] = sum % 10; 
            idx_n2++; 
        } 

        if (carry > 0) 
            product[idx_n1 + idx_n2] += carry; 

        idx_n1++; 
    } 
    
    int k = product.size() - 1; 

    while (k >= 0 && product[k] == 0)
    {
    	k--;    	
    }  
   
    if (k == -1)
    {
    	return "0"; 
    }

    string str = ""; 
       
    while (k >= 0)
    {
    	str += to_string(product[k--]); 	
    }

    return str; 
} 

/* This function times the mult4 function */
double time_mult4(int len)
{
	double sum_of_times = 0;

	for (int i = 0; i < 10; i++)
	{
		string s1 = random_numeric_string(len);
		string s2 = random_numeric_string(len);
		
		auto start = chrono::high_resolution_clock::now();

		mult4(s1, s2);

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		sum_of_times += elapsed.count() * (1000);		
	}

	double average_time = sum_of_times / 10;
	return average_time;
}

/* This function generates a random numeric string 
of size 'len' */
string random_numeric_string(int len)
{
	string random_numeric_string = "";
	for (int i = 0; i < len; i++)
	{
		random_numeric_string += to_string(rand() % 10);
	}
	return random_numeric_string;
}

/* This function adds x and y, and is used in the 
mult3a/mult3b functions */
string add(string x, string y) 
{
    int len = max(x.size(), y.size());
    int column_sum;
    int carry = 0;
    string total_sum;

    while (x.size() < len)
    {
    	x.insert(0, "0");
    }   

    while (y.size() < len) 
    {
    	y.insert(0, "0");
    }

    for (int i = len - 1; i >= 0; i--) 
    {
      column_sum = (x[i] - '0') + (y[i] - '0') + carry;
      carry = column_sum / 10;
      total_sum.insert(0, to_string(column_sum % 10));
    }
    
    if (carry != 0)
    {
    	total_sum.insert(0, to_string(carry));
    }

    return total_sum.erase(0, min(total_sum.find_first_not_of('0'), total_sum.size() - 1));
}

/* This function subtracts y from x, and is used in the 
mult3a/mult3b functions */
string subtract(string x, string y) 
{
    int len = max(x.size(), y.size());
    int difference;
    string total_difference;

    while (x.size() < len) 
    {
    	x.insert(0, "0");
    }
      
    while (y.size() < len)
    {
    	y.insert(0, "0");
    }
      
    for (int i = len - 1; i >= 0; i--) 
    {
        difference = (x[i] - '0') - (y[i] - '0');
        if (difference >= 0)
        {
        	total_difference.insert(0, to_string(difference));
        }
        else 
        {
            int j = i - 1;
            while (j >= 0) 
            {
                x[j] = ((x[j] - '0') - 1) % 10 + '0';
                if (x[j] != '9') 
                {
                	break;
                }    
                else
                { 
                    j--;
                }
            }
            total_difference.insert(0, to_string(difference + 10));
        }
    }

    return total_difference.erase(0, min(total_difference.find_first_not_of('0'), total_difference.size() - 1));
}

/* mult3a function */
string mult3a(string x, string y) 
{
	int len = max(x.size(), y.size());
    
    while (x.size() < len) 
    {
      	x.insert(0, "0");
    }

    while (y.size() < len)
    {
    	y.insert(0, "0");
    } 
      
    if (len == 1)
    {
    	return to_string((x[0] - '0') * (y[0] - '0'));
    }
        
    string x0 = x.substr(0, len / 2);
    string x1 = x.substr(len / 2, len - len / 2);
    string y0 = y.substr(0, len / 2);
    string y1 = y.substr(len / 2, len - len / 2);
    
    string p0 = mult3a(x0, y0);
    string p1 = mult3a(x1, y1);
    string p2 = mult3a(add(x0, x1), add(y0, y1));
    string p3 = subtract(p2, add(p0, p1));

    for (int i = 0; i < 2 * (len - len / 2); i++)
    {
    	p0.append("0");
    }
        
    for (int i = 0; i < len - len / 2; i++)
    {
    	p3.append("0");
    }
        
    string product = add(add(p0, p1), p3);

    return product.erase(0, min(product.find_first_not_of('0'), product.size() - 1));
}

/* This function times the mult3a function */
double time_mult3a(int len)
{
	double sum_of_times = 0;

	for (int i = 0; i < 10; i++)
	{
		string s1 = random_numeric_string(len);
		string s2 = random_numeric_string(len);
		
		auto start = chrono::high_resolution_clock::now();

		mult3a(s1, s2);

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		sum_of_times += elapsed.count() * (1000);		
	}

	double average_time = sum_of_times / 10;
	return average_time;
}

/* mult3b function */
string mult3b(string x, string y) 
{
	int len = max(x.size(), y.size());
	unsigned int number1 = stoi(y);
	unsigned int number2 = stoi(x);
	if (len < 6)
	{
	    unsigned int number1 = stoi(y);
	    unsigned int number2 = stoi(x);

	    if (number1 < 65536 && number2 < 65536)
		{
			unsigned int result = number1 * number2;
			return to_string(result);
		}
	}	
    
    while (x.size() < len) 
    {
      	x.insert(0, "0");
    }

    while (y.size() < len)
    {
    	y.insert(0, "0");
    } 
      
    if (len == 1)
    {
    	return to_string((x[0] - '0') * (y[0] - '0'));
    }
        
    string x0 = x.substr(0, len / 2);
    string x1 = x.substr(len / 2, len - len / 2);
    string y0 = y.substr(0, len / 2);
    string y1 = y.substr(len / 2, len - len / 2);
    
    string p0 = mult3b(x0, y0);
    string p1 = mult3b(x1, y1);
    string p2 = mult3b(add(x0, x1), add(y0, y1));
    string p3 = subtract(p2, add(p0, p1));

    for (int i = 0; i < 2 * (len - len / 2); i++)
    {
    	p0.append("0");
    }
        
    for (int i = 0; i < len - len / 2; i++)
    {
    	p3.append("0");
    }
        
    string product = add(add(p0, p1), p3);

    return product.erase(0, min(product.find_first_not_of('0'), product.size() - 1));
}

/* This function times the mult3b function */
double time_mult3b(int len)
{
	double sum_of_times = 0;

	for (int i = 0; i < 10; i++)
	{
		string s1 = random_numeric_string(len);
		string s2 = random_numeric_string(len);
		
		auto start = chrono::high_resolution_clock::now();

		mult3b(s1, s2);

	    auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = finish - start;
		sum_of_times += elapsed.count() * (1000);		
	}

	double average_time = sum_of_times / 10;
	return average_time;
}

int main()
{
	srand(time(0));

	/* timing mult3a function for k values between 1e1 and 5e3 */
	double mult3a_1e1 = time_mult3a(1e1);
	double mult3a_5e1 = time_mult3a(5e1);
	double mult3a_1e2 = time_mult3a(1e2);
	double mult3a_3e2 = time_mult3a(3e2);
	double mult3a_5e2 = time_mult3a(5e2);
	double mult3a_1e3 = time_mult3a(1e3);
	double mult3a_3e3 = time_mult3a(3e3);
	double mult3a_5e3 = time_mult3a(5e3);

	/* timing mult3b function for k values between 1e1 and 5e3 */	
	double mult3b_1e1 = time_mult3b(1e1);
	double mult3b_5e1 = time_mult3b(5e1);
	double mult3b_1e2 = time_mult3b(1e2);
	double mult3b_3e2 = time_mult3b(3e2);
	double mult3b_5e2 = time_mult3b(5e2);
	double mult3b_1e3 = time_mult3b(1e3);
	double mult3b_3e3 = time_mult3b(3e3);
	double mult3b_5e3 = time_mult3b(5e3);

	/* timing mult4 function for k values between 1e1 and 5e3 */
	double mult4_1e1 = time_mult4(1e1);
	double mult4_5e1 = time_mult4(5e1);
	double mult4_1e2 = time_mult4(1e2);
	double mult4_3e2 = time_mult4(3e2);
	double mult4_5e2 = time_mult4(5e2);
	double mult4_1e3 = time_mult4(1e3);
	double mult4_3e3 = time_mult4(3e3);
	double mult4_5e3 = time_mult4(5e3);

	ofstream myfile;
	myfile.open ("CCPS616_Lab2_SpencerWalls.txt");

	myfile << fixed << showpoint << setprecision(3)
		   << "CCPS616 - Lab 2 – Spencer Walls\n" << "Each result is the average (in ms) of 10 trials\n\n"
		   << "k =" << setw(20) << "mult4()" << setw(20) << "mult3a()" <<  setw(20) << "mult3b()" << endl
		   << "1e1" << setw(20) << mult4_1e1 << setw(20) << mult3a_1e1 << setw(20) << mult3b_1e1 << endl
		   << "5e1" << setw(20) << mult4_5e1 << setw(20) << mult3a_5e1 << setw(20) << mult3b_5e1 << endl
		   << "1e2" << setw(20) << mult4_1e2 << setw(20) << mult3a_1e2 << setw(20) << mult3b_1e2 << endl
		   << "3e2" << setw(20) << mult4_3e2 << setw(20) << mult3a_3e2 << setw(20) << mult3b_3e2 << endl
		   << "5e2" << setw(20) << mult4_5e2 << setw(20) << mult3a_5e2 << setw(20) << mult3b_5e2 << endl
		   << "1e3" << setw(20) << mult4_1e3 << setw(20) << mult3a_1e3 << setw(20) << mult3b_1e3 << endl
		   << "3e3" << setw(20) << mult4_3e3 << setw(20) << mult3a_3e3 << setw(20) << mult3b_3e3 << endl
		   << "5e3" << setw(20) << mult4_5e3 << setw(20) << mult3a_5e3 << setw(20) << mult3b_5e3 << endl;

    return 0;
}