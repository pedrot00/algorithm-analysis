#include <iostream>
#include "MyList2.h"
using namespace std;


void testaPushFront() {
  MyList2<char> v;
  cout << v << endl;
  v.push_front('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_front('a'+i);
    cout << v << endl;
  }
}

void testaInsert() {
  int n,numInserts;
  cin >> n >> numInserts;
  MyList2<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }

  cout << "V antes das insercoes: " << endl;
  cout << v << endl;

  //agora vamos fazer os inserts..
  //cada insert e' composto de uma posicao (inteira) e de uma string
  for(int i=0;i<numInserts;i++) {
    int posInsert;
    cin >> posInsert >> st;
    MyList2<string>::iterator it = v.begin();
    for(int i=0;i<posInsert;i++, it++); //faca it apontar para a posicao "posInsert"
    v.insert(st,it);
    cout << "V apos a insercao de " << st << " na posicao " << posInsert << endl;
    cout << v << endl;

    cout << "Elementos em torno de " << st << ":" << endl;    
    if(it!=v.end()) {
      cout << *it << " ";
      it--;
      cout << *it << " ";
      if(it!=v.begin()) {
        it--;
        cout << *it << " ";
      }
    }
    cout << endl << endl;    
  }
}

void testaConstrutoresEtc() {
  MyList2<char> v;
  cout << v << endl;
  v.push_back('a');
  cout << v << endl;  
  for(int i=1;i<10;i++) {
    v.push_back('a'+i);
    cout << v << endl;
  }



  { //testando criacao e destrucao de vetor vazio..
    MyList2<char> v2;
  }

  {
    //copias de vetor vazio
    MyList2<char> v2;
    MyList2<char> v3 = v2; //construtor de copia
    v3 = v2;

    v2 = v;
    v2 = v;
    v3 = v;

    MyList2<char> v4 = v2;
  }

  v.insert('0',v.begin());
  cout << v << endl;

  MyList2<char>::iterator it = v.begin();
  it++;
  ++it;
  it++;
  v.insert('w',it);

  cout << v << endl;

  MyList2<char>::iterator it2 = it;
  it2++;
  while(it2!=v.end()) {
    it++;
    it2++;
  }
  v.insert('z',it);

  cout << v << endl; 


}


void testaSize() {
  MyList2<int> v;
  for(int i=0;i<10;i++) {
    cout << v.size() << "\n";
    v.push_back(i);
  }
}

//Comente abaixo as chamadas das funções que você ainda nao implementou (para poder testar as outras)
void testaEraseMatchingElements() {
  int n, numErase;
  cin >> n >> numErase;
  MyList2<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }

  cout << "Lista: " << endl;
  cout << v << endl;
  for(int i=0;i<numErase;i++) {
      string elemRemover;
      cin >> elemRemover;
      cout << "Removendo: " << elemRemover << endl;
      int numRemoved = v.eraseMatchingElements(elemRemover);
      cout << "Numero de elementos removidos: " << numRemoved << endl;
      cout << "Nova lista: ";
      cout << v << endl;
    }
}

template<class T>
void reverse(typename MyList2<T>::iterator begin, typename MyList2<T>::iterator end) {
    if (begin == end) return;

    int size = 0;
    for (typename MyList2<T>::iterator it = begin; it != end; ++it) {
        ++size;
    }

    if (size <= 1) return;

    T* temp = new T[size];
    int i = 0;

    for (typename MyList2<T>::iterator it = begin; it != end; ++it, ++i) {
        temp[i] = *it;
    }

    i = 0;
    for (typename MyList2<T>::iterator it = begin; it != end; ++it, ++i) {
        *it = temp[size - 1 - i];
    }

    delete[] temp;
}



void testaReverse() {
  int n;
  cin >> n;
  MyList2<string> v; //Realiza testes com strings...
  string st;
  for(int i=0;i<n;i++) {
    cin >> st;
    v.push_back(st);
  }
  cout << "Antes de reverse: " << endl;
  cout << v << endl;
  reverse<string>(v.begin(),v.end());

  cout << "Apos reverse: " << endl;
  cout << v << endl;
}



