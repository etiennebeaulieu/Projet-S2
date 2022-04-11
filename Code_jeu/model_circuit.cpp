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
    return (positions[position.y][position.x] == PARCOUR);
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
    
    for (int x = 1; x < (positions.size() - 1); x++) {
        for (int y = 1; y < (positions[x].size() - 1); y++) {
            if (positions[x][y] == PARCOUR) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (positions[x + dx][y + dy] == VIDE) {
                            positions[x + dx][y + dy] = BORDURE;
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

    for (float x = 0; x < width; x++) {
        c.positions.push_back(std::vector<int>());
        c.positions[x].resize(height);
        for (float y = 0; y < height; y++) {
            i >> c.positions[x][y];
            if (c.positions[x][y] == STARTPOSITION) { //Si la case est la starting position
                c.startingPoint = Position{y, x, 0};
                c.positions[x][y] = PARCOUR;
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

    for (int x = 0; x < c.positions.size(); x++) {
        for (int y = 0; y < c.positions[x].size(); y++) {
            if (c.positions[x][y] == BORDURE) {
                o << "x ";
            } else {
                o << "  ";
            }
        }
        o << std::endl;
    }
    
    return o;
}