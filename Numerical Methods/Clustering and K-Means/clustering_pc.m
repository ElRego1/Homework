% computes the NC centroids corresponding to the given points using K-Means
function centroids = clustering_pc(points, NC)
	centroids = [];
	% TODO K-Means code 
  check_centroids = [];
  check_cost = [];
  % How many times to check centroids for the smallest norm
  no_of_checks = 4;
  
  
  for k = 1 : no_of_checks
    centroids = points(randperm(size(points), NC), :);
    old_centroids(:,:) = centroids(:,:) - 200;
    while centroids != old_centroids && max(norm(centroids - old_centroids,2,"rows")) > 0.0001
      medie_x(1 : NC) = 0;
      medie_y(1 : NC) = 0;
      medie_z(1 : NC) = 0;
      no_conected_points(1 : NC) = 0;
      for i = 1 : rows(points)
        for j = 1 : NC
             norms(j) = norm(points(i, :) - centroids(j, :));
        endfor
        index = find(norms == min(norms));
        medie_x(index) += points(i, 1);
        medie_y(index) += points(i, 2);
        medie_z(index) += points(i, 3);
        no_conected_points(index)++;
      endfor
      
      old_centroids = centroids;
      
      for i = 1: NC
        if no_conected_points(i) > 0
          centroids(i, 1) = medie_x(i) / no_conected_points(i);
          centroids(i, 2) = medie_y(i) / no_conected_points(i);
          centroids(i, 3) = medie_z(i) / no_conected_points(i);
        endif
      endfor
    endwhile
    % Saving the result for later comparison
    check_centroids(k, 1:NC ,1:3) = centroids(1:NC, 1:3);
    check_cost(k) = compute_cost_pc(points, centroids);
  endfor
  
  % Find the centroid with the smallest cost
  index = find(check_cost == min(check_cost));
  
  centroids(1:NC, 1:3) = check_centroids(index(1), 1:NC, 1:3);

  % plot to see how cost may change
  % plot(1:no_of_checks, check_cost);
end
