#ifndef JUMP_NLP
#define JUMP_NLP

#ifdef IPOPT_OPTION

#include <IpTNLP.hpp>
//#include "../../../../../third-party/CoinIpopt/build/include/coin/IpTNLP.hpp"
#include "cppTypes.h"

static const int NUM_FEET = 2;
static const int NUM_STATES = 6;
static const int NUM_INPUTS = 4;

static const int NUM_PREDICTIONS = 27;
static const int NUM_DECISION_VARS = NUM_STATES * NUM_PREDICTIONS;

static const int NUM_CONSTRAINTS = 10;
static const int NNZ_J_G = 35;//258;
static const int NNZ_J_G_F = 26;  // 200; <-- old number... new is unverified
static const int NNZ_H = 10;//84;  // 482
static const int NNZ_H_F = 10;  // 482


// C++ Files generated by MATLAB
#include "cpp/Jump2DBounds.h"
#include "cpp/Jump2DConstraintJacobian.h"
#include "cpp/Jump2DConstraintJacobianFinal.h"
#include "cpp/Jump2DConstraintJacobianFinalSP.h"
#include "cpp/Jump2DConstraintJacobianSP.h"
#include "cpp/Jump2DConstraints.h"
#include "cpp/Jump2DConstraintsFinal.h"
#include "cpp/Jump2DCost.h"
#include "cpp/Jump2DCostGradient.h"
#include "cpp/Jump2DInitialize.h"
#include "cpp/Jump2DLagrangianHessian.h"
#include "cpp/Jump2DLagrangianHessianFinal.h"
#include "cpp/Jump2DLagrangianHessianFinalSP.h"
#include "cpp/Jump2DLagrangianHessianSP.h"


using namespace Ipopt;

template<typename T>
class JumpNLP: public TNLP{
  public:
    JumpNLP();
    virtual ~JumpNLP(){}

    T _half_body = 0.19;
    T _leg_max = 0.3;

    /* ---------------------Environment Parameters---------------------- */
    double _mu = 0.65;                                // coefficient of friction
    double _gravity = -9.81;                       // magnitude of gravity z
    T _mass = 9.;
    T _I_yy = 0.271426;

 
    T _min_height = 0.18;

    void _print_problem_setup();


    // (x, z, theta, xdot, zdot, theta_dot)

    /* ------------------------Robot Parameters------------------------- */
    double Q[NUM_STATES * NUM_PREDICTIONS] = {0};
    double R[NUM_INPUTS * NUM_PREDICTIONS] = {0};

    double p_foot_0[2 * NUM_FEET] = {0};

    // state * (num_step + 1) + 
    // front reaction force (x, z) + 
    // hind reaction force (x, z) +
    // hind foot location
    int n_opt = 2;

    // initial + 
    // dynamics + 
    // front foot friction cone (-mu*fr_z < fr_x < mu*fr_z) + 
    // hind foot friction cone (-mu*fr_z < fr_x < mu*fr_z) + 
    // leg length
    int n_constr = 1;

    T v_des = 1.;
    T w_des = 1.0;
    T theta_des = -0.05;
    T dt = 0.01;

    Vec3<T> ini_pos; // x, z, theta
    Vec3<T> ini_vel; // d(x, z, theta)
    Vec2<T> Fr_foot_loc; // foot(x, z)

    /* -------------------------Gait Parameters------------------------- */
    // Vector of timesteps to take at each prediction
    double X_final[NUM_PREDICTIONS * NUM_DECISION_VARS] = {0};
    double dt_pred[NUM_PREDICTIONS];

    // An extra row for the last prediction being unconstrained
    double contact_state_pred[NUM_FEET * (NUM_PREDICTIONS + 1)] = {0};

    // Hold when a new touchdown event occurs for the foot
    double touchdown_pred[NUM_FEET * NUM_PREDICTIONS] = {0};

    // The index of the next step
    int next_step[NUM_FEET] = {0};

    double x_touchdown[3 * NUM_FEET] = {0};

    // Get the gait data from LCM
    double phi_0[NUM_FEET] = {0};  // should eventually come from the robot
    double T_p[NUM_FEET] = {0};                        // should eventually come from the robot
    double T_swing[NUM_FEET] = {0};                   // should eventually come from the robot
    double phi_0_new[NUM_FEET] = {0};  // should eventually come from the robot
    double T_p_new[NUM_FEET] = {0};                        // should eventually come from the robot
    double T_swing_new[NUM_FEET] = {0};                   // should eventually come from the robot
    double T_stance[NUM_FEET] = {0};
    double stance_fraction = 0;
    double flight_phase[NUM_PREDICTIONS] = {0};
    double enabled[NUM_FEET] = {0};
    double enabled_new[NUM_FEET] = {0};

    /* ------------------Max and min values for states------------------ */

    // Position min and max
    double x_min = -10000, x_max = 10000;
    double z_min = 0.05, z_max = 1.0;

    // Velocity min and max
    double dx_min = -20, dx_max = 20;
    double dz_min = -100, dz_max = 100;

    // Rotation min and max
    double pitch_min = -M_PI, pitch_max = M_PI;

    // Angular Velocity min and max
    double omega_y_min = -50, omega_y_max = 50;

