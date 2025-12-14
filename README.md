# player-stage-college-learning

A set of utilities to use at **player-stage 2.1.1**, designed to test both **VFH** and **ND**.

## Compilation

To compile the client, use the following command:

```
gcc -std=c99 main.c -o main `pkg-config --cflags --libs playerc`
```

# Environments

The environments are based on everything.world. To use them, you need to update the worldfile inside the everything.cfg configuration file.

# Usage

Launch Player with the appropriate configuration file:
```
player everything.cfg
```

Once the world is successfully loaded, execute the client (main compiled from main.c) which contains the objective logic:
```
./main
```
This is done inside the trigger.sh but you got to change the paths.

Ensure that all paths in the scripts and configuration files are correctly set for your environment.
