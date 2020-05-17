#include <cmath>
#include <cstdio>
#include  <string>

#include <../Quaternion.hpp>
using namespace libQuaternion;

inline bool test(const Quaternion & i_cQuat, float i_fW, float i_fX, float i_fY, float i_fZ)
{
	const float fEpsilon = 1.0e-7;
	return std::fabs(i_cQuat.w() - i_fW) < fEpsilon && std::fabs(i_cQuat.x() - i_fX) < fEpsilon && std::fabs(i_cQuat.y() - i_fY) < fEpsilon && std::fabs(i_cQuat.z() - i_fZ) < fEpsilon;
}
inline int testAndReport(bool bSilent_Pass, const char * i_psTest, const Quaternion & i_cQuat, float i_fW, float i_fX, float i_fY, float i_fZ)
{
	int iRet = 0;
	std::string sSuccess = "Pass";
	bool bPrint = !bSilent_Pass;
	if (!test(i_cQuat,i_fW,i_fX,i_fY,i_fZ))
	{
		iRet = 1;
		bPrint = true;
		sSuccess = "Fail";
	}
	if (bPrint)
		printf("%s: %s: w=%.1f (%.1f) x=%.1f (%.1f) y=%.1f (%.1f) z=%.1f (%.1f)\n",
				sSuccess.c_str(),
				i_psTest,
				i_cQuat.w(),i_fW,
				i_cQuat.x(),i_fX,
				i_cQuat.y(),i_fY,
				i_cQuat.z(),i_fZ
				);
	return 0;
}
void printQ(const Quaternion & i_cQuat)
{
	printf("<%.2f, %.2f, %.2f, %.2f>",i_cQuat.w(),i_cQuat.x(),i_cQuat.y(),i_cQuat.z());
}

