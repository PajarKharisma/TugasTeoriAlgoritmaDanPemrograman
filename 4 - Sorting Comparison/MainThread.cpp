#include <iostream>
#include <pthread.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
using namespace std; 

#define NUM_OF_SORTING 3

struct RawData{
    int *data;
    int n;
    int id;
};

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
            delete L;
            L = NULL;
            delete R;
            R = NULL;
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

void *threadSorting(void *input){
    QuickSort qs;
    MergeSort ms;
    HeapSort hs;

    int *data = ((struct RawData*)input)->data;
    int n = ((struct RawData*)input)->n;
    int id = ((struct RawData*)input)->id;

    double duration = 0;
    clock_t start = clock();

    switch (id){
        case 0:
            qs.quickSort(data, 0, n-1);
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            cout << "Waktu Quick Sort : " << duration << " second" << endl;
        break;
        case 1:
            ms.mergeSort(data, 0, n - 1);
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            cout << "Waktu Merge Sort : " << duration << " second" << endl;
        break;
        default:
            hs.heapSort(data, n);
            duration = (clock() - start) / (double)CLOCKS_PER_SEC;
            cout << "Waktu Heap Sort : " << duration << " second" << endl;
        break;
    }

    delete data;
    data = NULL;
    pthread_exit(NULL);
}

void printArray(int arr[], int n, string title){
    cout << title << " : ";
	for (int i=0; i<n; ++i) 
		cout << arr[i] << " ";
	cout << endl; 
} 

int main(int argc, char *argv[]) {
    int n;
    struct RawData *rawData[NUM_OF_SORTING];
    cout << "Input banyak data : ";
    cin >>  n;

    for(int i=0; i<NUM_OF_SORTING; i++){
        rawData[i] = (struct RawData *)malloc(sizeof(struct RawData));
        rawData[i]->data = new int[n];
        rawData[i]->id = i;
        rawData[i]->n = n;
    }

    for(int i=0; i<n; i++){
        int val = rand()*rand()+1;
        //int val = (rand()%100)+1;
        rawData[0]->data[i] = val;
        rawData[1]->data[i] = val;
        rawData[2]->data[i] = val;
    }

    pthread_t tid[NUM_OF_SORTING];
    cout << "START SORTING" << endl;
    for(int i=0; i<NUM_OF_SORTING; i++){
        int rc = pthread_create(&tid[i], NULL, threadSorting, (void *)rawData[i]);
        if(rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
    getch();
} 
