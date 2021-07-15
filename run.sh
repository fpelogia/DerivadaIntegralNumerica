#!/bin/bash
gcc deriv_int.c -o di -lm 
./di 5 0.01 0
python plot.py
rm di
