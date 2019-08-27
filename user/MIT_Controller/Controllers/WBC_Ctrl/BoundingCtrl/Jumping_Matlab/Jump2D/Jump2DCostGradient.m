function cost_gradient = Jump2DCostGradient(in1,in2,in3,in4,in5,in6)
%JUMP2DCOSTGRADIENT
%    COST_GRADIENT = JUMP2DCOSTGRADIENT(IN1,IN2,IN3,IN4,IN5,IN6)

%    This function was generated by the Symbolic Math Toolbox version 8.0.
%    27-Aug-2019 12:38:30

Fxb = in2(3,:);
Fxb_d = in4(3,:);
Fxf = in2(1,:);
Fxf_d = in4(1,:);
Fzb = in2(4,:);
Fzb_d = in4(4,:);
Fzf = in2(2,:);
Fzf_d = in4(2,:);
dphi = in1(6,:);
dphi_d = in3(6,:);
dx = in1(4,:);
dx_d = in3(4,:);
dz = in1(5,:);
dz_d = in3(5,:);
phi = in1(3,:);
phi_d = in3(3,:);
q1 = in5(1,:);
q2 = in5(2,:);
q3 = in5(3,:);
q4 = in5(4,:);
q5 = in5(5,:);
q6 = in5(6,:);
r1 = in6(1,:);
r2 = in6(2,:);
r3 = in6(3,:);
r4 = in6(4,:);
x = in1(1,:);
x_d = in3(1,:);
z = in1(2,:);
z_d = in3(2,:);
cost_gradient = [q1.*(x.*2.0-x_d.*2.0);q2.*(z.*2.0-z_d.*2.0);q3.*(phi.*2.0-phi_d.*2.0);q4.*(dx.*2.0-dx_d.*2.0);q5.*(dz.*2.0-dz_d.*2.0);q6.*(dphi.*2.0-dphi_d.*2.0);r1.*(Fxf.*2.0-Fxf_d.*2.0);r2.*(Fzf.*2.0-Fzf_d.*2.0);r3.*(Fxb.*2.0-Fxb_d.*2.0);r4.*(Fzb.*2.0-Fzb_d.*2.0)];
