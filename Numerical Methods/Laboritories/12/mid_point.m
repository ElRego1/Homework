function y_final = mid_point(f, x0, y0, x_final, num_pasi)
  dx = (x_final - x0) / num_pasi;
  x = x0;
  y = y0;
  a1 = 0;
  a2 = 1;
  for i =1:num_pasi
    x0 = x + dx;
    k1 = f(x, y);
    k2 = f(x + dx / 2, y + k1 * dx / 2);
    y0 = y + k2 * dx;
    x = x0;
    y = y0;
  endfor
  y_final = y;
endfunction