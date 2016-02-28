# Project #20 LEM-IPC, Feb 2016
>>>>> #####System V IPCs

#####Grade ``(TBD/100)`` ``(TBD/125)*``
--------  -----------------------

#####Goals:
- [ ] Code in C, observe school's C norm, turn a Makefile, never crash.
- [X] Create a game where each process is an IA player, use SysV IPCs to organize the game.
- [X] Only one binary for players, the first player in generate the IPCs, the last player out destroys it.
- [X] A board must be stored in **Shared memory**, each player has a position on it.
- [X] A **Semaphore** controls access to the board, a player can move in any of the 4 directions.
- [ ] A player belong to a team. If a player is surrounded by 2 players of a same enemy team, it must leave the game.
- [ ] Teammates can only communicate with **Messages Queues**.
- [ ] Display the board content.

#####Recommended bonuses:
- [ ] Pretty graphic interface for the board.
- [ ] Competitive IA.

#####My work:
- [ ] Robust code versus all kind of attacks but: 1. IPCs corruption from the outside, 2. Process killed with semaphore control.
- [ ] Signal handling to leave properly.
<BR><BR>
- [X] A SEM to guard resources creation/destruction/fetch.
- [X] A MSQ containing all players PIDs (used as a tiny protection versus killed processes).
- [X] A SHM containing some data that was passed to the first process as arguments, (board size, num teams).
- [X] A SHM for the board (sizeof(int) * board_width * board_width).
- [ ] Several MSQs for teammates communications.
- [X] A SEM for the board read/write operations and for the teammates MSQs.
<BR><BR>
- [X] Abstraction of the resources Creation/Destruction such that previous steps can be reverted in case of trouble. ([ressources_life.c](./srcs/ressources_life.c?ts=4))

<br><br><br><br><br><br>


```
All my C files strictly observes school's norm, it may often lead to odd or illogical syntaxes.
- [ ] Forbiden keywords: for, do, switch, goto.
- [ ] No more than 25 lines inside a function block.
- [ ] No more than 80 characters per lines.
- [ ] At most 5 functions per files.
- [ ] Only 1 declaration per line.  
- [ ] No declaration and assignation on the same line.
- [ ] At most 1 assignation per line.
- [ ] No more than 4 parameters for a function.
- [ ] No nested ternary.
```
```
*
- A grade of 85 was required to validate the project.
- A maximum grade of 125 was reachable.
- Second sessions are organised for failed projects.
```
