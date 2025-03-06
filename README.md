# Two-dimensional-parity-bits

# Description

This project implements a two-dimensional parity bit error detection system for binary messages. The program ensures message integrity by calculating and verifying parity bits for both rows and columns of a matrix representation of the input message.

# Features

✅ Accepts a binary message of length multiple of 7 (with input validation).

✅ Stores the message in a matrix with 7 columns and a variable number of rows.

✅ Computes parity bits for each row and column based on the following rules:


If the number of 1s in a row/column is even, append 0 as the parity bit.

If the number of 1s is odd, append 1.

The bottom-right corner bit serves as a global parity bit.

✅ Displays the resulting matrix after parity bit computation.

✅ Simulates message corruption by randomly flipping a bit in the matrix.

✅ Recalculates the parity bits at the receiver's end and detects the exact corrupted bit.

✅ Outputs the position of the corrupted bit for error correction.

# Usage
Run the program and enter a binary string with a length that is a multiple of 7.

The program generates the matrix and displays it.

A random bit is flipped to simulate an error.

The program identifies the corrupted bit and prints its position.

# Example Run

![image](https://github.com/user-attachments/assets/31c5f861-45e8-4d6a-9668-061f991ccc92)
