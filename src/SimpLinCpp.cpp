// src/SimpLinCpp.cpp
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::List SimpLinCpp(const arma::vec& x, const arma::vec& y) {
  // Means
  double xbar = arma::mean(x);
  double ybar = arma::mean(y);
  
  // Centered vectors
  arma::vec xc = x - xbar;
  arma::vec yc = y - ybar;
  
  // Sufficient statistics
  double Sxx = arma::dot(xc, xc);
  double Sxy = arma::dot(xc, yc);
  
  // Coefficients
  double beta1 = Sxy / Sxx;
  double beta0 = ybar - beta1 * xbar;
  
  // Predicted & residuals
  arma::vec pred = beta0 + beta1 * x;
  arma::vec resid  = y - pred;
  
  // SE & 95% CI
  int n       = x.n_elem;
  double RSS  = arma::dot(resid, resid);
  double df   = n - 2.0;
  double sigma2 = RSS / df;
  
  double se_b1 = std::sqrt(sigma2 / Sxx);
  double se_b0 = std::sqrt(sigma2 * (1.0 / n + (xbar * xbar) / Sxx));
  
  double crt_val = R::qt(0.975, df, /*lower_tail=*/1, /*log_p=*/0); // two-sided 95%
  
  NumericVector ci_b1 = NumericVector::create(beta1 - crt_val * se_b1,
                                              beta1 + crt_val * se_b1);
  NumericVector ci_b0 = NumericVector::create(beta0 - crt_val * se_b0,
                                              beta0 + crt_val * se_b0);
  
  return List::create(
    _["beta0_hat"]   = beta0,
    _["beta1_hat"]   = beta1,
    _["se_beta0"]    = se_b0,
    _["se_beta1"]    = se_b1,
    _["ci_beta0_95"] = ci_b0,
    _["ci_beta1_95"] = ci_b1,
    _["residuals"]   = resid,
    _["predicted"]   = pred
  );
}
