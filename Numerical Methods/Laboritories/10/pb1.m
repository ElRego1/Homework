function pb1(x, y, linspace_size)	
	[a0, a1] = compute_least_squares_linear_params(x, y);

	n = length(x);
	xx = linspace(x(1), x(n), linspace_size);
	yy = [];
	for i = 1:linspace_size
		yy = [yy, a0 + a1 * xx(i)];
	endfor

	figure
	plot(x, y, 'o', xx, yy);

	legend("f(x)", "cmmp-liniar(x)");
	title("Aproximare liniara in sensul celor mai mici patrate");
endfunction
