#include <ctre/Phoenix.h>

class Shooter {
public:
  Shooter();
  ~Shooter();
  
  void RunShooter(double speed);
  void RunHood(double speed);
  
private:
  WPI_TalonSRX *shooter, *hood;
};
