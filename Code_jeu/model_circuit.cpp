#include "model_circuit.h"



ModelCircuit::ModelCircuit(){
    startingPoint = Position{ 0, 0, 0 };
    name = "Circuit par défaut";
}

Position ModelCircuit::getStart() {
    return startingPoint;
}

/**
 * Retourne vrai si la position est sur la route
 */
bool ModelCircuit::positionIsActive(Position position){
    return (positions[position.x][position.y] == 1);
}


/**
 * Génère les bordures de la map en fonction des positions actives.
 * Les bordures sont représentés dans le tableau par le chifre 2
 */
void ModelCircuit::generateBorders(){
    
    for (int x = 1; x < (positions.size() - 1); x++) {
        for (int y = 1; y < (positions[x].size() - 1); y++) {
            if (positions[x][y] == 1) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (positions[x + dx][y + dy] == 0) {
                            positions[x + dx][y + dy] = 2;
                        }
                    }
                }
            }
        }
    }
    bordersGenerated = true;
}

/**
 * Retourne le nom de la map
 */
string ModelCircuit::getName(){
    return name;
}

/**
 * Lit une map à partir d'un fichier
 * 
 * 1 = piste, 0 = hors piste
 */
istream& operator>>(istream& i, ModelCircuit& c) {
    Position currentPos;

    int width;
    int height;
    i >> width >> height;

    c.positions.clear();
    c.bordersGenerated = false;

    for (int x = 0; x < width; x++) {
        c.positions.push_back(vector<int>());
        for (int y = 0; y < height; y++) {
            i >> c.positions[x][y];
            if (c.positions[x][y] == 3) { //Si la case est la starting position
                c.startingPoint = Position{x, y, 0};
            }
        }
    }
    
    return i;
}

/**
 * Affiche une map dans un ostream.
 * 
 * Bien s'assurer de généré les borders avant
 */
ostream& operator<<(ostream& o, const ModelCircuit& c) {

    for (int x = 0; x < c.positions.size(); x++) {
        for (int y = 0; y < c.positions[x].size(); y++) {
            if (c.positions[x][y] == 2) {
                o << "x";
            } else {
                o << " ";
            }
        }
        o << endl;
    }
    
    return o;
}