#ifndef MODEL_CIRCUIT_H
#define MODEL_CIRCUIT_H

#include "position.h"
#include <iostream>
#include <vector>
  
using namespace std;

class ModelCircuit {
public:
    ModelCircuit();

    Position getStart();
    void setStart(Position pStart);

    bool positionIsActive(Position);

    void generateBorders();

    friend istream& operator>>(istream&, ModelCircuit&);
    friend ostream& operator<<(ostream&, const ModelCircuit&);
private:
    vector<vector<int>> positions;
    bool bordersGenerated = false;
    Position startingPoint;
};


#endif