#ifndef DS_H_2021
#define DS_H_2021
#include <iostream>
#include <unordered_map>

using namespace std;

struct Representative;

struct Node {
    int element; // guarda o valor do elemento
    Node *next; // ponteiro para o proximo node na lista
    Representative *repr; // ponteiro para o representante
};

struct Representative {
    Node *head; // ponteiro para o primeiro node na lista
    Node *tail; // ponteiro para o ultimo node da lista
    int size; // numero de elementos na lista
};

/* Classe que implementa conjuntos disjuntos usando
   listas encadeadas e heuristica de uniao ponderada */
class DisjointSets {
private:
    unordered_map<int, Node*> nodeAddress; // tabela hash

public:
    /* funcao Make-Set
     * cria um conjunto somente com o elemento 'elem' do tipo int.
     * Um conjunto eh composto por um objeto Representative e um objeto Node.
     * Um par (elem, Node*) deve ser armazenado na tabela hash 'nodeAddress' */
    void makeset(const int& elem);

    /* funcao Find
     * Devolve um ponteiro para o representante de 'elem'
     * A fim de encontrar o Node que contem 'elem', deve ser usada a tabela hash 'nodeAddress' */
    Representative* find(const int& elem);

    /* funcao Union
     * Se 'elem1' e 'elem2' nao estiverem no mesmo conjunto,
     * entao os seus conjuntos serao unidos. Eles terao um mesmo representante.
     * Supoe que esta funcao eh sempre chamada para dois elementos em conjuntos disjuntos
     * Um dos Representative não será mais usado e deve ser deletado */
    void unionSets(const int& elem1, const int& elem2);

    /* funcao printSet
     * imprime na tela todos os elementos que estao no mesmo conjunto que 'elem'
     * no formato: { e1 e2 e3 ... en }
     * onde cada elemento eh separado por espacos em branco */
    void printSet(const int& elem);

    // Destrutor
    ~DisjointSets(){
        /* percorre todos os elementos da tabela hash e libera todos os
         * elementos do tipo Node que foram alocados dinamicamente.
         * A tabela hash em si nao precisa ser liberada ja que ela foi
         * alocada estaticamente pelo proprio compilador. Ele se encarrega de libera-la.
         * Note que essa implementacao tem um problema pois os elementos do tipo
         * Representative nao sao liberados aqui no destrutor. Isso deve ser consertado futuramente */
        for(auto it = nodeAddress.begin(); it != nodeAddress.end(); ++it){
            delete it->second;
        }
    }
};

inline void DisjointSets::makeset(const int &elem){

    Node * conjunto = new Node();
    Representative * representante = new Representative();

    conjunto->element = elem;
    conjunto->next = nullptr;

    representante->head = conjunto;
    representante->tail = conjunto;
    representante->size = 1;

    conjunto->repr = representante;

    nodeAddress.insert(make_pair(elem,conjunto));

}

inline Representative *DisjointSets::find(const int &elem){
    auto par = nodeAddress.find(elem);
    return par->second->repr;
}

inline void DisjointSets::unionSets(const int &elem1, const int &elem2){

    Representative * rep1 = new Representative();
    Representative * rep2 = new Representative();
    Node * node = new Node();

    rep1 = find(elem1);
    rep2 = find(elem2);

    if(rep1 != rep2){
        if(rep1->size >= rep2->size){
            node = rep2->head;
            rep1->size += rep2->size;
            rep1->tail->next = rep2->head;
            rep1->tail = rep2->tail;
            while(node != nullptr){
                node->repr = rep1;
                node = node->next;
            }
            delete rep2;
        }
        else{
            node = rep1->head;
            rep2->size += rep1->size;
            rep2->tail->next = rep1->head;
            rep2->tail = rep1->tail;
            while(node != nullptr){
                node->repr = rep2;
                node = node->next;
            }
            delete rep1;
        }

    }
}

inline void DisjointSets::printSet(const int &elem){
    Representative * representante = find(elem);
    Node * node = new Node();
    node = representante->head;
    cout << "{ ";
    while(node != nullptr){
        cout << node->element << " ";
        node = node->next;
    }
    cout << "}" << endl;
    delete node;
}

#endif
