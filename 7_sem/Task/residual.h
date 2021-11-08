#ifndef RESIDUAL_H
#define RESIDUAL_H

#include "structs.h"
#include "addition.h"

#include <utility>

void calc_residual (
    const params_t &params, const vect &results,
    residual_t &all_residual_g, residual_t &all_residual_v);

void calc_residual (
    const params_t &params, const vect &res_1, const vect &res_2,
    residual_t &all_residual_g, residual_t &all_residual_v, const int k);


void fill_diff_vect (const params_t &params, const vect &res,
                     vect &diff_g, vect &diff_v);

void fill_diff_vect (const params_t &params,
                     const vect &res_1, const vect &res_2,
                     vect &diff_g, vect &diff_v, const int k);

/* ============================================================================ */

void calc_all_norm (
    const params_t &params, const vect &diff_g, const vect &diff_v,
    residual_t &all_residual_g, residual_t &all_residual_v);

double C_norm (const vect &v);
double L2_norm (const vect &v, double h);
double W2_1h_norm (const vect &v, double h);

#endif // RESIDUAL_H