void printReverse(MyList2<int> &l1) { 
  //nao passamos por referencia constante porque nao nos preocupamos com iteradores constantes
  //na implementacao da classe MyList2 (sem esses iteradores nao podemos iterar em listas constantes,
  //visto que um iterador pode modificar a lista com a operacao de derreferencia)
  MyList2<int>::iterator it = l1.end();
  if(it!=l1.begin()) { //lista nao vazia...
    do {
      it--;
      cout << *it << " ";
    } while(it!=l1.begin());
  }
  cout << endl;
}

void testaDecrementoEnd() {
  cout << "Testando o decremento do iterador end()" << endl;
  MyList2<int> l1;

  for(int i=0;i<6;i++) {
    printReverse(l1);
    l1.push_back(i);
  }

  //e se criarmos um iterador para end() e inserirmos algo antes do end(), o decremento
  //vai acessar o novo valor corretamente?
  MyList2<int>::iterator it = l1.end();
  l1.insert(6,l1.end());
  it--;
  cout << "Isso deve imprimir o numero 6...: " << *it << endl;
  it--;
  cout << "Isso deve imprimir o numero 5...: " << *it << endl;

}




/*
O arquivo de entrada contem um tipo de teste (ou testes com a funcao eraseMatchingElements ou testes com a funcao reverse ou testes mais gerais com a criacao/destruicao de listas)

As listas utilizadas nos testes contem apenas strings. Cada string e' formada apenas por letras e numeros.

A primeira linha do arquivo contem um caractere. 
- Se o caractere for 'I', representa testes com a funcao insert. 
- Se for 'S', entao o arquivo representa testes com a funcao size. 
- Se for 'E', entao o arquivo representa testes com a funcao eraseMatchingElements. 
- Se for 'R' significa testes com a funcao reverse. 
- Se for 'D', significa testes com o decremento do end
- Se nao for nenhum dos anteriores, entao representa testes gerais com push_front, construtores, etc

-----------------
Arquivos de testes gerais, da função size() e de decremento do end():
Sem dados de entrada
-----------------
Arquivos de teste da funcao eraseMatchingElements:
A segunda linha contem dois inteiros o tamanho do vetor inicial e o numero N de chamadas a funcao eraseMatchingElements que serao realizadas
Na terceria linha teremos os elementos do vetor utilizado nos testes
Cada uma das proximas N linhas contem uma string representando o elemento que desejamos remover do vetor
-----------------
Arquivos de teste da funcao reverse:  
A segunda linha contem um numero N representando o numero de elementos a serem inseridos na lista
Na terceira linha ha N strings a serem inseridas na lista (sempre comecamos com uma lista vazia)
-----------------
Arquivos de teste da funcao insert: 
A segunda linha contem dois numeros N e M.
N representa o numero de elementos a serem inseridos na lista inicial
M representa o numero de insercoes posteriores na lista.

A terceira linha contem N strings a serem inseridas na lista inicial
As proximas M linhas contem pares com um inteiro P e uma string S
: P representa a posicao da lista onde S sera inserida (note que a cada nova insercao a lista cresce)
*/



int main() {
  MyList2<string> v; //Realiza testes com strings...
  char tipoTeste;
  cin >> tipoTeste; 

  if(tipoTeste=='E') { //testes com funcao eraseMatchingElements...
    cout << "Testes com eraseMatchingElements" << endl;
    testaEraseMatchingElements();
  } else if(tipoTeste=='R') { //testes com funcao reverse
    cout << "Testes com reverse" << endl;
    testaReverse();
  } else if(tipoTeste=='I') {
    cout << "Testes com insert" << endl;
    testaInsert();
  } else if(tipoTeste=='S') {
    cout << "Testes com size()" << endl;
    testaSize();
  } else if(tipoTeste=='D') {
    cout << "Testes com decremento do end" << endl;
    testaDecrementoEnd();
  } else {
    cout << "Testes gerais" << endl;
    testaPushFront();
    testaConstrutoresEtc();
  }
}

