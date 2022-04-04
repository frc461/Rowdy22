#include "Robot.h"

//------------------------------------------------------------------------DriveTrain-----
void Robot::DriveTrainPeriodic() {
  bool t = GET_BOOL("Tank", true);
  bool ramp = GET_BOOL("Ramp",false);

  PUT_NUM("gyro", driveTrain->GetAngle());
  
  if (t && !aim) {
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
    if (!aim) driveTrain->Arcade(-control->LeftY(),control->RightX());
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
bool Robot::WiggleHood() {
  shooter->RunHood(0);
  if (counter->SecondsPassed(0.1)) { 
    shooter->RunHood(2);
    return true;
  }
  return false;
}
void Robot::ShooterPeriodic() {
  shooter->RunShooter((control->Shooter()) ? ((hoodState==1) ? GET_NUM("HighSpeed", SHOOTER_RPM_TOP) : ((hoodState==2) ? GET_NUM("MidSpeed", SHOOTER_RPM_MID) : GET_NUM("LowSpeed", SHOOTER_RPM_BOT))) : 0.0);
  shooter->RunSmallShooter((control->Shooter()) ? ((hoodState==1) ? GET_NUM("sHighSpeed", 0.5) : ((hoodState==2) ? GET_NUM("sMidSpeed", 0.9) : GET_NUM("sLowSpeed", 0.5))) : 0.0);
  
  PUT_BOOL("ShooterLoadedUp", (shooter->GetShooterSpeed() >= ((hoodState==1) ? SHOOTER_RPM_TOP : (hoodState==2) ? SHOOTER_RPM_MID : SHOOTER_RPM_BOT)));

  PUT_NUM("velcoty", shooter->GetShooterSpeed());
  
  if (control->ShooterHoodUp()) { hoodState = 0; climb = false; }
  else if (control->ShooterHoodDown()) { hoodState = 1; climb = false; }
  else if (control->ShooterHoodMid()) { 
    if (hoodState == 1) toMid = true;
    hoodState = 2;
    climb = false;
  }

  if (toMid) { if (WiggleHood()) { counter->ResetAll(); toMid = false; } }
  else shooter->RunHood((climb) ? 1 : hoodState);
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
}
//--------------------------------------------------------------------------------Vision---------
void Robot::VisionPeriodic() {
  bool on = control->DPadAngle()==0 || control->DPadAngle()==180;
  vision->SetLimelightState(on, on);
  if (control->DPadAngle() == 0) {
    double p = aimPID->Get(vision->GetValues().x, 0.0);
    double power = (p<0) ? std::max(p, -0.6) : std::min(p, 0.6);
    driveTrain->Arcade(0.0, -power);
    
    aim = true;
  } else { aimPID->Reset(); aim = false; }
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
  aimPID = new PID(0.05, 0.0, 0.0, "aim");

  counter = new Counter();
  counter->Start();

  driveTrain->CalibrateGyro();

  lSpeed = rSpeed = 0.0;

  climb = false;
  hoodState = toMid = false;

  PUT_BOOL("Tank", true);
  PUT_BOOL("Ramp", false);
  
  PUT_NUM("HighSpeed", SHOOTER_RPM_TOP);
  PUT_NUM("MidSpeed", SHOOTER_RPM_MID);
  PUT_NUM("LowSpeed", SHOOTER_RPM_BOT);

  PUT_NUM("sHighSpeed", 0.5);
  PUT_NUM("sMidSpeed", 0.9);
  PUT_NUM("sLowSpeed", 0.5);

  PUT_NUM("Auto", 2);
  PUT_NUM("AutoHigh", 2);
  PUT_NUM("AutoDelay", 0.0);
}

void Robot::AutonomousInit() {
  driveTrain->ResetEncoder();
  driveTrain->ResetGyro();

  moves.erase(moves.begin(), moves.end());
  values.erase(values.begin(), values.end());
  delayed = shooterloaded = loaded = shot = moveNow = false;
  index = 0;
  dDummy = 0.0; bDummy = false; iDummy = 0;
  
  int level = GET_NUM("Auto",2);
  if (level==1) {
    moves.push_back(&Robot::AutoShoot); values.push_back({dDummy, SHOOTER_RPM_MID, bDummy, 1});
    moves.push_back(&Robot::AutoMove);  values.push_back({-70.0, 0.6, false, iDummy});
  }
  else if (level == 2 || level == 3) {
    moves.push_back(&Robot::AutoMove);  values.push_back({(level==2) ? -55.0 : -60.0, 0.6, false, iDummy});
    moves.push_back(&Robot::AutoShoot); values.push_back({dDummy, SHOOTER_RPM_MID, bDummy, GET_NUM("AutoHigh",2)});
  }
  else if (level == 4 || level == 5) {
    moves.push_back(&Robot::AutoMove);  values.push_back({-55.0, 0.6, level==5, iDummy});
    moves.push_back(&Robot::AutoShoot); values.push_back({dDummy, SHOOTER_RPM_MID, bDummy, GET_NUM("AutoHigh",2)});
    moves.push_back(&Robot::AutoTurn);  values.push_back({(level==4) ? 102.0 : -42.0, 0.6, level==5, iDummy});
    moves.push_back(&Robot::AutoMove);  values.push_back({(level==4) ? -100.0 : -182.0, 0.8, level==5, iDummy});
    moves.push_back(&Robot::AutoTurn);  values.push_back({(level==4) ? -70.0 : 42.0, 0.6, level==5, iDummy});
    moves.push_back(&Robot::AutoShoot); values.push_back({dDummy, SHOOTER_RPM_MID+400, bDummy, GET_NUM("AutoHigh",2)});
  }
}
void Robot::AutoShoot(double time1, double midSpeed, bool dummy, int hood) {
  shooter->RunHood(hood);
  shooter->RunShooter((hood==1) ? SHOOTER_RPM_TOP : ((hood==2) ? midSpeed : SHOOTER_RPM_BOT));
  shooter->RunSmallShooter((hood==1) ? 0.5 : ((hood==2) ? ((midSpeed>SHOOTER_RPM_MID) ? 1.0 : 0.9) : 0.5));
  conveyor->RunMotor(0.8);
  if (!shooterloaded && counter->SecondsPassed(0.65)) { conveyor->RunHold(true); shooterloaded = true; }
  if (!loaded) { loaded = conveyor->GetBallSensorState(true);  }
  if (!shot && loaded && !conveyor->GetBallSensorState(true)) { counter->ResetAll(); moveNow = shot = true; }
  if (moveNow && counter->SecondsPassed(0.75)) {
    conveyor->RunMotor(0.0); conveyor->RunHold(false);
    shooter->RunShooter(0.0); shooter->RunSmallShooter(0.0);
    shooterloaded = loaded = shot = moveNow = false; counter->ResetAll();
    return true;
  } return false;
}
void Robot::AutoMove(double distance, double cap, bool fast, int dummy) {
  intake->RunPush(true); intake->RunMotor(0.8); conveyor->RunMotor(0.8);
  if (driveTrain->MoveDistance(distance, cap, fast)) {
    intake->RunPush(false); intake->RunMotor(0.0); conveyor->RunMotor(0.0);
    driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    return true;
  } return false;
}
void Robot::AutoTurn(double angle, double cap, bool fast, int dummy) {
  if (driveTrain->Turn(angle, fast)) {
    driveTrain->ResetMoveVars(); driveTrain->ResetTurnVars();
    return true;
  } return false;
}
void Robot::AutonomousPeriodic() {
  if (!delayed) if (counter->SecondsPassed(GET_NUM("AutoDelay",0.0))) { counter->ResetAll(); delayed = true; }
  else if (index <= moves.size()-1) if (this->*moves.at(index))(values.at(index).d1, values.at(index).d2, values.at(index).b, values.at(index).i)) index++;
}

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
