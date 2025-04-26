/* Questao 1
using namespace std;
#include<iostream>
#include <string>

template <typename T>
T maximo(T a, T b){
    return (a < b ) ? b: a;
}


int main(){
    int a = 2, b = 5;
    float c = 3.4, d = 23.4;
    string e = "teste2", f = "teste1";

    cout << maximo(a, b) << endl;
    cout << maximo(c, d) << endl;
    cout << maximo(e, f) << endl;
    return 0;
}
*/


/* Questao 2
#include <string>
template <class T>

class Array{
public:
    T get(int pos) { return v[pos];}
    void set(int pos, T valor) { v[pos] = valor;}
private:
    T v[10];
};


void exemplo(){
    Array<int> a; // cria array de inteiros usando template
    Array<char> b; // cria array de char usando template
    // ...
} 

*/
/*
#include<iostream>
#include "MyVec.h"
using namespace std;

int main() {
    MyVec<int> v;

    std::cout << "Inserindo elementos...\n";
    for (int i = 1; i <= 5; ++i) {
        v.push_back(i * 10);
        std::cout << v << "\n";
    }

    std::cout << "\nRemovendo um elemento com pop_back:\n";
    v.pop_back();
    std::cout << v << "\n";

    std::cout << "\nRedimensionando com fill (resize(8, 99)):\n";
    v.resize(8, 99);
    std::cout << v << "\n";

    std::cout << "\nRedimensionando para menor (resize(3)):\n";
    v.resize(3);
    std::cout << v << "\n";

    std::cout << "\nCriando vetor inicializado com 4 elementos 7:\n";
    MyVec<int> w(4, 7);
    std::cout << w << "\n";

    std::cout << "\nAcessando elementos com operador []:\n";
    for (int i = 0; i < w.size(); ++i) {
        std::cout << "w[" << i << "] = " << w[i] << "\n";
    }

    return 0;
}
*/