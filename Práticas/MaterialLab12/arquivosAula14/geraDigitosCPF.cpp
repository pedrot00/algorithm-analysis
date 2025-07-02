#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        string cpf;
        cin >> cpf;
        
        int soma1 = 0;
        for (int j = 0; j < 9; j++) {
            int digito = cpf[j] - '0'; 
            soma1 += digito * (10 - j); 
        }
        
        int primeiro_digito = (soma1 * 10) % 11;
        if (primeiro_digito == 10) {
            primeiro_digito = 0;
        }
        
        int soma2 = 0;
        for (int j = 0; j < 9; j++) {
            int digito = cpf[j] - '0';
            soma2 += digito * (11 - j);
        }
        soma2 += primeiro_digito * 2;
        
        int segundo_digito = (soma2 * 10) % 11;
        if (segundo_digito == 10) {
            segundo_digito = 0;
        }
        cout << primeiro_digito << segundo_digito << endl;
    }
    
    return 0;
}