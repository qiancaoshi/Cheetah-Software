#include "JPosInitializer.h"
#include <ParamHandler/ParamHandler.hpp>
#include <Configuration.h>
#include <Utilities/Utilities_print.h>

template<typename T>
JPosInitializer<T>::JPosInitializer(T end_time):
    _b_first_visit(true),
    _end_time(end_time),
    _curr_time(0.),
    _dt(0.001)
{
    _UpdateParam();
}

template<typename T>
JPosInitializer<T>::~JPosInitializer(){}

template<typename T>
bool JPosInitializer<T>::IsInitialized(LegController<T>* ctrl){
    _curr_time += _dt;
    // Initial Setup
    if(_b_first_visit){
        _UpdateInitial(ctrl);
        _b_first_visit = false;
    }

    //T ini[cheetah::num_act_joint];
    //for(int leg(0); leg<4; ++leg){
        //for(int jidx(0); jidx<3; ++jidx){
            //ini[3*leg + jidx] = ctrl->datas[leg].q[jidx];
        //}
    //}
    //pretty_print(ini, "jpos", cheetah::num_act_joint);

    // Smooth movement
    if(_curr_time<_end_time){
        T jpos[cheetah::num_act_joint];
        _jpos_trj.getCurvePoint(_curr_time, jpos);

        for(size_t leg(0); leg<cheetah::num_leg; ++leg){
            for(size_t jidx(0); jidx<cheetah::num_leg_joint; ++jidx){
                ctrl->commands[leg].tauFeedForward[jidx] = 0.;
                ctrl->commands[leg].qDes[jidx] = jpos[3*leg + jidx];
                ctrl->commands[leg].qdDes[jidx] = 0.;
            }
        }
        return false;
    }
    return true;
}

template<typename T>
void JPosInitializer<T>::_UpdateInitial(const LegController<T>* ctrl){
    T ini[3 * cheetah::num_act_joint];
    T fin[3 * cheetah::num_act_joint];
    T** mid = new T*[1];
    mid[0] = new T[cheetah::num_act_joint];

    for(size_t i(cheetah::num_act_joint); i<3*cheetah::num_act_joint; ++i){
        ini[i] = 0.;
        fin[i] = 0.;
    }

    for(int leg(0); leg<4; ++leg){
        for(int jidx(0); jidx<3; ++jidx){
            ini[3*leg + jidx] = ctrl->datas[leg].q[jidx];
        }
    }

    for(size_t i(0); i<cheetah::num_act_joint; ++i){
        fin[i] = _target_jpos[i];
        mid[0][i] = _mid_jpos[i];
    }
    _jpos_trj.SetParam(ini, fin, mid, _end_time);

    delete [] mid[0];
    delete [] mid;
}

template<typename T>
void JPosInitializer<T>::_UpdateParam(){
    ParamHandler handler(THIS_COM"config/initial_jpos_ctrl.yaml"); 
    handler.getVector<T>("target_jpos", _target_jpos);
    handler.getVector<T>("mid_jpos", _mid_jpos);
}

template class JPosInitializer<double> ;
template class JPosInitializer<float> ;
