#ifndef FSM_State_H
#define FSM_State_H

#include <stdio.h>

#include "Controllers/GaitScheduler.h"
#include "../include/ControlFSMData.h"
//#include "../include/TransitionData.h"

/**
 * Enumerate all of the FSM states so we can keep track of them.
 */
enum class FSM_StateName {
  INVALID,
  PASSIVE,
  JOINT_PD,
  IMPEDANCE_CONTROL,
  BALANCE_STAND,
  LOCOMOTION
};


/**
 *
 */
template <typename T>
class FSM_State {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // Generic constructor for all states
  FSM_State(ControlFSMData<T>* _controlFSMData,
            FSM_StateName stateNameIn,
            std::string stateStringIn);

  // Behavior to be carried out when entering a state
  virtual void onEnter() { }

  // Run the normal behavior for the state
  virtual void run() { }

  // Manages state specific transitions
  virtual FSM_StateName checkTransition() { return FSM_StateName::INVALID; }

  // Runs the transition behaviors and returns true when done transitioning
  virtual bool transition() { return false; }

  // Behavior to be carried out when exiting a state
  virtual void onExit() { }

  //
  void jointPDControl(int leg, Vec3<T> qDes = Vec3<T>::Zero(), Vec3<T> qdDes = Vec3<T>::Zero());
  void cartesianImpedanceControl(int leg, Vec3<T> pDes = Vec3<T>::Zero(), Vec3<T> vDes = Vec3<T>::Zero());
  void footstepHeuristicPlacement(int leg);
  void runControls();

  // Holds all of the relevant control data
  ControlFSMData<T>* _data;

  // FSM State info
  FSM_StateName stateName;		// enumerated name of the current state
  FSM_StateName nextStateName;	// enumerated name of the next state
  std::string stateString;		// state name string

  // Transition parameters
  T transitionDuration;		// transition duration time
  T tStartTransition; 		// time transition starts

  // Notify the FSM if the state needs to check for rotation safety
  bool checkSafeOrientation = true;

  Mat34<T> groundReactionForces;	// Ground reaction forces for the stance feet to be calculated by the controllers
  Mat34<T> footstepLocations;		// Next footstep location for the swing feet

private:

  // Create the cartesian P gain matrix
  Mat3<float> kpMat;

  // Create the cartesian D gain matrix
  Mat3<float> kdMat;

};

#endif // FSM_State_H
