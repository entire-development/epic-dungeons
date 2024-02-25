#pragma once
#include <vector>
#include "events/event.h"

typedef std::pair<int, int> Position;

class Cell;
class Room;
class Corridor;

class Cell
{

public:
    Cell(Position position);
    Event *get_event() const { return _event; }
    Position get_position() const { return _position; }
private:
    Event *_event = nullptr;
    Position _position;
};


class Corridor
{
public:
    // Room -> {Cell -> ... -> Cell} -> Room  
    Corridor(Room *room1, std::vector<Cell *> cells, Room *room2);
    // Room -> Cell -> ... -> Cell -> Room
    Corridor(std::Vector<Cell *> cells);
    Room* other_side(Room *room);
    Cell* next_cell(Cell *current, Room* target_room);

private:
    std::vector<Cell *> _cells; // Room->Cell->...->Cell->Room
};

class Room : public Cell {
public:
    Room(Position position);

    std::vector<Room *> get_neighbours() const;

    private:
        std::vector<Corridor *> _corridors;
};
