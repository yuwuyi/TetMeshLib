#ifndef TetMesh_h__
#define TetMesh_h__

#include <hash_map>
#include <sstream>

class TetVertex;
class TetHalfFace;
class TetFace;
class Tetra;

class TetMesh {
public:
	TetMesh();
	~TetMesh();

	bool read(const char *filename);
	void save(const char *filename);

protected:
	TetVertex *createTetVertex(std::stringstream &ss);
	TetHalfFace *createTetHalfFace(TetVertex *half[3]);
	TetFace *createTetFace(const std::string &str);	
	Tetra *createTetra(std::stringstream &ss);

private:
	//some helper functions
private:
	stdext::hash_map<int, TetVertex *>		id2Ver;			// given a vertex id, get the corresponding vertex pointer in the container
	stdext::hash_map<int, Tetra *>		id2Tetra;		// given a face id, get the corresponding face pointer in the container
};

#endif // TetMesh_h__