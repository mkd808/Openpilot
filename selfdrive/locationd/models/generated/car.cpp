#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1004709138138956157) {
   out_1004709138138956157[0] = delta_x[0] + nom_x[0];
   out_1004709138138956157[1] = delta_x[1] + nom_x[1];
   out_1004709138138956157[2] = delta_x[2] + nom_x[2];
   out_1004709138138956157[3] = delta_x[3] + nom_x[3];
   out_1004709138138956157[4] = delta_x[4] + nom_x[4];
   out_1004709138138956157[5] = delta_x[5] + nom_x[5];
   out_1004709138138956157[6] = delta_x[6] + nom_x[6];
   out_1004709138138956157[7] = delta_x[7] + nom_x[7];
   out_1004709138138956157[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7715134271309005436) {
   out_7715134271309005436[0] = -nom_x[0] + true_x[0];
   out_7715134271309005436[1] = -nom_x[1] + true_x[1];
   out_7715134271309005436[2] = -nom_x[2] + true_x[2];
   out_7715134271309005436[3] = -nom_x[3] + true_x[3];
   out_7715134271309005436[4] = -nom_x[4] + true_x[4];
   out_7715134271309005436[5] = -nom_x[5] + true_x[5];
   out_7715134271309005436[6] = -nom_x[6] + true_x[6];
   out_7715134271309005436[7] = -nom_x[7] + true_x[7];
   out_7715134271309005436[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5553063673957256880) {
   out_5553063673957256880[0] = 1.0;
   out_5553063673957256880[1] = 0;
   out_5553063673957256880[2] = 0;
   out_5553063673957256880[3] = 0;
   out_5553063673957256880[4] = 0;
   out_5553063673957256880[5] = 0;
   out_5553063673957256880[6] = 0;
   out_5553063673957256880[7] = 0;
   out_5553063673957256880[8] = 0;
   out_5553063673957256880[9] = 0;
   out_5553063673957256880[10] = 1.0;
   out_5553063673957256880[11] = 0;
   out_5553063673957256880[12] = 0;
   out_5553063673957256880[13] = 0;
   out_5553063673957256880[14] = 0;
   out_5553063673957256880[15] = 0;
   out_5553063673957256880[16] = 0;
   out_5553063673957256880[17] = 0;
   out_5553063673957256880[18] = 0;
   out_5553063673957256880[19] = 0;
   out_5553063673957256880[20] = 1.0;
   out_5553063673957256880[21] = 0;
   out_5553063673957256880[22] = 0;
   out_5553063673957256880[23] = 0;
   out_5553063673957256880[24] = 0;
   out_5553063673957256880[25] = 0;
   out_5553063673957256880[26] = 0;
   out_5553063673957256880[27] = 0;
   out_5553063673957256880[28] = 0;
   out_5553063673957256880[29] = 0;
   out_5553063673957256880[30] = 1.0;
   out_5553063673957256880[31] = 0;
   out_5553063673957256880[32] = 0;
   out_5553063673957256880[33] = 0;
   out_5553063673957256880[34] = 0;
   out_5553063673957256880[35] = 0;
   out_5553063673957256880[36] = 0;
   out_5553063673957256880[37] = 0;
   out_5553063673957256880[38] = 0;
   out_5553063673957256880[39] = 0;
   out_5553063673957256880[40] = 1.0;
   out_5553063673957256880[41] = 0;
   out_5553063673957256880[42] = 0;
   out_5553063673957256880[43] = 0;
   out_5553063673957256880[44] = 0;
   out_5553063673957256880[45] = 0;
   out_5553063673957256880[46] = 0;
   out_5553063673957256880[47] = 0;
   out_5553063673957256880[48] = 0;
   out_5553063673957256880[49] = 0;
   out_5553063673957256880[50] = 1.0;
   out_5553063673957256880[51] = 0;
   out_5553063673957256880[52] = 0;
   out_5553063673957256880[53] = 0;
   out_5553063673957256880[54] = 0;
   out_5553063673957256880[55] = 0;
   out_5553063673957256880[56] = 0;
   out_5553063673957256880[57] = 0;
   out_5553063673957256880[58] = 0;
   out_5553063673957256880[59] = 0;
   out_5553063673957256880[60] = 1.0;
   out_5553063673957256880[61] = 0;
   out_5553063673957256880[62] = 0;
   out_5553063673957256880[63] = 0;
   out_5553063673957256880[64] = 0;
   out_5553063673957256880[65] = 0;
   out_5553063673957256880[66] = 0;
   out_5553063673957256880[67] = 0;
   out_5553063673957256880[68] = 0;
   out_5553063673957256880[69] = 0;
   out_5553063673957256880[70] = 1.0;
   out_5553063673957256880[71] = 0;
   out_5553063673957256880[72] = 0;
   out_5553063673957256880[73] = 0;
   out_5553063673957256880[74] = 0;
   out_5553063673957256880[75] = 0;
   out_5553063673957256880[76] = 0;
   out_5553063673957256880[77] = 0;
   out_5553063673957256880[78] = 0;
   out_5553063673957256880[79] = 0;
   out_5553063673957256880[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8622990458116735126) {
   out_8622990458116735126[0] = state[0];
   out_8622990458116735126[1] = state[1];
   out_8622990458116735126[2] = state[2];
   out_8622990458116735126[3] = state[3];
   out_8622990458116735126[4] = state[4];
   out_8622990458116735126[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8622990458116735126[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8622990458116735126[7] = state[7];
   out_8622990458116735126[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5464552643576745249) {
   out_5464552643576745249[0] = 1;
   out_5464552643576745249[1] = 0;
   out_5464552643576745249[2] = 0;
   out_5464552643576745249[3] = 0;
   out_5464552643576745249[4] = 0;
   out_5464552643576745249[5] = 0;
   out_5464552643576745249[6] = 0;
   out_5464552643576745249[7] = 0;
   out_5464552643576745249[8] = 0;
   out_5464552643576745249[9] = 0;
   out_5464552643576745249[10] = 1;
   out_5464552643576745249[11] = 0;
   out_5464552643576745249[12] = 0;
   out_5464552643576745249[13] = 0;
   out_5464552643576745249[14] = 0;
   out_5464552643576745249[15] = 0;
   out_5464552643576745249[16] = 0;
   out_5464552643576745249[17] = 0;
   out_5464552643576745249[18] = 0;
   out_5464552643576745249[19] = 0;
   out_5464552643576745249[20] = 1;
   out_5464552643576745249[21] = 0;
   out_5464552643576745249[22] = 0;
   out_5464552643576745249[23] = 0;
   out_5464552643576745249[24] = 0;
   out_5464552643576745249[25] = 0;
   out_5464552643576745249[26] = 0;
   out_5464552643576745249[27] = 0;
   out_5464552643576745249[28] = 0;
   out_5464552643576745249[29] = 0;
   out_5464552643576745249[30] = 1;
   out_5464552643576745249[31] = 0;
   out_5464552643576745249[32] = 0;
   out_5464552643576745249[33] = 0;
   out_5464552643576745249[34] = 0;
   out_5464552643576745249[35] = 0;
   out_5464552643576745249[36] = 0;
   out_5464552643576745249[37] = 0;
   out_5464552643576745249[38] = 0;
   out_5464552643576745249[39] = 0;
   out_5464552643576745249[40] = 1;
   out_5464552643576745249[41] = 0;
   out_5464552643576745249[42] = 0;
   out_5464552643576745249[43] = 0;
   out_5464552643576745249[44] = 0;
   out_5464552643576745249[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5464552643576745249[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5464552643576745249[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5464552643576745249[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5464552643576745249[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5464552643576745249[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5464552643576745249[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5464552643576745249[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5464552643576745249[53] = -9.8000000000000007*dt;
   out_5464552643576745249[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5464552643576745249[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5464552643576745249[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5464552643576745249[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5464552643576745249[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5464552643576745249[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5464552643576745249[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5464552643576745249[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5464552643576745249[62] = 0;
   out_5464552643576745249[63] = 0;
   out_5464552643576745249[64] = 0;
   out_5464552643576745249[65] = 0;
   out_5464552643576745249[66] = 0;
   out_5464552643576745249[67] = 0;
   out_5464552643576745249[68] = 0;
   out_5464552643576745249[69] = 0;
   out_5464552643576745249[70] = 1;
   out_5464552643576745249[71] = 0;
   out_5464552643576745249[72] = 0;
   out_5464552643576745249[73] = 0;
   out_5464552643576745249[74] = 0;
   out_5464552643576745249[75] = 0;
   out_5464552643576745249[76] = 0;
   out_5464552643576745249[77] = 0;
   out_5464552643576745249[78] = 0;
   out_5464552643576745249[79] = 0;
   out_5464552643576745249[80] = 1;
}
void h_25(double *state, double *unused, double *out_889265146022464943) {
   out_889265146022464943[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6804285110175098999) {
   out_6804285110175098999[0] = 0;
   out_6804285110175098999[1] = 0;
   out_6804285110175098999[2] = 0;
   out_6804285110175098999[3] = 0;
   out_6804285110175098999[4] = 0;
   out_6804285110175098999[5] = 0;
   out_6804285110175098999[6] = 1;
   out_6804285110175098999[7] = 0;
   out_6804285110175098999[8] = 0;
}
void h_24(double *state, double *unused, double *out_6495393270646742639) {
   out_6495393270646742639[0] = state[4];
   out_6495393270646742639[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4631635511169599433) {
   out_4631635511169599433[0] = 0;
   out_4631635511169599433[1] = 0;
   out_4631635511169599433[2] = 0;
   out_4631635511169599433[3] = 0;
   out_4631635511169599433[4] = 1;
   out_4631635511169599433[5] = 0;
   out_4631635511169599433[6] = 0;
   out_4631635511169599433[7] = 0;
   out_4631635511169599433[8] = 0;
   out_4631635511169599433[9] = 0;
   out_4631635511169599433[10] = 0;
   out_4631635511169599433[11] = 0;
   out_4631635511169599433[12] = 0;
   out_4631635511169599433[13] = 0;
   out_4631635511169599433[14] = 1;
   out_4631635511169599433[15] = 0;
   out_4631635511169599433[16] = 0;
   out_4631635511169599433[17] = 0;
}
void h_30(double *state, double *unused, double *out_4636792290528558170) {
   out_4636792290528558170[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4725768622042835862) {
   out_4725768622042835862[0] = 0;
   out_4725768622042835862[1] = 0;
   out_4725768622042835862[2] = 0;
   out_4725768622042835862[3] = 0;
   out_4725768622042835862[4] = 1;
   out_4725768622042835862[5] = 0;
   out_4725768622042835862[6] = 0;
   out_4725768622042835862[7] = 0;
   out_4725768622042835862[8] = 0;
}
void h_26(double *state, double *unused, double *out_7563500725720819978) {
   out_7563500725720819978[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3062781791301042775) {
   out_3062781791301042775[0] = 0;
   out_3062781791301042775[1] = 0;
   out_3062781791301042775[2] = 0;
   out_3062781791301042775[3] = 0;
   out_3062781791301042775[4] = 0;
   out_3062781791301042775[5] = 0;
   out_3062781791301042775[6] = 0;
   out_3062781791301042775[7] = 1;
   out_3062781791301042775[8] = 0;
}
void h_27(double *state, double *unused, double *out_443595101086111806) {
   out_443595101086111806[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6900531933843260773) {
   out_6900531933843260773[0] = 0;
   out_6900531933843260773[1] = 0;
   out_6900531933843260773[2] = 0;
   out_6900531933843260773[3] = 1;
   out_6900531933843260773[4] = 0;
   out_6900531933843260773[5] = 0;
   out_6900531933843260773[6] = 0;
   out_6900531933843260773[7] = 0;
   out_6900531933843260773[8] = 0;
}
void h_29(double *state, double *unused, double *out_14606261072449856) {
   out_14606261072449856[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8613894660712811806) {
   out_8613894660712811806[0] = 0;
   out_8613894660712811806[1] = 1;
   out_8613894660712811806[2] = 0;
   out_8613894660712811806[3] = 0;
   out_8613894660712811806[4] = 0;
   out_8613894660712811806[5] = 0;
   out_8613894660712811806[6] = 0;
   out_8613894660712811806[7] = 0;
   out_8613894660712811806[8] = 0;
}
void h_28(double *state, double *unused, double *out_5588485164201759343) {
   out_5588485164201759343[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4750450395927209236) {
   out_4750450395927209236[0] = 1;
   out_4750450395927209236[1] = 0;
   out_4750450395927209236[2] = 0;
   out_4750450395927209236[3] = 0;
   out_4750450395927209236[4] = 0;
   out_4750450395927209236[5] = 0;
   out_4750450395927209236[6] = 0;
   out_4750450395927209236[7] = 0;
   out_4750450395927209236[8] = 0;
}
void h_31(double *state, double *unused, double *out_2980953142071459300) {
   out_2980953142071459300[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6834931072052059427) {
   out_6834931072052059427[0] = 0;
   out_6834931072052059427[1] = 0;
   out_6834931072052059427[2] = 0;
   out_6834931072052059427[3] = 0;
   out_6834931072052059427[4] = 0;
   out_6834931072052059427[5] = 0;
   out_6834931072052059427[6] = 0;
   out_6834931072052059427[7] = 0;
   out_6834931072052059427[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1004709138138956157) {
  err_fun(nom_x, delta_x, out_1004709138138956157);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7715134271309005436) {
  inv_err_fun(nom_x, true_x, out_7715134271309005436);
}
void car_H_mod_fun(double *state, double *out_5553063673957256880) {
  H_mod_fun(state, out_5553063673957256880);
}
void car_f_fun(double *state, double dt, double *out_8622990458116735126) {
  f_fun(state,  dt, out_8622990458116735126);
}
void car_F_fun(double *state, double dt, double *out_5464552643576745249) {
  F_fun(state,  dt, out_5464552643576745249);
}
void car_h_25(double *state, double *unused, double *out_889265146022464943) {
  h_25(state, unused, out_889265146022464943);
}
void car_H_25(double *state, double *unused, double *out_6804285110175098999) {
  H_25(state, unused, out_6804285110175098999);
}
void car_h_24(double *state, double *unused, double *out_6495393270646742639) {
  h_24(state, unused, out_6495393270646742639);
}
void car_H_24(double *state, double *unused, double *out_4631635511169599433) {
  H_24(state, unused, out_4631635511169599433);
}
void car_h_30(double *state, double *unused, double *out_4636792290528558170) {
  h_30(state, unused, out_4636792290528558170);
}
void car_H_30(double *state, double *unused, double *out_4725768622042835862) {
  H_30(state, unused, out_4725768622042835862);
}
void car_h_26(double *state, double *unused, double *out_7563500725720819978) {
  h_26(state, unused, out_7563500725720819978);
}
void car_H_26(double *state, double *unused, double *out_3062781791301042775) {
  H_26(state, unused, out_3062781791301042775);
}
void car_h_27(double *state, double *unused, double *out_443595101086111806) {
  h_27(state, unused, out_443595101086111806);
}
void car_H_27(double *state, double *unused, double *out_6900531933843260773) {
  H_27(state, unused, out_6900531933843260773);
}
void car_h_29(double *state, double *unused, double *out_14606261072449856) {
  h_29(state, unused, out_14606261072449856);
}
void car_H_29(double *state, double *unused, double *out_8613894660712811806) {
  H_29(state, unused, out_8613894660712811806);
}
void car_h_28(double *state, double *unused, double *out_5588485164201759343) {
  h_28(state, unused, out_5588485164201759343);
}
void car_H_28(double *state, double *unused, double *out_4750450395927209236) {
  H_28(state, unused, out_4750450395927209236);
}
void car_h_31(double *state, double *unused, double *out_2980953142071459300) {
  h_31(state, unused, out_2980953142071459300);
}
void car_H_31(double *state, double *unused, double *out_6834931072052059427) {
  H_31(state, unused, out_6834931072052059427);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
