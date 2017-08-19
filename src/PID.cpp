#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  /*Initialize coefficients*/
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  /*Initialize error values*/
  p_error = 0.0;
  d_error = 0.0;
  i_error = 0.0; 

  first_cte = false;
  prev_cte = 0.0;
}

void PID::UpdateError(double cte) {
 
  /*Set previous cte to current cte for the first step*/ 
  if (!first_cte)
  {
    prev_cte = cte;
    first_cte = true;
  }
  
  /*Calculate each P-,I-,D- error components*/
  p_error = cte;
  d_error = cte - prev_cte;
  i_error += cte;
  prev_cte = cte;
}

double PID::TotalError() {
  double steer_value;
  /*Calculate the final steer value*/
  steer_value = -p_error*Kp - d_error*Kd - i_error*Ki;
  return steer_value;
}

