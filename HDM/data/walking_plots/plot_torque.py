import numpy as np

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib.animation as animation



def plot(angles_ori, row, i, type):
    plt.plot(range(row), angles_ori[:, 4, i], type , label= 'r_elbow')
    plt.plot(range(row), angles_ori[:, 8, i], type , label= 'l_elbow')

    plt.plot(range(row), angles_ori[:, 12, i], type , label= 'r_hip')
    plt.plot(range(row), angles_ori[:, 16, i], type , label= 'l_hip')

    plt.plot(range(row), angles_ori[:, 13, i], type , label= 'r_knee')
    plt.plot(range(row), angles_ori[:, 17, i], type , label= 'l_knee')



Jointlist = ["", ""]

nJoint = 22

folder = "."

f= open(folder+'/test_torque_round2.txt')
joint_torque_ori2 = [float(x.strip('\n')) for x in f.readlines()]
row1 = len(joint_torque_ori2)
row1 = int(row1 / (nJoint*3))
torque_ori2 = np.reshape(joint_torque_ori2, (row1,nJoint,3))


#f= open(folder+'/totals.txt')
#joint_torque_ori4 = [float(x.strip('\n')) for x in f.readlines()]
#row = len(joint_torque_ori4)
#row = int(row / (nJoint*3))
#torque_ori4 = np.reshape(joint_torque_ori4, (row,nJoint,3))
#torque_ori4_1 = torque_ori4[0:row // 2]
#torque_ori4_2 = torque_ori4[row // 2:]


axis = 0
plot(torque_ori2, row1, axis, '-')

#plot(torque_ori4_1, row // 2, 0, '-')
#plot(torque_ori4_2, row // 2, 0, '*')

plt.xlabel('frame')
plt.ylabel('Torque(Nm)')
plt.legend()
plt.show()



