#!/bin/bash
VALUE=$xprintidle
if [$VALUE -ge 10000]; then
	echo "No input detected, beginning PVE mode"
	./npc.out
	break
else
	echo "Input detected, beginning PVP mode"
	./tictactoe.out
fi