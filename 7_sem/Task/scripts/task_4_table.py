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

M = 1000
N = 1000

colums = 4

def create_table(mode, c, gamma, mu):
    command = f'{exe} {mode} 1 10 {c} {gamma} {mu} {N} {M} > {tmpfile}'
    os.system(command)
    with open(tmpfile, 'r') as f:
        txt = f.read().replace('\n', '')
    resids = txt.split(' ')

    print(r'\begin{table}[H]')
    print(r'\centering')
    print(r'\begin{tabular}{|c|' + 'c|' * colums + r'}')
    print(r'\hline')
    print(r'\diagPU', end = '')
    for i in range(1, colums+1):
        print(r' & \texttt{' + str(i) + r'}', end = '')
    print(r' \\')
    print(r'\hline')

    for rho in range(colums):
        print(r' \texttt{' + str(rho+1) + r'}', end = '')
        for u in range(colums):
            print(r' & \texttt{' + resids[rho * colums + u] + r'}', end = '')
        print(r' \\ \hline')

    print(r'\end{tabular}')
    print(r'\caption{Время стабилизации при', end = '')
    print(f' $C = {c}$, $\\gamma = {gamma}$ и~$\\mu = {mu}$.', end = '')
    print(r'}')
    print(r'\end{table}')
    print()

create_table(mode, C, gamma, mu)
os.remove(tmpfile)
