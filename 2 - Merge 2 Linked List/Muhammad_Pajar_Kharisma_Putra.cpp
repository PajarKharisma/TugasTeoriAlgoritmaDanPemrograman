#include<iostream>
#include <conio.h>
#include <ctime>
using namespace std;

struct node{
    int data;
    node *next;
};

//FUNGSI INSERT DATA RANDOM KE DALAM LINKEDLIST
node *insertNode(node *list, int n){
    list = NULL;
    for (int i = 0; i < n; i++){
        node *newNode = new node;
        newNode->data = (rand() % 100) + 1;
        if(list == NULL){
            list = newNode;
            list->next = NULL;
        }else{
            newNode->next = list;
            list = newNode;
        }
    }
    return list;
}

//FUNGSI MENGURUTKAN DATA DALAM LINKEDLIST
node *sortNode(node *list){
    node *resultNode = NULL;
    node *l = list;
    node *tail;
    while(l != NULL){
        node *newNode = new node;
        newNode->data = l->data;
        if (resultNode == NULL){
            resultNode = newNode;
            resultNode->next = NULL;
            tail = resultNode;
        }else{
            if(newNode->data < resultNode->data){
                //insert depan
                newNode->next = resultNode;
                resultNode = newNode;
            }else if(newNode->data >= tail->data){
                tail->next = newNode;
                tail = newNode;
                tail->next = NULL;
            }else{
                //insert tengah
                node *p = resultNode;
                node *tmp;
                while (newNode->data > p->data){
                    tmp = p;
                    p = p->next;
                }
                newNode->next = tmp->next;
                tmp->next = newNode;
            }
        }
        l = l->next;
    }
    return resultNode;
}

//FUNGSI MENJUMLAHKAN NILAI DARI 2 LINKEDLIST
node *mergeList(node *l1, node *l2){
    node *root = l1;
    node *t = l1;
    node *tmp;
    while(t != NULL){
        tmp = t;
        t = t->next;
    }
    tmp->next = l2;
    return root;
}

//FUNGSI CETAK ISI LINKEDLIST
void print(node *l){
    node *p = l;
    while (p != NULL){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main(){
    int n;
    //PROSES INSERT DATA RANDOM KE DALAM LINKED LIST
    cout << "Input banyak data : ";
    cin >> n;
    node *l1 = insertNode(l1, n);

    cout << "Input banyak data : ";
    cin >> n;
    node *l2 = insertNode(l2, n);

    cout << endl << "DATA AWAL" << endl;
    cout << "L1 : ";
    print(l1);
    cout << "L2 : ";
    print(l2);

    //PROSES SORTING DATA AGAR TERURUT
    l1 = sortNode(l1);
    l2 = sortNode(l2);

    cout << endl << "DATA SETELAH DISORTING" << endl;
    cout << "L1 : ";
    print(l1);
    cout << "L2 : ";
    print(l2);

    //PROSES MERGE LIST 1 DAN LIST 2
    l1 = mergeList(l1, l2);
    l2 = NULL;

    cout << endl << "DATA SETELAH DIMERGE" << endl;
    cout << "L : ";
    print(l1);

    l1 = sortNode(l1);
    cout << endl << "DATA SETELAH DIMERGE DAN DISORTING" << endl;
    cout << "L : ";
    print(l1);

    getch();
    return 0;
}