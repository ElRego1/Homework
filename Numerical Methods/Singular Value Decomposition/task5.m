function task5(image)
  %TODO
  A = double(imread(image));
  [A_k, S] = task3(image, min(size(A)(1), size(A)(2)));
  figure(1);
  plot(diag(S));
  S_safe = S;
  
  % asta imi seteaza finetea
  INCREMENT = 8;
  S2_k = [];
  S3_k = [];
  S4_k = [];
  k_vector = [];
  k = 1;
  while (k < (min(size(S_safe)(1), size(S_safe)(2)) - 1))
    k_vector = [k_vector, k];
    
    % pentru graficul al 2-lea
    temp_sum = 0;
    for i = 1:k
      temp_sum = temp_sum + S_safe(i, i);
    endfor
    S2_k = [S2_k, temp_sum / sum(diag(S_safe))];
    
    % pentru graficul al 3-lea
    [A_k, S] = task3(image, k);
    S3_k = [S3_k, media_suma(A, A_k)];
  
    S4_k = [S4_k, (2 * k + 1) / size(A)(2)];
  
    k = k + INCREMENT;
  endwhile
  k_vector = [k_vector, min(size(S)(1), size(S_safe)(2))];
  
  temp_sum = 0;
  for i = 1:min(size(S_safe)(1), size(S_safe)(2))
    temp_sum = temp_sum + S_safe(i, i);
  endfor
  S2_k = [S2_k, temp_sum / sum(diag(S_safe))];
  figure(2);
  plot(k_vector, S2_k);

  [A_k, S] = task3(image, min(size(S_safe)(1), size(S_safe)(2)));
  S3_k = [S3_k, suma = media_suma(A, A_k)];
  figure(3);
  plot(k_vector, S3_k);
  
  S4_k = [S4_k, (2 * min(size(S_safe)(1), size(S_safe)(2)) + 1) / size(A)(2)];
  figure(4);
  plot(k_vector, S4_k);
endfunction

function suma = media_suma(A, A_k)
  suma = 0;
  suma = sum(sum((A - A_k) .^ 2));
  suma = suma / (size(A)(1) * size(A)(2));
endfunction