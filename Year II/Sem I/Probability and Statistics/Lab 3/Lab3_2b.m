close all
clc
clear all
n = 30;
p = 0.05;
k = 0:n;
y = pdf('bino',k,n,p);

figure(1)
hold on
bar(k,y,'r')

lambda = n*p;
z = pdf('poiss',k,lambda);

figure(2)
bar(k,z,'b')

bar(k,[y',z'])