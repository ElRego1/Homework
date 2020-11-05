// Copyright Robert Lica robertlica21@gmail.com
package map;

import player.AbstractPlayer;

import java.util.ArrayList;

public final class Cell {
    private int x, y;
    private Enviroments type;
    private ArrayList<AbstractPlayer> playersInCell;

    public Cell(final int x, final int y, final String environmentType) {
        playersInCell = new ArrayList<>();
        this.x = x;
        this.y = y;
        switch (environmentType) {
            case "L":
                this.type = Enviroments.Land;
                break;
            case "V":
                this.type = Enviroments.Volcanic;
                break;
            case "D":
                this.type = Enviroments.Desert;
                break;
            case "W":
                this.type = Enviroments.Woods;
                break;
            default:
                System.out.println("\t\t*****ERROR: Invalid Terrain Modifier!!!");
        }
    }

    public void removePlayerFromCell(final AbstractPlayer player) {
        playersInCell.remove(player);
    }

    public void enterPlayerInCell(final AbstractPlayer player) {
        playersInCell.add(player);
    }

    public ArrayList<AbstractPlayer> getPlayersInCell() {
        return playersInCell;
    }

    public Enviroments getType() {
        return type;
    }
    public int getX() {
        return x;
    }
    public int getY() {
        return y;
    }
}
