// Simple library to print graph structures as html file
// by Giovanni M Guidini and Vitor F Dullens

#include <bits/stdc++.h>

using namespace std;

#define HEADER "<!DOCTYPE html>\n<html>\n<body>\n<svg height=\"1000\" width=\"1000\">\n"
#define FOOTER "</svg>\n</body>\n</html>\n"

string addCircle(int cx, int cy){
    return "<circle cx=\"" + to_string(cx) + "\" cy=\"" + to_string(cy) + "\" r=\"20\" stroke=\"white\" stroke-width=\"3\" fill=\"lightgreen\" />\n";
}

string addLine(int x1, int y1, int x2, int y2){
    return "<line x1=\"" + to_string(x1) + "\" y1=\"" + to_string(y1) + "\" x2=\"" + to_string(x2) +
           "\" y2=\"" + to_string(y2) + "\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n";
}

string addText(int x, int y, string text){
    return "<text x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" fill=\"black\">" + text +"</text>\n";
}

void printGraph(vector<int>* G, string file = "out.html"){
    srand(34);
    // open file, add header
    ofstream out (file);
    out << HEADER;
    int l = graphSize();

    // scatter nodes through canvas
    int x[l], y[l];
        for(int i = 0; i < l; i++){
        x[i] = rand() % 960 + 20;
        y[i] = rand() % 960 + 20;
    }

    // add edges to image
    for(int i = 1; i <= l; i++){
        for(auto e : G[i]){
            out << addLine(x[i-1], y[i-1], x[e-1], y[e-1]);
        }
    }

    // add nodes and names
    for(int i = 1; i <= l; i++){
        out << addCircle(x[i-1], y[i-1]) << addText(x[i-1]-5, y[i-1]+5, getID(i));
    }

    out << FOOTER;
    out.close();
    cout << "Image generated as file " + file << endl;
}
