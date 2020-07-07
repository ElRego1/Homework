function y_final = runge(f, x0, y0, x_final, num_pasi)
  dx = (x_final - x0) / num_pasi;
  x = x0;
  y = y0;
  a1 = 0.25;
  a2 = 0.25;
  a3 = 0.25;
  a4 = 0.25;
  for i =1:num_pasi
    x0 = x + dx;
    k1 = f(x, y);
    k2 = f(x + dx / 2, y + dx / 2 * k1);
    k3 = f(x + dx / 2, y + dx / 2 * k2);
    k4 = f(x + dx, y + dx * k3);
    y0 = y + (k1 + 2 * k2 + 2 * k3 + k4) * dx / 6;
    x = x0;
    y = y0;
  endfor
  y_final = y;
endfunction