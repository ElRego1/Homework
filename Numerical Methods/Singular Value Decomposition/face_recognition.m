function [min_dist output_img_index] = face_recognition(image_path, m, A, eigenfaces, pr_img)
  %TODO
  img = double(rgb2gray(imread(image_path)));
  img = img(:);
  img = img - m;


  pr_test_img = eigenfaces' * img;
  min_dist = norm(pr_img(:, 1) - pr_test_img);
  output_img_index = 1;
  for i = 2:10
    if norm(pr_img(:, i) - pr_test_img) < min_dist
      min_dist = norm(pr_img(:, i) - pr_test_img);
      output_img_index = i;
    endif
  endfor
end