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


def position_shift(shift, axis, plots):

    markerlist = ["", ""]
    nMarker = 41
    folder = "/Users/lijialiu/Documents/QtVR/data/results"
    f= open(folder+'/test_position_round1.txt')
    body_position_ori = [float(x.strip('\n')) for x in f.readlines()]
    row = len(body_position_ori)
    row = int(row / (nMarker*4))
    position_ori = np.reshape(body_position_ori, (row,nMarker,4))
    position_ori = np.array(position_ori[:-shift])
    
    f= open(folder+'/test_position_round2.txt')
    body_position_ori2 = [float(x.strip('\n')) for x in f.readlines()]
    row = len(body_position_ori2)
    row = int(row / (nMarker*4))
    position_ori2 = np.reshape(body_position_ori2, (row,nMarker,4))
    position_ori2 = position_ori2[shift:]
    
    if plots:
        plot(position_ori, row-shift, axis, '-')
        plot(position_ori2, row-shift, axis, '.')
        plt.xlabel('frame')
        plt.ylabel('position (m)')
        plt.legend()
        plt.show()

    return position_ori, position_ori2


def angle_shift(shift, axis, plots):
    Jointlist = ["", ""]
    nJoint = 22

    folder = "/Users/lijialiu/Documents/QtVR/data/results"
    f= open(folder+'/test_angle_round1.txt')
    joint_angles_ori = [float(x.strip('\n')) for x in f.readlines()]
    row = len(joint_angles_ori)
    row = int(row / (nJoint*3))
    angles_ori = np.reshape(joint_angles_ori, (row,nJoint,3))
    angles_ori = angles_ori[:-shift]

    f= open(folder+'/test_angle_round2.txt')
    joint_angles_ori2 = [float(x.strip('\n')) for x in f.readlines()]
    row = len(joint_angles_ori2)
    row = int(row / (nJoint*3))
    angles_ori2 = np.reshape(joint_angles_ori2, (row,nJoint,3))
    angles_ori2 = angles_ori2[shift:]

    if plots:
        plot(angles_ori, row-shift, axis, '-')
        plot(angles_ori2, row-shift, axis, '.')
        plt.xlabel('frame')
        plt.ylabel('angle (rad)')
        plt.legend()
        plt.show()
    return angles_ori, angles_ori2

def torque(axis, plots):
    Jointlist = ["", ""]
    nJoint = 22
    folder = "/Users/lijialiu/Documents/QtVR/data/results"
    f= open(folder+'/test_torque_round2.txt')
    joint_torque_ori2 = [float(x.strip('\n')) for x in f.readlines()]
    row = len(joint_torque_ori2)
    row = int(row / (nJoint*3))
    torque_ori2 = np.reshape(joint_torque_ori2, (row,nJoint,3))
   
    if plots:
        plot(torque_ori2, row, axis, '-')
        plt.xlabel('frame')
        plt.ylabel('torque (Nm)')
        plt.legend()
        plt.show()
    return torque_ori2

shift = 2
plots = True
frames_start = 25
frames_end = 190
axis = 2

position_ori, position_ori2 = position_shift(shift, axis, plots)
position_ori = np.array(position_ori[frames_start:frames_end])
position_ori2 = np.array(position_ori2[frames_start:frames_end])

angles_ori, angles_ori2 = angle_shift(shift, axis, plots)
angles_ori = np.array(angles_ori[frames_start:frames_end])
angles_ori2 = np.array(angles_ori2[frames_start:frames_end])

torque_ori2 = torque(axis, plots)
torque_ori2 = np.array(torque_ori2[frames_start:frames_end])


def process(data, cnt):
    data_diff = np.linalg.norm(data, axis=2)
    data_norm = data_diff.flatten()
   # data_norm = (data_diff - min(data_diff)) / (max(data_diff) - min(data_diff))
    data_sum = np.sum(data_norm)
    data_avg = data_sum / cnt

    return data_avg

cntA = 22
cntM = 41
cost = [0,0,0]
cost[0] = process(angles_ori - angles_ori2, cntA)
cost[1] = process(position_ori - position_ori2, cntM)
cost[2] = process(torque_ori2, cntA)
print(cost[:2])
object = np.sum(cost[:3])
print(object)


matlabFile = "/Users/lijialiu/Documents/MATLAB/tracing_ver3/test/val.dat"
file = open(matlabFile,"w")
file.write(str(object))
file.close()

matlabFile = "/Users/lijialiu/Documents/QtVR/data/results/done.txt"
file = open(matlabFile,"w")
file.write("done")
file.close()





#exit()
#
#angle_cost = np.sum() /avga
#print(angle_cost)
#
#position_cost = np.sum(np.linalg.norm(position_ori - position_ori2, axis=2)) / avgm
#print(position_cost)
#
#torque_cost = np.sum(np.linalg.norm(torque_ori2, axis=2)) / avga
#print(torque_cost)

#def distance(angles_ori, angles_ori2):
#    frames, joints, axis = angles_ori.shape
#    res = 0
#    diff = angles_ori - angles_ori2
#    for i in range(frames):
#        for j in range(joints):
#            #res += np.linalg.norm([i, j] - angles_ori2[i, j])
#            res +=  np.sqrt(pow(diff[i,j,0],2)+pow(diff[i,j,1],2)+pow(diff[i,j,2],2))
#    return res
#print(distance(position_ori, position_ori2) / avgm)

#def torqueCost(torque_ori2):
#    frames, joints, axis = torque_ori2.shape
#    res = 0
#    for i in range(frames):
#        for j in range(joints):
#            #res += np.sum(abs(torque_ori2[i, j, :]))
#            res += np.linalg.norm(torque_ori2[i, j])
#    return res / 22
#print(torqueCost(torque_ori2))

#def normalization(data):
#    data = (data - min(data)) / (max(data) - min(data))
#    return data
#angle_norm = np.linalg.norm(angles_ori - angles_ori2, axis=2)
#angle_norm = normalization(angle_norm.flatten())
#print(np.sum(angle_norm) / cntA)
#exit()
