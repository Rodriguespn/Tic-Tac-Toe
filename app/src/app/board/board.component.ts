import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss']
})

export class BoardComponent implements OnInit {
  myForm: FormGroup;
  begin: boolean = false;

  squares: any[];
  xIsNext: boolean;
  winner: string;

  constructor(private fb: FormBuilder) {}

  ngOnInit(): void {
    this.myForm = this.fb.group({
      playerOne: ['Player1', [
        Validators.required,
        Validators.maxLength(15)
      ]],
      playerTwo: ['Player2',[
        Validators.required,
        Validators.maxLength(15)
      ]]
    })
  }

  get playerOne() {
    return this.myForm.get('playerOne');
  }

  get playerTwo() {
    return this.myForm.get('playerTwo');
  }

  newGame(): void {
    this.begin=true;
    const formValue = this.myForm.value;
    console.log()

    this.squares = Array(9).fill(null);
    this.winner = null;
    this.xIsNext = true;
  }

  get player(): string{
    return this.xIsNext ? 'X' : 'O';
  }

  currentPlayer(): string {
    return this.player=='X' ? this.playerOne.value : this.playerTwo.value;
  }

  makeMove(idx: number): void {
    if (!this.squares[idx]) {
      this.squares.splice(idx, 1, this.player);
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

    // tslint:disable-next-line:prefer-for-of
    for (let i = 0; i < lines.length; i++) {
      const [a, b, c] = lines[i];
      if (this.squares[a] &&
        this.squares[a] === this.squares[b] &&
        this.squares[a] === this.squares[c]
      ) {
        if (this.squares[a] == 'X')
          return this.playerOne.value;
        else {
          return this.playerTwo.value; 
        }
      }
    }
    return null;
  }

}
