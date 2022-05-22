import matplotlib.pyplot as plt
import numpy as np
import sys

plt.rc ('text', usetex = True)
plt.rc ('text.latex', preamble = r'\usepackage[charter, expert, cal = cmcal]{mathdesign}')

def to_name(mode, c, gamma, mu, N, M):
    return f'{mode}_{c}_{gamma}_{mu}_{N}_{M}.txt'

def to_picfile(mode, c, gamma, mu):
    return f'{mode}_{c}_{gamma}_{mu}.pdf'

def get_del (size):
    if (size == 2000):
        return "/2"
    else:
        return ""

N_set = [1000, 2000]
M_set = [1000, 2000]

def create_V_pic_1d(mode, c, gamma, mu):
    fig, ax = plt.subplots()

    for N in N_set: 
        for M in M_set:
            filename = to_name(mode, c, gamma, mu, M, N);
            file_norm_V = "norm_V" + filename

            with open (file_norm_V, 'r') as f:
                V_val = [float (line) for line in f]

            x_val = np.linspace(0, len(V_val), num=len(V_val))

            ax.set_xlabel(r'$N_0 \tau$')
            ax.set_ylabel(r'$\left\| V \right\|_C$')

            label = r'$ \bar Q_{\tau' + get_del(N) + r', h' + get_del(M) + r'} $'
            ax.plot(x_val, V_val, label=label)

    ax.legend()

    picname = to_picfile(mode, c, gamma, mu);
    plt.savefig ("norm_V_" + picname, dpi = 300)
    plt.close ()


def create_M_pic_1d(mode, c, gamma, mu):
    fig, ax = plt.subplots()

    for N in N_set: 
        for M in M_set:
            filename = to_name(mode, c, gamma, mu, M, N);
            file_diff_mass = "diff_mass_" + filename;

            with open (file_diff_mass, 'r') as f:
                M_val = [float (line) for line in f]

            x_val = np.linspace(0, len(M_val), num=len(M_val))

            ax.set_xlabel(r'$N_0 \tau$')
            ax.set_ylabel(r'$\Delta_{m}$')

            label = r'$ \bar Q_{\tau' + get_del(N) + r', h' + get_del(M) + r'} $'
            ax.plot(x_val, M_val, label=label)

    ax.legend()

    picname = to_picfile(mode, c, gamma, mu);
    plt.savefig ("diff_mass_" + picname, dpi = 300)
    plt.close ()


mode_set = [3, 4] 
C_set = [1, 10]
mu_set = [.1, .01]

for mode in mode_set:
    for mu in mu_set:
        for C in C_set:
            create_V_pic_1d(mode, C, 1, mu)
            create_M_pic_1d(mode, C, 1, mu)
        create_V_pic_1d(mode, 1, 1.4, mu)
        create_M_pic_1d(mode, 1, 1.4, mu)