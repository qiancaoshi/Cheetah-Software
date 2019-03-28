#include "BodyPostureTask.hpp"
// (X, Y, Z)
#include <Configuration.h>
#include <WBC_States/Cheetah_DynaCtrl_Definition.h>
#include <Utilities/Utilities_print.h>
#include <Dynamics/FloatingBaseModel.h>

template <typename T>
BodyPostureTask<T>::BodyPostureTask(const FloatingBaseModel<T>* robot):
    Task<T>(6),
    _robot_sys(robot)
{
    TK::Jt_ = DMat<T>::Zero(TK::dim_task_, cheetah::dim_config);
    TK::Jt_.block(0,0,6,6).setIdentity();
    TK::JtDotQdot_ = DVec<T>::Zero(TK::dim_task_);


    // TEST
    _Kp = DVec<T>::Constant(TK::dim_task_, 300.);
    _Kd = DVec<T>::Constant(TK::dim_task_, 30.);

    //_Kp = DVec<T>::Constant(TK::dim_task_, 0.);
    //_Kd = DVec<T>::Constant(TK::dim_task_, 0.);
}

template <typename T>
BodyPostureTask<T>::~BodyPostureTask(){}

template <typename T>
bool BodyPostureTask<T>::_UpdateCommand(void* pos_des,
        const DVec<T> & vel_des,
        const DVec<T> & acc_des){
    DVec<T>* pos_cmd = (DVec<T>*)pos_des;

    // Orientation (w, x, y, z)
    Quat<T> ori_cmd;
    for(size_t i(0); i<4; ++i) ori_cmd[i] = (*pos_cmd)[i];
    Quat<T> link_ori = (_robot_sys->_state.bodyOrientation);
    Quat<T> link_ori_inv;
    link_ori_inv[0]= link_ori[0];
    link_ori_inv[1]= -link_ori[1];
    link_ori_inv[2]= -link_ori[2];
    link_ori_inv[3]= -link_ori[3];
    link_ori_inv /= link_ori.norm();

    Quat<T> ori_err = ori::quatProduct(link_ori_inv, ori_cmd);
    if(ori_err[0] < 0.){
        ori_err *= (-1.);
    }
    Vec3<T> ori_err_so3;
    ori::quaternionToso3(ori_err, ori_err_so3);

    // Rx, Ry, Rz
    for(int i(0); i<3; ++i){
        TK::pos_err_[i] = ori_err_so3[i];
        TK::vel_des_[i] = vel_des[i];
        TK::acc_des_[i] = acc_des[i];
    }
 
    // Position
    Vec3<T> link_pos = _robot_sys->_state.bodyPosition;
  
    // X, Y, Z
    for(int i(3); i<6; ++i){
        TK::pos_err_[i] = (*pos_cmd)[i+1] - link_pos[i-3];
        TK::vel_des_[i] = vel_des[i];
        TK::acc_des_[i] = acc_des[i];
    }

    // Op acceleration command
    for(size_t i(0); i<TK::dim_task_; ++i){
        TK::op_cmd_[i] = 
            _Kp[i] * TK::pos_err_[i]
            + _Kd[i] * (TK::vel_des_[i] - _robot_sys->_state.bodyVelocity[i])
            + TK::acc_des_[i];
    }

    //printf("[Body Posture Task]\n");
    //pretty_print(acc_des, std::cout, "acc_des");
    //pretty_print(TK::pos_err_, std::cout, "pos_err");
    //pretty_print(*pos_cmd, std::cout, "pos cmd");
    //pretty_print(TK::op_cmd_, std::cout, "op cmd");
    //pretty_print(TK::Jt_, std::cout, "Jt");

    return true;
}

template <typename T>
bool BodyPostureTask<T>::_UpdateTaskJacobian(){
    return true;
}

template <typename T>
bool BodyPostureTask<T>::_UpdateTaskJDotQdot(){
    return true;
}

template class BodyPostureTask<double>;
template class BodyPostureTask<float>;
