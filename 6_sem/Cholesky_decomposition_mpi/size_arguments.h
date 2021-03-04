#ifndef SIZE_ARGUMENTS_H
#define SIZE_ARGUMENTS_H

class size_arguments
{
public:
  int my_rank = -1;
  int comm_size = -1;

  int matrix_size = -1;
  int block_size = -1;
  int print_size = -1;

  int mod = -1;
  int div = -1;
  int block_lim = -1;

  int squared_block_size = -1;
  int buff_column_size = -1;

public:
  size_arguments () = default;
  ~size_arguments () = default;

  void set_args (int m_s, int bl_s, int pr_s);

  int get_col_width (int ind);
  int get_alloc_column_size (int ind);

  int get_alloc_size ();
  int get_local_block_lim ();

  bool is_my_column (int ind) { return my_rank == (ind % comm_size); }
  int get_column_owner (int ind) { return ind % comm_size; }

  int get_start_ind (int ind);
};

#endif

