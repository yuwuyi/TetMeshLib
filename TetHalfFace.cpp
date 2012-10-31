#include "TetHalfFace.h"


TetHalfFace::TetHalfFace(TetVertex *vers[3]) {
	for (int i = 0; i < 3; ++i) {
		m_vers[i] = vers[i];
	}
}

TetHalfFace::~TetHalfFace() {

}