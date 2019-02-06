#include "Collision/ContactConstraint.h"

template<typename T>
size_t ContactConstraint<T>::_CheckContact(){
    _cp_pos_list.clear();
    _cp_local_force_list.clear();
    _cp_penetration_list.clear();

    _cp_frame_list.clear();
    _cp_resti_list.clear();
    _cp_mu_list.clear();
    _idx_list.clear();

    Vec3<T> tmp_vec;
    Mat3<T> cp_frame;

    T penetration;
    for(size_t i(0); i<_model->_nGroundContact; ++i){
        _cp_force_list[i].setZero();
        for(size_t j(0); j<_nCollision; ++j){
            if(_collision_list[j]->ContactDetection(
                        _model->_pGC[i], penetration, cp_frame)) {
                // Contact Happens
                _cp_pos_list.push_back(_model->_pGC[i]);
                //_cp_local_force_list.push_back(Vec3<T>::Zero());
                _cp_local_force_list.push_back(_cp_local_force_list_pre[i]);
                _cp_frame_list.push_back(cp_frame);
                _cp_penetration_list.push_back(penetration);

                _idx_list.push_back(i);

                _cp_resti_list.push_back(_collision_list[j]->getRestitutionCoeff());
                _cp_mu_list.push_back(_collision_list[j]->getFrictionCoeff());
            }
        }
    }
    return _cp_pos_list.size();
}

template class ContactConstraint<double>;
template class ContactConstraint<float>;
