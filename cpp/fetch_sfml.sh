#!/bin/bash

wget https://www.sfml-dev.org/files/SFML-2.6.1-linux-gcc-64-bit.tar.gz
tar -xvzf SFML-2.6.1-linux-gcc-64-bit.tar.gz
rm -rf sfml
mv SFML-2.6.1 sfml
rm SFML-2.6.1-linux-gcc-64-bit.tar.gz
echo -e "\nsfml ready"
