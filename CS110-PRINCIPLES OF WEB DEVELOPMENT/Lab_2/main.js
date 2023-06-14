$(".score").text("X: 0 O: 0");
$(".display_player").text("X");

var aiON = false;

$(".vs_game").click(function() {
    aiON = false;
    hardReset();
    stopTimer();
    runPlayerGame();
});

$(".ai_game").click(function() {
    if (aiON === false) {
        aiON = true;
    }
    else {
        aiON = false;
    }
    hardReset();
    stopTimer();
    runPlayerGame();
});

var gameBoard = $(".game_board");
var newGame = $(".new_game");
var reset = $(".reset");
var timer = $(".timer");
var secondsLeft = 5;
var timeLimit = 120;

// Holds the squares that contain Xs and holds the moves made by O
var board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];

// false is X
// true is O
var turn = false;

var score_x = 0;
var score_y = 0;

function startTime() {
    $(".timer").text(secondsLeft);
    $(".timeLeft").text(timeLimit);
    timer = setInterval(function() {
    secondsLeft--;
    timeLimit--;
    $(".timer").text(secondsLeft);
    $(".timeLeft").text(timeLimit);
    if (timeLimit === -1) {
        tieGame();
    }
    else if (secondsLeft === -1) {
        clearInterval(timer);
        endTurn();
    }}, 1000);
}

function endTurn() {
    alert("skipped");
    clearInterval(timer);
    secondsLeft = 5;
    turn = !turn;
    $(".display_player").text(function(){
        if (turn === false) {
            return "X";
        }
        else{
            return "O";
        }
    });
    startTime();
}

function tieGame() {
    alert("Your 2 minutes ran out! Tie game and resetting");
    turn = false;
    $(".display_player").text("X");
    secondsLeft = 5;
    gameBoard.find("span").text("");
    for(var i = 1; i < 10; i++){
        var box = "#box_" + i;
        $(box).attr("is_checked", "false");
    }
    timeLimit = 120;
    board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];
}

function resetGame() {
    secondsLeft = 5;
    timeLimit = 120;
    turn = false;
    board = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];
    gameBoard.find("span").text("");
    for(var i = 1; i < 10; i++){
        $(`#${i}`).attr("is_checked", "false");
    }
    $(".display_player").text("X");
    $(".score").text("X: " + score_x + " O: " + score_y);
}

function stopTimer() {
    clearInterval(timer);
}

function hardReset() {
    score_y = 0;
    score_x = 0;
    timeLimit = 120;
    secondsLeft = 5;
    resetGame();
}

newGame.click(function(){
    resetGame();
});

reset.click(function(){
    hardReset();
});

function winChecker(divID) {
    // Log move onto board and check if win
    /*
    [[0, 0, 0],
     [0, 0, 0],
     [0, 0, 0]]

     divID
     [[1, 4, 7],
      [2, 5, 8],
      [3, 6, 9]]
    */
    if (parseInt(divID) === 1) {
        board[0][0] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 2) {
        board[1][0] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 3) {
        board[2][0] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 4) {
        board[0][1] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 5) {
        board[1][1] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 6) {
        board[2][1] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 7) {
        board[0][2] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 8) {
        board[1][2] = turn ? "O" : "X";
    }
    else if (parseInt(divID) === 9) {
        board[2][2] = turn ? "O" : "X";
    }

    // Check rows
    for (var row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != 0) {
        return board[row][0];
        }
    }
    // Check columns
    for (var col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != 0) {
        return board[0][col];
        }
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)) {
        return board[1][1];
    }
    //alert(board);
    return;
}

function updateDisplay() {
    $(".display_player").text(function(){
        if(turn === false){
            secondsLeft = 5;
            $(".timer").text(secondsLeft);
        }
        else{
            secondsLeft = 5;
            $(".timer").text(secondsLeft);
        }
        return turn ? "O" : "X";
    });
}

function aiMove() {
    var randomInt = Math.floor(Math.random() * 9) + 1;
    while ($(`#${randomInt}`).attr("is_checked") === "true") {
        randomInt = Math.floor(Math.random() * 9) + 1;
    }
    document.getElementById(`${randomInt}`).setAttribute("is_checked", "true");
    document.getElementById(`${randomInt}`).firstChild.textContent = "O";
    var temp = winChecker(randomInt);
    if (temp != null && temp == "O") {
        alert("O wins!");
        score_y += 1;
        resetGame();
    }
    else {
        turn = !turn;
        updateDisplay();
    }
    return;
}

function runPlayerGame() {    
    if (aiON) {
        $(".mode").text(function(){
            return "AI Versus";
        })
    }
    else {
        $(".mode").text(function(){
            return "1v1";
        })
    }

    startTime();
    gameBoard.click(function(event){
        updateDisplay();
        // Turn selector and place move
        if(event.target != this){
            if($(event.target).attr("is_checked") == "false"){
                $(event.target.firstChild).text(function(){
                    return turn ? "O" : "X";
                });
                $(event.target).attr("is_checked", "true");
                updateDisplay();
                // Add to internal moves and see if anyone has won
                var temp = winChecker(event.target.id);
                if (temp != null && temp == "X") {
                    alert("X wins!");
                    score_x += 1;
                    resetGame();
                }
                else if (temp != null && temp == "O") {
                    alert("O wins!");
                    score_y += 1;
                    resetGame();
                }
                else if (aiON) {
                    turn = !turn;
                    aiMove();
                }
                else {
                    turn = !turn;
                    updateDisplay();
                }
            }
        }
    });

}