#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = GET_BOOL("Tank", true);
  bool ramp = GET_BOOL("Ramp",false);
  
  if (t) {
    if (driveTrain->GetLeftVelocity() > 7500 || !ramp) {
      driveTrain->Tank(-control->LeftY(), control->RightY());
    }
    else if (driveTrain->GetLeftVelocity() < 7500 && ramp) {
      double increment = .015;
      lSpeed = (control->LeftY()>0) ? std::min(lSpeed+increment, control->LeftY()) : (control->LeftY()<0) ? std::max(lSpeed-increment, control->LeftY()) : 0.0;
      rSpeed = (control->RightY()>0) ? std::min(rSpeed+increment, control->RightY()) : (control->RightY()<0) ? std::max(rSpeed-increment, control->RightY()) : 0.0;
      driveTrain->Tank(-lSpeed, rSpeed);
    }
    driveTrain->Tank(-control->LeftY(),control->RightY());
  }
  else {
    driveTrain->Arcade(-control->LeftY(),control->RightX());
  }
}
//-------------------------------------------------------------------------Intake-----
void Robot::IntakeConveyorPeriodic()  {
  double speed = 0.8;
  intake->RunMotor((control->IntakeConveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);
  conveyor->RunMotor((control->IntakeConveyor() || control->Conveyor()) ? speed : (control->IntakeConveyorR()) ? -speed : 0.0);

  conveyor->RunHold(control->Conveyor() && control->Shooter());

  if (control->IntakePush()) { intake->RunPush((intake->GetPushState()) ? false : true); }

  PUT_NUM("NumBalls", conveyor->GetNumBalls());
}
//--------------------------------------------------------------------------Shooter-----
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? ((hoodState > 0) ? GET_NUM("HighSpeed", SHOOTER_SPEED_TOP) : GET_NUM("LowSpeed", SHOOTER_SPEED_BOT)) : 0.0);

  PUT_BOOL("ShooterLoadedUp", (shooter->GetShooterSpeed() >= ((hoodState) ? SHOOTER_RPM_TOP : SHOOTER_RPM_BOT)));
  
  if (control->ShooterHoodUp() ) { hoodState = 1; }
  if (control->ShooterHoodDown() ) { hoodState = 0; }
  if (control->ShooterHoodMid() ) { hoodState = 2; }

  // TODO
  // Momentarily go to high before going to mid
  // Set a 3rd shooter speed

  // if (control->ShooterHood()) { 
  //   hoodState = (hoodState) ? false : true;
  //   climb = false;
  // }
  // shooter->RunHood(hoodState);

  shooter->RunHood(hoodState);
  PUT_NUM("HoodState", hoodState);
}
//-----------------------------------------------------------------------------Climber--
void Robot::ClimberPeriodic() {
  double speed = 1.0;
  climber->RunLeft((control->ClimberExtend() && !climber->GetTopLimit(climber->GetTiltState() ? CLIMBER_TOP_ENC_2 : CLIMBER_TOP_ENC_1)) ? speed : (control->ClimberRetract() && !climber->GetBotLimit(CLIMBER_BOT_ENC)) ? -speed : 0.0);
  climber->RunRight((control->ClimberExtend() && !climber->GetTopLimit(climber->GetTiltState() ? CLIMBER_TOP_ENC_2 : CLIMBER_TOP_ENC_1)) ? -speed : (control->ClimberRetract() && !climber->GetBotLimit(CLIMBER_BOT_ENC)) ? speed : 0.0);
  climber->RunBrake(!((!control->ClimberExtend() && !control->ClimberRetract() && !control->ClimberOverrideRetract()) || (climber->GetBotLimit(CLIMBER_BOT_ENC) && !control->ClimberExtend() && !control->ClimberOverrideRetract()) || (climber->GetTopLimit((climber->GetTiltState()) ? CLIMBER_TOP_ENC_2 : CLIMBER_TOP_ENC_1)) && (!control->ClimberRetract())));

  if (control->ClimberExtend() || control->ClimberRetract()) climb = true;

  if (control->ClimberOverrideRetract()) { climber->RunLeft(-speed); climber->RunRight(speed); }
  if (control->ClimberResetEncoder()) { climber->ResetEncoder(); }

  if (control->ClimberGrab()) { climber->RunGrab((climber->GetGrabState()) ? false : true); climb = true; }
  if (control->ClimberTilt()) { climber->RunTilt((climber->GetTiltState()) ? false : true); climb = true; }
  // if (control->ClimberTilt()) { climber->RunTilt((climber->GetTiltState()) ? ((climber->GetTopLimit(CLIMBER_TOP_ENC_1)) ? true : false) : true); climb = true; }         // FOR INSPECTION ONLY

  PUT_NUM("CLIMBER",climber->GetEncoder());
}
//--------------------------------------------------------------------------------Vision---------
void Robot::VisionPeriodic() {
  PUT_NUM("Gyro",driveTrain->GetAngle());
}
//-----------------------------------------------------------------------------------------
//====================================================================================================================================================
void Robot::RobotInit() {
  control = new Control();
  
  driveTrain = new DriveTrain();
  shooter = new Shooter();
  intake = new Intake();
  climber = new Climber();
  conveyor = new Conveyor();
  vision = new Vision();

  driveTrain->CalibrateGyro();

  lSpeed = rSpeed = 0.0;

  climb = climberMoveDown = climberDelay = false;
  hoodState = false;

  PUT_BOOL("Tank", true);
  PUT_BOOL("Ramp", false);
  
  PUT_NUM("HighSpeed", SHOOTER_SPEED_TOP);
  PUT_NUM("LowSpeed", SHOOTER_SPEED_BOT);

  PUT_NUM("Auto", 2);
  PUT_BOOL("AutoHigh", true);
  PUT_NUM("AutoDelay", 0.0);
}

