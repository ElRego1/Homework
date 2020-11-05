function [m, steps] = tangenta(a, p, tol)
  m_old = a;
  steps = 0;
  while (1)
    steps++;
    m = m_old - polyval(p, m_old) / polyval( polyder(p), m_old);
    if (polyval(p, m) == 0)
      return;
    elseif (abs((m - m_old) / m_old) < tol)
      return;
    endif
    m_old = m;
  endwhile
endfunction
