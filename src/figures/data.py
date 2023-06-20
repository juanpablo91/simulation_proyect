import matplotlib.pyplot as plt # plot
import numpy as np # read data

t, xMercury, yMercury  = np.loadtxt("data.txt", unpack=True)
fig, ax = plt.subplots()
ax.plot(xMercury, yMercury, '-o', label="data")
ax.set_xlabel("X")
ax.set_ylabel("Y")
fig.savefig("orb_datos.pdf",bbox_inches='tight')
plt.show()

