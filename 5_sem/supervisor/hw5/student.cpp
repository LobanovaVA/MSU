#include "student.h"

/* ============ initialization ============ */
student::
student (const char* new_name, int new_value)
{
  init (new_name, new_value);
}

void student::
set_value (int new_value)
{
  value = new_value;
}

int student::
set_name (const char* new_name)
{
  int len;

  if (new_name)
    {
      len = strlen (new_name) + 1;
      name = std::make_unique <char []> (len);
      //name = std::unique_ptr <char []> (new char [len]);
      if (!name)
        return ERROR_INITIALIZATION_STUDENT;
      strcpy (name.get (), new_name);
      //memcpy (name.get(), new_name, len);
    }
  else
    name = nullptr;

  return SUCCESS;
}

int student::
init (const char* new_name, int new_value)
{
  int ret;
  ret = set_name (new_name);

  if (ret == SUCCESS)
    {
      set_value (new_value);
      return SUCCESS;
    }
  else
    return ret;
}


/* ============ get data ============ */
int student::
get_value () const
{
  return value;
}

int student::
get_length () const
{
  return (name != nullptr ? 1 : 0);
}

char * student::
get_name () const
{
  return name.get ();
}


/* ============ comparison ============ */
int student::
operator< (const student& x)
{
  if (!this -> get_name () && !x.get_name ())
    return this -> get_value () < x.get_value ();

  if (!this -> get_name ())
    return 1;

  if (!x.get_name ())
    return 0;

  int res = strcmp (this -> get_name (), x.get_name ());
  if (res == 0)
    return this -> get_value () < x.get_value ();
  else
    return (res < 0) ? 1 : 0;
}


/* ============ in-out ============ */
int student::
read (FILE* fp)
{
  int new_value;
  char buff[LEN];
  this -> ~student ();

  if (fscanf (fp, "%s %d", buff, &new_value) != 2)
    {
      if (feof(fp))
        return ERROR_END_OF_INPUT_FILE;
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  if (init (buff, new_value))
    return ERROR_INITIALIZATION_STUDENT;

  return SUCCESS;
}

void student::
print ()
{    
  if (!this -> get_length ())
    printf (" (empty_name) %d", this -> get_value ());
  else
    printf (" %s %d", this -> get_name (), this -> get_value ());
}





