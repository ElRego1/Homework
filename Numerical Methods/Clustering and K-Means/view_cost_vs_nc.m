function view_cost_vs_nc(file_points)
	% TODO compute cost for NC = [1..10] and plot 
  points = dlmread(file_points, ' ', 5, 1);
  for NC = 1:10
    centroids = clustering_pc(points, NC);
    cost(NC) = compute_cost_pc(points, centroids);
  endfor
  figure(2);
  plot(1:10, cost);
end

