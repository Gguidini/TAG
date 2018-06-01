#include <bits/stdc++.h>
#include "dataDef.hpp"
# define ESC 0x1b

using namespace std;

char GREEN[] = { ESC, '[', '1', ';', '3', '2', 'm', 0 };
char YELLOW[] = { ESC, '[', '1', ';', '3', '3', 'm', 0 };
char NORMAL[] = { ESC, '[', '0', ';', '3', '9', 'm', 0 };

namespace Parser {
    // regex for reading file
    regex escola ("\\(E(\\d+)\\):\\(([\\d])\\):\\((\\d)\\)");
    regex professor ("\\(P(\\d+), (\\d)\\): \\(E(\\d+), E(\\d+), E(\\d+), E(\\d+), E(\\d+)\\)\\s*");

    // groups of the graph
    vector<Professor*> profs;
    vector<Escola*> escolas;

    vector<Professor*> getTeachers(){
        return profs;
    }

    vector<Escola*> getSchools(){
        return escolas;
    }

    void readFile(string fileName){
        ifstream fd (fileName);
        if(!fd){
            cout << "File " << fileName << " not found. Did you add extension?\n";
            exit(1);
        }
        cout << GREEN << "==>" << NORMAL << " Reading file...";
        string line;
        std::smatch sm; // store capturing groups
        while(getline(fd, line)){
            // professor
            if(regex_match(line ,sm, professor)){
                int c = stoi(sm[1]);
                int h = stoi(sm[2]);
                vector<int> e(5);
                for(int i = 3; i < 8; i++){
                    e[i-3] = stoi(sm[i]);
                }
                Professor* p = new Professor(c, h, e);
                profs.push_back(p);
            }
            // escola
            else if(regex_match(line ,sm, escola)){
                int c = stoi(sm[1]);
                int n = stoi(sm[2]);
                int j = stoi(sm[3]);

                Escola* e = new Escola(c, n, j);
                escolas.push_back(e);
            }
        }
        cout <<"Done.\n";
        cout << "[ " << GREEN << profs.size() << NORMAL << " ] Professores\n";
        cout << "[ " << GREEN << escolas.size() << NORMAL << " ] Escolas\n";
    } 

    void checkRead(){
        cout << YELLOW << "Professores:\n" << NORMAL;

        vector<Professor*> p = getTeachers();
        for(auto v : p){
            cout << v << endl;
        }

        cout << YELLOW << "Escolas:\n" << NORMAL;
        vector<Escola*> e = getSchools();
        for(auto v: e){
            cout << v << endl;
        }
    }
}