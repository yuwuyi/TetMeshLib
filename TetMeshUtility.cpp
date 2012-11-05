#include "TetMeshUtility.h"
#include "TetIterators.h"
#include "TetHalfFace.h"
#include "TetVertex.h"
#include "TetEdge.h"
#include "TetFace.h"
#include "TetMesh.h"
#include "Tetra.h"
#include "Point.h"
#include "Triple.h"

#include <map>
#include <iostream>

void TetMeshUtility::split(TetMesh *tetmesh, Tetra *tetra) {
	//create the new vertex
	Point newPos;
	for (int i = 0; i < 4; ++i) {
		newPos += tetra->vertex(i)->point();
	}
	newPos /= 4.0;

	//create new Vertex;
	TetVertex *nver = new TetVertex(tetmesh->m_next_vid, newPos, "");
	nver->index() = tetmesh->id2Ver.size();
	tetmesh->id2Ver[nver->id()] = nver;
	++tetmesh->m_next_vid;
	std::vector<Tetra*> nTets;

	for (int i = 0; i < 4; ++i) {
		TetHalfFace *halfface = tetra->halfface(i);
		Tetra *ntet = new Tetra(tetmesh->m_next_tid, tetmesh->id2Tetra.size(), halfface, nver);
		tetmesh->id2Tetra[ntet->id()] = ntet;
		++tetmesh->m_next_tid;
		nTets.push_back(ntet);
	}

	std::vector<TetHalfFace*> halffaces;
	for (size_t i = 0; i < nTets.size(); ++i) {
		Tetra *tet = nTets[i];	
		for (int i = 0; i < 4; ++i) {
			halffaces.push_back(tet->halfface(i));	
		}
	}


	std::vector<TetFace*> faces;
	buildFaces(halffaces, faces);
	
	//remove the tet from the vertex 
	//the old edges are located in halfface(0)
	for (int i = 0; i < 4; ++i) {
		TetVertex *tv = tetra->vertex(i);
		std::vector<Tetra*>& vec = tv->m_tetra; // use shorter name
		vec.erase(std::remove(vec.begin(), vec.end(), tetra), vec.end());
	}

	//add the previous face
	for (int i = 0; i < 4; ++i) {
		faces.push_back(tetra->halfface(i)->face());
	}


	std::vector<TetEdge*> edges;
	buildEdges(faces, edges);
	
	//link the tetra with the vertex
	for (size_t i = 0; i < nTets.size(); ++i) {
		Tetra *tet = nTets[i];	
		for (int j = 0; j < 4; ++j) {
			TetVertex *tv = tet->vertex(j);
			tv->add(tet);
		}
	}

	tetmesh->id2Tetra[tetra->id()] = 0;
	//delete tetra;
	
}

void TetMeshUtility::split(TetMesh *tetmesh, TetEdge *tedge) {
	Point newPos = (tedge->vertex(0)->point() + tedge->vertex(1)->point()) / 2.0; 
	TetVertex *nver = new TetVertex(tetmesh->m_next_vid, newPos, "");
	nver->index() = tetmesh->id2Ver.size();
	tetmesh->id2Ver[nver->id()] = nver;
	++tetmesh->m_next_vid;
	std::vector<Tetra*> nTets;

	//find the one-ring tets;
	std::vector<TetFace *> prev_faces;
	for (TetEdgeTetraIterator iter(tedge); !iter.end(); ++iter) {
		Tetra *tet = *iter;
		for (int i = 0; i < 4; ++i) {
			TetHalfFace *hf = tet->halfface(i);
			if (hf->has(tedge->vertex(0)) && hf->has(tedge->vertex(1))) {
				continue;
			}
			

			Tetra *ntet = new Tetra(tetmesh->m_next_tid, tetmesh->id2Tetra.size(), hf, nver);
			prev_faces.push_back(hf->face());
			tetmesh->id2Tetra[ntet->id()] = ntet;
			++tetmesh->m_next_tid;
			nTets.push_back(ntet);

		}
	

	}	


	//delete the surrounding tetra;
	for (TetEdgeTetraIterator iter(tedge); !iter.end(); ++iter) {
		Tetra *tet = *iter;
		tet->isValid() = false;
		tetmesh->id2Tetra[tet->id()] = 0;
		delete tet;
	}

	std::vector<TetHalfFace*> halffaces;
	for (size_t i = 0; i < nTets.size(); ++i) {
		Tetra *tet = nTets[i];	
		for (int i = 1; i < 4; ++i) {
			halffaces.push_back(tet->halfface(i));	
		}
	}

	std::vector<TetFace*> faces;
	buildFaces(halffaces, faces);
	
	faces.insert(faces.end(), prev_faces.begin(), prev_faces.end());

	std::vector<TetEdge*> edges;
	buildEdges(faces, edges);

	tedge->isValid() = false;
}


