#include "tree_node.h"
#include "addition.h"
#define LEN 1234

tree_node::tree_node (const tree_node& rhs){	init(rhs.name);   }
tree_node::~tree_node(){		destroy ();    }

int tree_node::init (const char *iname)
{

        if (iname)
        {
            name = new char[strlen (iname) + 1];
            if ( !name ) return ERROR_CANNOT_READ_CLASS;
            strcpy (name, iname);
        }
        else  name = nullptr;
        return 0;
}

tree_node::tree_node (const char *iname)
{
    if (iname)
    {
        name = new char[strlen (iname) + 1];
        if (name) strcpy (name, iname);
    }
    else  name = nullptr;
}

void tree_node::destroy ()
{
	if (name)
	{
		delete []name;
                name = nullptr;
	}
}

int tree_node::read (FILE* fp)
{
	char buff[LEN];
	destroy ();
        if (fgets(buff, LEN, fp)==nullptr)
        {
        if (feof(fp)) return ERROR_END_OF_INPUT_FILE;
        return ERROR_CANNOT_READ_INPUT_FILE;
	}
        if(strlen(buff)>0) buff[strlen(buff)-1]=0;
        if (init(buff)) return ERROR_CANNOT_READ_CLASS ;
	return 0;
}

void tree_node::print (FILE* out){    	fprintf(out, "%s\n", name);  }


//operators:

tree_node& tree_node::operator= (const tree_node& x)
{
	destroy ();
	init (x.name);
	return *this;
}

int tree_node::operator< (const tree_node& x)
{
	if (!name) return 1;
        if (!x.name) return 0;
        if (strcmp (name, x.name) < 0) return 1;
	else return 0;
}

int tree_node::operator> (const tree_node& x)
{
	if (!name) return 0;
	if (!x.name) return 1;
        if (strcmp ( name, x.name) > 0) return 1;
        else return 0;
}        
        

//adding:

bool tree_node::set_left   (tree_node *elem)
{
    if (this -> left  ) return false;
    return this -> left  = elem, true;
}

bool tree_node::set_right  (tree_node *elem)
{
    if (this -> right ) return false;
    return this -> right = elem, true;
}
