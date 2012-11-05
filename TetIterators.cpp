#include "TetIterators.h"
#include "TetEdge.h"
#include "TetFace.h"
#include "TetHalfFace.h"

TetEdgeTetraIterator::TetEdgeTetraIterator(TetEdge* tedge) {
//TODO: can speed up. shall we need to add every two half faces,
//      or just halfface(0)? 
	
	for (size_t i = 0; i < tedge->m_faces.size(); ++i) {
		TetFace *face = tedge->m_faces[i];
		m_tetra.insert(face->halfface(0)->tetra());

		if (face->halfface(1)) {
			m_tetra.insert(face->halfface(1)->tetra());
		}
	}

	m_it = m_tetra.begin();
}




TetEdgeTetraIterator::~TetEdgeTetraIterator() {
	

}