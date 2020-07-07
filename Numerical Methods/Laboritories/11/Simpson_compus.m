function arie = Simpson_compus(x, y)
  n = length(x);
  h = (x(n) - x(1)) / n;
  arie = h / 3 * (y(1) + y(n) + 4 * sum(y(2 : 2 : (n - 1))) + 2 * sum(y(3 : 2 : (n - 2))));
endfunction
