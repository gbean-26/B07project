# B07project
Chess Game
Due Date 1: Tuesday, November 17, 2026, 5:00 pm EST
Due Date 2: Tuesday, December 1, 2026, 5:00 pm EST

## How to use

These commands describe the game interface.

### Starting a Game

Enter `game <white-player> <black-player>`.

Each player can be `human` or `computer[1]` through `computer[4]`.

Examples:
- `game human human` — two human players
- `game human computer[2]` — human as White, level 2 computer as Black
- `game computer[1] computer[3]` — two computer players

White moves first in a standard game.

### Making Moves

| Command | Action |
| --- | --- |
| `move e2 e4` | Move a piece from e2 to e4 |
| `move e1 g1` | Castle kingside, if legal |
| `move e1 c1` | Castle queenside, if legal |
| `move e7 e8 Q` | Move a pawn to e8 and promote it to a queen |
| `move` | Ask the current computer player to make a move |
| `resign` | Concede the game to the opponent |

Promotion choices are queen (`Q`), rook (`R`), bishop (`B`), or knight (`N`).
Use the appropriate case for the piece’s colour.

Illegal moves are rejected. The board is displayed after every move command.

### Custom Board Setup

Enter `setup` when no game is running.

| Command | Action |
| --- | --- |
| `+ K e1` | Place a white king on e1, replacing any existing piece |
| `+ k e8` | Place a black king on e8 |
| `- e1` | Remove the piece on e1 |
| `= white` | Set White to move next |
| `= black` | Set Black to move next |
| `done` | Finish setup if the position is valid |

Uppercase letters represent white pieces; lowercase letters represent black pieces.
Piece symbols are `K`, `Q`, `R`, `B`, `N`, and `P`.

To finish setup:
- There must be exactly one king of each colour.
- Neither king may be in check.
- No pawns may be on the first or last rank.

After leaving setup, use `game` to select the players and start playing.

### Results and Scores

The game reports check, checkmate, stalemate, and resignation.

- A win awards 1 point to the winner.
- A draw awards 0.5 points to each player.
- Scores carry over between games in the same session.

Press Ctrl-D to end the program and display the final scores.
