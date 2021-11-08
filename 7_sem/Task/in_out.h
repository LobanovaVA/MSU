#ifndef IN_OUT_H
#define IN_OUT_H

#include "structs.h"

#include <string>

void print_usage (const std::string& hint);

int get_args (const int argc, char **argv, int& mode, data_t &data, params_t &params);

/* ============================================================================ */

void create_table (const params_t &params, vect &result, const std::string& filenam);

void write_table     (const std::string& var_name, const residual_t &res, const std::string& filenam);
void write_table_tex (const std::string& var_name, const residual_t &res, const std::string& filenam);


#endif // IN_OUT_H
