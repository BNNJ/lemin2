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

## options

|   Options   |                  Usage                        |
|-------------|-----------------------------------------------|
|--help       | Display usage and description                 |
|-g --debug   | Enable debug mode                             |
|-s --strict  | Disable strict mode (more permissive parsing) |
|-p --print   | Do not print the map                          |
|-d --display | Enable alternative solution display (incompatible with viewer)|
|-c --color   | Enable colorized ants                         |
|-a --alt     | Find alternative path                         |
|-v --viewer  | Enable viewer                                 |
|--ants=X     | Set X as number of ants (if X is valid)       |

viewer controls:
|left/right   | Move backward/forward                         |
|-------------|-----------------------------------------------|
|up/down      | Speed up/down                                 |
|-------------|-----------------------------------------------|
|space        | Pause/unpause                                 |
|-------------|-----------------------------------------------|
|return       | Reset                                         |