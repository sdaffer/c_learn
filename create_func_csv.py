import matplotlib.pyplot as plt
import numpy as np

dt = 0.001  # s
t_max = 10  # s
freq = 10  # Hz
amp = 3
f_path = f"/home/jfeltman/data/test_funcs/{freq}hz_{amp}amp_{t_max}s.csv"
header_str = f"freq={freq}, amp={amp}, t_max={t_max}, dt={dt}"
time_arr = np.linspace(0.0, t_max, num=int(t_max/dt))
func_arr = amp*np.sin(2*np.pi*freq*time_arr)
# func_arr_test = amp*np.cos(2*np.pi*freq*time_arr)

m = 1.0
b = time_arr[-1]/2
# func_arr = m*time_arr + b

save_arr = np.zeros((func_arr.shape[0], 2))
save_arr[:, 0] = func_arr
# save_arr[:, 1] = func_arr_test
# np.savetxt(f_path, func_arr, fmt="%f", header=header_str)
np.savetxt(f_path, save_arr, delimiter=",")

# fig, ax = plt.subplots()
# ax.plot(time_arr, func_arr)
# plt.show()