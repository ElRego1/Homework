x = [1:10];  
y = [1.3, 3.5, 4.2, 5, 7, 8.8, 10.1, 12.5, 13, 15.6];

xx = linspace(1, 10);
p = polyfit(x, y, length(x));
for i = 1:length(xx)
	yy(i) = polyval(p, xx(i));
endfor

figure
plot(x, y, 'o', xx, yy);
legend("f(x)", "neville(x)");
title("Aproximare polinomiala a lui f(x) cu Neville");
