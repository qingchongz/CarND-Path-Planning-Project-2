#include "Vehicle.h"
#include "CoordinateUtils.h"
#include <cmath>

Vehicle::Vehicle() {
  id_ = 0;
  x_ = 0.0;
  y_ = 0.0;
  vx_ = 0.0;
  vy_ = 0.0;
  s_ = 0.0;
  d_ = 0.0;

  ax_ = 0.0;
  ay_ = 0.0;
  v_ = 0.0;
  a_ = 0.0;
  yaw_ = 0.0;
  width_ = DEFAULT_VEHICLE_WIDTH;
  updated_ = false;

  lane_ = -1; // unknown
}

Vehicle::Vehicle(int id, double x, double y, double vx, double vy, double s, double d) {
  id_ = id;
  x_ = x;
  y_ = y;
  vx_ = vx;
  vy_ = vy;
  s_ = s;
  d_ = d;

  ax_ = 0.0;
  ay_ = 0.0;
  v_ = sqrt(pow(vx_, 2) + pow(vy_, 2));
  a_ = sqrt(pow(ax_, 2) + pow(ay_, 2));
  yaw_ = vx_ == 0 ? atan(vy_ / vx_) : 0.0f;
  width_ = DEFAULT_VEHICLE_WIDTH;
  updated_ = true;

  lane_ = -1; // unknown
}

Vehicle::Vehicle(double x, double y, double s, double d, double yaw, double velocity) {
  id_ = 0;
  x_ = x;
  y_ = y;
  vx_ = 0.0f;
  vy_ = 0.0f;
  s_ = s;
  d_ = d;

  ax_ = 0.0;
  ay_ = 0.0;
  v_ = velocity;
  a_ = sqrt(pow(ax_, 2) + pow(ay_, 2));
  yaw_ = yaw;
  width_ = DEFAULT_VEHICLE_WIDTH;
  updated_ = true;

  lane_ = -1; // unknown
}

void Vehicle::generatePredictions(double prediction_time) {

  // clear previous prediction results
  predicted_trajectory_x_.clear();
  predicted_trajectory_y_.clear();
  predicted_trajectory_vx_.clear();
  predicted_trajectory_vy_.clear();
  predicted_trajectory_ax_.clear();
  predicted_trajectory_ay_.clear();
  predicted_trajectory_v_.clear();
  predicted_trajectory_a_.clear();
  predicted_trajectory_yaw_.clear();
  predicted_trajectory_s_.clear();
  predicted_trajectory_d_.clear();

  // predict vehicle trajectory until prediction time
  for (int i = 0; i < (prediction_time / CONTROLLER_CYCLE_TIME); ++i) {
    double dt = i * CONTROLLER_CYCLE_TIME;
    predicted_trajectory_x_.push_back(x_ + (vx_ * dt + 0.5 * ax_ * pow(dt, 2)));
    predicted_trajectory_y_.push_back(y_ + (vy_ * dt + 0.5 * ay_ * pow(dt, 2)));

    predicted_trajectory_vx_.push_back(vx_ + ax_ * prediction_time);
    predicted_trajectory_vy_.push_back(vy_ + ay_ * prediction_time);
    predicted_trajectory_v_.push_back(v_ + a_ * prediction_time);
  }
}
