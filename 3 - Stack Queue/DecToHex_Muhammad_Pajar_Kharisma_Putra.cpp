#include <iostream>
#include <conio.h>
using namespace std;

struct Node{
    char data;
    Node *next;
};

//STRUKTUR STACK
struct Stack{
  private:
    Node *list;

  public:
    //FUNGSI INITIALIZE SEPERTI CONSTRUCTOR
    void init(){
        list = NULL;
    }

    //GETER UNTUK MENDAPATKAN LIST KARENA OBJECT LIST DISET PRIVATE
    Node *getList(){
        return this->list;
    }

    //FUNGSI PUSH
    void push(char data){
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = this->list;
        this->list = newNode;
    }

    //FUNGSI POP
    char pop(){
        Node *p = this->list;
        char data = p->data;
        this->list = p->next;
        delete p;

        return data;
    }

    //FUNGSI MENGECEK STACK KOSONG ATAU TIDAK
    bool isEmpty(){
        if (this->list == NULL)
            return true;
        else
            return false;
    }
};

int main(){
    cout << "MUHAMMAD PAJAR KHARISMA PUTRA" << endl << endl;
    Stack stack;
    stack.init();
    
    int des;
    cout << "Masukan bilangan desimal : ";
    cin >> des;

    while(des > 0){
        int res = des % 16;
        char hex;
        (res < 10) ? hex = res + 48 : hex = res + 55;
        
        stack.push(hex);
        des = des / 16;
    }

    cout << "Bilangan Hexadesimal : ";
    while(!stack.isEmpty()){
        cout << stack.pop();
    }
    getch();
    return 0;
}