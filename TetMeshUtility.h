#ifndef TetMeshUtility_h__
#define TetMeshUtility_h__

#include <vector>
class Tetra;
class TetMesh;
class TetFace;
class TetEdge;
class TetHalfFace;

class TetMeshUtility {
public:
	static void split(TetMesh *tetmesh, Tetra *tet);
	static void split(TetMesh *tetmesh, TetEdge *tedge);
	static void split(TetMesh *tetmesh, TetHalfFace *halfface);

	static void extractSurface(TetMesh *tetmesh);

	static void buildFaces(
		std::vector<TetHalfFace*> & halffaces, std::vector<TetFace*> & faces
		);

	static void buildEdges(std::vector<TetFace*>& faces, std::vector<TetEdge*>& edges);
};
#endif // TetMeshUtility_h__