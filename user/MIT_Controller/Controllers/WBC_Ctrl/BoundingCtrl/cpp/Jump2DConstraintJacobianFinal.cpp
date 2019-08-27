/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Jump2DConstraintJacobianFinal.cpp
 *
 * Code generation for function 'Jump2DConstraintJacobianFinal'
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
void Jump2DConstraintJacobianFinal(const double in1[2], double dt, const double
  in3[4], double m, double Iyy, double mu_g, double
  constraint_jacobian_final_nz[26])
{
  double t2;
  double t3;
  double t4;

  /* JUMP2DCONSTRAINTJACOBIANFINAL */
  /*     CONSTRAINT_JACOBIAN_FINAL_NZ = JUMP2DCONSTRAINTJACOBIANFINAL(IN1,DT,IN3,M,IYY,MU_G) */
  /*     This function was generated by the Symbolic Math Toolbox version 8.0. */
  /*     27-Aug-2019 12:38:33 */
  t2 = dt * dt;
  t3 = 1.0 / m;
  t4 = 1.0 / Iyy;
  constraint_jacobian_final_nz[0] = 1.0;
  constraint_jacobian_final_nz[1] = 1.0;
  constraint_jacobian_final_nz[2] = 1.0;
  constraint_jacobian_final_nz[3] = 1.0;
  constraint_jacobian_final_nz[4] = 1.0;
  constraint_jacobian_final_nz[5] = 1.0;
  constraint_jacobian_final_nz[6] = in1[0] * t2 * t3 * -0.5;
  constraint_jacobian_final_nz[7] = in3[1] * in1[0] * t2 * t4 * -0.5;
  constraint_jacobian_final_nz[8] = -dt * in1[0] * t3;
  constraint_jacobian_final_nz[9] = -dt * in3[1] * in1[0] * t4;
  constraint_jacobian_final_nz[10] = in1[0] * t2 * t3 * -0.5;
  constraint_jacobian_final_nz[11] = in3[0] * in1[0] * t2 * t4 * 0.5;
  constraint_jacobian_final_nz[12] = -dt * in1[0] * t3;
  constraint_jacobian_final_nz[13] = dt * in3[0] * in1[0] * t4;
  constraint_jacobian_final_nz[14] = -in1[0] * (mu_g - 1.0);
  constraint_jacobian_final_nz[15] = -in1[0] * (mu_g + 1.0);
  constraint_jacobian_final_nz[16] = in1[1] * t2 * t3 * -0.5;
  constraint_jacobian_final_nz[17] = in3[3] * in1[1] * t2 * t4 * -0.5;
  constraint_jacobian_final_nz[18] = -dt * in1[1] * t3;
  constraint_jacobian_final_nz[19] = -dt * in3[3] * in1[1] * t4;
  constraint_jacobian_final_nz[20] = in1[1] * t2 * t3 * -0.5;
  constraint_jacobian_final_nz[21] = in3[2] * in1[1] * t2 * t4 * 0.5;
  constraint_jacobian_final_nz[22] = -dt * in1[1] * t3;
  constraint_jacobian_final_nz[23] = dt * in3[2] * in1[1] * t4;
  constraint_jacobian_final_nz[24] = -in1[1] * (mu_g - 1.0);
  constraint_jacobian_final_nz[25] = -in1[1] * (mu_g + 1.0);
}

/* End of code generation (Jump2DConstraintJacobianFinal.cpp) */
