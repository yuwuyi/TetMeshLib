#ifndef TetIterators_h__
#define TetIterators_h__

#include <set>

class TetEdge;
class Tetra;

class TetEdgeTetraIterator {
public:
	TetEdgeTetraIterator(TetEdge* tedge);
	~TetEdgeTetraIterator();
	
	void operator++() {
		++m_it;
	}

	Tetra* operator*() {
		return *m_it;
	}

	bool end() {
		return m_it == m_tetra.end();
	}

private:
	std::set<Tetra*> m_tetra;
	std::set<Tetra*>::iterator m_it;

};
#endif // TetIterators_h__