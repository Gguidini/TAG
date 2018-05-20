#include <bits/stdc++.h>
#include "dataDef.hpp"
#include "parser.hpp"

using namespace std;

void matchMaker(Professor* p, Escola* e){
    int t = e->isFree(); // schools can have more than 1 job opening
    // school matched
    // cout << "T: " << t << endl; // DEBUG
    e->setMatch(t, p);
    // professor matched
    if(!p->isFree()){
        // cout << "Freeing some school.\nBefore: " << (p->getMatch()) << endl; // DEBUG
        Escola* prev = p->getMatch();
        prev->setFree(p);
        // cout << "After: " << prev << endl; // DEBUG
    }
    p->setMatch(e);
}

bool isPreferred(Professor* p, Escola* e){
    return find(p->pref.begin(), p->pref.end(), e->getCode()) < find(p->pref.begin(), p->pref.end(), p->getMatch()->getCode()) ;
}

bool possibleMatch(Professor* p, Escola* e){
    if(p->isFree()){
        return true;
    }
    // checks if current school is before in teacher's preference list
    else if( isPreferred(p, e)){
        return true;
    }
    return false;
}

int lowerBound(vector<Professor*> v, int low, int high, int need, int asw){
    int mid = (low+high)/2;
    if (low > high)
        return asw;
    else if (v[mid]->getHab() == need)
        return lowerBound(v, low, mid-1, need, mid);
    else if (v[mid]->getHab() > need)
        return lowerBound(v, low, mid-1, need, asw);
    else
        return lowerBound(v, mid+1, high, need, asw);
}

void merge(vector<Professor*>& p, int low, int mid, int high){
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 =  high - mid;
    /* create temp arrays */
    Professor* L[n1];
    Professor* R[n2];
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = p[low + i];
    for (j = 0; j < n2; j++)
        R[j] = p[mid + 1+ j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = low; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (isSmaller(L[i], R[j])){
            p[k] = L[i];
            i++;
        }
        else{
            p[k] = R[j];
            j++;
        }
        k++;
    }
    // possible remaining elements
    while (i < n1){
        p[k] = L[i];
        i++;
        k++;
    }
    // possible remaining elements
    while (j < n2){
        p[k] = R[j];
        j++;
        k++;
    }  
}

void mergeSort(vector<Professor*>& p, int low, int high){
    if(low >= high)
        return;
    int mid = (low + high)/2;
    mergeSort(p, low, mid);
    mergeSort(p, mid+1, high);
    merge(p, low, mid, high);
}

void matchOptimalForSchools(){
    vector<Professor*> p = Parser::getTeachers();
    mergeSort(p, 0, p.size()-1);
    vector<Escola*> e = Parser::getSchools();
    queue<Escola*> Q;
    vector<bool> isInQueue(50);
    // initially, everyone is free
    for(auto v : e){
        // cout << v << endl; // DEBUG
        Q.push(v);
        isInQueue[v->getCode()] = true;
    }
    // cout << "entering main loop\n"; // DEBUG
    while(!Q.empty()){
        Escola* curr = Q.front(); Q.pop();
        isInQueue[curr->getCode()] = false;
        // cout << "Curr: " << curr << endl; // DEBUG
        // first index with professor with desired habilitation
        int idx = lowerBound(p, 0, p.size()-1, curr->getNeed(), -1);
        // cout << "LowerBound Result: " << idx << endl; // DEBUG
        int it = idx;
        int n = p.size();
        bool matchDone = false;
        // run through all professors with habilitation >= desired
        while(it != -1 && it < n){
            // didn't try the teacher?
            if(!curr->tried(p[it]->getCode())){
                curr->setTry(p[it]->getCode());
                if(possibleMatch(p[it], curr)){
                    if(!p[it]->isFree()) // if there was a previous match
                        if(!isInQueue[p[it]->getMatch()->getCode()]){ // and School is not in queue
                            // cout << "Pushing back to queue: " << p[it]->getMatch() << endl; // DEBUG
                            Q.push(p[it]->getMatch()); // returns previously match to queue
                            isInQueue[p[it]->getMatch()->getCode()] = true;
                        }
                    matchMaker(p[it], curr);
                    if(curr->isFree() != -1){
                        Q.push(curr);
                        isInQueue[curr->getCode()] = true;
                    }
                    matchDone = true;
                    break;
                }  
                it++;
            }
            else{
                it++;
            }  
        }
        // in case no suitable professor was found, look for professors with habilitations < desired
        if(!matchDone){
            cout << "Going for the leftovers with " << curr << endl;
            int it = 0;
            while(it < idx){
                if(!curr->tried(p[it]->getCode())){
                    curr->setTry(p[it]->getCode());
                    if(possibleMatch(p[it], curr)){
                        if(!p[it]->isFree()) // if there was a previous match
                            if(!isInQueue[p[it]->getMatch()->getCode()]){ // and School is not in queue
                            Q.push(p[it]->getMatch()); // returns previously match to queue
                            isInQueue[p[it]->getMatch()->getCode()] = true;
                        }
                        cout << "Matching " << curr << " to leftover " << p[it] << endl;
                        matchMaker(p[it], curr);
                        if(curr->isFree() != -1){
                            Q.push(curr);
                            isInQueue[curr->getCode()] = true;
                        }
                        break;
                    }  
                }
                else{
                    it++;
                }  
            }
        }
    }
}

int main(){
    string file = "entradaProj3TAG.txt";
    // populate graph
    Parser::readFile(file);
    // MATCH teachers and schools
    matchOptimalForSchools();
    // Results?
    Parser::checkRead();

}