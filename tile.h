#ifndef TILE_H
#define TILE_H

class Tile {
private:
    char type;

public:
    Tile() {}
    void setType(char);
    char getType();
};

void Tile::setType(char xtype) {
    type = xtype;
}

char Tile::getType() {
    return type;
}


#endif