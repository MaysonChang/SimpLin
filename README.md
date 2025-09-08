# SimpLin

This package is mainly used for running simple linear regression implemented in C++ via Rcpp/RcppArmadillo.

## Installation

```r
# install.packages("remotes")
remotes::install_github("MaysonChang/SimpLin")
# with vignettes:
# remotes::install_github("MaysonChang/SimpLin", build_vignettes = TRUE)
```

## Example

This is a basic example which shows you how to run a linear regression with simulated data:

```{r example}
library(SimpLin)
set.seed(123); n <- 200
x <- rnorm(n); y <- 1 + 2*x + rnorm(n)
fit <- SimpLinR(x, y)
str(fit, max.level = 1)

```

## Vignette

```{r, eval=FALSE}
# After installing the package:
browseVignettes("SimpLin")
# or open a specific article:
vignette("SimpLin-intro", package = "SimpLin")
```
