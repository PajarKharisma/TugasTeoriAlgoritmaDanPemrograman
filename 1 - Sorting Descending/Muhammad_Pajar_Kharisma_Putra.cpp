#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void radixsort(int *input, int n){
    int i;
    int maxNumber = input[0];
    for (i = 1; i < n; i++){
        if (input[i] > maxNumber)
            maxNumber = input[i];
    }

    int exp = 1;
    int *tmpBuffer = new int[n];
    while (maxNumber / exp > 0){
        int decimalBucket[10] = {0};
        for (i = 0; i < n; i++){
            decimalBucket[9-input[i] / exp % 10]++;
        }

        for (i = 1; i < 10; i++){
            decimalBucket[i] += decimalBucket[i - 1];
        }

        for (i = n - 1; i >= 0; i--){
            tmpBuffer[--decimalBucket[9-input[i] / exp % 10]] = input[i];
        }
        for (i = 0; i < n; i++){
            input[i] = tmpBuffer[i];
        }
        exp *= 10;
    }
}

void printArray(int arr[], int arraySize){
    int counter = 0;
    for(int i=0; i<arraySize; i++){
        cout << arr[i] << " ";
        counter++;
        if(counter >= 10){
            cout << endl;
            counter = 0;
        }
    }
}

void print(int data[], int n){
    int counter = 0;
    for(int i=0; i<n-1; i++){
        if(data[i] != data[i+1]){
            counter++;
            if(counter <= 10){
                cout << data[i] << " ";
            }else{
                break;
            }
        }
    }
}

int main(){
    int n;
    int *data;

    cout << "Masukan data : ";
    cin >> n;
    data = new int[n];
    
    clock_t start;
    double duration;
    start = clock();

    for(int i=0; i<n; i++){
        data[i] = (rand() % 1000) + 1;
    }

    radixsort(data, n);
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "Waktu Eksekusi : " << duration << " second" << endl;

    cout << "=============================" << endl;
    print(data, n);
    return 0;
}