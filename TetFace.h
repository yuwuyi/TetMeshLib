#ifndef TetFace_h__
#define TetFace_h__

class TetHalfFace;
class TetFace {
public:
	TetFace(TetHalfFace *halfface);
	~TetFace();

private:
	TetHalfFace *m_halfface[2];
};

#endif // TetFace_h__