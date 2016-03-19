#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION	1.0.0
class PID
{
  public:
#define AUTOMATIC	1
#define MANUAL	0
#define DIRECT  0
#define REVERSE  1
    PID(double*, double*, double*, double, double, double, int);
    void SetMode(int Mode);
    bool Compute();
    void SetOutputLimits(double, double);
    void SetTunings(double, double, double);
    void SetControllerDirection(int);
    void SetSampleTime(int);
    double GetKp();
    double GetKi();
    double GetKd();
    int GetMode();
    int GetDirection();
  private:
    void Initialize();
    double dispKp;
    double dispKi;
    double dispKd;
    double kp;
    double ki;
    double kd;
    int controllerDirection;
    double *myInput;
    double *myOutput;
    double *mySetpoint;
    unsigned long lastTime;
    double ITerm, lastInput;
    unsigned long SampleTime;
    double outMin, outMax;
    bool inAuto;
};
#endif

