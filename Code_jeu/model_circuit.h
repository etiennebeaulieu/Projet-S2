#ifndef MODEL_CIRCUIT_H
#define MODEL_CIRCUIT_H

#include <string>
#include "position.h"
#include <iostream>
#include <vector>

using namespace std;

#define VIDE 0
#define PARCOUR 1
#define BORDURE 2
#define STARTPOSITION 3
  
using namespace std;

class ModelCircuit {
public:
    ModelCircuit();
    ModelCircuit(string name);

    Position getStart();

    bool positionIsActive(Position);

    void generateBorders();

    string getName();

    friend istream& operator>>(istream&, ModelCircuit&);
    friend ostream& operator<<(ostream&, const ModelCircuit&);
private:
    vector<vector<int>> positions;
    bool bordersGenerated = false;
    Position startingPoint;
    string name;
};


#endif