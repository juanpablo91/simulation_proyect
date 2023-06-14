import matplotlib.pyplot as plt # plot
import numpy as np # read data

t, xMercury, yMercury  = np.loadtxt("data.txt", unpack=True)
fig, ax = plt.subplots()
ax.plot(xMercury, yMercury, '-o', label="data")
ax.set_xlabel("iter")
ax.set_ylabel("Percentual diff")
plt.show()
fig.savefig("fig_datos.pdf",bbox_inches='tight')

