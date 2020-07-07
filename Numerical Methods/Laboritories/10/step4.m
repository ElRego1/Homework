x = 1:10;
y = [1.3, 3.5, 4.2, 5, 7, 8.8, 10.1, 12.5, 13, 15.6];

xx = linspace(1, 10);
for i = 1:length(xx)
	yy(i) = 1.538 * xx(i) - 0.360;
endfor

figure
plot(x, y, 'o', xx, yy);

legend("f(x)", "cmmp-liniar(x)");
title("Aproximare liniara in sensul celor mai mici patrate");
