#!/bin/bash
# lanzar player
player /home/ic/installations/player-stage/stage-2.1.1/worlds/everything.cfg & 
PLAYER_PID=$!

sleep 10

/home/ic/code/client

kill $PLAYER_PID
wait $PLAYER_PID
