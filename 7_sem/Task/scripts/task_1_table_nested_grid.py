import os
import math
import sys

pid = os.getpid()
tmpfile = f'res_{pid}.txt'

if len(sys.argv) != 2:
    print(f'Use: python3 {sys.argv[0]} EXE')
    exit(0)

exe = sys.argv[1]

M_set = [10, 100, 1000]

mu_set = [.1, .01, .001]
C_set = [1, 10, 100]

colums = 4

def create_table(c, gamma, mu):
    print(r'\begin{table}[H]')
    print(r'\centering')
    print(r'\begin{tabular}{|c|' + 'c|' * colums + r'}')
    print(r'\hline')
    print(r'\diagTHk', end = '')
    for i in range(1, colums):
        print(r' & $1/' + str(int(math.pow(2, i))) + r'$', end = '')
    print(r' & $u$', end = '')
    print(r' \\')
    print(r'\hline')

    #resids = []
    for M in M_set:
        command = f'{exe} 2 1 1 {c} {gamma} {mu} {M} {M} > {tmpfile}'
        os.system(command)
        with open(tmpfile, 'r') as f:
            txt = f.read().replace('\n', '')
        resids = txt.split(' ')

        for i in range(colums):
            print(r' & \texttt{' + resids[3 * i] + r'}', end = '')
        print(r' \\')

        print(r'$10^{-' + str(int(math.log10(M))) + r'}$')

        for i in range(colums):
            print(r' & \texttt{' + resids[3 * i + 1] + r'}', end = '')
        print(r' \\')

        for i in range(colums):
            print(r' & \texttt{' + resids[3 * i + 2] + r'}', end = '')
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

'''
9.584758e+00 4.577004e+00 4.894111e+01 
2.071762e+01 8.654796e+00 8.185248e+01 
9.584758e+00 4.196730e+00 4.704864e+01 
2.071762e+01 8.883265e+00 7.600471e+01 
1.181652e+01 4.893319e+00 3.968220e+01 

[['9.584758e+00', '4.577004e+00', '4.894111e+01', 
  '2.071762e+01', '8.654796e+00', '8.185248e+01', 
  '1.325387e+01', '5.659948e+00', '5.468561e+01', 
  '1.325387e+01', '5.659948e+00', '5.468561e+01', 
  '1.181652e+01', '4.893319e+00', '3.968220e+01', ''], 

 ['3.196891e+00', '1.993162e+00', '3.917889e+01', '2.016810e+03', '2.366805e+02', '2.625421e+04', '2.323232e+01', '6.133694e+00', '1.548631e+02', '1.862079e+01', '5.584740e+00', '2.198958e+02', '1.443212e+00', '8.042684e-01', '7.933857e+00', ''], 
 ['1.558378e+01', '2.191799e+00', '7.389106e+02', '4.488682e+04', '5.311051e+03', '7.364670e+06', '2.950597e+00', '', '', '', '', '', '', '', 'nan', '', '', '', '', '', '', '', 'nan', '2.950597e+00', '1.608954e+00', '8.776668e+01', '1.443281e+00', '8.003429e-01', '7.912020e+00', '']]
'''