#include "MyVecNewIterator.h"
#include "MyList2NewIterator.h"
#include <utility>
#include <exception>
#include <iostream>

const int TABLE_SIZE = 20;

template <class KEY, class VALUE, class HASH>
class MyHashMap{
private:
    template<typename T>
    using MyVec = MyVec<T>;  
    template<typename T>
    using MyList = MyList2<T>;  

    //atributos
    MyVec<MyList<std::pair<KEY, VALUE>>> table;
    int numElem;
    HASH funcaoHash;

public:
    MyHashMap();
    void set(const KEY &k, const VALUE &v);
    int count(const KEY &k) const;
    VALUE &getValue(const KEY &k);
    int size(){return TABLE_SIZE;}

    void imprime();
};

template <class KEY, class VALUE, class HASH>
MyHashMap<KEY, VALUE, HASH>::MyHashMap(){
    numElem = 0;
    table.resize(TABLE_SIZE);
}

template<class KEY, class VALUE, class HASH>
void MyHashMap<KEY, VALUE, HASH>::imprime(){
    std::cout<<"Size: " << size() << std::endl;
    for(int i = 0; i < size(); i++){
        std::cout << "Bucket " << i << ": ";
        
        for(typename MyList<std::pair<KEY, VALUE>>::iterator it = table[i].begin();
            it != table[i].end(); ++it){
            std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
        }
        std::cout << std::endl;
    }    
}

template <class KEY, class VALUE, class HASH>
void MyHashMap<KEY, VALUE, HASH>::set(const KEY &key, const VALUE &val){
    int pos = funcaoHash(key) % TABLE_SIZE;
    
    for(typename MyList<std::pair<KEY,VALUE>>::iterator it = table[pos].begin();
        it != table[pos].end(); ++it){
        if((*it).first == key){
            (*it).second = val;
            return;
        } 
    }
    
    table[pos].push_back(std::pair<KEY, VALUE>(key, val));
    numElem++;
}

template<class KEY, class VALUE, class HASH>
int MyHashMap<KEY, VALUE, HASH>::count(const KEY &key) const{
    int pos = funcaoHash(key) % TABLE_SIZE;

    for(typename MyList<std::pair<KEY, VALUE>>::iterator it = table[pos].begin();
        it != table[pos].end(); ++it){
        if((*it).first == key) return 1;
    }
    return 0;
}

template<class KEY, class VALUE, class HASH>
VALUE& MyHashMap<KEY, VALUE, HASH>::getValue(const KEY &key){
    int pos = funcaoHash(key) % TABLE_SIZE;
    
    for(typename MyList<std::pair<KEY, VALUE>>::iterator it = table[pos].begin();
        it != table[pos].end(); ++it){
        if ((*it).first == key) return (*it).second;
    }
    throw std::runtime_error("Chave não encontrada na HashMap.");
}