int testRotation(bool i_bSilent_Pass, float i_fAngle, float i_fAxis_X, float i_fAxis_Y, float i_fAxis_Z)
{
	int iRet = 0;
	char sStr[64];
	
	double dRadDeg = acos(-1.0) / 180.0;
	Quaternion qA;
	qA.loadRotationDegrees(i_fAngle,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
//	double dDegRad = 180.0 / acos(-1.0);
	sprintf(sStr,"%.0f rotation (%.0f,%.0f,%.0f)",i_fAngle,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
	iRet += testAndReport(i_bSilent_Pass,sStr,qA,std::cos(i_fAngle * dRadDeg * 0.5),i_fAxis_X * std::sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Y * std::sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Z * std::sin(i_fAngle * dRadDeg * 0.5));

	qA.loadRotationRadians(i_fAngle * dRadDeg,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
//	double dDegRad = 180.0 / acos(-1.0);
	sprintf(sStr,"%.0f rotation (%.0f,%.0f,%.0f)",i_fAngle,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
	iRet += testAndReport(i_bSilent_Pass,sStr,qA,std::cos(i_fAngle * dRadDeg * 0.5),i_fAxis_X * std::sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Y * std::sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Z * std::sin(i_fAngle * dRadDeg * 0.5));
	
	return iRet;
}

int main(void)
{
	int iFailures = 0;
	bool bSilent_Pass = true;
	Quaternion qA;
	Quaternion qW(1,0,0,0);
	Quaternion qX(0,1,0,0);
	Quaternion qY(0,0,1,0);
	Quaternion qZ(0,0,0,1);
	
	iFailures += testAndReport(bSilent_Pass,"W",qW,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X",qX,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y",qY,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Z",qZ,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"A",qA,0,0,0,0);
	
	iFailures += testAndReport(bSilent_Pass,"W^-1",qW.invert(),1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X^-1",qX.invert(),0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y^-1",qY.invert(),0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"Z^-1",qZ.invert(),0,0,0,-1);
	//iFailures += testAndReport(bSilent_Pass,qA.invert(),-nan(""),-nan(""),-nan(""),-nan(""));
	
	iFailures += testAndReport(bSilent_Pass,"-W",-qW,-1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"-X",-qX,0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"-Y",-qY,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"-Z",-qZ,0,0,0,-1);
	
	iFailures += testAndReport(bSilent_Pass,"W + W",qW + qW,2,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X + X",qX + qX,0,2,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y + Y",qY + qY,0,0,2,0);
	iFailures += testAndReport(bSilent_Pass,"Z + Z",qZ + qZ,0,0,0,2);
	iFailures += testAndReport(bSilent_Pass,"W + X",qW + qX,1,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"W + Y",qW + qY,1,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"W + Z",qW + qZ,1,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"X + W",qX + qW,1,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"X + Y",qX + qY,0,1,1,0);
	iFailures += testAndReport(bSilent_Pass,"X + Z",qX + qZ,0,1,0,1);
	iFailures += testAndReport(bSilent_Pass,"Y + W",qY + qW,1,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y + X",qY + qX,0,1,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y + Z",qY + qZ,0,0,1,1);
	iFailures += testAndReport(bSilent_Pass,"Z + W",qZ + qW,1,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z + X",qZ + qX,0,1,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z +YW",qZ + qY,0,0,1,1);

	iFailures += testAndReport(bSilent_Pass,"W - W",qW - qW,0,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X - X",qX - qX,0,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y - Y",qY - qY,0,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z - Z",qZ - qZ,0,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"W - X",qW - qX,1,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"W - Y",qW - qY,1,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"W - Z",qW - qZ,1,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"X - W",qX - qW,-1,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"X - Y",qX - qY,0,1,-1,0);
	iFailures += testAndReport(bSilent_Pass,"X - Z",qX - qZ,0,1,0,-1);
	iFailures += testAndReport(bSilent_Pass,"Y - W",qY - qW,-1,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y - X",qY - qX,0,-1,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y - Z",qY - qZ,0,0,1,-1);
	iFailures += testAndReport(bSilent_Pass,"Z - W",qZ - qW,-1,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z - X",qZ - qX,0,-1,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z - Y",qZ - qY,0,0,-1,1);

	iFailures += testAndReport(bSilent_Pass,"W * 2",qW * 2.0,2,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X * 2",qX * 2.0,0,2,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y * 2",qY * 2.0,0,0,2,0);
	iFailures += testAndReport(bSilent_Pass,"Z * 2",qZ * 2.0,0,0,0,2);

	iFailures += testAndReport(bSilent_Pass,"W / 2",qW / 2.0,0.5,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X / 2",qX / 2.0,0,0.5,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y / 2",qY / 2.0,0,0,0.5,0);
	iFailures += testAndReport(bSilent_Pass,"Z / 2",qZ / 2.0,0,0,0,0.5);
	
	iFailures += testAndReport(bSilent_Pass,"W * W",qW * qW,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X * X",qX * qX,-1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y * Y",qY * qY,-1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z * Z",qZ * qZ,-1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"W * X",qW * qX,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"W * Y",qW * qY,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"W * Z",qW * qZ,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"X * W",qX * qW,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"X * Y",qX * qY,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"X * Z",qX * qZ,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"Y * W",qY * qW,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y * X",qY * qX,0,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"Y * Z",qY * qZ,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z * W",qZ * qW,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z * X",qZ * qX,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Z * Y",qZ * qY,0,-1,0,0);
	
	iFailures += testAndReport(bSilent_Pass,"W / W",qW / qW,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X / X",qX / qX,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y / Y",qY / qY,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z / Z",qZ / qZ,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"W / X",qW / qX,0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"W / Y",qW / qY,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"W / Z",qW / qZ,0,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"X / W",qX / qW,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"X / Y",qX / qY,0,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"X / Z",qX / qZ,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y / W",qY / qW,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y / X",qY / qX,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"Y / Z",qY / qZ,0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z / W",qZ / qW,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"Z / X",qZ / qX,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"Z / Y",qZ / qY,0,1,0,0);

	iFailures += testAndReport(bSilent_Pass,"W * W / W",qW * qW / qW,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"W * X / W",qW * qX / qW,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"W * Y / W",qW * qY / qW,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"W * Z / W",qW * qZ / qW,0,0,0,1);
	iFailures += testAndReport(bSilent_Pass,"X * W / X",qX * qW / qX,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"X * X / X",qX * qX / qX,0,1,0,0);
	iFailures += testAndReport(bSilent_Pass,"X * Y / X",qX * qY / qX,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"X * Z / X",qX * qZ / qX,0,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"Y * W / Y",qY * qW / qY,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y * X / Y",qY * qX / qY,0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Y * Y / Y",qY * qY / qY,0,0,1,0);
	iFailures += testAndReport(bSilent_Pass,"Y * Z / Y",qY * qZ / qY,0,0,0,-1);
	iFailures += testAndReport(bSilent_Pass,"Z * W / Z",qZ * qW / qZ,1,0,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z * X / Z",qZ * qX / qZ,0,-1,0,0);
	iFailures += testAndReport(bSilent_Pass,"Z * Y / Z",qZ * qY / qZ,0,0,-1,0);
	iFailures += testAndReport(bSilent_Pass,"Z * Z / Z",qZ * qZ / qZ,0,0,0,1);



	for (float fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
		iFailures += testRotation(bSilent_Pass,fAngle,0,0,0);
	
	for (float fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
		iFailures += testRotation(bSilent_Pass,fAngle,1,0,0);

	for (float fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
		iFailures += testRotation(bSilent_Pass,fAngle,0,1,0);

	for (float fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
		iFailures += testRotation(bSilent_Pass,fAngle,0,0,1);
		
	printf("\e[32mPASS\e[39m: %i\t\e[31mFAIL\e[39m: %i\n",197-iFailures,iFailures);
	return 0;
}
