//Jeffrey Stoddard
//CECS 328
//Lab 5

#include <iostream>
#include <chrono>

int *arr;
long int size = 0;
int k = 0;

//Initializes array with size from user input
void InitArray()
{
	std::cout << "Please enter a positive integer for the array size: ";
	std::cin >> size;
	arr = new int[size];
}

//generates -5000 through 5000 in arr
void populateArray()
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 201 - 100;
	}
}

void getK()
{
	std::cout << "Please enter a positive integer for k between 1 and the array size: ";
	std::cin >> k;
}

//Prints array
void printArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "[" << arr[i] << "] ";
	}
	std::cout << std::endl;
}

//Sorts to the kth least element of given array
int quickSelect(int a[], int k, int left = 0, int right = size)
{
	int pivot = a[right - 1];
	int lower = left - 1;
	for (int i = left; i < right - 1; i++)
	{
		if (a[i] <= pivot)
		{
			//swap current selection with first element after lower elements
			lower++;
			int temp = a[i];
			a[i] = a[lower];
			a[lower] = temp;
		}
	}
	//swap last element (pivot) with the first element larger than the pivot
	lower++;
	int temp = a[right - 1];
	a[right - 1] = a[lower];
	a[lower] = temp;
	//done partitioning

	//if pivot = k return pivot
	if (lower == k - 1)
	{
		return a[lower];
	}
	//else if pivot index is greater than k, Select from left sub array
	else if (lower > k - 1)
	{
		return quickSelect(a, k, left, lower); // [left, pivot)
	}
	else //else pivot index is less than k and select from right sub array
	{
		return quickSelect(a, k, lower, right); // (pivot, right)
	}
}

//Modified quick select to track all negative elements that have become absolute from abs(a[i] - median)
int quickMedianElements(int a[], int neg[], int k, int left = 0, int right = size)
{
	int pivot = a[right - 1];
	int lower = left - 1;
	for (int i = left; i < right - 1; i++)
	{
		if (a[i] <= pivot)
		{
			//swap current selection with first element after lower elements
			lower++;
			int temp = a[i];
			a[i] = a[lower];
			a[lower] = temp;

			//swapping negative indicators that map to actual elements
			temp = neg[i];
			neg[i] = neg[lower];
			neg[lower] = temp;
		}
	}
	//swap last element (pivot) with the first element larger than the pivot
	lower++;
	int temp = a[right - 1];
	a[right - 1] = a[lower];
	a[lower] = temp;

	//swapping negative indicators that map to actual elements
	temp = neg[right - 1];
	neg[right - 1] = neg[lower];
	neg[lower] = temp;
	//done partitioning

	//if pivot = k return pivot
	if (lower == k - 1)
	{
		return a[lower];
	}
	//else if pivot index is greater than k, Select from left sub array
	else if (lower > k - 1)
	{
		return quickSelect(a, k, left, lower); // [left, pivot)
	}
	else //else pivot index is less than k and select from right sub array
	{
		return quickSelect(a, k, lower, right); // (pivot, right)
	}
}

//Selects k elements that are closest to the median (including the median)
void medianElements(int a[], int size, int k)
{
	//Initialize the median
	int median = -1;
	//if size is divisible by 2, index = size/2
	if(size % 2 == 0)
	{
		median = quickSelect(a, size / 2);
	}
	else //median is the average of 2 closest indexes to size/2
	{
		quickSelect(a, (size / 2) + 1);
		median = (a[size / 2] + a[size / 2 + 1]) / 2;
	}
	//O(qSelect * 2 + 1) = O(n) , worst case O(n^2)

	std::cout << "Median: " << median << std::endl;

	int* diff = new int[size]; //allocate differences array
	int* neg = new int[size]; //allocate negative indicators array

	//populating neg and diff arrays: O(4 * size) = O(n)
	for (int i = 0; i < size; i++)
	{
		int difference = a[i] - median;
		if (difference < 0)
		{
			neg[i] = -1;
		}
		else
		{
			neg[i] = 1;
		}
		diff[i] = abs(difference);
	}

	//O(n) 
	quickMedianElements(diff, neg, k);

	//shifting elements back to original values and print result: O(k)
	for (int i = 0; i < k; i++)
	{
		diff[i] = (diff[i] * neg[i]) + median;
		std::cout << diff[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	//seed from clock
	srand(time(NULL));

	//create array
	InitArray();
	populateArray();
	printArray();

	//get k from user input
	getK();

	medianElements(arr, size, k);
	// = O(n) + O(n) + O(n) + O(k) = O(n + k) = O(n)

	system("pause");
	return 0;
}