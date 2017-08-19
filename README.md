# Pid Controller

I have used manual tuning to arrive at the pid controller coefficients to calculate the steering control.

## Effect of P-,I-,D-controllers:
### Propotional controller
The propotional controller tries to compensate cross track error (CTE) which is calculated as  directly propotional to the cross track error. Upon using just the propotional controller, the car never reaches the desired trajectory (CTE = 0) and it keeps overshooting it.
As the speed of the car is increasing initially, the magnitude of the oscillations keep increasing. The goal should be to arrive at a  coefficient for P-controller such that oscillations are minimal.
Setting Kp = 0.1 led to CTE correction but also led to oscillations because of the overshoot and increasing velocity.

![Video Link 1](./pid_kp_0.1.mp4)

Increasing Kp also increased the amplitude of the oscillations.

### Derivative controller
The D-controller along with P-controller tries to reduce the overshooting of the car so that it converges to the desired trajectory (CTE = 0). It does this by adding a term propotional to the derivative of the cross track error. The D-controller is actually propotional to the difference in the current and previous CTE which tries to compensate for the overshoot produced by the P-controller.
The goal should be to arrive at a coefficient for D-controller which reduces the overshoot and converge to CTE=0 trajectory.

Setting Kd to values 1.0 .. 3.0 .. 5.0 reduced the overshoot.
Following result with kp = 0.1 & kd = 0.3.

![Video Link 2](./pid_kp_0.1_kd_3.0.mp4)

### Integral controller
The I-controller along with PD-controller tries to compensate the CTE in case of systematic bias, which could be because of misalligned steering. It does this by adding a term propotional to the integral of the cross track error. The I-controller takes into account the sum of all previous CTE. Based on the accumulated CTE and compensates appropriately. 

By setting Ki to 0.1 was steering the car out of the road immediately. This would be because the systematic bias is not very high.

![Video Link 3](./pid_track_kp_0.2_kd_7.0_ki_0.1.mp4)

Reducing the Ki to lesser order values reduced this behaviour.


## Approach for final parameters:
1) Started with Kp = 0, Kd = 0, Ki = 0.
2) Tried tuning the Kp parameter with a range of values to achieve minimal oscilations. With Kp = 1.0, the car was able to traverse to some extent without high oscillations.
3) Tried tuning Kd parameter to minimize the overshooting and achieve convergence. Increased Kd from 1.0 to 7.0 with step and 1.0. With observed results, Kd=7.0 gave good results.
4) Further tuning Kp to 2.0 to provide the CTE correction in case of sharp turns.
5) Tuned Ki to further fine tune remaining small errors. Reducing Ki from 0.1 to 0.0001 gave good results.

With Kp = 0.2, Kd = 7.0 and Ki = 0.0001, I was able to get good results.

![Video Link 4](./final_pid.mp4)

There are few instances where there quick turns taken by the car. The trajectory may not be completely smooth.
Upon reflection, the PID parameters should be adjusted in real-time based on the speed of the car and the track that the car traverses.
A real-time algorithm similar to twiddle which keeps adjusting these parameters with every step would further smoothen the trajectory of the car.
