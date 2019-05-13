#include<iostream>
using namespace std;

struct node{
    int data;
    node *next;
};

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

node *sortNode(node *list){
    node *resultNode = NULL;
    node *l = list;
    while(l != NULL){
        node *newNode = new node;
        newNode->data = l->data;
        if (resultNode == NULL){
            resultNode = newNode;
            resultNode->next = NULL;
        }else{
            if(newNode->data < resultNode->data){
                //insert depan
                newNode->next = resultNode;
                resultNode = newNode;
            }else{
                node *t = resultNode;
                while(t->next != NULL){
                    t = t->next;
                }
                if(newNode->data > t->data){
                    t->next = newNode;
                    newNode->next = NULL;
                }else{
                    node *p = resultNode;
                    node *tmp;
                    while (newNode->data > p->data) {
                        tmp = p;
                        p = p->next;
                    }
                    newNode->next = tmp->next;
                    tmp->next = newNode;
                }
            }
        }
        l = l->next;
    }
    return resultNode;
}

node *gabung(node *list1, node *list2){
    node *list = list1;
    node *t = list1;
    node *tmp;
    while (t != NULL)
    {
        tmp = t;
        t = t->next;
    }
    tmp->next = list2;
    return list;
}

void cetak(node *l){
    node *p = l;
    while (p != NULL){
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main(){
    node *l1 = new node;
    node *l2 = new node;
    
    int n;
    cout << "Input banyak data : ";
    cin >> n;
    l1 = insertNode(l1, n);
    l2 = insertNode(l2, n);

    node *sortL1 = sortNode(l1);
    node *sortL2 = sortNode(l2);

    cout << "L1 : ";
    cetak(sortL1);
    cout << "L2 : ";
    cetak(sortL2);

    node *l = gabung(sortL1, sortL2);
    l = sortNode(l);

    cout << "L : ";
    cetak(l);

    return 0;
}