% computes a clustering solution total cost
function cost = compute_cost_pc(points, centroids)
	cost = 0; 
	% TODO compute clustering solution cost
  for i = 1 : length(points(:, 1))
    for j = 1 : length(centroids(:, 1))
      norms(j) = norm(points(i, :) - centroids(j, :));
    endfor
      cost += min(norms);
  endfor
end
