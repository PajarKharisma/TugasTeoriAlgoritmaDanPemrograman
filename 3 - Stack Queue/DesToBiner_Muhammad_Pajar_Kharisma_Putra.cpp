#include <iostream>
#include <conio.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

struct Stack{
    Node *list;
    
    void init(){
        list = NULL;
    }

    Node *getList(){
        return this->list;
    }

    void push(int data){
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = this->list;
        this->list = newNode;
    }

    int pop(){
        Node *p = this->list;
        int data = p->data;
        this->list = p->next;
        delete p;

        return data;
    }

    bool isEmpty(){
        if (this->list == NULL)
            return true;
        else
            return false;
    }
};

int main(){
    Stack stack;
    stack.init();
    int des;
    cout << "Masukan bilangan desimal : ";
    cin >> des;

    while(des > 0){
        int bin = des % 2;
        stack.push(bin);
        des = des / 2;
    }

    cout << "Bilangan biner : ";
    while(!stack.isEmpty()){
        cout << stack.pop();
    }
    getch();
    return 0;
}