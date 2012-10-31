#ifndef Tetra_h__
#define Tetra_h__

#include <string>

class TetVertex;
class TetHalfFace;

class Tetra {
public:
	Tetra(int id, TetVertex *vers[4], std::string& property);
	~Tetra();
	
	int& index() { return m_index; }
	int id() const { return m_id; }
	TetHalfFace *halfface(int i) { return m_halffaces[i]; }
	TetVertex *vertex(int i) { return m_vers[i]; }
private:
	int m_id;
	int m_index;
	TetVertex *m_vers[4];
	TetHalfFace *m_halffaces[4];
	std::string m_property;
};
#endif // Tetra_h__