void TetMeshUtility::split(TetMesh *tetmesh, TetHalfFace *halfface) {
	
	Point newPos;
	for (int i = 0; i < 3; ++i) {
		newPos += halfface->vertex(i)->point();
	}
	newPos /= 3.0;

	TetVertex *nver = new TetVertex(tetmesh->m_next_vid, newPos, "");
	tetmesh->id2Ver[nver->id()] = nver;
	++tetmesh->m_next_vid;
	std::vector<Tetra*> nTets;

	Tetra *tet = halfface->tetra();

	for (int i = 0; i < 4; ++i) {
		TetHalfFace *hf = tet->halfface(i);
		if (hf == halfface) {
			continue;
		}
	
		Tetra *ntet = new Tetra(tetmesh->m_next_tid, tetmesh->id2Tetra.size(), hf, nver);
		tetmesh->id2Tetra[ntet->id()] = ntet;
		++tetmesh->m_next_tid;
		nTets.push_back(ntet);
	}



	std::vector<TetHalfFace*> halffaces;
	for (size_t i = 0; i < nTets.size(); ++i) {
		Tetra *tet = nTets[i];	
		for (int i = 0; i < 4; ++i) {
			halffaces.push_back(tet->halfface(i));	
		}
	}

	std::vector<TetFace*> faces;
	buildFaces(halffaces, faces);

	//remove the tet from the vertex 
	//the old edges are located in halfface(0)
	for (int i = 0; i < 4; ++i) {
		TetVertex *tv = tet->vertex(i);
		std::vector<Tetra*>& vec = tv->m_tetra; // use shorter name
		vec.erase(std::remove(vec.begin(), vec.end(), tet), vec.end());
	}

	//add the previous face
	for (int i = 0; i < 4; ++i) {
		faces.push_back(tet->halfface(i)->face());
	}

	std::vector<TetEdge*> edges;
	buildEdges(faces, edges);

	halfface->tetra()->isValid() = false;
		
} 

void TetMeshUtility::buildFaces(std::vector<TetHalfFace*> & halffaces, 
								std::vector<TetFace*> & faces) 
{
	std::map<triple, TetFace*> tripleMap;
	for (size_t i = 0; i < halffaces.size(); ++i) {
		TetHalfFace *halfface = halffaces[i];
		if (halfface->face()) {
			triple tri = construct_triple(halfface);	
			tripleMap[tri] = halfface->face();
		}
	}

	for (size_t i = 0; i < halffaces.size(); ++i) {
		TetHalfFace *hf = halffaces[i];
		triple tri = construct_triple(hf);	
		TetFace *tface = tripleMap[tri];
		if (tface && (hf == tface->halfface(0) || hf == tface->halfface(1))) {
			continue;
		}
		if (!tface) {
			tface = new TetFace(hf);//createTetFace(hf);
			faces.push_back(tface);
			tripleMap[tri] = tface;
		} else if (!tface->halfface(1)){
			tface->halfface(1) =	hf;
		} else {
			std::cout << "non-manifold!\n";
			exit(-1);
		}
		hf->face() = tface;
	}
}


void TetMeshUtility::buildEdges(std::vector<TetFace*>& faces, std::vector<TetEdge*>& edges) {
	std::map<pairint, TetEdge*> edgeMap;
	
	//initial the map
	// if there are exist edges, add them first

	for (size_t i = 0; i < faces.size(); ++i) {
		TetFace *face = faces[i];
		for (int j = 0; j < 3; ++j) {
			TetEdge *tedge = face->edge(j);
			if (tedge) {
				pairint p = construct_pairint(tedge->vertex(0), tedge->vertex(1));
				edgeMap[p] = tedge;
			}
		}
	}


	for (size_t i = 0; i < faces.size(); ++i) {
		TetFace *face = faces[i];
		
		for (int j = 0; j < 3; ++j) {
			TetVertex *v0 = face->halfface(0)->vertex(j);
			TetVertex *v1 = face->halfface(0)->vertex((j+1)%3);
			pairint p = construct_pairint(v0, v1);
			
			TetEdge *tedge = edgeMap[p];
			if (!tedge) {
				tedge = new TetEdge(v0, v1);
				edgeMap[p] = tedge;
				edges.push_back(tedge);
			}

			face->edge(j) = tedge;
			tedge->add(face);
		}

	}
}