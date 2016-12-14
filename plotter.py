import numpy as np
import pylab as pl

out = open("task2_solution.txt", 'r')

N = int(out.readline())
x = [None] * N
y = [None] * N

for i in range(N):
	x[i] = float(out.readline())
for i in range(N):
	y[i] = float(out.readline())

pl.plot(x, y,label="Solution")
pl.xlabel("x")
pl.ylabel("y")
pl.grid()
pl.show()

out.close()
