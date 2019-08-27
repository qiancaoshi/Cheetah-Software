/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Jump2DConstraintJacobianSP.cpp
 *
 * Code generation for function 'Jump2DConstraintJacobianSP'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Jump2DBounds.h"
#include "Jump2DConstraintJacobian.h"
#include "Jump2DConstraintJacobianFinal.h"
#include "Jump2DConstraintJacobianFinalSP.h"
#include "Jump2DConstraintJacobianInitial.h"
#include "Jump2DConstraintJacobianInitialSP.h"
#include "Jump2DConstraintJacobianSP.h"
#include "Jump2DConstraints.h"
#include "Jump2DConstraintsFinal.h"
#include "Jump2DConstraintsInitial.h"
#include "Jump2DCost.h"
#include "Jump2DCostGradient.h"
#include "Jump2DInitialize.h"
#include "Jump2DLagrangianHessian.h"
#include "Jump2DLagrangianHessianFinal.h"
#include "Jump2DLagrangianHessianFinalSP.h"
#include "Jump2DLagrangianHessianInitial.h"
#include "Jump2DLagrangianHessianInitialSP.h"
#include "Jump2DLagrangianHessianSP.h"

/* Function Definitions */
void Jump2DConstraintJacobianSP(double iter, double NUM_X, double NUM_C, double
  row_index_CJ[35], double col_index_CJ[35])
{
  double t2;

  /* JUMP2DCONSTRAINTJACOBIANSP */
  /*     [ROW_INDEX_CJ,COL_INDEX_CJ] = JUMP2DCONSTRAINTJACOBIANSP(ITER,NUM_X,NUM_C) */
  /*     This function was generated by the Symbolic Math Toolbox version 8.0. */
  /*     27-Aug-2019 12:38:32 */
  t2 = NUM_C * iter;
  row_index_CJ[0] = t2;
  row_index_CJ[1] = t2 + 1.0;
  row_index_CJ[2] = t2 + 2.0;
  row_index_CJ[3] = t2;
  row_index_CJ[4] = t2 + 3.0;
  row_index_CJ[5] = t2 + 1.0;
  row_index_CJ[6] = t2 + 4.0;
  row_index_CJ[7] = t2 + 2.0;
  row_index_CJ[8] = t2 + 5.0;
  row_index_CJ[9] = t2;
  row_index_CJ[10] = t2 + 1.0;
  row_index_CJ[11] = t2 + 2.0;
  row_index_CJ[12] = t2 + 3.0;
  row_index_CJ[13] = t2 + 4.0;
  row_index_CJ[14] = t2 + 5.0;
  row_index_CJ[15] = t2;
  row_index_CJ[16] = t2 + 2.0;
  row_index_CJ[17] = t2 + 3.0;
  row_index_CJ[18] = t2 + 5.0;
  row_index_CJ[19] = t2 + 1.0;
  row_index_CJ[20] = t2 + 2.0;
  row_index_CJ[21] = t2 + 4.0;
  row_index_CJ[22] = t2 + 5.0;
  row_index_CJ[23] = t2 + 6.0;
  row_index_CJ[24] = t2 + 7.0;
  row_index_CJ[25] = t2;
  row_index_CJ[26] = t2 + 2.0;
  row_index_CJ[27] = t2 + 3.0;
  row_index_CJ[28] = t2 + 5.0;
  row_index_CJ[29] = t2 + 1.0;
  row_index_CJ[30] = t2 + 2.0;
  row_index_CJ[31] = t2 + 4.0;
  row_index_CJ[32] = t2 + 5.0;
  row_index_CJ[33] = t2 + 8.0;
  row_index_CJ[34] = t2 + 9.0;
  t2 = NUM_X * iter;
  col_index_CJ[0] = t2;
  col_index_CJ[1] = t2 + 1.0;
  col_index_CJ[2] = t2 + 2.0;
  col_index_CJ[3] = t2 + 3.0;
  col_index_CJ[4] = t2 + 3.0;
  col_index_CJ[5] = t2 + 4.0;
  col_index_CJ[6] = t2 + 4.0;
  col_index_CJ[7] = t2 + 5.0;
  col_index_CJ[8] = t2 + 5.0;
  col_index_CJ[9] = t2 + 10.0;
  col_index_CJ[10] = t2 + 11.0;
  col_index_CJ[11] = t2 + 12.0;
  col_index_CJ[12] = t2 + 13.0;
  col_index_CJ[13] = t2 + 14.0;
  col_index_CJ[14] = t2 + 15.0;
  col_index_CJ[15] = t2 + 16.0;
  col_index_CJ[16] = t2 + 16.0;
  col_index_CJ[17] = t2 + 16.0;
  col_index_CJ[18] = t2 + 16.0;
  col_index_CJ[19] = t2 + 17.0;
  col_index_CJ[20] = t2 + 17.0;
  col_index_CJ[21] = t2 + 17.0;
  col_index_CJ[22] = t2 + 17.0;
  col_index_CJ[23] = t2 + 17.0;
  col_index_CJ[24] = t2 + 17.0;
  col_index_CJ[25] = t2 + 18.0;
  col_index_CJ[26] = t2 + 18.0;
  col_index_CJ[27] = t2 + 18.0;
  col_index_CJ[28] = t2 + 18.0;
  col_index_CJ[29] = t2 + 19.0;
  col_index_CJ[30] = t2 + 19.0;
  col_index_CJ[31] = t2 + 19.0;
  col_index_CJ[32] = t2 + 19.0;
  col_index_CJ[33] = t2 + 19.0;
  col_index_CJ[34] = t2 + 19.0;
}

/* End of code generation (Jump2DConstraintJacobianSP.cpp) */
