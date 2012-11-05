#ifndef MutableTetMesh_h__
#define MutableTetMesh_h__

#include <queue>
#include "TetMesh.h"

class TetVertex;
class TetHalfFace;
class TetFace;
class TetEdge;
class Tetra;

class MutableTetMesh : public TetMesh {
public:
	MutableTetMesh();
	virtual ~MutableTetMesh();	
	void addVertex();
	void addTetra();
	void removeVertex();
	void removeTetra();

protected:
	struct ElementPool;
	ElementPool *m_pool;
};

#endif // MutableTetMesh_h__