function y_final = euler(f, x0, y0, x_final, num_pasi)
  dx = (x_final - x0) / num_pasi;
  x = x0;
  y = y0;
  for i =1:num_pasi
    x0 = x + dx;
    y0 = y + f(x, y) * dx;
    x = x0;
    y = y0;
  endfor
  y_final = y;
endfunction
