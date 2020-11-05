function [m A eigenfaces pr_img] = eigenface_core(database_path)
  %TODO
  database_path = strcat(database_path, '/');
  T = [];
  no_images = 10;
  for i = 1:no_images
    image = strcat(database_path, int2str(i), '.jpg');
    img = double(rgb2gray(imread(image)));
    T = [T, img(:)];
  endfor
  
  suma = sum(T');
  m = [];
  for i = 1:size(T)(1)
    m = [m, suma(i) / no_images];
  endfor
  
  m = m';
  A = T - m;
  [V_nono, eig_diag] = eigs(A' * A, size(A)(1));
  V = [];
  for i = 1:rows(V_nono)
    if eig_diag(i,i) > 1 
      V = [V, V_nono(:, i)];
    else
      break;     
    endif
  endfor
  eigenfaces = A * V;
  pr_img = eigenfaces' * A;
endfunction