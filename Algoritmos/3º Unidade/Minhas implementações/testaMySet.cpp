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

    MySet<int>tree2;
    
    typename MySet<int>::iterator it = tree.find(2);
    cout<<"Aqui: " << *it;
    tree2.imprimeBFS();
    std::cout<<std::endl;

    tree2.imprimeDFS_in();
    std::cout<<std::endl;

    tree2.imprimeDFS_pos();
    std::cout<<std::endl;

    tree2.imprimeDFS_pre();
    std::cout<<std::endl;
    

    //testanto iteradores
    std::cout <<"Imprime iteradores ";
    for( MySet<int>::iterator it = tree.begin(); it!= tree.end(); it++){
        std::cout << *it <<" ";
    }



    return 0;
}