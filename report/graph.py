import numpy
import scipy
import matplotlib.pyplot as plt

arr = numpy.genfromtxt("out.txt", delimiter=',')

fig, subplots = plt.subplots()
subplots.plot(numpy.arange(20000), arr)
plt.title("Number of Correctly Recognized Images (out of 10000 test cases)")
plt.xlabel("Number of Iterations")
plt.ylabel("Number of Correctly-Recognized Images")
fig.savefig("network.png")