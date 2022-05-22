import matplotlib.pyplot as plt
import numpy as np

plt.rc ('text', usetex = True)
plt.rc ('text.latex', preamble = r'\usepackage[charter, expert, cal = cmcal]{mathdesign}')

def to_name(mode, c, gamma, mu):
    return f'{mode}_{c}_{gamma}_{mu}_1000_1000.txt'

def to_picfile(mode, c, gamma, mu):
    return f'{mode}_{c}_{gamma}_{mu}.png'


def create_pic_2d(in_file, out_file):
    fig = plt.figure ()
    ax = fig.add_subplot (111)
    ax.set_aspect ('auto')

    ax.set_xlabel("Time")
    ax.set_ylabel("Space")

    with open (in_file, 'r') as f:
        t, h = [float (x) for x in next (f).split ()]
        Z = [[float (x) for x in line.split ()] for line in f]

    h = 10 / (len (Z[0]) - 1)
    t = 60 / (len (Z) - 1) 

    x_val = [h * m for m in range (len (Z[0]))]
    y_val = [t * n for n in range (len (Z))]

    X, Y = np.meshgrid (x_val, y_val)

    cp = plt.contourf (Y, X, Z, 1000, cmap = 'nipy_spectral')
    plt.colorbar (cp)

    plt.savefig (out_file, dpi = 300)
    plt.close ()


mode_set = [3, 4] 
C_set = [1, 10]
mu_set = [.1, .01]

for mode in mode_set:
    for mu in mu_set:
        for C in C_set:
            filename = to_name(mode, C, 1, mu)
            picname = to_picfile(mode, C, 1, mu)
            create_pic_2d("all_V_" + filename, "plot_V_" + picname)
            create_pic_2d("all_G_" + filename, "plot_G_" + picname)
        filename = to_name(mode, 1, 1.4, mu)
        picname = to_picfile(mode, 1, 1.4, mu)
        create_pic_2d("all_V_" + filename, "plot_V_" + picname)
        create_pic_2d("all_G_" + filename, "plot_G_" + picname)

