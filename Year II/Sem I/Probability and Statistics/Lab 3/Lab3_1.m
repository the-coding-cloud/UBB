clc
clear all
m = 1;
s = 2;
n = 10;

% a)

am = cdf('Normal',0,m,s);
at = cdf('t', 0, n);

fprintf('a)\n')
fprintf('NORMAL\n')
fprintf('P(X<=0) = %f\n', am)
fprintf('P(x>=0) = %f\n', 1-am)

fprintf('STUDENT\n')
fprintf('P(X<=0) = %f\n', at)
fprintf('P(x>=0) = %f\n', 1-at)

% b)
bn = cdf('Normal', 1, m, s) - cdf('Normal', -1, m, s);
bt = cdf('t', 1, n) - cdf('t', -1, n);

fprintf('b)\n')
fprintf('NORMAL\n')
fprintf('P(-1<=X<=1) = %f\n', bn)
fprintf('P(X<=-1 or X>=1) = %f\n', 1-bn)

fprintf('STUDENT\n')
fprintf('P(-1<=X<=1) = %f\n', bt)
fprintf('P(X<=-1 or X>=1) = %f\n', 1-bt)

% c)
alpha = 0.6;
xna = icdf('Normal', alpha, m, s);
xta = icdf('t', alpha, n);

fprintf('Normal\n')
fprintf('Quantile of order %f is %f\n', alpha, xna)
fprintf('Student\n')
fprintf('Quantile of order %f is %f\n', alpha, xta)

% d)
beta = 0.3;
xnb = icdf('Normal', 1-beta, m, s);
xtb = icdf('t', 1-beta, n);

fprintf('Normal\n')
fprintf('Quantile of order 1-%f is %f\n', 1-beta, xnb)
fprintf('Student\n')
fprintf('Quantile of order 1-%f is %f\n', 1-beta, xtb)
