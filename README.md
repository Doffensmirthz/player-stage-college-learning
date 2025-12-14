# player-stage-college-learning

A set of utilities to use at **player-stage 2.1.1**, designed to test both **VFH** and **ND**.

## How to configure

Set the objective at `main.c` gx,gy and ga.
Set the endpoint (ip/port) at create client.
Compile and decide to use the shell or a script (trigger.sh) to execute both commands.

# The position2d driver


Configure the `.cfg` file so that `position2d1` (or `position2dX`, where `X` is the 
second parameter passed to `playerc_position2d_create` in `main.c`) is mapped to a
commandable driver (for example, `ND` or `VFH`).



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

# Notes

I tried implementing the `player everything.cfg` at main.c using system and fork, both gave me trouble and ended up using [shell scripting](trigger.sh).
