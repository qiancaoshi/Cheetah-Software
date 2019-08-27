function constraint_jacobian_nz = Jump2DConstraintJacobian(in1,dt,in3,m,Iyy,mu_g)
%JUMP2DCONSTRAINTJACOBIAN
%    CONSTRAINT_JACOBIAN_NZ = JUMP2DCONSTRAINTJACOBIAN(IN1,DT,IN3,M,IYY,MU_G)

%    This function was generated by the Symbolic Math Toolbox version 8.0.
%    27-Aug-2019 12:38:32

rxb = in3(3,:);
rxf = in3(1,:);
rzb = in3(4,:);
rzf = in3(2,:);
sb = in1(2,:);
sf = in1(1,:);
t2 = dt.^2;
t3 = 1.0./m;
t4 = 1.0./Iyy;
t5 = mu_g-1.0;
t6 = mu_g+1.0;
constraint_jacobian_nz = [-1.0;-1.0;-1.0;-dt;-1.0;-dt;-1.0;-dt;-1.0;1.0;1.0;1.0;1.0;1.0;1.0;sf.*t2.*t3.*(-1.0./2.0);rzf.*sf.*t2.*t4.*(-1.0./2.0);-dt.*sf.*t3;-dt.*rzf.*sf.*t4;sf.*t2.*t3.*(-1.0./2.0);rxf.*sf.*t2.*t4.*(1.0./2.0);-dt.*sf.*t3;dt.*rxf.*sf.*t4;-sf.*t5;-sf.*t6;sb.*t2.*t3.*(-1.0./2.0);rzb.*sb.*t2.*t4.*(-1.0./2.0);-dt.*sb.*t3;-dt.*rzb.*sb.*t4;sb.*t2.*t3.*(-1.0./2.0);rxb.*sb.*t2.*t4.*(1.0./2.0);-dt.*sb.*t3;dt.*rxb.*sb.*t4;-sb.*t5;-sb.*t6];
