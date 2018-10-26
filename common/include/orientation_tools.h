/*! @file orientation_tools.h
 *  @brief Utility functions for 3D rotations
 *
 *  This file contains rotation utilities.  We generally use "coordinate transformations"
 *  as opposed to the displacement transformations that are commonly found in graphics.  To describe the
 *  orientation of a body, we use a rotation matrix which transforms from world to body coordinates.
 *  This is the transpose of the matrix which would rotate the body itself into the correct orientation.
 *
 *  This follows the convention of Roy Featherstone's excellent book, Rigid Body Dynamics Algorithms
 *  and the spatial_v2 MATLAB library that comes with it.  Note that we don't use the spatial_v2
 *  convention for quaternions!
 *
 *  Additionally, this file defines common Vector and Matrix types.
 */

#ifndef LIBBIOMIMETICS_ORIENTATION_TOOLS_H
#define LIBBIOMIMETICS_ORIENTATION_TOOLS_H

#include <cmath>
#include <eigen3/Eigen/Dense>
#include <type_traits>
#include <iostream>


template<typename T>
using RotMat = typename Eigen::Matrix<T, 3, 3>;

template<typename T>
using Vec3 = typename Eigen::Matrix<T, 3, 1>;

template<typename T>
using Mat3 = typename Eigen::Matrix<T, 3, 3>;

template<typename T>
using Quat = typename Eigen::Matrix<T, 4, 1>;


namespace ori {
  enum class CoordinateAxis {
    X, Y, Z
  };

  /*!
   * Convert radians to degrees
   */
  template<typename T>
  T rad2deg(T rad) {
    static_assert(std::is_floating_point<T>::value, "must use floating point value");
    return rad * T(180) / T(M_PI);
  }

  /*!
   * Convert degrees to radians
   */
  template<typename T>
  T deg2rad(T deg) {
    static_assert(std::is_floating_point<T>::value, "must use floating point value");
    return deg * T(M_PI) / T(180);
  }


  /*!
   * Square a number
   */
  template <typename T>
  T square(T a) {
    return a*a;
  }

