#include "TetVertex.h"

TetVertex::TetVertex(int id, Point& pos, const std::string& property)
: m_id(id), m_pos(pos), m_property(property) 
{
}

TetVertex::~TetVertex() {

}
