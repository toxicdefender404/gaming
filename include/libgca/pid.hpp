#pragma once
#include <string>

class PID {
    double output;
    double cur;
    double error;
    double target;
    double prev_error;
    double integral;
    double derivative;
    long time;
    long prev_time;

   

    int smalltime;
    int bigtime;
    int veltime;
 public: 
    bool settled;
  /**
   * Default constructor.
   */
  PID();

  /**
   * Constructor with constants.
   *
   * \param p
   *        kP
   * \param i
   *        ki
   * \param d
   *        kD
   * \param p_start_i
   *        error value that i starts within
   */
  PID(double p, double i = 0, double d = 0, double start_i = 0);

  /**
   * Set constants for PID.
   *
   * \param p
   *        kP
   * \param i
   *        ki
   * \param d
   *        kD
   * \param p_start_i
   *        error value that i starts within
   */
  void set_constants(double p, double i = 0, double d = 0, double p_start_i = 0);

  /**
   * Struct for constants.
   */
  struct Constants {
    double kp;
    double ki;
    double kd;
    double start_i;
  };

  /**
   * Struct for exit condition.
   */
  struct exit_condition_ {
    int small_exit_time = 0;
    double small_error = 0;
    int big_exit_time = 0;
    double big_error = 0;
    int velocity_exit_time = 0;
    int mA_timeout = 0;
  };

    Constants constants;
    exit_condition_ exit;
  /**
   * Sets constants for exit conditions.
   *
   * \param small_exit_time
   *        Timer for to exit within small_error.
   * \param small_error
   *        Timer will start when error is within this.
   * \param big_exit_time
   *        Timer for to exit within big_error.
   * \param big_error
   *        imer will start when error is within this.
   * \param velocity_exit_time
   *        Timer will start when velocity is 0.
   */
  void set_exit_condition(int small_exit_time, double small_error, int big_exit_time = 0, double big_error = 0, int velocity_exit_time = 0);

  /**
   * Set's target.
   *
   * \param target
   *        Target for PID.
   */
  void set_target(double input);

  /**
   * Computes PID.
   *
   * \param current
   *        Current sensor value.
   */
  double step(double current);

  /**
   * Returns target value.
   */
  double get_target();

  /**
   * Returns constants.
   */
  Constants get_constants();

  /**
   * Resets all variables to 0.  This does not reset constants.
   */
  void reset_variables();

  void reset_timers();
};