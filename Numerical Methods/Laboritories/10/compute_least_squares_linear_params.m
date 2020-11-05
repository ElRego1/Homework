% TODO: compute a0, a1
function [a0, a1] = compute_least_squares_linear_params(x, y)
  m = length(x);
	a0 = (sum(x .^ 2) * sum(y) - sum(x .* y) * sum(x)) / (m * sum(x .^ 2) - sum(x) ^ 2);
	a1 = (m * sum(x .* y) - sum(x) * sum(y)) / (m * sum(x .^ 2) - sum(x) ^ 2);
endfunction
