#include <iostream>

using namespace std;


// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
//#include "MyStack.h"


#include "MyQueue.h"  
#include "MyStack.h"
#include "string.h"

void etapa1() {
    MyQueue<int> fila;
    MyStack<int> pilha; 

    for (int i = 0; i < 6; i++) {
        int num;
        std::cin >> num;
        fila.push(num);
        pilha.push(num);
    }

    while (!pilha.empty()) {
        std::cout << pilha.top() << " ";
        pilha.pop();
    }
    std::cout << std::endl;

    while (!fila.empty()) {
        std::cout << fila.front() << " "; 
        fila.pop();
    }
    std::cout << std::endl;
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2() {
    string str;
    MyStack<char> stack;
    
    getline(cin, str);
    
    for (int i = 0; i < str.length(); i++) { 
        char c = str[i];
        if (c == '{' || c == '(' || c == '[') {
            stack.push(c);
        }
        else if (c == '}' || c == ')' || c == ']') {
            if (stack.empty()) {
                cout << "Inconsistente" << endl << endl;
                return;
            }
            
            char top = stack.top();
            stack.pop();
            
            if ((c == '}' && top != '{') || 
                (c == ')' && top != '(') || 
                (c == ']' && top != '[')) {
                cout << "Inconsistente" << endl << endl;
                return;
            }
        }
    }
    
    cout << (stack.empty() ? "Consistente" : "Inconsistente") << endl << endl;
}

//---------------------------------------

// Insira aqui o codigo para a etapa 3....


//#include "MedianaLenta.h" //use essa implementacao para fazer os primeiros testes (com o calculo lento da mediana...)
//#include "Mediana.h" //descomente esta linha para utilizar sua classe mais eficiente!
void etapa3() {
	//descomente o codigo abaixo ao fazer a etapa 3
	/*Mediana mediana;

	int n,elem;	
	cin >> n;
	for(int i=0;i<n;i++) {
		cin >> elem;
		mediana.insere(elem);
		cout << mediana.getMediana() << " ";
	}
	cout << endl;*/
}

//---------------------------------------




int main() {
	int etapa;
	cin >> etapa;
	switch(etapa) {
		case 1:
			cout << "Etapa 1" << endl;
			etapa1();
			break;
		case 2:
			cout << "Etapa 2" << endl;
			etapa2();
			break;
		case 3:
			cout << "Etapa 3" << endl;
			etapa3();
			break;
	}
}