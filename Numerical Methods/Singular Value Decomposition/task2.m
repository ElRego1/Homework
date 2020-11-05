function task2(image)
   %TODO
   % fac primul grafic
   sum = 0;
   A = double(imread(image));
   [U, S, V] = svd(A);
   for i = 1:min(size(S)(1), size(S)(2))
     S1_k(i) = S(i, i);
     sum += S1_k(i);
   endfor
   figure(1);
   plot(1:min(size(S)(1), size(S)(2)), S1_k);
   
   % asta imi seteaza finetea
   INCREMENT = 8;
   S2_k = [];
   S3_k = [];
   S4_k = [];
   k_vector = [];
   k = 1;
   while (k < (min(size(S)(1), size(S)(2)) - 1))
     k_vector = [k_vector, k];
     
     % pentru graficul al 2-lea
     temp_sum = 0;
     for i = 1:k
       temp_sum = temp_sum + S1_k(i);
     endfor
     S2_k = [S2_k, temp_sum / sum];
     
     % pentru graficul al 3-lea
     A_k = task1(image, k);
     S3_k = [S3_k, media_suma(A, A_k)];
     
     % pentru graficul al 4-lea
     S4_k = [S4_k, (size(S)(1) * k + size(S)(2) * k + k) / (size(A)(1) * size(A)(2))];
     
     k = k + INCREMENT;
   endwhile
   k_vector = [k_vector, min(size(S)(1), size(S)(2))];
   
   temp_sum = 0;
   for i = 1:min(size(S)(1), size(S)(2))
       temp_sum = temp_sum + S1_k(i);
   endfor
   S2_k = [S2_k, temp_sum / sum];
   figure(2);
   plot(k_vector, S2_k);
   
   A_k = task1(image, min(size(S)(1), size(S)(2)));
   S3_k = [S3_k, suma = media_suma(A, A_k)];
   figure(3);
   plot(k_vector, S3_k);
   
   S4_k = [S4_k, (size(S)(1) * min(size(S)(1), size(S)(2)) + size(S)(2) * min(size(S)(1), size(S)(2)) + min(size(S)(1), size(S)(2))) / (size(A)(1) * size(A)(2))];
   figure(4);
   plot(k_vector, S4_k);
   
endfunction

function suma = media_suma(A, A_k)
  %{
  for i = 1:size(A)(1)
    for j = 1:size(A)(2)
      suma = suma + (A(i, j) - A_k(i, j)) * (A(i, j) - A_k(i, j));
    endfor
  endfor
  %}
  suma = 0;
  suma = sum(sum((A - A_k) .^ 2));
  suma = suma / (size(A)(1) * size(A)(2));
endfunction
