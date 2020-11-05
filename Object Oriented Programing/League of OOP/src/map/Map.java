// Copyright Robert Lica robertlica21@gmail.com
package map;

import fileio.FileSystem;
import java.io.IOException;

public final class Map {
    private int n, m;
    private Cell[][] grid;

    public Map() {

    }

    public void createMap(final int rows, final int colloms) {
        this.n = rows;
        this.m = colloms;
        grid = new Cell[n][m];
    }

    public void setTerrain(final FileSystem fs) {
        try {
            for (int i = 0; i < n; ++i) {
                String line = fs.nextWord();
                for (int j = 0; j < m; ++j) {
                    grid[i][j] = new Cell(i, j, line.substring(0, 1));
                    line = line.substring(1);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Cell getCell(final int x, final int y) {
        return grid[x][y];
    }

}