  /*!
   * Are two eigen matrices almost equal?
   */
  template<typename T, int x, int y>
  bool almostEqual(Eigen::Matrix<T, x, y> a, Eigen::Matrix<T, x, y> b, T tol) {
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        T error = std::abs(a(i, j) - b(i, j));
        if (error >= tol)
          return false;
      }
    }
    return true;
  }



  /*!
   * Compute rotation matrix for coordinate transformation. Note that coordinateRotation(CoordinateAxis:X, .1) * v
   * will rotate v by -.1 radians - this transforms into a frame rotated by .1 radians!.
   */
  template<typename T>
  Mat3<T> coordinateRotation(CoordinateAxis axis, T theta) {
    static_assert(std::is_floating_point<T>::value, "must use floating point value");
    T s = std::sin(theta);
    T c = std::cos(theta);

    Mat3<T> R;

    if (axis == CoordinateAxis::X) {
      R << 1, 0, 0,
              0, c, s,
              0, -s, c;
    } else if (axis == CoordinateAxis::Y) {
      R << c, 0, -s,
              0, 1, 0,
              s, 0, c;
    } else if (axis == CoordinateAxis::Z) {
      R << c, s, 0,
              -s, c, 0,
              0, 0, 1;
    }

    return R;
  }

  /*!
   * Convert a 3x1 vector to a skew-symmetric 3x3 matrix
   */
  template<typename T>
  Mat3<typename T::Scalar> vectorToSkewMat(const Eigen::MatrixBase<T>& v) {
    static_assert(T::ColsAtCompileTime == 1 && T::RowsAtCompileTime == 3, "Must have 3x1 matrix");
    Mat3<typename T::Scalar> m;
    m << 0, -v[2], v[1],
            v[2], 0, -v[0],
            -v[1], v[0], 0;
    return m;
  }

  /*!
   * Put the skew-symmetric component of 3x3 matrix m into a 3x1 vector
   */
  template<typename T>
  Vec3<typename T::Scalar> matToSkewVec(const Eigen::MatrixBase<T>& m) {
    static_assert(T::ColsAtCompileTime == 3 && T::RowsAtCompileTime == 3, "Must have 3x3 matrix");
    return 0.5 * Vec3<typename T::Scalar>(m(2, 1) - m(1, 2), m(0, 2) - m(2, 0), (m(1, 0) - m(0, 1)));
  }

  /*!
   * Convert a coordinate transformation matrix to an orientation quaternion.
   */
  template<typename T>
  Quat<T> rotationMatrixToQuaternion(Mat3<T> r) {
    Quat<T> q;
    T tr = r.trace();
    if (tr > 0.0) {
      T S = sqrt(tr + 1.0) * 2.0;
      q(0) = 0.25 * S;
      q(1) = (r(2, 1) - r(1, 2)) / S;
      q(2) = (r(0, 2) - r(2, 0)) / S;
      q(3) = (r(1, 0) - r(0, 1)) / S;
    } else if ((r(0, 0) > r(1, 1)) && (r(0, 0) > r(2, 2))) {
      T S = sqrt(1.0 + r(0, 0) - r(1, 1) - r(2, 2)) * 2.0;
      q(0) = (r(2, 1) - r(1, 2)) / S;
      q(1) = 0.25 * S;
      q(2) = (r(0, 1) + r(1, 0)) / S;
      q(3) = (r(0, 2) + r(2, 0)) / S;
    } else if (r(1, 1) > r(2, 2)) {
      T S = sqrt(1.0 + r(1, 1) - r(0, 0) - r(2, 2)) * 2.0;
      q(0) = (r(0, 2) - r(2, 0)) / S;
      q(1) = (r(0, 1) + r(1, 0)) / S;
      q(2) = 0.25 * S;
      q(3) = (r(1, 2) + r(2, 1)) / S;
    } else {
      T S = sqrt(1.0 + r(2, 2) - r(0, 0) - r(1, 1)) * 2.0;
      q(0) = (r(1, 0) - r(0, 1)) / S;
      q(1) = (r(0, 2) + r(2, 0)) / S;
      q(2) = (r(1, 2) + r(2, 1)) / S;
      q(3) = 0.25 * S;
    }
    return q;
  }

  /*!
   * Convert a quaternion to a rotation matrix.  This matrix represents a coordinate transformation into the frame
   * which has the orientation specified by the quaternion
   */
  template<typename T>
  Mat3<T> quaternionToRotationMatrix(Quat<T> q) {
    T e0 = q(0);
    T e1 = q(1);
    T e2 = q(2);
    T e3 = q(3);

    Mat3<T> R;

    R << 1 - 2 * (e2 * e2 + e3 * e3), 2 * (e1 * e2 - e0 * e3), 2 * (e1 * e3 + e0 * e2),
            2 * (e1 * e2 + e0 * e3), 1 - 2 * (e1 * e1 + e3 * e3), 2 * (e2 * e3 - e0 * e1),
            2 * (e1 * e3 - e0 * e2), 2 * (e2 * e3 + e0 * e1), 1 - 2 * (e1 * e1 + e2 * e2);

    return R;
  }


  /*!
   * Convert a quaternion to RPY.  Uses ZYX order (yaw-pitch-roll), but returns angles in (roll, pitch, yaw).
   * @tparam T
   * @param q
   * @return
   */
  template <typename T>
  Vec3<T> quatToRPY(Quat<T> q) {
    Vec3<T> rpy;
    T as = std::min(-2.*(q[1]*q[3]-q[0]*q[2]),.99999);
    rpy(2) = std::atan2(2*(q[1]*q[2]+q[0]*q[3]),square(q[0]) + square(q[1]) - square(q[2]) - square(q[3]));
    rpy(1) = std::asin(as);
    rpy(0) = atan2(2*(q[2]*q[3]+q[0]*q[1]),square(q[0]) - square(q[1]) - square(q[2]) + square(q[3]));
    return rpy;
  }


}


#endif //LIBBIOMIMETICS_ORIENTATION_TOOLS_H
