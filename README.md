# Lab-6
 
AI lab to create a goal based vector field pathfinding algorithm.
Functionality of the algorithm demonstrated on a 50x50 grid of tiles.

controls with keyboard 
Buttons

 A = set new start position
 S = set new goal
 click mouse button (any) to toggle if a tile is a wall

Display Controls
1 = show tile IDS
2 = show only vector paths
3 = show costs associated with each tile


run in x86 
SFML used as graphics library
https://www.sfml-dev.org/

Issues

neighbour generation isn't scalable, ran out of time to fix it
path can be put into a position where it cannot reach the goal
the path isn't the true shortest, did not have enough time to add in integration field