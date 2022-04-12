#include "model_circuit.h"

ModelCircuit::ModelCircuit(){
    startingPoint = Position{ 0, 0, 0 };
    name = "Circuit par défaut";
}

ModelCircuit::ModelCircuit(std::string name) : ModelCircuit() {
    this->name = name;
}

Position ModelCircuit::getStart() {
    return startingPoint;
}

/**
 * Retourne vrai si la position est sur la route
 */
bool ModelCircuit::positionIsActive(Position position) {
    return (positions[position.y][position.x] == PARCOUR || positions[position.y][position.x] == LIGNEARRIVE || positions[position.y][position.x] == STARTPOSITION);
}

/**
 * Retourne vrai si la position est sur la ligne d'arrivé  
 */
bool ModelCircuit::positionIsOnFinishLine(Position position) {
    return (positions[position.y][position.x] == LIGNEARRIVE);
}


/**
 * Génère les bordures de la map en fonction des positions actives.
 * Les bordures sont représentés dans le tableau par le chifre 2
 */
void ModelCircuit::generateBorders(){
    
    for (int y = 1; y < (positions.size() - 1); y++) {
        for (int x = 1; x < (positions[y].size() - 1); x++) {
            if (positionIsActive(Position{ x, y, 0 })) {
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (positions[y + dy][x + dx] == VIDE) {
                            positions[y + dy][x + dx] = BORDURE;
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
std::string ModelCircuit::getName(){
    return name;
}

void ModelCircuit::setWidth(int pWidth)
{
    width = pWidth;
}

int ModelCircuit::getWidth()
{
    return width;
}

void ModelCircuit::setHeight(int pHeight)
{
    height = pHeight;
}

int ModelCircuit::getHeight()
{
    return height;
}

/**
 * Lit une map à partir d'un fichier
 * 
 * 0 = hors piste, 1 = piste, 2 = bordure, 3 = point de départ, 4 = ligne d'arrivé
 */
std::istream& operator>>(std::istream& i, ModelCircuit& c) {
    int width;
    int height;
    i >> width >> height;
    c.setWidth(width);
    c.setHeight(height);
    c.positions.resize(width);

    c.positions.clear();
    c.bordersGenerated = false;

    for (int y = 0; y < height; y++) {
        c.positions.push_back(std::vector<int>());
        c.positions[y].resize(width);
        for (int x = 0; x < width; x++) {
            i >> c.positions[y][x];
            if (c.positions[y][x] == STARTPOSITION) { //Si la case est la starting position
                c.startingPoint = Position{x, y, 0};
                c.positions[y][x] = PARCOUR;
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
std::ostream& operator<<(std::ostream& o, const ModelCircuit& c) {

    for (int y = 0; y < c.positions.size(); y++) {
        for (int x = 0; y < c.positions[y].size(); x++) {
            if (c.positions[y][x] == BORDURE) {
                o << "x ";
            } else {
                o << "  ";
            }
        }
        o << std::endl;
    }
    
    return o;
}