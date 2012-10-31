#include "TetVertex.h"
#include "TetHalfFace.h"
#include "TetFace.h"
#include "TetEdge.h"
#include "TetMesh.h"
#include "Tetra.h"
#include "Point.h"

#include <iostream>
#include <fstream>
#include <tuple>
TetMesh::TetMesh() {
}

TetMesh::~TetMesh() {
}


typedef std::pair<int, std::pair<int, int> > triple;
triple construct_triple(TetHalfFace *halfface) {
	int vids[3] = {halfface->vertex(0)->id(), halfface->vertex(1)->id(), halfface->vertex(2)->id()};
	int mn = std::min(vids[0], std::min(vids[1], vids[2]));
	int mx = std::max(vids[0], std::max(vids[1], vids[2]));
	int mid = vids[0] + vids[1] + vids[2] - mn -mx;
	return make_pair(mn, std::make_pair(mid, mx));
}

bool TetMesh::read(const char *filename) {
	std::ifstream input(filename);
	
	while(input.good()) {
		std::string line;
		getline(input, line);
		if (line.empty()) {
			continue;
		}

		std::stringstream ss(line);

		std::string title, remain;
		ss >> title;

		if (title == "Vertex") {
			TetVertex *tv = createTetVertex(ss);
			id2Ver[tv->id()] = tv;
		} else if (title == "Tetrahedron") {
			Tetra *tet = createTetra(ss);
			id2Tetra[tet->id()] = tet;
		}
	}

	input.close();

	id2Ver.rehash(id2Ver.size());
	id2Tetra.rehash(id2Tetra.size());

	
	stdext::hash_map<triple, TetFace*> tripleMap;
	//create the half face 
	for (stdext::hash_map<int, Tetra*>::iterator b = id2Tetra.begin(), e = id2Tetra.end(); b != e; ++b) {
		Tetra *tet = (*b).second;
		TetVertex *face[3];
		for (int id = 0; id < 4; ++id) {
			int j = 0;
			for (int i = 0; i < 4; ++i) {
				if (i == id) {
					continue;
				}
				face[j] = tet->vertex(i);
				++j;
			}

			if ((id % 2) == 1) {
				std::swap(face[0], face[1]);
			}
		}

		TetHalfFace *hf = createTetHalfFace(face);
		hf->index() = tet->index() * 4 + id;
		triple tri = construct_triple(hf);	
		TetFace *tface = tripleMap[tri];

		if (!tface) {
			tface = createTetFace(hf);
			tripleMap[tri] = tface;
		} else {
			tface[1] =	hf;
		}

			
	}
	return true;
}

void TetMesh::save(const char *filename) {

}


TetVertex * TetMesh::createTetVertex(std::stringstream &ss) {
	int id;
	Point pos;
	std::string property;
	ss >> id >> pos.v[0] >> pos.v[1] >> pos.v[2];
	getline(ss, property);
	TetVertex *v = new TetVertex(id, pos, property);
	v->index() = id2Ver.size();
	return v;
}

TetHalfFace * TetMesh::createTetHalfFace(TetVertex *half[3]) {
	return new TetHalfFace(half);
}

TetFace * TetMesh::createTetFace(TetHalfFace *halfface) {
	return new TetFace(halfface);
}

Tetra * TetMesh::createTetra(std::stringstream &ss) {
	int id;
	int vids[4];
	std::string property;
	ss >> id >> vids[0] >> vids[1] >> vids[2] >> vids[3];
	TetVertex *vers[4];
	for (int i = 0; i < 4; ++i) {
		vers[i] = id2Ver[vids[i]];
	}
	getline(ss, property);
	Tetra *tet = new Tetra(id, vers, property);
	tet->index() = id2Tetra.size();

	for (int i = 0; i < 4; ++i) {
		vers[i]->add(tet);
	}




	return tet;
}