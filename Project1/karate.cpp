#include <bits/stdc++.h>
#include "gmlParser.h"

using namespace std;

int main(){
	// Variavel para ler o nome do arquivo que contem o grafo
	string file;
	cout << "Input gml file name: ";
	// Le o nome do arquivo
	cin >> file;
	//Tenta ler o arquivo e caso nao exista, encerra o programa
	if (!read(file + ".gml")){
		cout << "System finished" << endl;
		return 0;
	}
}