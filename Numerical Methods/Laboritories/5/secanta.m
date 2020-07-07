function [m, steps] = secanta(m_o, m_i, p, tol)
  steps = 0;
  while (1)
    steps++;
    m = m_i - polyval(p, m_i) * (m_i - m_o) / (polyval(p, m_i) - polyval(p, m_o));
    if (polyval(p, m) == 0)
      return;
    elseif (abs((m - m_i) / m_i) < tol)
      return;
    endif
    m_o = m_i;
    m_i = m;
  endwhile
endfunction
