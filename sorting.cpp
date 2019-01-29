#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <stdio.h>
#define ARRAYSIZE 40

using namespace std;

int partition(int arr[], int lo, int hi, int &swaps);

/**
 * Generate an array sorted in ascending order.
 */
int* sorted_array() {
	int *arr = (int *) malloc(sizeof(int) * ARRAYSIZE);
	for (int i = 0; i < ARRAYSIZE; i++) {
		arr[i] = i;
	}
	return arr;
}

/**
 * Generate an array sorted in descending order.
 *
 * The best way to randomizes an array is using the knuth shuffle.
 */
int *reverse_array() {
	int *arr = (int *) malloc(sizeof(int) * ARRAYSIZE);
	for (int i = 0; i < ARRAYSIZE; i++) {
		arr[i] = ARRAYSIZE - i;
	}

	return arr;

}

/**
 * Randomize an array.
 */
int * randomize(int *arr) {
	srand(time(NULL)); // use system time for generating random numbers
	rand();

	for (int i = 0; i < ARRAYSIZE; i++) {
		int j = rand() % ARRAYSIZE;
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	return arr;
}

void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);

}

/**
 * The poor version of the bubble sort algorithm
 */
void bubble_sort_poor(int arr[], int n, int &swaps) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n - 1; y++) {
			if (arr[y] > arr[y + 1]) {
				int temp = arr[y + 1];
				arr[y + 1] = arr[y];
				arr[y] = temp;
				swaps++;
			}
		}
	}
}

/**
 * The smarter version of the bubble sort algorithm
 */
void bubble_sort_smart(int arr[], int n, int &swaps) {
	int last = 0;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n - 1; y++) {
			if (arr[y] > arr[y + 1]) {
				int temp = arr[y + 1];
				arr[y + 1] = arr[y];
				arr[y] = temp;
				swaps++;
			}
		}
		if (swaps == last) {
			break;
		}
		last = swaps;
	}
}

void selectionSort(int arr[], int n, int &swaps) {
	int i, j, minIndex, tmp;
	for (i = 0; i < n - 1; i++) {
		minIndex = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		if (minIndex != i) {
			tmp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = tmp;
			swaps++;
		}
	}
}

