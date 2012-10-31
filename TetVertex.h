#ifndef TetVertex_h__
#define TetVertex_h__

#include "Point.h"
#include <string>
#include <vector>

class Tetra;

class TetVertex {
public:
	TetVertex(int id, Point& pos, const std::string& property);
	~TetVertex();
	int id() const { return m_id; }
	int& index() { return m_index; }	
	std::string& property() { return m_property; }
	
	void add(Tetra* tetra) { m_tetra.push_back(tetra); }
private:
	int m_id, m_index;
	Point m_pos;
	std::string m_property;	
	std::vector<Tetra*> m_tetra;
};

#endif // TetVertex_h__