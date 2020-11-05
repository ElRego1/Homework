% TODO: compute a0, a1
function [a0, a1] = compute_gradient_descent_step_params(x, y, a0, a1, learning_rate)
	dif_a0 = -2 * sum(y .- (a1 * x) - a0);
  dif_a1 = -2 * sum((y .- (a1 * x) - a0) .* x);
  a0 = a0 - learning_rate * dif_a0;
	a1 = a1 - learning_rate * dif_a1;
endfunction
