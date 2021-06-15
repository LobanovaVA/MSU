#ifndef SIZE_ARGUMENTS_H
#define SIZE_ARGUMENTS_H

class size_arguments
{
public:
  int my_rank = -1;
  int comm_size = -1;

  int n_size = -1;

  int my_beg = -1;
  int my_end = -1;

public:
  size_arguments () = default;
  ~size_arguments () = default;

  int get_beg_ind (const int rank) const;
  int get_end_ind (const int rank) const;

  void set_args (int n_s);

  bool iam_main () const { return my_rank == 0; }
};

#endif

