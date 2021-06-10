# Zappy
Zappy - EPITECH project. The goal of this project is to create a network game. Several teams confront on a tiles map containing resources. The winning team is the one with 6 players who reached maximum elevation. The following pages describe all the details and constraints.

# Makefile
```bash
make
make re
make fclean
make clean
```

# USAGE SERVER
```bash

./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq

#DESCRIPTION
  port is the port number
  width is the width of the world
  height is the height of the world
  nameX is the name of the team X
  clientsNb is the number of authorized clients per team
  freq is the reciprocal of time unit for execution of actions
```

# USAGE GUI
```bash

./zappy_gui -p port -h machine

#DESCRIPTION
  port is the port number
  machine is the name of the machine; localhost by default
```

# USAGE AI
```bash

./zappy_ai -p port -n name -h machine
#DESCRIPTION
  port is the port number
  name is the name of the team
  machine is the name of the machine; localhost by default
```