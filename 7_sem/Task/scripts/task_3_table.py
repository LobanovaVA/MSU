import os
import math
import sys

pid = os.getpid()
tmpfile = f'res_{pid}.txt'

if len(sys.argv) != 6:
    print(f'Use: python3 {sys.argv[0]} EXE mode C gamma mu')
    exit(0)

exe   = sys.argv[1]
mode  = sys.argv[2]
C     = sys.argv[3]
gamma = sys.argv[4]
mu    = sys.argv[5]

M = 100 #ONLY
N = 1000

string = 10

def create_table(mode, c, gamma, mu):
    command = f'{exe} {mode} 1 1 {c} {gamma} {mu} {N} {M} > {tmpfile}'
    os.system(command)
    with open(tmpfile, 'r') as f:
        txt = f.read().replace('\n', '')
    resids = txt.split(' ')


    print(r'&')
    print(r'\begin{tabular}{c}')

    for i in range (string):
      print(r' \texttt{' + resids[i] + r'} \\', end = '')

    print()
    print(r'\end{tabular}')

create_table(mode, C, gamma, mu)
os.remove(tmpfile)
