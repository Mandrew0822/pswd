#!/bin/bash

# Compile the C program
gcc pswd.c -o pswd

# Move the executable to /bin
sudo mv pswd /bin
