#include<iostream>
#include "MySet.h"


int main(){
   // typename MySet<int>::iterator it;
    MySet<int> tree;

    tree.insert(8);
    tree.insert(9);
    tree.insert(2);
    tree.insert(7);
    tree.insert(10);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(1);
    tree.insert(6);

    
    for(MySet<int>::iterator it= tree.begin(); it!=tree.end(); it++){
        std:: cout << *it << " "; 
    }

    return 0;
}