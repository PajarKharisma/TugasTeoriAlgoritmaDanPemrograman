#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>

using namespace std;

clock_t begin_time;

void partisi(int *x, int aw, int ak, int &id){
	int i, j, t, pivot;
	pivot = x[aw];
	j = aw;
	for (i = aw + 1; i <= ak; i++){
		if (x[i] < pivot){
			j++;
			t = x[i];
			x[i] = x[j];
			x[j] = t;
		}
	}
	x[aw] = x[j];
	x[j] = pivot;
	id = j;
}

void qsort(int *x, int aw, int ak){
	int j;
	if (aw < ak){
		partisi(x, aw, ak, j);
		qsort(x, aw, j - 1);
		qsort(x, j + 1, ak);
	}
}

void merge(int *x,int aw,int mid,int ak){ 
	int *z = new int[ak+1];
	int i,j,k,l; 
	i=aw; 
	j=mid+1; 
	k=aw; 
	do{ 
		if(x[i]<=x[j]){
			z[k]=x[i];
			i++;
		}else{
			z[k]=x[j];
			j++;
		} 
		k++;
	}while((i<=mid) && (j<=ak)); 
	
	if(i>mid){
		for(l=j;l<=ak;l++){
			z[k]=x[l];
			k++;
		}
	}else{
		for(l=i;l<=mid;l++){
			z[k]=x[l];
			k++;
		}
	}
	for(k=aw;k<=ak;k++) 
			x[k]=z[k];
	delete[] z;
	z = NULL;
}

void mergesort(int *x,int aw,int ak){ 
	int mid;
	if(aw<ak){
		mid =(aw+ak)/2; 
		mergesort(x,aw,mid); 
		mergesort(x,mid+1,ak); 
		merge(x,aw,mid,ak); 
	} 
}

/* void merge(int *arr, int l, int m, int r){
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
	delete[] L;
	L = NULL;
	delete[] R;
	R = NULL;
}

void mergesort(int *arr, int l, int r){ 
	if (l < r){ 
			int m = l+(r-l)/2;
			mergesort(arr, l, m); 
			mergesort(arr, m+1, r); 
			merge(arr, l, m, r); 
	} 
} */

void create_heap(int *a, int n){
	int q, i, j, key;
	for (q = 0; q < n; q++){
		i = q;
		key = a[i];
		j = i / 2;
		while (i > 0 && key > a[j]){
			a[i] = a[j];
			i = j;
			j = i / 2;
			if (j < 1)
				j = 0;
		}
		a[i] = key;
	}
}

void sort_heap(int *a, int n){
	int q, i, j, key, temp;
	create_heap(a, n);
	for (q = n - 1; q >= 0; q--){
		temp = a[0];
		a[0] = a[q];
		a[q] = temp;
		i = 0;
		key = a[i];
		j = 2 * i;
		if (j + 1 < q){
			if (a[j + 1] > a[j])
				j++;
		}
		while (j <= q - 1 && key < a[j]){
			a[i] = a[j];
			i = j;
			j = 2 * i;
			if (j + 1 < q){
				if (a[j + 1] > a[j])
					j++;
			}
			else
				break;
		}
		a[i] = key;
	}
}

void generateData(int *x, int n){
	srand(time(NULL));
	for (int i = 0; i < n; i++){
		x[i] = rand()*rand()+1;
		//x[i] = (rand() % 100) + 1;
	}
}

void restartTimer(){
	begin_time = clock();
}

void printTimer(){
	cout << float(clock() - begin_time) / CLOCKS_PER_SEC << " second" << endl;
}

enum sortalgo{
	mergeSort,
	quickSort,
	heapSort,
};

void Sort(sortalgo s, int *x, int n){
	switch (s){
	case heapSort:
		sort_heap(x, n);
		cout << "Waktu Heap Sort : ";
		break;
	case quickSort:
		qsort(x, 0, n-1);
		cout << "Waktu Quick Sort : ";
		break;
	case mergeSort:
		mergesort(x, 0, n-1);
		cout << "Waktu Merge Sort : ";
		break;
	}
}

void printData(int *data, int n){
	for(int i=0; i<n; i++){
		cout << data[i] << " ";
	}
	cout << endl;
}

int main(){
	int *x, n;
	n = 1000000;
/* 	x = new int[n];
	generateData(x, n);
	restartTimer();
	mergesort(x, 0, n-1);
	qsort(x,0,n-1);
	sort_heap(x, n);
	printData(x, n);
	printTimer(); */
	for(int i=0; i<3; i++){
		x = new int[n];
		generateData(x, n);
		restartTimer();
		Sort(sortalgo(i), x, n);
		printTimer();
		delete[] x;
		x = NULL;
	}
	getch();
}
