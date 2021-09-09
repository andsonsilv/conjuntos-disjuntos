#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DisjointSets.h"

using namespace std;

int main(){

    DisjointSets p;

    while(1){

        string line, word;
        getline(cin, line);
        stringstream ss { line };
        vector<string> tokens;

        while(ss >> word)
            tokens.push_back(word);

        // exit
        if(tokens[0] == "exit"){
            cout << "saindo ..." << endl;
            break;
        }
        // makeset e1 e2 ... en
        else if(tokens[0] == "makeset"){
            for(size_t i = 1; i < tokens.size(); ++i)
                p.makeset( std::stoi(tokens[i]) );
        }
        // find e1 e2
        else if(tokens[0] == "find"){
            int e1 = std::stoi(tokens[1]);
            int e2 = std::stoi(tokens[2]);
            if(p.find(e1) == p.find(e2))
                cout << e1 << " e " << e2 << " estao no mesmo conjunto" << endl;
            else
                cout << e1 << " e " << e2 << " estao em conjuntos disjuntos" << endl;
        }
        // union e1 e2
        else if(tokens[0] == "union"){
            int e1 = std::stoi(tokens[1]);
            int e2 = std::stoi(tokens[2]);
            p.unionSets(e1,e2);
        }
        // print e
        else if(tokens[0] == "print"){
            int e = std::stoi(tokens[1]);
            p.printSet(e);
            cout << endl;
        }
        else{
            cout << "comando inexistente" << endl;
        }
    }

    return 0;
}
