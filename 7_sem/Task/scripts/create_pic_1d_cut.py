import matplotlib.pyplot as plt
import numpy as np
import sys

plt.rc ('text', usetex = True)
plt.rc ('text.latex', preamble = r'\usepackage[charter, expert, cal = cmcal]{mathdesign}')

def to_name(mode, c, gamma, mu):
    return f'{mode}_{c}_{gamma}_{mu}_1000_1000.txt'

def to_picfile(mode, c, gamma, mu, t):
    return f'{mode}_{c}_{gamma}_{mu}_{t}.pdf'


def create_pic_1d_cut(mode, c, gamma, mu):
    filename = to_name(mode, c, gamma, mu);
    file_V = "all_V_" + filename
    file_G = "all_G_" + filename

    with open (file_V, 'r') as f:
        V_val = [[float (x) for x in line.split ()] for line in f]

    with open (file_G, 'r') as f:
        G_val = [[float (x) for x in line.split ()] for line in f]

    x_val = np.linspace(0, 10, num=len(V_val[0]))

    for i in range (len(V_val)):
        fig, ax = plt.subplots()

        ax.set_xlabel("Spase")
    
        ax.plot(x_val, V_val[i], label=r'$V$')
        ax.plot(x_val, G_val[i], label=r'$G$')

        ax.legend()

        picname = to_picfile(mode, c, gamma, mu, i);
        plt.savefig ("cut_" + picname, dpi = 300)
        plt.close ()

#mode_set = [3, 4]
mode_set = [8]

for mode in mode_set:
    create_pic_1d_cut(mode, 1, 1, 0.1)
