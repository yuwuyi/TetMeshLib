#ifndef Element_h__
#define Element_h__

#include <queue>

struct Element {};

struct ElementPool {
		
	void add(Element* e) { pool.push(e); }

	template <typename T>
	T* get() { 
		if (pool.empty())	return 0;
		Element *e = pool.pop();
		return static_cast<T*>(e);
	}

	std::queue<Element*> pool;

};

#endif // Element_h__