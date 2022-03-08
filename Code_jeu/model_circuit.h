#ifndef MODEL_CIRCUIT_H
#define MODEL_CIRCUIT_H

#include <string>
#include "position.h"
#include <iostream>
#include <vector>
#include <fstream>



#define VIDE = 0;
#define PARCOUR = 1;
#define BORDURE = 2;
#define STARTPOSITION = 3;
  

class ModelCircuit {
public:
    ModelCircuit();
    ModelCircuit(std::string name);

    Position getStart();

    bool positionIsActive(Position);

    void generateBorders();

    std::string getName();

    void setWidth(int pWidth);
    int getWidth();
    void setHeight(int pHeight);
    int getHeight();

    friend std::istream& operator>>(std::istream&, ModelCircuit&);
    friend std::ostream& operator<<(std::ostream&, const ModelCircuit&);
private:
    std::vector<std::vector<int>> positions;
    bool bordersGenerated = false;
    Position startingPoint;
    std::string name;
    int width;
    int height;
};


#endif