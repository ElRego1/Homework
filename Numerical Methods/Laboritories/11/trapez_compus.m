function arie = trapez_compus(x, y)
  t0 = clock;
  n = length(x);
  h = (x(n) - x(1)) / n;
  suma = 0;
  for i = 2:(n-1)
    suma = suma + y(i);
  endfor
  arie = h / 2 * (y(1) + y(n) + 2 * suma);
  %arie = h / 2 * (y(1) + y(n) + 2 * sum(y(2:(n - 1))));
  etime(clock(), t0)
  endfunction
