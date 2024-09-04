/** 
 * CS451: Artificial Intelligence
 * Assignment #1 
 * Tyler Cady
 * 09.03.24
 */ 



#include <iostream>
#include <stack>
#include <queue>
#include <vector> 

using std::string; 



/* PCP Problem */

/**
 * State             : 
 * Initial State     :
 * Goal Test         : 
 * Successor Function:
 */

/* Data Structures */
struct domino {
    string top; // top string 
    string bot; // bottom string 
};

struct city {
    string place; 
    char first;
    char last;
};

/* Constructors */
city new_city(string place) {
    city c1;
    c1.place = place;
    c1.first = place[0];
    c1.last = place[place.length()];
    return c1;
}
domino new_dom(string top, string bot){
    domino d;
    d.top = top;
    d.bot = bot;
    return d;
}

vector to_cities(string places[]){
    vector <city> temp;
    for (int i = 0; i < sizeof(places); i++){
        city t1 = new_city(places[i]);
        temp.push_back(t1);
    }
}

/* Search Algorithms */
//depth-first search
void dfs(){
    
}

// //bredth-first search
void bfs(){

}

int main(){
    //Test Cases 
    string g1[7] = {"ABC", "CDE", "CFG", "EHE", "EIJ", "GHK", "GLC"}; 
    string g2[6] = {"ABC", "CDE", "CFG", "EHI", "GJC", "GKG"};
    vector <city> gc1 = to_cities(g1);
    vector <city> gc2 = to_cities(g2);
    
}