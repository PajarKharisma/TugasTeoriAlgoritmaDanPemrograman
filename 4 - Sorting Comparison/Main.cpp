#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
using namespace std; 

class MergeSort{
    private:
        void merge(int *arr, int l, int m, int r){ 
            int i, j, k; 
            int n1 = m - l + 1; 
            int n2 =  r - m; 
        
            int *L = new int[n1];
            int *R = new int[n2]; 
        
            for (i = 0; i < n1; i++) 
                L[i] = arr[l + i]; 
            for (j = 0; j < n2; j++) 
                R[j] = arr[m + 1+ j]; 
        
            i = 0;
            j = 0; 
            k = l;
            while (i < n1 && j < n2){ 
                if (L[i] <= R[j]) { 
                    arr[k] = L[i]; 
                    i++; 
                } 
                else{ 
                    arr[k] = R[j]; 
                    j++; 
                } 
                k++; 
            } 

            while (i < n1){ 
                arr[k] = L[i]; 
                i++; 
                k++; 
            } 

            while (j < n2){ 
                arr[k] = R[j]; 
                j++; 
                k++; 
            } 
        }

    public: 
        void mergeSort(int *arr, int l, int r){ 
            if (l < r){ 
                int m = l+(r-l)/2; 
                mergeSort(arr, l, m); 
                mergeSort(arr, m+1, r); 
                merge(arr, l, m, r); 
            } 
        }
};

class QuickSort{
    private:
        int partition (int *arr, int low, int high){ 
            int pivot = low;
            int i = low;
            int j = high;
            while(j > i){
                if (arr[j] <= arr[pivot]){ 
                    i++;
                    swap(arr[i], arr[j]); 
                }
                j--;
            }
            swap(arr[i], arr[pivot]);
            return i; 
        }

    public:
        void quickSort(int *arr, int low, int high){ 
            if (low < high){
                int pi = partition(arr, low, high);
                quickSort(arr, low, pi - 1); 
                quickSort(arr, pi + 1, high); 
            } 
        }
};

class HeapSort{
    private:
        void heapify(int *arr, int n, int i) { 
            int largest = i;
            int l = 2*i + 1;
            int r = 2*i + 2;
            
            if (l < n && arr[l] > arr[largest]) 
                largest = l; 

            if (r < n && arr[r] > arr[largest]) 
                largest = r; 

            if (largest != i){ 
                swap(arr[i], arr[largest]); 
                heapify(arr, n, largest); 
            } 
        } 

    public:
        void heapSort(int *arr, int n){
            for (int i = n / 2 - 1; i >= 0; i--) 
                heapify(arr, n, i); 

            for (int i=n-1; i>=0; i--){ 
                swap(arr[0], arr[i]);
                heapify(arr, i, 0); 
            } 
        } 
};

void printArray(int arr[], int n, string title){
    cout << title << " : ";
	for (int i=0; i<n; ++i) 
		cout << arr[i] << " ";
	cout << endl; 
} 

int main() { 
    HeapSort hs;
    MergeSort ms;
    QuickSort qs;

    int n;
    int *data;
    int *dataHeap;
    int *dataMerge;
    int *dataQuick;

    cout << "Input banyak data : ";
    cin >>  n;

    data = new int[n];
    dataHeap = new int[n];
    dataMerge = new int[n];
    dataQuick = new int[n];

    for(int i=0; i<n; i++){
        int val = rand()*rand()+1;
        //int val = (rand()%100)+1;
        dataHeap[i] = val;
        dataMerge[i] = val;
        dataQuick[i] = val;
    }

    double duration = 0;
    clock_t startMerge = clock();
    ms.mergeSort(dataMerge, 0, n-1);
    duration = (clock() - startMerge) / (double)CLOCKS_PER_SEC;
    cout << "Waktu Merge Sort : " << duration << " second" << endl;

    duration = 0;
    clock_t startQuick = clock();
    qs.quickSort(dataQuick, 0, n-1);
    duration = (clock() - startQuick) / (double)CLOCKS_PER_SEC;
    cout << "Waktu Quick Sort : " << duration << " second" << endl;

    duration = 0;
    clock_t startHeap = clock();
	hs.heapSort(dataHeap, n);
    duration = (clock() - startHeap) / (double)CLOCKS_PER_SEC;
    cout << "Waktu Heap Sort : " << duration << " second" << endl;

    getch();
} 
