import numpy as np

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.animation as animation



def plot(angles_ori, row, i, type):
    plt.plot(range(row), angles_ori[:, 4, i], type, label= 'r_elbow')
    plt.plot(range(row), angles_ori[:, 8, i], type, label= 'l_elbow')

    plt.plot(range(row), angles_ori[:, 12, i], type, label= 'r_hip')
    plt.plot(range(row), angles_ori[:, 16, i], type, label= 'l_hip')

    plt.plot(range(row), angles_ori[:, 13, i], type, label= 'r_knee')
    plt.plot(range(row), angles_ori[:, 17, i], type, label= 'l_knee')



cnt = 250
Jointlist = ["", ""]

nJoint = 22

folder = "."
f= open(folder+'/angles.txt')
joint_angles_ori = [float(x.strip('\n')) for x in f.readlines()]
row = len(joint_angles_ori)
row = int(row / (nJoint*3))
angles_ori = np.reshape(joint_angles_ori, (row,nJoint,3))
angles_ori = angles_ori[:cnt]

f= open(folder+'/altangles.txt')
joint_angles_ori2 = [float(x.strip('\n')) for x in f.readlines()]
row2 = len(joint_angles_ori2)
row2 = int(row2 / (nJoint*3))
angles_ori2 = np.reshape(joint_angles_ori2, (row2,nJoint,3))
angles_ori2 = angles_ori2[180:cnt+180]

print("#########")



plot(angles_ori, cnt, 0, '-')
plot(angles_ori2, cnt, 0, '.')
#plot(angles_ori3, row, 0, '--')


plt.xlabel('frame')
plt.ylabel('Angel(radius)')
plt.legend()
plt.show()



