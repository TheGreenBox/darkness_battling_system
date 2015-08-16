# Hexagonal Tetris Solver - ICFP Contest 2015

This project is a result of participating in the [ICFP Contest 2015][contest_page].

# Goal

If you strip away the contest's rather awesome techno-mythical lore about the
need to automatically generate counter-spells against the dark magic,
the task boils down to creation of a program (the Solver) that plays a
variation of a classical Tetris with a hexagonal cell grid.

The aim of the Solver is to earn maximum points in a variaty of game
sessions (problems) which were provided by the contest organizers.
Every game session has a unique set of settings that shape the
dimensions and structure of the playing board and the structure of the
"hexomino-s" (game pieces, like tetrimino-s in Tetris) that will be spawned
during the corresponding game session.

# Solution

Structurally, the code can be divided into 3 parts:
* Movement and rotation module that handles all the elementary movements
on the hexagonal grid (turns out this is harder than it looks, but the
trick is to move away from Row-Column cell coordinates to XYZ hexogonal
coordinate system)
* Hexomino way-find module (determines where on the current board the hexomino can be put and how to move there; to determine which final hexomino position is preferable, a simple metric, [borrowed from here][metric_source] was used)
* Misc modules like input JSON problem file parsing, generation of
problem solution JSON file etc.

Although the program itself may determine how much points it scored in
a particular game session, this was not implemented due to the fact
that all actual solution verifications and points awarding happened on
the contest server.

[contest_page]: http://icfpcontest.org/
[metric_source]: http://ielashi.com/el-tetris-an-improvement-on-pierre-dellacheries-algorithm/
