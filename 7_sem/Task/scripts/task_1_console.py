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
    print(r'==================================================================')
    print(r' C = ' + str(c) + f' gamma = ' + str(gamma) + f' mu = ' + str(mu))

    for N in N_set:
        resids = []

        for M in M_set:
            command = f'{exe} 1 1 1 {c} {gamma} {mu} {N} {M} > {tmpfile}'
            os.system(command)
            with open(tmpfile, 'r') as f:
                txt = f.read().replace('\n', '')
            resids += [txt.split(' ')]

        print(r'---------------------------------------------------')
        
        for r in resids:
            print(r[0], end = ' ')
        print()

        for r in resids:
            print(r[1], end = ' ')
        print()

        for r in resids:
            print(r[2], end = ' ')
        print()

    print()


for mu in mu_set:
    for C in C_set:
        create_table(C, 1, mu)
    create_table(1, 1.4, mu)
    
os.remove(tmpfile)
