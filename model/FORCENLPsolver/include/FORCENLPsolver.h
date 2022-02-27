#ifndef FORCENLPsolver_H
#define FORCENLPsolver_H
/* Generated by FORCESPRO v5.1.0 on Sunday, February 27, 2022 at 10:04:11 AM */

#ifndef SOLVER_STDIO_H
#define SOLVER_STDIO_H
#include <stdio.h>
#include <stddef.h>
#endif


/* DATA TYPE ------------------------------------------------------------*/
typedef double FORCENLPsolver_float;
typedef double FORCENLPsolver_callback_float;
typedef double FORCENLPsolverinterface_float;
typedef int FORCENLPsolver_int;

#ifndef SOLVER_STANDARD_TYPES
#define SOLVER_STANDARD_TYPES

typedef signed char solver_int8_signed;
typedef unsigned char solver_int8_unsigned;
typedef char solver_int8_default;
typedef signed short int solver_int16_signed;
typedef unsigned short int solver_int16_unsigned;
typedef short int solver_int16_default;
typedef signed int solver_int32_signed;
typedef unsigned int solver_int32_unsigned;
typedef int solver_int32_default;
typedef signed long long int solver_int64_signed;
typedef unsigned long long int solver_int64_unsigned;
typedef long long int solver_int64_default;

#endif

/* SOLVER SETTINGS ------------------------------------------------------*/

/* MISRA-C compliance */
#ifndef MISRA_C_FORCENLPsolver
#define MISRA_C_FORCENLPsolver (0)
#endif

/* restrict code */
#ifndef RESTRICT_CODE_FORCENLPsolver
#define RESTRICT_CODE_FORCENLPsolver (0)
#endif

/* print level */
#ifndef SET_PRINTLEVEL_FORCENLPsolver
#define SET_PRINTLEVEL_FORCENLPsolver    (0)
#endif

/* timing */
#ifndef SET_TIMING_FORCENLPsolver
#define SET_TIMING_FORCENLPsolver    (1)
#endif

/* Numeric Warnings */
/* #define PRINTNUMERICALWARNINGS */

/* maximum number of iterations  */
#define SET_MAXIT_FORCENLPsolver			(200)	 

/* desired maximum residual on equality constraints */
#define SET_ACC_RESEQ_FORCENLPsolver		(FORCENLPsolver_float)(1E-06)


/* RETURN CODES----------------------------------------------------------*/
/* solver has converged within desired accuracy */
#define OPTIMAL_FORCENLPsolver      (1)

/* maximum number of iterations has been reached */
#define MAXITREACHED_FORCENLPsolver (0)

/* solver has stopped due to a timeout */
#define TIMEOUT_FORCENLPsolver   (2)

/* NaN encountered in function evaluations */
#define BADFUNCEVAL_FORCENLPsolver  (-6)

/* no progress in method possible */
#define NOPROGRESS_FORCENLPsolver   (-7)

/* regularization error */
#define REGULARIZATION_ERROR_FORCENLPsolver   (-9)

/* invalid values in parameters */
#define PARAM_VALUE_ERROR_FORCENLPsolver   (-11)

/* too small timeout given */
#define INVALID_TIMEOUT_FORCENLPsolver   (-12)

/* error in linesearch */
#define LINESEARCH_ERROR_FORCENLPsolver   (-13)

/* thread error */
#define THREAD_FAILURE_FORCENLPsolver  (-98)

/* locking mechanism error */
#define LOCK_FAILURE_FORCENLPsolver  (-99)

/* licensing error - solver not valid on this machine */
#define LICENSE_ERROR_FORCENLPsolver  (-100)

/* qp solver error */
#define QP_SOLVER_FAILURE_FORCENLPsolver (-8)


/* INTEGRATORS RETURN CODE ------------*/
/* Integrator ran successfully */
#define INTEGRATOR_SUCCESS (11)
/* Number of steps set by user exceeds maximum number of steps allowed */
#define INTEGRATOR_MAXSTEPS_EXCEEDED (12)

