function [m, steps] = bisectia(a, b, p, tol)
  steps = 0;
  if (polyval(p, a) * polyval(p, b) < 0)
    m_old = min(a, b);  
    while (1)
      steps++;
      m = (a + b) / 2;
      if (polyval(p, a) * polyval(p, m) < 0)
        b = m;
      elseif (polyval(p,a) * polyval(p, m) > 0)
        a = m;
      else
        return; 
      endif
      
      if (abs((m - m_old)/m_old) < tol)
        return;
      endif
      m_old = m;
     endwhile
  endif
endfunction
