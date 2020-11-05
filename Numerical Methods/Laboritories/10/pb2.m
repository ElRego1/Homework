function pb2(x, y, linspace_size)
	a0 = 0; a1 = 0;
	for i = 1:100
		learning_rate = 0.0001;
		old_a0 = a0; old_a1 = a1;
		[a0, a1] = compute_gradient_descent_step_params(x, y, a0, a1, learning_rate);

		if norm([old_a0 - a0, old_a1 - a1]) < 1e-3
			break
		endif

		n = length(x);
		xx = linspace(x(1), x(n), linspace_size);
		yy = [];
		for i = 1:linspace_size
			yy = [yy, a0 + a1 * xx(i)];
		endfor

		%figure
		plot(x, y, 'o', xx, yy);

		legend("f(x)", "cmmp-liniar(x)");
		title("Aproximare liniara in sensul celor mai mici patrate");
		pause(1);
	endfor

	a0
	a1
endfunction
