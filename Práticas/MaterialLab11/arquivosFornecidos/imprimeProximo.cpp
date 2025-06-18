#include "MySet.h"
#include <iostream>

int main(){
    MySet<int> banco;
    char operacao;
    int n;

    while(std::cin >> operacao >> n){
        if(operacao == 'C'){
            banco.insert(n);
        }
        else if(operacao == 'S'){
            MySet<int>::iterator it = banco.find(n);
            
            if(it != banco.end()){
                // n no banco, busca o próximo
                ++it;
                if(it != banco.end()){
                    std::cout << *it << std::endl;
                }
                else { 
                    std::cout << "FALHA" << std::endl;
                }
            }
            else{
                // n fora do banco, busca o primeiro > n
                MySet<int>::iterator t1 = banco.begin();
                while(t1 != banco.end() && *t1 <= n){ 
                    ++t1; 
                }
                if(t1 != banco.end()){  
                    std::cout << *t1 << std::endl; 
                }
                else{
                    std::cout << "FALHA" << std::endl;
                }
            }
        }
    }

    return 0;
}