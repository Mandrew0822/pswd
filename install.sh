#!/bin/bash

# Check if OpenSSL development library is installed
if ! [ -x "$(command -v libssl-dev)" ]; then
    echo "OpenSSL development library is not installed. Installing..."
    # Install OpenSSL development library
    apt-get update
    apt-get install -y libssl-dev
else
    echo "OpenSSL development library is already installed."
fi

# Compile the C program with the OpenSSL library
gcc -o pswd pswd.c -I/usr/include/openssl -lssl -lcrypto

# Move the executable to a directory in the system PATH
mv pswd /usr/local/bin/

echo "pswd has been installed and can be run by typing 'pswd' in the terminal."
