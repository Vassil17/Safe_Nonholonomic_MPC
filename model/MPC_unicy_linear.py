"""
File containing the class definition of the Model Predictive Controller
"""

import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
from numpy.linalg import inv
from matplotlib import animation
from unicycle import Robot
import forcespro
import get_userid
from quadrotor import Quadrotor
import casadi

"""
Parameters of the class
"""

class MPC():
    def __init__(self, N):
        self.dt = 5e-3
        self.N = N  # planning horizon
        self.stages = forcespro.MultistageProblem(N)  # create the stages for the whole finite horizon
        self.nx = 3
        self.nu = 2
        self.Q = 100*np.diag([4, 40, 0.1])
        self.R = np.eye(self.nu)/100
        self.P = 0 * self.Q
        self.set_up_solver()
        import MPC_Project_FORCESPRO_py
        self.solver = MPC_Project_FORCESPRO_py

    def set_up_solver(self):
        for i in range(self.N):
            self.stages.dims[i]['n'] = self.nx + self.nu  # number of stage variables
            self.stages.dims[i]['r'] = self.nx  # number of equality constraints
            self.stages.dims[i]['l'] = 0  # nx + nu  # number of lower bounds
            self.stages.dims[i]['u'] = 0  # nx + nu  # number of upper bounds

            # Cost/Objective function
            # V = sum_i(z(i)*H*z(i)) + z(N)*H*z(N) -> where z(i) = [u1,u2,x1,x2] at stage/step i.
            if i == self.N - 1:
                # For xN use the terminal cost P to penalise the xN state
                self.stages.cost[i]['H'] = np.vstack(
                    (np.hstack((self.R, np.zeros((self.nu, self.nx)))), np.hstack((np.zeros((self.nx, self.nu)), self.P))))
            else:
                # For i from 0 to N-1 use the stage cost Q to penalise the state
                self.stages.cost[i]['H'] = np.vstack(
                    (np.hstack((self.R, np.zeros((self.nu, self.nx)))), np.hstack((np.zeros((self.nx, self.nu)), self.Q))))

            self.stages.cost[i]['f'] = np.zeros((self.nx + self.nu, 1))  # there's no linear fT*z term in the cost, so set to 0

            # Equality constraints (expressed in the form of C*z(i) + D*z(i+1) = 0, where C = ( B(i) | A(i) ), D = (0 | -I)
            if (i < self.N - 1):
                self.stages.eq[i]['C'] = np.zeros([self.nx, self.nx+self.nu])
            if (i > 0):
                self.stages.eq[i]['c'] = np.zeros((self.nx, 1))
            self.stages.eq[i]['D'] = np.hstack((np.zeros([self.nx, self.nu]), -np.eye(self.nx)))

        # parameter: initial state
        self.stages.newParam("xinit", [1], 'eq.c')  # 1-indexed
        # parameter: linearized model
        for i in range(self.N-1):
            self.stages.newParam("linear_model"+str(i+1), [i+1], 'eq.C')
        # define the output
        self.stages.newOutput('output', range(1, 11), range(1, self.nu + self.nx + 1))
        # # Set up the D matrix and c1 = -A*x0 as varying parameters:
        # stages.newParam(('D_current'+str(i)), i, 'eq.D')

        # solver settings
        self.stages.codeoptions['name'] = 'MPC_Project_FORCESPRO'
        self.stages.codeoptions['printlevel'] = 2
        self.stages.generateCode()

    def control(self, state, Ads, Bds):
        problem = {"xinit": -state}  # eq.c = -xinit
        # set up linearized models as equality constraints
        for i in range(self.N - 1):
            A = Ads[i]
            B = Bds[i]
            problem["linear_model"+str(i+1)] = np.hstack((B, A))
        self.output = self.solver.MPC_Project_FORCESPRO_solve(problem)[0]['output']
        control = self.output[:2]

        return control

# #=======================================================
# just for testing, remove later
from MPC_utils import *
T = 3
dt = 1e-3
Xref = traj_generate(T/dt, T)
Uref = get_ref_input(Xref)
linear_models = linearize_model(Xref, Uref, 1e-3)
# #=========================================================
N = 10
x0 = np.array([1, 0, np.pi/2])
env = Robot(x0[0], x0[1], x0[2])
mpc = MPC(N)
xPos = []
yPos = []
uStore = []
error_t = 0.5 * np.ones(3)
x_error = []
y_error = []

for i in range(int(T/dt)-N):
    # Find the new linearisation (from current step to current step + N
    Ads = linear_models[0][i:i+N]
    Bds = linear_models[1][i:i+N]
    control = mpc.control(error_t, Ads, Bds)
    # Extract the first control inputs:
    u = mpc.output[0:2]
    uStore.append(u)
    # Simulate the motion
    state = env.step(u[0], u[1])
    # Store the xy position for plotting:
    xPos.append(state.x)
    yPos.append(state.y)
    error_t_ = Ads[0] @ error_t + Bds[0] @ u
    x_error.append(error_t_[0])
    y_error.append(error_t_[1])

# plot the robot position
xPos = np.array(xPos)
yPos = np.array(yPos)
fig1,ax1 = plt.subplots()
ax1.plot(Xref[:,0],Xref[:,1],'g')
ax1.plot(xPos,yPos,'r')

# plot the error
x_error = np.array(x_error)
y_error = np.array(y_error)
fig2,ax2 = plt.subplots()
ax2.plot(range(len(x_error)), x_error,'b')
ax2.plot(range(len(y_error)), y_error,'g')
plt.show()