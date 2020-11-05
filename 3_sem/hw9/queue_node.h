#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include "list.h"
#include <stdio.h>

class queue;
class queue_node;
class queue_node: public list
{
	private:
		queue_node *next = nullptr;
	public:
		friend class queue;
};

#endif
