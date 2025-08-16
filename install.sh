#!/bin/bash

if ! command -v gcc &> /dev/null; then
    echo "gcc not found. Installing gcc..."
    sudo apt-get update
    sudo apt-get install -y gcc
else
    echo "gcc is already installed. using it"
    gcc main.c -o cps
    sudo cp cps /usr/local/bin/cps
    echo "cps installed successfully."
fi