void Robot::AutonomousInit() {
  counter = new Counter();
  counter->Start();

  driveTrain->ResetEncoder();
  driveTrain->ResetGyro();

  shooterloaded = loaded = shot = moveNow = false;

  nTimes = 0;
  thirdPickedUp = false;

  delayed = shoot1 = back1 = forward1 = shoot2 = turn1 = back2 = turn2 = shoot3 = false;
}
void Robot::Auto(int level, bool high, double delaySeconds) {
  if (!delayed) {
    if (counter->SecondsPassed(delaySeconds)) { counter->ResetAll(); delayed = true; }
  }
  else if (delayed && !shoot1) {
    shooter->RunHood(high);   shooter->RunShooter((high) ? SHOOTER_SPEED_TOP_AUTO : SHOOTER_SPEED_BOT_AUTO);
    conveyor->RunHold(true);
    if (!shooterloaded && counter->SecondsPassed(1.5)) { conveyor->RunMotor(0.8); shooterloaded = true; }
    if (!loaded) { loaded = conveyor->GetBallSensorState(true); }
    if (!shot && loaded && !conveyor->GetBallSensorState(true)) {
      counter->ResetAll();
      moveNow = true;
      shot = true;
    }
    if (moveNow && counter->SecondsPassed(1.0)) {
      conveyor->RunHold(false);
      if (!shoot3) shoot1 = true;
    }
  }
  else if (shoot1 && !turn1) {
    if (level != 4 || (level==4 && !shoot2)) turn1 = true;
    else if (driveTrain->Turn((shoot3) ? -60 : 60)) {
      driveTrain->ResetTurnVars();
      if (shoot3) shoot1 = loaded = shot = shooterloaded = moveNow = false;
      turn1 = true;
    }
  }
  else if (turn1 && !back1) {
    if (level != 1) {
      intake->RunPush(true); intake->RunMotor(0.8);
      conveyor->RunMotor(0.8);
      if (level==4 && shoot2 && conveyor->GetBallSensorState(false)) conveyor->RunMotor(0.0);
      PUT_BOOL("ok", conveyor->GetBallSensorState(false));
    }

    if (driveTrain->MoveDistance((level==2) ? -110.0 : ((level==4 && shoot2) ? -270.0 : -90.0))) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      intake->RunPush(false); intake->RunMotor(0.0);
      if (!(level==4 && shoot2)) back1 = true;
      else { shoot1 = turn1 = back1 = forward1 = shoot2 = true; }
    }
  }
  else if (back1 && !forward1 && level != 1) {
    if (driveTrain->MoveDistance((level==2) ? 100.0 : ((level==4 && shoot2) ? 110.0 : 80.0))) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      forward1 = true;
    }
  }
  else if (forward1 && !shoot2) {
    counter->ResetAll();
    if (nTimes == 1) { turn1 = false; shoot3 = true; driveTrain->ResetTurnVars(); }
    else { shoot1 = loaded = shot = shooterloaded = moveNow = false; if (level==4) back1 = turn1 = forward1 = false; }
    nTimes++;
    shoot2 = true;
  }
}
void Robot::AutonomousPeriodic() {
  Auto(GET_NUM("Auto", 2), GET_BOOL("AutoHigh",true), GET_NUM("AutoDelay",0.0));
}
//comment #1
void Robot::TeleopInit() {
  climber->ResetEncoder();
}

