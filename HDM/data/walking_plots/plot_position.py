import numpy as np

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.animation as animation



def plot(angles_ori, row, i, type):
    plt.plot(range(row), angles_ori[:, 11, i], type, label= 'r_elbow')
    plt.plot(range(row), angles_ori[:, 8, i], type, label= 'l_elbow')

    plt.plot(range(row), angles_ori[:, 2, i], type, label= 'r_frontWaist')
    plt.plot(range(row), angles_ori[:, 3, i], type, label= 'l_frontWaist')

    plt.plot(range(row), angles_ori[:, 24, i], type, label= 'r_knee')
    plt.plot(range(row), angles_ori[:, 21, i], type, label= 'l_knee')




markerlist = ["", ""]

nMarker = 41

folder = "."
f= open(folder+'/test_position_round1.txt')
body_position_ori = [float(x.strip('\n')) for x in f.readlines()]
row = len(body_position_ori)
row = int(row / (nMarker*4))
position_ori = np.reshape(body_position_ori, (row,nMarker,4))


folder = "."
f= open(folder+'/test_position_round2.txt')
body_position_ori2 = [float(x.strip('\n')) for x in f.readlines()]
row = len(body_position_ori2)
row = int(row / (nMarker*4))
position_ori2 = np.reshape(body_position_ori2, (row,nMarker,4))

#folder = "."
#f= open(folder+'/test_position_round3.txt')
#body_position_ori3 = [float(x.strip('\n')) for x in f.readlines()]
#row = len(body_position_ori3)
#row = int(row / (nMarker*4))
#position_ori3 = np.reshape(body_position_ori3, (row,nMarker,4))

axis = 0
plot(position_ori, row, axis, '-')
plot(position_ori2, row, axis, '.')
#plot(position_ori3, row,  axis, '--')


plt.xlabel('frame')
plt.ylabel('position (m)')
plt.legend()
plt.show()



