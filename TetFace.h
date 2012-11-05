#ifndef TetFace_h__
#define TetFace_h__

#include "Element.h"

class TetHalfFace;
class TetEdge;

class TetFace {
public:
	TetFace(TetHalfFace *halfface);
	~TetFace();
	TetHalfFace *&halfface(int i) { return m_halfface[i]; }
	TetEdge *&edge(int i) { return m_edges[i]; }
private:
	TetHalfFace *m_halfface[2];
	TetEdge *m_edges[3];
};

#endif // TetFace_h__