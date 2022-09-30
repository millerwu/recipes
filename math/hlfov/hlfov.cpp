#include <math.h>
#include <iostream>

using namespace std;

#define PAI          3.1415926
#define ROTATE_ANGLE 30

int main(int argc, char** argv) {
    int width = 5184, height = 3880;
    float ori_d_fov = 115;
    float fx = sqrt(width * width + height * height) / 2 / tan((ori_d_fov / 2) * PAI / 180);
    cout << fx << endl;
    float rotate_angle = ROTATE_ANGLE;
    float beta_angle = atan((float)4 / 3) * 180 / PAI;
    cout << beta_angle << endl;
    float bias = (float)height / 2 /cos((beta_angle - rotate_angle) * PAI / 180);
    cout << bias << endl;
    float new_height = bias * cos(beta_angle * PAI / 180);
    float new_width  = bias * sin(beta_angle * PAI / 180);
    cout << "new_width = " << new_width * 2 << endl;
    cout << "new_height = " << new_height * 2 << endl;
    float new_d_fov = atan(bias / fx) * 180 / PAI * 2;
    float new_h_fov = atan(new_width / fx) * 180 / PAI * 2;
    float new_v_fov = atan(new_height / fx) * 180 / PAI * 2;
    cout << "new_d_fov = " << new_d_fov << endl;
    cout << "new_h_fov = " << new_h_fov << endl;
    cout << "new_v_fov = " << new_v_fov << endl;
}