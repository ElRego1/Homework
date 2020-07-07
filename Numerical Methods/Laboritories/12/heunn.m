function y_final = heunn(f, x0, y0, x_final, num_pasi)
  dx = (x_final - x0) / num_pasi;
  x = x0;
  y = y0;
  a1 = 0.5;
  a2 = 0.5;
  for i =1:num_pasi
    x0 = x + dx;
    k1 = f(x, y);
    k2 = f(x + dx, y + k1 * dx);
    y0 = y + 0.5 * (k1 + k2) * dx;
    x = x0;
    y = y0;
  endfor
  y_final = y;
endfunction