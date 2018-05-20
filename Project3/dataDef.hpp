#include <bits/stdc++.h>

#ifndef _DATADEF_H
#define _DATADEF_H

class Professor;

// Schools have a code, a preference for teacher's habilitations (need),
// a number of job openings (jobs), and may or may not have been assigned a teacher.
class Escola{
    int code;
    int need;
    int jobs;
    std::vector<bool> matched;
    std::vector<Professor*> matches;
   std::set<int> attempts; // the professors it proposed to

public:
    Escola(int c, int n, int j){
        code = c;
        need = n;
        jobs = j;
        matched.clear();
        matches.clear();
        attempts.clear();
        matched.push_back(false);
        if(j == 1)
            matched.push_back(true);
        else
            matched.push_back(false);
        matches.push_back(NULL);
        matches.push_back(NULL);
    }

    int getCode(){
        return code;
    }
    int getNeed(){
        return need;
    }
    int getJobs(){
        return jobs;
    }
    // index at which school is free. -1 if it's not.
    int isFree(){
        if(!matched[0])
            return 0;
        if(!matched[1])
            return 1;
        return -1;
    }

    void setMatch(int idx, Professor* match){
        matched[idx] = true;
        matches[idx] = match;
    }

    void setTry(int i){
        attempts.insert(i);
    }

    void setFree(Professor* p){
        if(matches[0] == p){
            matches[0] = NULL;
            matched[0] = false;
        }
        else if(matches[1] == p){
            matches[1] = NULL;
            matched[1] = false;            
        }
    }

    bool tried(int idx){
        return attempts.count(idx);
    }

    std::vector<Professor*> getMatches(){
        return matches;
    }
};

// Teachers have a code, a number of habilitations (hab),
// and a list of preferences (pref)
class Professor {
    int code;
    int hab;
    bool matched;
    Escola* match;

public:
    std::vector<int> pref;

    Professor(int c, int h, std::vector<int> p){
        code = c;
        hab = h;
        pref = p;
        matched = false;
        match = NULL;
    }

    bool isFree(){
        return !matched;
    }

    int getCode(){
        return code;
    }

    int getHab(){
        return hab;
    }

    Escola* getMatch(){
        return match;
    }

    void setMatch(Escola* e){
        matched = true;
        match = e;
    }

    bool operator<(Professor& other){
        if (hab == other.hab){
            if (!matched)
                return true;
        else if(!other.matched)
                return false;
        else
            return code < other.code;
        }
        else
            return hab < other.hab;
    }
};

std::ostream& operator<<(std::ostream& os, Professor* p){  
    os << "P" << p->getCode() << "-" << p->getHab() << " preferences: {";
    for(auto e : p->pref){
        os << e << " ";
    }  
    os << "}\tMatched:" << !p->isFree();
    if(!p->isFree())
        os << " to E" << p->getMatch()->getCode();
    return os;  
}  

std::ostream& operator<<(std::ostream& os, Escola* e){
    os << "E" << e->getCode() << "- Quer: " << e->getNeed() << " Vagas: " << e->getJobs();
    os << "\tMatched:" << e->isFree();
    if(e->isFree() == -1){
        os << " to P" << e->getMatches()[0]->getCode() << " (" << e->getMatches()[0]->getHab() << " habs)";
        if(e->getJobs() == 2)
            os << " and P" << e->getMatches()[1]->getCode() << " (" << e->getMatches()[1]->getHab() << " habs)";
    }

    return os;
}

bool isSmaller(Professor* lhs, Professor* rhs){
    if (lhs->getHab() == rhs->getHab()){
        if (lhs->isFree())
            return true;
        else if(rhs->isFree())
            return false;
        else
            return lhs->getCode() < rhs->getCode();
    }
    else
        return lhs->getHab() < rhs->getHab();

}
#endif