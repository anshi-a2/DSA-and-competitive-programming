## Resources :

- https://gitlab.com/shrayansh8/interviewcodingpractise/-/tree/main/src/main/java/com/conceptandcoding/LowLevelDesign/LLDTicTacToe?ref_type=heads
- https://www.udemy.com/course/system_design_lld_hld/learn/lecture/41933094#overview
- https://www.lldcoding.com/design-lld-tic-tac-toe-machine-coding



## Problem Statement

Design and implement a Tic Tac Toe game that allows two players to play on a NxN board, alternating turns, and determines the winner or a draw.

---

## Requirements

- **Two Players:** The game is played between two players.
- **Board:** The game uses a NxN board.
- **Turns:** Players take turns to place their symbol (X or O) on the board.
- **Win Condition:** The game detects when a player has won (three in a row, column, or diagonal).
- **Draw Condition:** The game detects when the board is full and the game is a draw.
- **Input Validation:** The game prevents moves to already occupied cells.
- **Extensibility:** Easy to change the board size or add new features.

---

<img width="847" alt="image" src="https://github.com/user-attachments/assets/8f173198-d82c-4a84-ac3d-e18fd1578a38" />

<img width="831" alt="image" src="https://github.com/user-attachments/assets/59693a47-6632-4912-ad04-a286eb81fbf9" />


<img width="846" alt="image" src="https://github.com/user-attachments/assets/412c28c4-d899-4ab8-94d0-634c5161f78d" />

<img width="708" alt="image" src="https://github.com/user-attachments/assets/2a4d3776-6661-49fb-85d5-f1abddf6de43" />

<img width="791" alt="image" src="https://github.com/user-attachments/assets/524df6ee-13c9-4534-b594-a4631fadfb06" />


<img width="997" alt="image" src="https://github.com/user-attachments/assets/b6ebd9f8-447b-4d8d-bc88-9b961fd674c4" />


## Machine Coding :

### Main.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe;

public class Main {

    public static void main(String args[]) {
        TicTacToeGame game = new TicTacToeGame();
        game.initializeGame();
        System.out.println("game winner is: " + game.startGame());
    }
}
```


### TicTacToeGame.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe;

import com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model.*;
import org.antlr.v4.runtime.misc.Pair;

import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class TicTacToeGame {

    Deque<Player> players;
    Board gameBoard;


    public void initializeGame(){

        //creating 2 Players
       players = new LinkedList<>();
        PlayingPieceX crossPiece = new PlayingPieceX();
        Player player1 = new Player("Player1", crossPiece);

        PlayingPieceO noughtsPiece = new PlayingPieceO();
        Player player2 = new Player("Player2", noughtsPiece);

        players.add(player1);
        players.add(player2);

        //initializeBoard
        gameBoard = new Board(3);
    }

    public String startGame(){

        boolean noWinner = true;
        while(noWinner){

            //take out the player whose turn is and also put the player in the list back
            Player playerTurn = players.removeFirst();

            //get the free space from the board
            gameBoard.printBoard();
            List<Pair<Integer, Integer>> freeSpaces =  gameBoard.getFreeCells();
            if(freeSpaces.isEmpty()) {
                noWinner = false;
                continue;
            }

            //read the user input
            System.out.print("Player:" + playerTurn.name + " Enter row,column: ");
            Scanner inputScanner = new Scanner(System.in);
            String s = inputScanner.nextLine();
            String[] values = s.split(",");
            int inputRow = Integer.valueOf(values[0]);
            int inputColumn = Integer.valueOf(values[1]);


            //place the piece
            boolean pieceAddedSuccessfully = gameBoard.addPiece(inputRow,inputColumn, playerTurn.playingPiece);
            if(!pieceAddedSuccessfully) {
                //player can not insert the piece into this cell, player has to choose another cell
                System.out.println("Incorredt possition chosen, try again");
                players.addFirst(playerTurn);
                continue;
            }
            players.addLast(playerTurn);

            boolean winner = isThereWinner(inputRow, inputColumn, playerTurn.playingPiece.pieceType);
            if(winner) {
                return playerTurn.name;
            }
        }

        return "tie";
    }

    public boolean isThereWinner(int row, int column, PieceType pieceType) {

        boolean rowMatch = true;
        boolean columnMatch = true;
        boolean diagonalMatch = true;
        boolean antiDiagonalMatch = true;

        //need to check in row
        for(int i=0;i<gameBoard.size;i++) {

            if(gameBoard.board[row][i] == null || gameBoard.board[row][i].pieceType != pieceType) {
                rowMatch = false;
            }
        }

        //need to check in column
        for(int i=0;i<gameBoard.size;i++) {

            if(gameBoard.board[i][column] == null || gameBoard.board[i][column].pieceType != pieceType) {
                columnMatch = false;
            }
        }

        //need to check diagonals
        for(int i=0, j=0; i<gameBoard.size;i++,j++) {
            if (gameBoard.board[i][j] == null || gameBoard.board[i][j].pieceType != pieceType) {
                diagonalMatch = false;
            }
        }

        //need to check anti-diagonals
        for(int i=0, j=gameBoard.size-1; i<gameBoard.size;i++,j--) {
            if (gameBoard.board[i][j] == null || gameBoard.board[i][j].pieceType != pieceType) {
                antiDiagonalMatch = false;
            }
        }

        return rowMatch || columnMatch || diagonalMatch || antiDiagonalMatch;
    }

}
```


### PieceType.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

public enum PieceType {
    X,
    O;
}
```


### PlayingPiece.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

public class PlayingPiece {

    public PieceType pieceType;

    PlayingPiece(PieceType pieceType) {
        this.pieceType = pieceType;
    }
}
```


### PlayingPieceO.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

public class PlayingPieceO extends PlayingPiece{

    public PlayingPieceO() {
        super(PieceType.O);
    }
}
```


### PlayinPieceX.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

public class PlayingPieceX extends PlayingPiece{

    public PlayingPieceX() {
        super(PieceType.X);
    }
}
```


### Player.java


```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

public class Player {

    public String name;
    public PlayingPiece playingPiece;

    public Player(String name, PlayingPiece playingPiece) {
        this.name = name;
        this.playingPiece = playingPiece;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public PlayingPiece getPlayingPiece() {
        return playingPiece;
    }

    public void setPlayingPiece(PlayingPiece playingPiece) {
        this.playingPiece = playingPiece;
    }
}
```


### Board.java

```java
package com.conceptandcoding.LowLevelDesign.LLDTicTacToe.Model;

import org.antlr.v4.runtime.misc.Pair;

import java.util.ArrayList;
import java.util.List;

public class Board {

    public int size;
    public PlayingPiece[][]board;

    public Board(int size) {
        this.size = size;
        board = new PlayingPiece[size][size];
    }


    public boolean addPiece(int row, int column, PlayingPiece playingPiece) {

        if(board[row][column] != null) {
            return false;
        }
        board[row][column] = playingPiece;
        return true;
    }


    public List<Pair<Integer, Integer>> getFreeCells() {
        List<Pair<Integer, Integer>> freeCells = new ArrayList<>();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == null) {
                    Pair<Integer, Integer> rowColumn = new Pair<>(i, j);
                    freeCells.add(rowColumn);
                }
            }
        }

        return freeCells;
    }

    public void printBoard() {

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] != null) {
                   System.out.print(board[i][j].pieceType.name() + "   ");
                } else {
                    System.out.print("    ");

                }
                System.out.print(" | ");
            }
            System.out.println();

        }
    }
}
```


















