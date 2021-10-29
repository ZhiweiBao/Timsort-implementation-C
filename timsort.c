// This is a C program to implement Timsort.

#include <stdio.h> // Include file for standard input/output
#include <stdlib.h> // so we can use atoi()
#include <time.h>   // so we can use time_t and clock_gettime()

#define EXPERIMENT 0 // use this for the experimentation in this algorithm
#define RUN 2

// =============== Helper Functions ===============
// Provided below is a helper function which can sort an array by insertion sort.
// Name: insertionSort
// Input(s):
//  (1) 'arr' is a pointer to an integer address. 
//      This is the start of some 'contiguous block of memory' that we will sort.
//  (2) 'l' and 'r' are integers, which are the first index and the last index of 'arr' respectively.
// Output: No value is returned, but 'arr' should be modified to store a sorted array of numbers.
void insertionSort(int arr[], int l, int r) {
    if (arr == NULL || l>=r) return;
    
    int key; 
    int i, j;
    for (i=l+1; i<=r; i++) {
        key = arr[i];
        j = i-1;
        while (j>=l && arr[j]>key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
    
}

// Provided below is a merge function.
// Name: merge
// Input(s):
//      (1) 'arr' is a pointer to an integer address. 
//          This is the start of some 'contiguous block of memory' that we will sort.
//      (2) 'temp' is a pointer to an integer address. 
//          This helps temporarily store the sorted subarray.
//      (3) 'l', 'm' and 'r' are integers, which are the first index, the middle and the last index of 'array' respectively.
// Output: No value is returned, but 'array' should be modified to store a sorted array of numbers.
void merge(int arr[], int temp[], int l, int m, int r){
    if (arr == NULL || temp == NULL) return;
    
    if (l > m || m+1 > r) return;

    int i = l;
    int j = m + 1;
    int start = l;

    // After comparing, merge the two arrays in a larger subarray
    while (i <= m && j <= r){
	if (arr[i] < arr[j]){
	    temp[start++] = arr[i++];
	} else if (arr[i] == arr[j]){
	    temp[start++] = arr[i++];
	    temp[start++] = arr[j++];
	}
	else{
	    temp[start++] = arr[j++];
	}
	
    }

    // Copy remaining elements of left, if any
    while (i <= m){
	    temp[start++] = arr[i++];
    }

    // Copy remaining element of right, if any
    while (j <= r){
	    temp[start++] = arr[j++];
    }

    for (i = l; i <= r; i++){
	    arr[i] = temp[i];
    }
}

// Provided below is a min function.
// Name: min
// Input(s):
//      (1) 'arg1' and 'arg2' are two integers to compare. 
// Output: the smaller integer.
int min(int arg1, int arg2){
    if (arg1 <= arg2){
        return arg1;
    } else {
        return arg2;
    }
} 

// Provided below is a sort function.
// Name: timSort
// Input(s):
//      (1) 'arr' is a pointer to an integer address. 
//          This is the start of some 'contiguous block of memory' that we will sort.
//      (2) 'size' tells us how big the array of data is we are sorting.
// Output: No value is returned, but 'arr' should be modified to store a sorted array of numbers.
void timSort(int arr[], unsigned int size){
    if (arr == NULL || size <= 1) return;
    
    // Sort individual subarrays of size RUN
    for (int i=0; i < size; i+=RUN){
        insertionSort(arr, i, min(i+RUN-1, size-1));
    }
    
    int* temp = (int*)malloc(sizeof(int)*size);

    // Start merging from size RUN. It will merge to size 2*RUN, then 4*RUN, and so on and so forth.
    // 'l', 'm' and 'r' are the left, middle and right index of two contiguous subarrays.
    // 'n' is the size of one subarray.
    int l, m, r, n;                 
    for (n=RUN; n < size; n*=2){
        for (l=0; l < size; l+=2*n){
            m = l+n-1;
            r = min(l+2*n-1, size-1);
            if (m<r){
                merge(arr, temp, l, m, r);
            }
        }
    }
    free(temp);
}

// Provided below is a print function.
// Name: printIntArray
// Input(s):
//      (1) 'arr' is a pointer to an integer address. 
//          This is the start of some 'contiguous block of memory'.
//      (2) 'size' tells us how big the array of data is.
// Output: No value is returned, just print 'arr'.
void printIntArray(int arr[], unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[]){
#if EXPERIMENT==0
  // Some test data sets.
  int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
  int dataset2[] = {10,9,8,7,6,5,4,3,2,1,0};
  int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
  int dataset4[] = {2,1,1,1,1,1,1,1,1,1,1};
  int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
  int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};
  
  // Sort our integer array
  timSort(dataset1, 11);
  timSort(dataset2, 11);
  timSort(dataset3, 11);
  timSort(dataset4, 11);
  timSort(dataset5, 11);
  timSort(dataset6, 11);
  
  // Print out an array
  printIntArray(dataset1, 11);
  printIntArray(dataset2, 11);
  printIntArray(dataset3, 11);
  printIntArray(dataset4, 11);
  printIntArray(dataset5, 11);
  printIntArray(dataset6, 11);

#else

  if (argc != 2) {
    printf("One argument expected: ./insertion 1000\n");
    return 1;
  }

  // Convert the argument of the program into an integer
  const int size = atoi(argv[1]);
  // Generate a random seed
  time_t t;
  srand((unsigned)time(&t));
  // Allocate memory
  int* random = (int*)malloc(sizeof(int)*size);

  // Populate our test data set
  for(int i = 0 ; i < size ; i++) {
    // Generate random values from 0 to 99
    random[i] = rand()%size; 
  }

  // You can uncomment if you'd like to see the size sorted
  // printf("Before the sort: ");
  // printIntArray(random, size);

  // Setup timers  
  struct timespec begin, end;
  // Get the time before we start
  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
  // Perform the sort
  timSort(random,size);
  // Get the time after we are done
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  double time_taken = (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
            (end.tv_sec  - begin.tv_sec);
  printf ("Total time = %f seconds\n", time_taken);

  // Confirm the sort worked
  // printf("After the sort: ");
  // printIntArray(random, size);
  
  // Free our random array
  free(random);

#endif

  return 0;
}
