#include "TetFace.h"


TetFace::TetFace(TetHalfFace *halfface) {
	m_halfface[0] = halfface;
	m_halfface[1] = NULL;
}

TetFace::~TetFace() {

}