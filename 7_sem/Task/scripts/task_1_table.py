import os
import math
import sys

pid = os.getpid()
tmpfile = f'res_{pid}.txt'

if len(sys.argv) != 2:
    print(f'Use: python3 {sys.argv[0]} EXE')
    exit(0)

exe = sys.argv[1]

N_set = [10, 100, 1000, 10000]
M_set = [10, 100, 1000, 10000]

mu_set = [.1, .01, .001]
C_set = [1, 10, 100]

def create_table(c, gamma, mu):
    print(r'\begin{table}[H]')
    print(r'\centering')
    print(r'\begin{tabular}{|c|' + 'c|' * len(M_set) + r'}')
    print(r'\hline')
    print(r'\diagTH', end = '')
    for M in M_set:
        print(r' & $10^{-' + str(int(math.log10(M))) + r'}$', end = '')
    print(r' \\')
    print(r'\hline')

    for N in N_set:
        resids = []

        for M in M_set:
            command = f'{exe} 1 1 1 {c} {gamma} {mu} {N} {M} > {tmpfile}'
            os.system(command)
            with open(tmpfile, 'r') as f:
                txt = f.read().replace('\n', '')
            resids += [txt.split(' ')]

        for r in resids:
            print(r' & \texttt{' + r[0] + r'}', end = '')
        print(r' \\')

        print(r'$10^{-' + str(int(math.log10(N))) + r'}$')

        for r in resids:
            print(r' & \texttt{' + r[1] + r'}', end = '')
        print(r' \\')

        for r in resids:
            print(r' & \texttt{' + r[2] + r'}', end = '')
        print(r' \\')

        print(r'\hline')

    print(r'\end{tabular}')
    print(r'\caption{Ошибки для схемы 1 при', end = '')
    print(f' $C = {c}$, $\\gamma = {gamma}$ и~$\\mu = {mu}$.', end = '')
    print(r'}')
    print(r'\end{table}')
    print()


for mu in mu_set:
    for C in C_set:
        create_table(C, 1, mu)
    create_table(1, 1.4, mu)
    
os.remove(tmpfile)
