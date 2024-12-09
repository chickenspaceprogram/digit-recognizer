import numpy
import scipy
import matplotlib.pyplot as plt

arr = numpy.genfromtxt("test-2layer-10node-act0.3-2/out.txt", delimiter=',')

fig, subplots = plt.subplots()
subplots.plot(numpy.arange(20000), arr)
plt.title("Number of Correctly Recognized Images (out of 10000 test cases)")
plt.xlabel("Number of Iterations")
plt.ylabel("Number of Correctly-Recognized Images")
fig.savefig("network.png", dpi=1200)