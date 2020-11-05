#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

#include "student.h"

class B_tree;
class B_tree_node;
class B_tree_node: public student
{
	private:
		student **value;
		B_tree_node **children;
		int size;
	public:
		friend class B_tree;

		B_tree_node(int size = 0)
		{
			if (!size) { value = nullptr; children = nullptr; }
			else
			{
				value = new student *[size];
				children = new B_tree_node *[size + 1];
				B_tree_node **children;
				for (int i = 0; i< size; i++)
				{
					value[i] = nullptr;
					children [i] = nullptr;
				}
				children [size] = nullptr;
			}
		}

//deleting: 
		~b_tree_node ();

		void delete_node()
	    {
	    	for (int i = 0; i < size; i++)	{	delete value [i]; delete children [i];  	}
	    	delete children [size];	
	    	if (size)  	{	delete [] value;	delete [] children;  	}
	    	size = 0;
	    }

	    void clean_node()
	    {
	      for (int i = 0; i < size; i++) {	value [i] = nullptr; children [i] = nullptr; }
	      children [size] = nullptr; size = 0; 
	    }

	    void clean_start_from (int n)
		{
			for(int i = n; i < size; i++) {	 value [i] = nullptr; children [i + 1] = nullptr;}
			size = n;
		}

//adding:
		int find_insert_position (student *x)
	    {
	        int pos = 0, len = size, i = 0;
	        while (pos != len)
	        {
	            i = (pos + len) / 2;
	            if (*x > *values[i]) pos = i + 1;
	            else len = i;
	        }
	        return pos;
	    }

//others:
	    void print(int space)
	    {
	      if (!value) return;
	      for (int i = 0; i < (2 * space < MAX_PRINT ? 2 * space : MAX_PRINT); i++)
	      {
	        if (value && value[i]) value [i] -> print();
	        else {printf("N N");}
	        printf(", ");
	      }
	      if(children && children[0] == 0) {printf("<END>");}
	      printf("\n");
	    }
};

#endif
