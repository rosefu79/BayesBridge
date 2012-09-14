#include "Matrix.h"
#include "RNG.hpp"
#include "BridgeWrapper.hpp"
#include "BridgeRegression.h"

int main(int argc, char** argv)
{
  // The data.
  Matrix X; X.read("X.lars", true);
  Matrix y; y.read("Y.lars", true);

  // // True data.
  // Matrix beta_data; beta_data.read("beta.data", true);

  uint M = 100000;
  uint P = X.cols();

  double alpha = 0.5;

  // Least squares.
  Matrix XX(X, X, 'T', 'N');
  Matrix ls(X, y, 'T', 'N');
  symsolve(XX, ls);

  cout << "LS:\n" << ls;

  Matrix beta(P      , (uint)1, M);

  Matrix u    (P, 1, M, 0.0);
  Matrix omega(P, 1, M, 2.0);

  Matrix sig2((uint)1, (uint)1, M);
  Matrix tau ((uint)1, (uint)1, M);

  //bridge_regression_test(beta, u, omega, tau, y, X, 2500.0, alpha, 0.5, 0.5, 500);

  bridge_regression(beta, u, omega,
		    y, X,
		    2500.0, 1.0, 0.5, 100);

  printf("Regression done.  Write out.\n");

  // beta.write("beta.post");
  // u.write("u.post");
  // omega.write("omega.post");
  // tau.write("tau.post");

  // RNG r;
  // Matrix blah(100000);
  // for(uint i = 0; i < blah.vol(); i++)
  //   blah(i) = r.tnorm(2.0, 3.0);
  // blah.write("tn.data");

  // // EM
  // BridgeRegression br(X, y);
  // Matrix beta_EM(P);
  // double tau_seed = 2.0;

  // int iter_direct = br.EM(beta_EM, 50.0, tau_seed, alpha, 10e8, 10e-9, 1000, false);
  // cout << "Not CG...\n";
  // cout << "iters (dir): " << iter_direct << "\n";
  // cout << "beta (EM):\n" << beta_EM;

  // iter_direct = br.EM(beta_EM, 50.0, tau_seed, alpha, 10e8, 10e-9, 1000, true);
  // cout << "CG...\n";
  // cout << "iters (dir): " << iter_direct << "\n";
  // cout << "beta (EM):\n" << beta_EM;

  // // rtnorm
  // Matrix A(2, 2);
  // A << "2 1 0 1";
  // Matrix AA(A, A, 'T', 'N');
  // Matrix beta(2);
  // beta << "0 0";
  // Matrix bmean(2);
  // bmean << "1 0";
  // Matrix b(2);
  // b << "2 1";
  // double sig2 = 1.0;

  // int nsamp = 1;
  // Matrix samp(2, 1, nsamp);
  // samp.fill(0.0);

  // RNG r;
  // BridgeRegression br2(AA, beta);

  // Matrix mn(2); mn.fill(2);

  // for(int i=0; i<nsamp; i++) {
  //   br2.rtnorm_gibbs(beta, bmean, AA, sig2, b, r);
  //   samp[i].copy(beta);
  //   mn(0) += beta(0);
  //   mn(1) += beta(1);
  // }
  
  // cout << "mean: " << hdiveq(mn, (double)nsamp);

  // samp.write("samp.txt");

}