/* PARAMETERS -----------------------------------------------------------*/
/* fill this with data before calling the solver! */
typedef struct
{
	    /* vector of size 3 */
    FORCENLPsolver_float xinit[3];

    /* vector of size 100 */
    FORCENLPsolver_float x0[100];

    /* vector of size 60 */
    FORCENLPsolver_float all_parameters[60];

    /* scalar */
    FORCENLPsolver_int reinitialize;


} FORCENLPsolver_params;


/* OUTPUTS --------------------------------------------------------------*/
/* the desired variables are put here by the solver */
typedef struct
{
	    /* vector of size 5 */
    FORCENLPsolver_float x01[5];

    /* vector of size 5 */
    FORCENLPsolver_float x02[5];

    /* vector of size 5 */
    FORCENLPsolver_float x03[5];

    /* vector of size 5 */
    FORCENLPsolver_float x04[5];

    /* vector of size 5 */
    FORCENLPsolver_float x05[5];

    /* vector of size 5 */
    FORCENLPsolver_float x06[5];

    /* vector of size 5 */
    FORCENLPsolver_float x07[5];

    /* vector of size 5 */
    FORCENLPsolver_float x08[5];

    /* vector of size 5 */
    FORCENLPsolver_float x09[5];

    /* vector of size 5 */
    FORCENLPsolver_float x10[5];

    /* vector of size 5 */
    FORCENLPsolver_float x11[5];

    /* vector of size 5 */
    FORCENLPsolver_float x12[5];

    /* vector of size 5 */
    FORCENLPsolver_float x13[5];

    /* vector of size 5 */
    FORCENLPsolver_float x14[5];

    /* vector of size 5 */
    FORCENLPsolver_float x15[5];

    /* vector of size 5 */
    FORCENLPsolver_float x16[5];

    /* vector of size 5 */
    FORCENLPsolver_float x17[5];

    /* vector of size 5 */
    FORCENLPsolver_float x18[5];

    /* vector of size 5 */
    FORCENLPsolver_float x19[5];

    /* vector of size 5 */
    FORCENLPsolver_float x20[5];


} FORCENLPsolver_output;


/* SOLVER INFO ----------------------------------------------------------*/
/* diagnostic data from last interior point step */
typedef struct
{
	/* iteration number */
	solver_int32_default it;

	/* inf-norm of equality constraint residuals */
	FORCENLPsolver_float res_eq;

	/* norm of stationarity condition */
	FORCENLPsolver_float rsnorm;

	/* primal objective */
	FORCENLPsolver_float pobj;

	/* total solve time */
	FORCENLPsolver_float solvetime;

	/* time spent in function evaluations */
	FORCENLPsolver_float fevalstime;

	/* time spent solving QPs */
	FORCENLPsolver_float QPtime;
} FORCENLPsolver_info;



/* SOLVER FUNCTION DEFINITION -------------------------------------------*/
/* Time of Solver Generation: (UTC) Sunday, February 27, 2022 10:04:12 AM */
/* User License expires on: (UTC) Wednesday, June 1, 2022 10:00:00 PM (approx.) (at the time of code generation) */
/* Solver Static License expires on: (UTC) Wednesday, June 1, 2022 10:00:00 PM (approx.) */
/* Solver Generation Request Id: a1670085-abcf-436f-be56-5176f39690c0 */
/* examine exitflag before using the result! */
#ifdef __cplusplus
extern "C" {
#endif		

typedef void(*FORCENLPsolver_extfunc)(FORCENLPsolver_float* x, FORCENLPsolver_float* y, FORCENLPsolver_float* lambda, FORCENLPsolver_float* params, FORCENLPsolver_float* pobj, FORCENLPsolver_float* g, FORCENLPsolver_float* c, FORCENLPsolver_float* Jeq, FORCENLPsolver_float* h, FORCENLPsolver_float* Jineq, FORCENLPsolver_float* H, solver_int32_default stage, solver_int32_default iterations, solver_int32_default threadID);

extern solver_int32_default FORCENLPsolver_solve(FORCENLPsolver_params *params, FORCENLPsolver_output *output, FORCENLPsolver_info *info, FILE *fs, FORCENLPsolver_extfunc evalextfunctions_FORCENLPsolver);







#ifdef __cplusplus
}
#endif

#endif