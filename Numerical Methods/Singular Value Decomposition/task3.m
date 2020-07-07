function [A_k S] = task3(image, k)
  %TODO
  A = double(imread(image));
  
  suma = sum(A');
  for i = 1:size(A)(1)
    u(i) = suma(i) / size(A)(2);
  endfor
  
  for i = 1:size(A)(1)
    A(i,:) = A(i,:) - u(i);
  endfor
  
  Z = A';
  Z = Z / sqrt(size(A)(2) - 1);
  
  [U, S, V] = svd(Z);
  
  W = [];
  for i = 1:k
    temp = [];
    temp = [temp, V(:, i)];
    W = [W, temp];
  endfor
  
  Y = W' * A;
  
  A_k = W * Y + u';
endfunction