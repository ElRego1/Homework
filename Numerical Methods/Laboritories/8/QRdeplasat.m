function [valori_proprii] = QRdeplasat(A)
  n = length(A);
  tol = 0.000001;
  valori_proprii = [];
  for i = 1:(length(A) - 1)
    while 1
      B = [A(n-1, n-1), A(n-1, n); A(n,n-1), A(n, n)];
      C = eig(B);
      for k = 1:2
        C(k) = abs(C(k));
      endfor
      sig = min(C);
      %sig = A(n, n);
      
      B = A - sig*eye(n);
      [Q,R] = qr(B);
      A = R * Q + sig*eye(n);
      if abs(A(n, n-1)) < tol
        valori_proprii = [valori_proprii, A(n, n)];
        A = A(1:n - 1, 1:n - 1);
        n = n - 1;
        break;
      endif
    endwhile
  endfor
  valori_proprii = [valori_proprii, A(1, 1)];
endfunction
