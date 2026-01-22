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
np.savetxt(f_path, func_arr, fmt="%f", header=header_str)
# fig, ax = plt.subplots()
# ax.plot(time_arr, func_arr)
# plt.show()