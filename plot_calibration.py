import numpy as np
import matplotlib.pyplot as plt

coeffs = [-9.085681659276021e-27, 4.6790804314609205e-23, -1.0317125207013292e-19,
  1.2741066484319192e-16, -9.684460759517656e-14, 4.6937937442284284e-11, -1.4553498837275352e-08,
   2.8216624998078298e-06, -0.000323032620672037, 0.019538631135788468, -0.3774384056850066, 12.324891083404246]

coeffs2 = coeffs[-6:]

xs = np.linspace(0, 100, int(1e5))
ys = np.polyval(coeffs, xs)
y2s = np.polyval(coeffs2, xs)

plt.figure()
plt.plot(xs, ys)
plt.plot(xs, y2s, color='blue')
plt.show()