    // Collect the initial mins and maxs in vectors
    double states_min[NUM_STATES] = {x_min, z_min, pitch_min, dx_min, dz_min, omega_y_min};
    double states_max[NUM_STATES] = {x_max, z_max, pitch_max, dx_max, dz_max, omega_y_max};
   double z_g[NUM_FEET] = {0, 0};            // ground height at foot locations

    // Collect the initial mins and maxs in vectors
        double f_z_min = 0,             f_z_max = 200;
    double f_x_min = -_mu * f_z_max, f_x_max = _mu * f_z_max;

    double inputs_min[NUM_INPUTS] = {f_x_min, f_z_min, f_x_min, f_z_min};
    double inputs_max[NUM_INPUTS] = {f_x_max, f_z_max, f_x_max, f_z_max};

    /* -------------------------Index Tracking-------------------------- */
    // Keep track of vector index
    int i_X = 0;
    int i_x = 0;
    int i_u = 0;
    int i_xd = 0;
    int i_uref = 0;
    int i_c = 0;
    int i_g = 0;
    int i_jc = 0;
    int i_h = 0;
    int i_f = 0;
    int i_x1 = 0;
    int i_u1 = 0;
    int i_f1 = 0;
    int i_Q = 0;
    int i_R = 0;


    void InitializeMPC(double* X_0);
    void Bounds(double* X_ub, double* X_lb, double* constraints_ub, double* constraints_lb);
    double PredictedCost(const double* X);
    void Constraints(const double* X, double* constraints);
    void PredictedCostGradient(const double* X, double* gradient);
    void ConstraintJacobian(const double* X, double* constraint_jacobian);
    void LagrangianHessian(const double* X, double* hessian,
                           Number obj_factor, const Number* lambda);
    void GetPredictedTimeVector();
    void SetParameters();

    // Set Robot states
    void SetCurrentState(double* current_state_in);
    void SetFootLocations(double* p_foot_0_in);


    // Set configuration variables
    //void SetNumPredictions(double NUM_PREDICTIONS_in);
    void SetStateWeights(double* Q_in);
    void SetInputRegularization(double* R_in);
    void SetRobotParameters(double mass_in, double Inertia_in);
    void SetGaitParameters(double * enabled_in, double * phi_0_in, double T_p_in, double T_swing_in);
    void SetEnvironmentParameters(double gravity_in, double mu_in, double* z_g_in);
    void SetModifiedRegularization();

    // Get the final solution
    double GetSolution(int index);
    int GetSolved();

    double current_state[NUM_STATES] = {0};
    double x_d[NUM_PREDICTIONS * NUM_STATES] = {0};
    double u_ref[NUM_INPUTS * NUM_PREDICTIONS] = {0};


  public:
    int SOLVED = 0;
    /* --------------------------IPOPT Methods-------------------------- */

    /**@name Overloaded from TNLP */
    //@{
    /** Method to return some info about the nlp */
    virtual bool get_nlp_info(Ipopt::Index& n, Ipopt::Index& m, Ipopt::Index& nnz_jac_g,
                              Ipopt::Index& nnz_h_lag, IndexStyleEnum& index_style);

    /** Method to return the bounds for my problem */
    virtual bool get_bounds_info(Ipopt::Index n, Number* x_l, Number* x_u,
                                 Ipopt::Index m, Number* g_l, Number* g_u);

    /** Method to return the starting point for the algorithm */
    virtual bool get_starting_point(Ipopt::Index n, bool init_x, Number* x,
                                    bool init_z, Number* z_L, Number* z_U,
                                    Ipopt::Index m, bool init_lambda,
                                    Number* lambda);

    /** Method to return the objective value */
    virtual bool eval_f(Ipopt::Index n, const Number* x, bool new_x, Number& obj_value);

    /** Method to return the gradient of the objective */
    virtual bool eval_grad_f(Ipopt::Index n, const Number* x, bool new_x, Number* grad_f);

    /** Method to return the constraint residuals */
    virtual bool eval_g(Ipopt::Index n, const Number* x, bool new_x, Ipopt::Index m, Number* g);

    /** Method to return:
     *   1) The structure of the jacobian (if "values" is NULL)
     *   2) The values of the jacobian (if "values" is not NULL)
     */
    virtual bool eval_jac_g(Ipopt::Index n, const Number* x, bool new_x,
                            Ipopt::Index m, Ipopt::Index nele_jac,
                            Ipopt::Index* iRow, Ipopt::Index *jCol,
                            Number* values);

    /** Method to return:
     *   1) The structure of the hessian of the lagrangian (if "values" is NULL)
     *   2) The values of the hessian of the lagrangian (if "values" is not NULL)
     */
    virtual bool eval_h(Ipopt::Index n, const Number* x, bool new_x,
                        Number obj_factor, Ipopt::Index m, const Number* lambda,
                        bool new_lambda, Ipopt::Index nele_hess, Ipopt::Index* iRow,
                        Ipopt::Index* jCol, Number* values);

    //@}

    /** @name Solution Methods */
    //@{
    /** This method is called when the algorithm is complete 
     * so the TNLP can store/write the solution */
    virtual void finalize_solution(SolverReturn status,
                                   Ipopt::Index n, const Number* x,
                                   const Number* z_L, const Number* z_U,
                                   Ipopt::Index m, const Number* g,
                                   const Number* lambda, Number obj_value,
                                   const IpoptData* ip_data,
                                   IpoptCalculatedQuantities* ip_cq);
};

#endif // IPOPT_OPTION

#endif
