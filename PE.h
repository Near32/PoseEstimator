#ifndef PE_H
#define PE_H

#include "EKF.h"
#include "Mat.h"

#include <stdio.h>
#include <bcm2835.h>

#include "RPI/I2Cdev/I2Cdev.h"
#include "MPU6050/MPU6050.h"

#include <time.h>

class PE
{
	private :
	
	MPU6050* IMU;
	Mat<float>* biasGy;
	Mat<float> Gravity;
	float sgyro;
	float sacc;
	float angleX;
	float angleY;
	float angleZ;
	
	
	float dt;
	float stdnoise;
	float stdnoise_obs;
	
	//-------------------------
	// gravity field estimator :
	//-------------------------
	Mat<float>* Xg;
	Mat<float>* XgCovar;
	
	EEKF<float>* instanceEEKF;
	//----------------------------
	//----------------------------
	
	//------------------------
	// Pose Estimator :
	//------------------------
	
	/*state : 
		LinearAcceleration
		LinearVelocity
		AngularVelocity
		X-Y-Z position
		Quaternion orientation
		*/
	Mat<float>* X;
	Mat<float>* XCovar;
	EEKF<float>* instanceEEKFPose;
	
	float stdnoiseX;
	float stdnoise_obsX;
	
	public :
	
	PE(float dt_=1e-3f);
	~PE();
	
	void initialize();
	void initializeIMU();
	
	void callback(float dt_=1e-4f);
	
	void setDT(float dt_);
	float getDT();
	
	static Mat<float> Euler2Rot(const float& roll, const float& pitch, const float& yaw);
};

#endif
