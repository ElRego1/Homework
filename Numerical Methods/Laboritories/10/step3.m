disp("	xi	yi	   xi^2       xi*yi	 P(xi) = 1.538xi - 0.360");

x = [1:10]';
y = [1.3, 3.5, 4.2, 5, 7, 8.8, 10.1, 12.5, 13, 15.6]';
xi2 = x.^2;
xiyi = x.*y;

P = 1.538 * x - 0.360;
M = [x y xi2 xiyi P]

sums = [sum(x), sum(y), sum(xi2), sum(xiyi), sum((y .- P).^2)]
