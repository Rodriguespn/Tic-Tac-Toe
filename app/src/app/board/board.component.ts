import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})

export class BoardComponent implements OnInit {
  myForm: FormGroup;
  begin = false;

  squares: any[];
  xIsNext: boolean;
  winner: string;

  constructor(private fb: FormBuilder) {}

  ngOnInit(): void {
    this.myForm = this.fb.group({
      playerOne: ['', [
        Validators.required,
        Validators.maxLength(15)
      ]],
      playerTwo: ['', [
        Validators.maxLength(15)
      ]],
      twoPlayersGame: [true]
    });
  }

  get playerOne() {
    return this.myForm.get('playerOne');
  }

  get playerTwo() {
    return this.myForm.get('playerTwo');
  }

  get twoPlayersGame() {
    return this.myForm.get('twoPlayersGame');
  }

  newGame(): void {
    this.begin = true;

    if (!this.twoPlayersGame.value) {
      this.playerTwo.setValue('Computer');
    }

    else if (this.playerTwo.value === '') {
      this.playerTwo.setValue('Player2');
    }

    this.squares = Array(9).fill(null);
    this.winner = null;
    this.xIsNext = true;
  }

  get player(): string{
    return this.xIsNext ? 'X' : 'O';
  }

  currentPlayer(): string {
    return this.player === 'X' ? this.playerOne.value : this.playerTwo.value;
  }

  setPositionValue(idx: number, value): void {
    this.squares.splice(idx, 1, value);
  }

  makeMove(idx: number): void {
    if (!this.winner && !this.squares[idx]) {
        this.setPositionValue(idx, this.player);
        this.xIsNext = !this.xIsNext;
    }
    this.winner = this.calculateWinner();
    if (!this.twoPlayersGame.value && !this.winner) {
      this.computerMove();
      this.xIsNext = !this.xIsNext;
    }
    this.winner = this.calculateWinner();
  }

  calculateWinner(): string {
    const lines = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6],
    ];

    for (let i = 0; i < lines.length; i++) {
      const [a, b, c] = lines[i];
      if (this.squares[a] &&
        this.squares[a] === this.squares[b] &&
        this.squares[a] === this.squares[c]
      ) {
        if (this.squares[a] === 'X') {
          return this.playerOne.value;
        }
        else {
          return this.playerTwo.value;
        }
      }
    }

    let tie = true;
    for (let i = 0; i < this.squares.length; i++) {
      if (!this.squares[i]) {
        tie = false;
      }
    }

    if (tie) {
      return 'tie';
    }

    return null;
  }

  private computerMove(): void {
    const minmaxConst = {
      X: -1,
      O: 1,
      tie: 0,
    };

    function minmaxCalculateWinner(board): number {
      const lines = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6],
      ];

      for (let i = 0; i < lines.length; i++) {
        const [a, b, c] = lines[i];
        if (board[a] &&
          board[a] === board[b] &&
          board[a] === board[c]
        ) {
          return board[a];
        }
      }
      return minmaxConst['tie'];
    }

    function minmax(board, alpha: number, beta: number, player: number): number {
      // How is the position like for player (their turn) on board?
      const winner: number = minmaxCalculateWinner(board);
      if (winner !== minmaxConst['tie']) { return winner * player; }

      let move = -1;
      let score = -2; // Losing moves are preferred to no move
      for (let i = 0; i < board.length; ++i) { // For all moves,
        if (!board[i]) { // If legal,
          board.splice(i, 1, player);
          const thisScore: number = -minmax(board, alpha, beta, player * -1);
          // Pick the one that's worst for the opponent
          if (thisScore > score) {
            score = thisScore;
            move = i;
          }
          // Reset board after try
          board.splice(i, 1, null);

          if (score <= alpha) { return score; }
          if (score < beta) {
            beta = score;
          }
        }
      }
      if (move === -1) { return minmaxConst.tie; }
      return score;
    }

    let x = -1;
    let score = -2;
    const board = new Array(9);
    for (let i = 0; i < this.squares.length; ++i) {
      if (this.squares[i]) {
        board[i] = minmaxConst[this.squares[i]];
      }
    }
    for (let i = 0; i < board.length; ++i) {
      if (!board[i]) {
        board.splice(i, 1, minmaxConst['O']);
        const tempScore: number = -minmax(board, -2, 2, minmaxConst['X']);
        board.splice(i, 1, null);
        if (tempScore > score) {
          score = tempScore;
          x = i;
        }
      }
    }
    // returns a score based on minimax tree at a given node.
    this.setPositionValue(x, 'O');
  }
}