void swap(int arr[], int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void quickSort(int arr[], int lo, int hi, int &swaps) {
	if (hi <= lo)
		return;
	int j = partition(arr, lo, hi, swaps);
	quickSort(arr, lo, j - 1, swaps);
	quickSort(arr, j + 1, hi, swaps);
}

int partition(int arr[], int lo, int hi, int &swaps) {
	int i = lo;
	int j = hi + 1;
	int v = arr[lo];
	while (1) {
		while (arr[++i] < v) {
			if (i == hi)
				break;
		}
		while (v < arr[--j]) {
			if (j == lo)
				break;    // redundant since a[lo] acts as sentinel
		}

		if (i >= j)
			break;

		swap(arr, i, j);
		swaps++;
	}

	swap(arr, lo, j);
	swaps++;

	return j;
}

/**
 * This is inspired by geeks for geeks - this is a standard algorithm even a clean room implementation will look like this.
 */
void merge(int arr[], int l, int m, int r, int &swaps) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int left[n1], right[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		left[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		right[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (left[i] <= right[j]) {
			arr[k] = left[i];
			i++;
			swaps++;
		} else {
			arr[k] = right[j];
			j++;
			swaps++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1) {
		arr[k] = left[i];
		i++;
		k++;
		swaps++;
	}

	while (j < n2) {
		arr[k] = right[j];
		j++;
		k++;
		swaps++;
	}
}

void mergeSort(int a[], int l, int r, int &swaps) {
	int q;
	if (l < r) {
		q = (l + r) / 2;
		mergeSort(a, l, q, swaps);
		mergeSort(a, q + 1, r, swaps);
		merge(a, l, q, r, swaps);
	}
}

void insertionSort(int arr[], int length, int &swaps) {
	int i, j, tmp;
	for (i = 1; i < length; i++) {
		j = i - 1;
		tmp = arr[i];
		while (j >= 0 && arr[j] > tmp) {
			arr[j + 1] = arr[j];
			j--;
			swaps++;
		}
		arr[j + 1] = tmp;
	}

}

void version1() {
	int *arr;
	int user_input;
	int swaps;

	do {
		cout << "\n\nMenu\n";
		cout << "Option 1: Create sorted array in ascending order.\n"
				<< "Option 2: Create unsorted array in descending order.\n"
				<< "Option 3; Create unsorted array in random order.\n"
				<< "Enter 0 to exit\n\n";

		cin >> user_input;
		switch (user_input) {
		case 0:
			cout << "exiting....\n";
			break;

		case 1:
			arr = sorted_array();
			cout << "creating sorting array in ascending order...\n";
			cout << "Array before sort: ";

			printArray(arr, ARRAYSIZE);
			cout << endl << endl;
			cout << "Bubble sort: ";
			bubble_sort_poor(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			cout << endl << endl << "Selection sort: ";
			selectionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			cout << endl << endl << "Insertion sort: ";
			insertionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			free(arr);
			arr = reverse_array();
			cout << endl << "Merge sort: ";
			mergeSort(arr, 0, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);
			break;

		case 2:
			arr = reverse_array();
			cout << "creating sorting array in ascending order...\n";
			cout << "Array before sort: ";
			printArray(arr, ARRAYSIZE);

			cout << endl << endl << "Bubble sort: ";
			bubble_sort_poor(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			free(arr);
			arr = reverse_array();

			cout << endl << endl << "Selection sort: ";
			selectionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			free(arr);
			arr = reverse_array();

			cout << endl << endl << "Insertion sort: ";
			insertionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			free(arr);
			arr = reverse_array();
			cout << endl << "Merge sort: ";
			mergeSort(arr, 0, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			break;

		case 3:
			arr = sorted_array();
			randomize(arr);
			cout << "creating sorting array in ascending order...\n";
			cout << "Array before sort: ";
			printArray(arr, ARRAYSIZE);

			cout << endl << endl << "Bubble sort: ";
			bubble_sort_poor(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			randomize(arr);

			cout << endl << endl << "Selection sort: ";
			selectionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			randomize(arr);

			cout << endl << endl << "Insertion sort: ";
			insertionSort(arr, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			randomize(arr);
			cout << endl << "Merge sort: ";
			mergeSort(arr, 0, ARRAYSIZE, swaps);
			printArray(arr, ARRAYSIZE);

			break;

		default:
			cout << "\nthat is not a valid option" << endl;

		}

	} while (user_input != 0);
}

int main() {
	int *arr;
	int bc = 0, wc = 0, ac = 0;

	cout << "        Table     of      Results " << endl;
	cout << "              number of swaps     " << endl;
	cout << "                  BC        WC       AC   " << endl;

	arr = sorted_array();
	bubble_sort_poor(arr, ARRAYSIZE, bc);
	randomize(arr);
	bubble_sort_poor(arr, ARRAYSIZE, ac);
	free(arr);
	arr = reverse_array();
	bubble_sort_poor(arr, ARRAYSIZE, wc);

	cout << "Bubble sort poor   " << bc << "       " << wc << "     " << ac
			<< endl;

	ac = bc = wc = 0;
	bubble_sort_smart(arr, ARRAYSIZE, bc);
	randomize(arr);
	bubble_sort_smart(arr, ARRAYSIZE, ac);
	free(arr);
	arr = reverse_array();
	bubble_sort_smart(arr, ARRAYSIZE, wc);

	cout << "Bubble sort smart  " << bc << "       " << wc << "     " << ac
			<< endl;

	ac = bc = wc = 0;
	bubble_sort_smart(arr, ARRAYSIZE, bc);
	randomize(arr);
	insertionSort(arr, ARRAYSIZE, ac);
	free(arr);
	arr = reverse_array();
	insertionSort(arr, ARRAYSIZE, wc);

	cout << "Insertion sort     " << bc << "       " << wc << "     " << ac
			<< endl;

	ac = bc = wc = 0;
	mergeSort(arr, 0, ARRAYSIZE, bc);
	randomize(arr);
	mergeSort(arr, 0, ARRAYSIZE, ac);
	free(arr);
	arr = reverse_array();
	mergeSort(arr, 0, ARRAYSIZE, wc);

	cout << "Merge sort       " << bc << "       " << wc << "     " << ac
			<< endl;

	ac = bc = wc = 0;
	selectionSort(arr, ARRAYSIZE, bc);
	randomize(arr);
	selectionSort(arr, ARRAYSIZE, ac);
	free(arr);
	arr = reverse_array();
	selectionSort(arr, ARRAYSIZE, wc);

	cout << "Selection sort     " << bc << "       " << wc << "     " << ac
			<< endl;

	ac = bc = wc = 0;
	quickSort(arr, 0, ARRAYSIZE, bc);
	randomize(arr);
	quickSort(arr, 0, ARRAYSIZE -1, ac);
	free(arr);
	arr = reverse_array();


	quickSort(arr, 0, ARRAYSIZE -1, wc);

	cout << "Quick sort        " << bc << "       " << wc << "     " << ac
			<< endl;


}
