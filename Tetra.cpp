#include "Tetra.h"

Tetra::Tetra(int id, TetVertex *vers[4], std::string& property) 
: m_id(id), m_property(property)
{
	for (int i = 0; i < 4; ++i) {
		m_vers[i] = vers[i];
	}
}

Tetra::~Tetra() {

}