# codes-for-AI-course-homeworks
Some simple codes for AI course.

These codes were my homeworks for my AI course at 2013-2014 fall semester. I put some of the homeworks which are related with that class.
Codes are not fully explained but I tried to add some explanations on comments.
I hope it is helpful for your homeworks.
These are all old works and I add them when I found them on my computer :) that is why there is only two homeworks.

## 1. Homework summary for 8puzzle

Write a program to solve the 8-puzzle problem using the following search algorithms;

* Breadth-first search
* Uniform-cost search
* Depth-first search
* Iterative deepening search
* Greedy Best Search
* A* Search

Test all the algorithms with at least 10 random inputs and calculate both the number of nodes expanded and the maximum number of nodes saved in the memory. Write one page report giving the results of your experiments and make comments on the results. 

**The problem.** The *8-puzzle problem* is a puzzle popularized by Sam Loyd in the 1870s. It is played on a 3-by-3 grid with 8 square blocks labeled 1 through 8 and a blank square. Your goal is to rearrange the blocks so that they are in order. You are permitted to slide blocks horizontally or vertically into the blank square.

## 2. Homework summary for TicTacToe

Write a game program for tic-tac-toe.
Tic-tac-toe (or Noughts and crosses, Xs and Os) is a paper-and-pencil
game for two players, X and O, who take turns marking the spaces in a 3×3
grid. The player who succeeds in placing three respective marks in a
horizontal, vertical, or diagonal row wins the game.

Your program should play perfect Tic-tac-toe (win or draw) given they choose
the first possible move from the following list.

1. **Win:** If the player has two in a row, they can place a third to get three in a row.
2. **Block:** If the [opponent] has two in a row, the player must play the third themself to block the opponent.
3. **Fork:** Create an opportunity where the player has two threats to win (two non-blocked lines of 2).
4. **Blocking an opponent's fork:**
  * *Option 1:* The player should create two in a row to force the opponent
into defending, as long as it doesn't result in them creating a fork.
For example, if "X" has a corner, "O" has the center, and "X" has
the opposite corner as well, "O" must not play a corner in order to
win. (Playing a corner in this scenario creates a fork for "X" to
win.)
  * *Option 2:* If there is a configuration where the opponent can fork, the player should block that fork.
5. **Center:** A player marks the center. (If it is the first move of the game, playing on a corner gives "O" more opportunities to make a mistake and may
therefore be the better choice; however, it makes no difference between perfect players.)
6. **Opposite corner:** If the opponent is in the corner, the player plays the opposite corner.
7. **Empty corner:** The player plays in a corner square.
8. **Empty side:** The player plays in a middle square on any of the 4 sides.
