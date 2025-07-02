#include<iostream>
#include "MySet.h"


int main(){
   // typename MySet<int>::iterator it;
    MySet<int> tree;

    tree.insert(15);
    tree.insert(30);
    tree.insert(32);
    tree.insert(12);
    tree.insert(13);

    
    std::cout<< "POS INCREMENTO:" <<std::endl;
    for(MySet<int>::iterator it= tree.begin(); it!=tree.end(); ++it){
        std:: cout << *it << " "; 
    }
    std::cout<<'\n';
    std::cout<< "PRE INCREMENTO:" <<std::endl;
    for(MySet<int>::iterator it= tree.begin(); it!=tree.end();it++){
        std:: cout << *it << " "; 
    }

    return 0;
}