void Robot::TeleopPeriodic() {
  DriveTrainPeriodic();
  IntakeConveyorPeriodic();
  ShooterPeriodic();
  ClimberPeriodic();
  VisionPeriodic();
}

void Robot::RobotPeriodic() {}
void Robot::DisabledInit() {
  climber->RunBrake(true);
}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
//====================================================================================================================================================

/*

if (!delayed) {
    if (counter->SecondsPassed(delaySeconds)) { counter->ResetAll(); delayed = true; }
  }
  else if (delayed && !shoot1) {
    shooter->RunHood(high);   shooter->RunShooter((high) ? SHOOTER_SPEED_TOP_AUTO : SHOOTER_SPEED_BOT_AUTO);
    conveyor->RunHold(true);
    if (!shooterloaded && shooter->GetShooterSpeed() > ((high) ? SHOOTER_RPM_TOP : SHOOTER_RPM_BOT)) { conveyor->RunMotor(0.8); shooterloaded = true; }
    if (!loaded) { loaded = conveyor->GetBallSensorState(true); }
    if (!shot && loaded && !conveyor->GetBallSensorState(true)) {
      counter->ResetAll();
      moveNow = true;
      shot = true;
    }
    if (moveNow && counter->SecondsPassed(1.0)) {
      conveyor->RunMotor(0.0); conveyor->RunHold(false);
      if (shoot2) shooter->RunShooter(0.0);
      shoot1 = true;
    }
  }
  else if (shoot1 && !back1) {
    if (level != 1) {
      intake->RunPush(true); intake->RunMotor(0.8);
      conveyor->RunMotor(0.8);
    }
    if (driveTrain->MoveDistance((level==2) ? -120.0 : (turn1) ? -90 : -100)) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      intake->RunPush(false); intake->RunMotor(0.0);
      if (turn1 && level==4) { back2 = true; turn1 = false; }
      back1 = true;
    }
  }
  else if (back1 && !turn1) {
    if (level != 4) { turn1 = turn2 = true; }
    else if (driveTrain->Turn((back2) ? ((forward1) ? -60 : -40) : 80)) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      if (back2) { turn2 = true; }
      else back1 = false;
      turn1 = true;
    }
  }
  else if (turn1 && turn2 && !forward1 && level != 1) {
    if (driveTrain->MoveDistance((level==2) ? 100.0 : ((level==4) ? 100.0 : 80.0))) {
      driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
      turn1 = false;
      forward1 = true;
    }
  }
  else if (forward1 && !shoot2) {
    counter->ResetAll();
    shoot1 = loaded = shot = shooterloaded = moveNow = false;
    shoot2 = true;
  }

*/