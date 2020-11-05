function A_k = task1(image, k)
  %TODO
  
  [U, S, V] = svd(double(imread(image)));
  % tinem minte numai elementele de pe diagonala pt ca i mai eficient
  for i = 1:k
    S_k(i) = S(i, i);
  endfor
  U_k(:, 1:k) = U(:, 1:k);
  V_k(:, 1:k) = V(:, 1:k);
  A_k = U_k*diag(S_k)*V_k';
  round(A_k(:, :));
  % scapam de elementele negative
  for i = 1:size(U)(1)
    for j = 1 : size(S)(2)
      if(A_k(i, j) < 0)
        A_k(i, j) = 0;
      endif
    endfor
  endfor
  %{
  figure(5);
  imshow(uint8(imread(image)));
  figure(6);
  imshow(uint8(A_k));
  %}
  endfunction