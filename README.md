# lemin2

42 project\
Pathfinding for ants !\
In the High Energy Magic building of the Unseen University, Ponder Stibbons and
 some other students created a strange device that uses ants for computation...

Lem-in is a path finding program, in which ants are sent through a maze of rooms linked by pipes. It computes the best combination of paths from a room to another for a given network and number of ants.\
It parses stdin for data about ants, rooms and pipes.

## usage

Compilation:\
\> make\
Usage:	./lem-in [-g/s/p/d/c/a/v] [--ants=X] < map\
&emsp;--help: Display usage and description\
&emsp;-g --debug : enable debug mode\
&emsp;-s --strict : disable strict mode\
&emsp;-p --print : do not print the map\
&emsp;-d --display : enable alternative solution display (incompatible with viewer)\
&emsp;-c --color : enable colorized ants\
&emsp;-a --alt : find alternative path\
&emsp;-v --viewer : enable viewer\
&emsp;--ants=X : set X as number of ants (if X is valid)\
&emsp;viewer controls :\
&emsp;&emsp;left/right : move backward/forward\
&emsp;&emsp;up/down : speed up/down\
&emsp;&emsp;space : pause/unpause\
&emsp;&emsp;return : reset
