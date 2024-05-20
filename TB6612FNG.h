#ifndef TB6612FNG_H
#define TB6612FNG_H

class TB6612FNG {
  public: 
    TB6612FNG(
      int PWMA, int PWMB, int AIN1, int AIN2, int BIN1, int BIN2, int STBY
    );
    void run(int motor, int speed);
    void stop(int motor);
    void standby();
  private:
    int STBY;
    int PWMA;
    int PWMB;
    int AIN1;
    int AIN2;
    int BIN1;
    int BIN2;
};

#endif