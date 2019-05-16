# these are the drafts from which the notebook resulted
# can easily be run in Visual Studio Code, with basic python setup, and anaconda env

#%%
import ipywidgets as widgets
import matplotlib.pyplot as plt
import numpy as np

#%%
a = 0
b = 1
N = 100
activ_func_choice = 'step'

scale_sigm = 100
x_split = 1000

def f(x):
    return 0.2 + 0.4 * x ** 2 + 0.3 * np.sin(15 * x) + 0.05 * np.cos(50 * x)

def activ(x, c):
    if c is 'step':
        return np.heaviside(x, 1)
    elif c is 'sigmoid':
        return 1 / (1 + np.exp(-x * scale_sigm))

plt.figure(figsize=(9, 3))
range_x = np.linspace(a, b, x_split)
fx = f(range_x)
plt.plot(range_x, fx)
range_N = np.arange(N+1)
h = (b - a) / (N + 1)
fap = [
    f(a) + 
    np.sum(
        (f(a + (range_N+1) * h) - 
        f(a + range_N * h)) * 
        activ(x - (a + range_N * h), activ_func_choice)
    )
     for x in range_x]

plt.plot(range_x, fap)

#%%
import matplotlib.pyplot as plt
import numpy as np

x1 = -1
x2 = 1

input_layer = np.array([x1, x2])
w01 = np.matrix([
    [1, 1],
    [1, 1]
])
w12 = np.matrix([
    [0.7, -0.4]
])
b1 = np.array([0.5, -1.5])
b2 = np.array([-1])

def activ(x, c='sign'):
    if c is 'sign':
        return np.sign(x)
    elif c is 'step':
        return np.heaviside(x, 1)
    elif c is 'sigmoid':
        return 1 / (1 + np.exp(-x))

def ff(x):
    return activ(w12 @ activ(w01 @ x + b1).transpose() + b2)

from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
xline = np.linspace(-1, 1, 10)
yline = np.linspace(-1, 1, 10)
X, Y = np.meshgrid(xline, yline)
zline = np.array([ff([x, y]) for x in xline for y in yline])
zline = np.reshape(zline, (10, 10))
ax.plot_surface(X, Y, zline)
plt.show()

#%%
plt.plot([-1, 1], [-1, 1], 'bs')
plt.plot([-1, 1], [1, -1], 'r^')

#%%
plt.figure(figsize=(9, 3))
#range_x = np.linspace(0, np.pi * 2, 100)
range_x = np.linspace(-5, 5, 50)
fx = np.sin(range_x)
fx2 = np.sin(4*range_x)
fx3 = 3*np.sin(range_x)
# plt.plot(range_x, fx)
# plt.plot(range_x, fx2)
# plt.plot(range_x, fx3)
plt.plot(range_x, 1/(1 + np.exp(-range_x*100)))
plt.plot(range_x, 1/(1 + np.exp(-range_x)))