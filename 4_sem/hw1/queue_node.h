#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include "list.h"
#include <stdio.h>

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class queue;

template <class T, template <class> class T1, template <class, template <class> class> class T2>
class queue_node: public T2 <T, T1>
{
	private:
		queue_node <T, T1, T2> *next = nullptr;
	public:
		friend class queue <T, T1, T2>;
		queue_node () = default;
		~queue_node () { next = nullptr; }
};

#endif
