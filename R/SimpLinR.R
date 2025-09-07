# R/SimpLinR.R
#' Simple Linear Regression (minimal, with SE & 95% CI)
#' @param x numeric vector (predictor)
#' @param y numeric vector (response)
#' @return list: beta0_hat, beta1_hat, se_beta0, se_beta1,
#'               ci_beta0_95, ci_beta1_95, residuals, fitted, predicted
#' @export
SimpLinR <- function(x, y) {
  if (!is.numeric(x) || !is.vector(x) || !is.numeric(y) || !is.vector(y)) {
    stop("x and y must be numeric vectors", call. = FALSE)
  }
  if (length(x) != length(y)) {
    stop("x and y must be the same length", call. = FALSE)
  }
  SimpLinCpp(x, y)
}

