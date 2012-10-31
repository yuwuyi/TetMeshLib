#ifndef TetHalfFace_h__
#define TetHalfFace_h__

#include <string>

class TetVertex;

class TetHalfFace {
public:
	TetHalfFace(TetVertex *vers[3]);
	~TetHalfFace();

	int& index() { return m_index; }
	
	TetVertex *vertex(int i) { return m_vers[i]; }
private:
	int m_index;
	TetVertex *m_vers[3];

};
#endif // TetHalfFace_h__