#include <iostream>
#include <map>
#include <string>
#include <numeric>
#include <iomanip>

using namespace std; //pra facilitar

//  usa iteradores
double calcularCRAMedio_Iteradores(const map<string, double>& estudantes) {
    if (estudantes.empty()) return 0.0; // o ponto eh p/ identifcar double
    
    //percorre todo o estudantes depois so divide a soma pela quantidade do size
    double soma = 0.0;
    for (map<string, double>::const_iterator it = estudantes.begin(); 
         it != estudantes.end(); ++it) {
        soma += it->second;
    }
    return soma / estudantes.size();
}

// c/ range-based for usa auto
double calcularCRAMedio_RangeBased(const map<string, double>& estudantes) {
    if (estudantes.empty()) return 0.0;
    
    // percorer estudantes com item somando o valor
    double soma = 0.0;
    for (const auto& item : estudantes) {
        soma += item.second;
    }
    return soma / estudantes.size();
}

// usa structured binding
double calcularCRAMedio_StructuredBinding(const map<string, double>& estudantes) {
    if (estudantes.empty()) return 0.0;
    
    //percorre estudantes mas so vai usar o seugndo elemento
    double soma = 0.0;
    for (const auto& [nome, cra] : estudantes) {
        soma += cra;
    }
    return soma / estudantes.size();
}

// usa accumulate
double calcularCRAMedio_Accumulate(const map<string, double>& estudantes) {
    if (estudantes.empty()) return 0.0;
    
    //acumula de begin a end de 0.0 inicial (p identificar double)
    //lembrar que [](...) eh a utilizacao do lambda
    double soma = accumulate(estudantes.begin(), estudantes.end(), 0.0,
        [](double acumulador, const pair<string, double>& par) {
            return acumulador + par.second;
        });
    
    return soma / estudantes.size();
}

int main() {
    map<string, double> estudantes;
    
    //--------------------------- teste da etapa i1
    estudantes["Ana "] = 8.5;
    estudantes["Bruno "] = 7.2;
    estudantes["Carlos "] = 9.1;
    estudantes["Pedro1 "] = 6.8;
    estudantes["Pedro2 "] = 8.9;
    estudantes["Pedro3 "] = 7.7;
    
    cout << "=== SISTEMA DE CRA ===" << endl << endl;
    
    cout << "estudantes cadastrados:" << endl;
    for (const auto& [nome, cra] : estudantes) {
        cout << "- " << nome << ": " << fixed << setprecision(1) << cra << endl;
    } cout << endl;
    
    cout << "calc do CRA:" << endl;
    cout << fixed << setprecision(2);
    
    cout << "testa iteradores : " 
         << calcularCRAMedio_Iteradores(estudantes) << endl;
    
    cout << "testa Range-based for com auto: " 
         << calcularCRAMedio_RangeBased(estudantes) << endl;
    
    cout << "testa Structured binding: " 
         << calcularCRAMedio_StructuredBinding(estudantes) << endl;
    
    cout << "testa Accumulate: " 
         << calcularCRAMedio_Accumulate(estudantes) << endl;

    //--------------------------- teste da etapa 2





    
    return 0;
}