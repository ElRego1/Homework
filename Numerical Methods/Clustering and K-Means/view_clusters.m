% outputs a graphical representation of the clustering solution
function view_clusters(points, centroids)
	% TODO graphical representation coded here
  color = [];
  for i = 1 : rows(points)
      for j = 1 : length(centroids(:, 1))
           norms(j) = norm(points(i, :) - centroids(j, :));
      endfor
      index = find(norms == min(norms));
      color(i) = index;
    endfor
    figure(1);
    scatter3(points(:,1), points(:,2), points(:,3), 20, color, "s", 'filled');
end

