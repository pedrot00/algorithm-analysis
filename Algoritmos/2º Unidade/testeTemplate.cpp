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