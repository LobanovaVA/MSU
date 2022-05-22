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

N_set = [1000, 2000]
M_set = [1000, 2000]

colums = 5

def create_table(mode, c, gamma, mu):
    for N in N_set: 
        for M in M_set:
            command = f'{exe} {mode} 1 10 {c} {gamma} {mu} {N} {M} > {tmpfile}'
            os.system(command)
            with open(tmpfile, 'r') as f:
                txt = f.read().replace('\n', '')
            resids = txt.split(' ')

            for i in range (colums):
              print(r' & \texttt{' + resids[i] + r'}', end = '')
            print(r' \\')

            for i in range (colums):
              print(r' & \texttt{' + resids[colums + i] + r'}', end = '')
            print(r' \\')
           
    print(r'\hline')
    print()

create_table(mode, C, gamma, mu)
os.remove(tmpfile)
