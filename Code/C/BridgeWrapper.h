//////////////////////////////////////////////////////////////////////
/*
 Herein we implement Gibbs sampling for Bridge Regression a la Polson
 and Scott.  For a detailed description of the specifics of the setup
 and algorithm please see their paper The Bayesian Bridge
 (http://arxiv.org/abs/1109.2279).

 One starts with the basic regression:

   y = X beta + ep, ep ~ N(0, sig2 I).

 To regularize the selection of beta one may chose a variety of
 priors.  In the Bridge regression the prior lives within the familiy
 of exponential prior distributions described by

   p(beta | alpha, tau) \propto exp( - | beta_j / tau |^alpha ).

 GIBBS SAMPLING:

 The challenge is to compute the posterior distribution efficiently.
 Polson and Scott use a Normal mixure of Bartlett-Fejer kernels to
 carry out this procedure.

 See BridgeRegression.h for the conditional posteriors used when Gibbs
 Sampling.

 R WRAPPER:

 We also provide functions that may be called from R so that one can
 speed up their Gibbs sampling or prevent copying large matrices when
 doing an expectation maximization.

 In what follows:

   - y is N x 1.
   - X is N x P.
   - beta is P x 1.

 */
//////////////////////////////////////////////////////////////////////

#ifndef __BRIDGE__
#define __BRIDGE__

#include "Matrix.h"
#include "RNG.hpp"
#include "BridgeRegression.h"

//////////////////////////////////////////////////////////////////////
		    // EXPECTATION MAXIMIZATION //
//////////////////////////////////////////////////////////////////////

int EM(Matrix & beta, MatrixFrame &y, MatrixFrame &X,
	double ratio, double alpha, double lambda_max,
	double tol, int max_iter, bool use_cg=false);

//////////////////////////////////////////////////////////////////////
		       // BRIDGE REGRESSION //
//////////////////////////////////////////////////////////////////////

double bridge_regression(MatrixFrame & beta,
			 MatrixFrame & u,
			 MatrixFrame & omega,
			 MatrixFrame & sig2,
			 MatrixFrame & tau,
			 const MatrixFrame & y,
			 const MatrixFrame & X,
			 double alpha,
			 double sig2_shape,
			 double sig2_scale,
			 double nu_shape,
			 double nu_rate,
			 double true_sig2,  
			 double true_tau , 
			 uint burn);

double bridge_regression_stable(MatrixFrame & beta,
				MatrixFrame & lambda,
				MatrixFrame & sig2,
				MatrixFrame & tau,
				const MatrixFrame & y,
				const MatrixFrame & X,
				double alpha,
				double sig2_shape,
				double sig2_scale,
				double nu_shape,
				double nu_rate,
				double true_sig2,
				double true_tau,
				uint burn);

double bridge_regression_ortho(MatrixFrame & beta,
			 MatrixFrame & u,
			 MatrixFrame & omega,
			 MatrixFrame & sig2,
			 MatrixFrame & tau,
			 const MatrixFrame & y,
			 const MatrixFrame & X,
			 double alpha,
			 double sig2_shape,
			 double sig2_scale,
			 double nu_shape,
			 double nu_rate,
			 double true_sig2,  
			 double true_tau , 
			 uint burn);

double bridge_regression_stable_ortho(MatrixFrame & beta,
				MatrixFrame & lambda,
				MatrixFrame & sig2,
				MatrixFrame & tau,
				const MatrixFrame & y,
				const MatrixFrame & X,
				double alpha,
				double sig2_shape,
				double sig2_scale,
				double nu_shape,
				double nu_rate,
				double true_sig2,
				double true_tau,
				uint burn);

//////////////////////////////////////////////////////////////////////
			    // WRAPPERS //
//////////////////////////////////////////////////////////////////////


extern "C"
{
  void bridge_EM(double *beta,
		 const double *y,
		 const double *X,
		 const double *ratio,
		 const double *alpha,
		 const int *P,
		 const int *N,
		 const double *lambda_max,
		 const double *tol,
		       int *max_iter,
		 const bool *use_cg);

  void bridge_regression(double *betap,
			 double *up,
			 double *omegap,
			 double *sig2p,
			 double *taup,
			 const double *yp,
			 const double *Xp,
			 const double *alpha,
			 const double *sig2_shape,
			 const double *sig2_scale,
			 const double *nu_shape,
			 const double *nu_rate,
			 const double *true_sig2,
			 const double *true_tau,
			 const int *P,
			 const int *N,
			 const int *M,
			 const int *burn,
			 double *runtime,
			 const bool *ortho);

  void bridge_reg_stable(double *betap,
			 double *lambdap,
			 double *sig2p,
			 double *taup,
			 const double *yp,
			 const double *Xp,
			 const double *alpha,
			 const double *sig2_shape,
			 const double *sig2_scale,
			 const double *nu_shape,
			 const double *nu_rate,
			 const double *true_sig2,
			 const double *true_tau,
			 const int *P,
			 const int *N,
			 const int *M,
			 const int *burn,
			 double *runtime,
			 const bool *ortho);

  void rtnorm_left(double *x, double *left, double *mu, double *sig, int *num);

  void rtnorm_both(double *x, double *left, double* right, double *mu, double *sig, int *num);

  void rrtgamma_rate(double *x, double *scale, double *rate, double *right_t, int *num);

}

#endif

//////////////////////////////////////////////////////////////////////
			  // END OF CODE //
//////////////////////////////////////////////////////////////////////

