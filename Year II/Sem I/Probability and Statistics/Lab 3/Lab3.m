close all
clc
clear all
n = 30;
p = 0.65;
k = 0:n;
y = pdf('bino',k,n,p);

figure(1)
hold on
bar(k,y,'r')

med = n*p;
sig = sqrt(n*p*(1-p));
x = med - 3*sig:0.01:med + 3*sig;
z = pdf('Normal',x,med,sig);

figure(1)
hold on
plot(x,z,'Color','b','LineWidth',2);