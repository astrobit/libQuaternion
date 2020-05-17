#pragma once

#include <cmath>
namespace libQuaternion
{
	class Quaternion
	{
	private:
		float fVal[4];
	public:
		Quaternion(void)
		{
			fVal[0] = 0.0;
			fVal[1] = 0.0;
			fVal[2] = 0.0;
			fVal[3] = 0.0;
		}
		Quaternion(float i_fW, float i_fX, float i_fY, float i_fZ)
		{
			fVal[0] = i_fW;
			fVal[1] = i_fX;
			fVal[2] = i_fY;
			fVal[3] = i_fZ;
		}

		float w(void) const {return fVal[0];}
		float x(void) const  {return fVal[1];}
		float y(void) const  {return fVal[2];}
		float z(void) const  {return fVal[3];}

		void setW(float i_fVal) {fVal[0] = i_fVal;}
		void setX(float i_fVal) {fVal[1] = i_fVal;}
		void setY(float i_fVal) {fVal[2] = i_fVal;}
		void setZ(float i_fVal) {fVal[3] = i_fVal;}


		float magnitude(void) {return std::sqrt(fVal[0] * fVal[0] + fVal[1] * fVal[1]  + fVal[2] * fVal[2] + fVal[3] * fVal[3]);}

		Quaternion operator - (void) const
		{
			return Quaternion(-fVal[0],-fVal[1],-fVal[2],-fVal[3]);
		}
		Quaternion & operator += (const Quaternion & i_cRHO)
		{
			fVal[1] += i_cRHO.fVal[1];
			fVal[2] += i_cRHO.fVal[2];
			fVal[3] += i_cRHO.fVal[3];
			fVal[0] += i_cRHO.fVal[0];
			return *this;
		}
		Quaternion operator + (const Quaternion & i_cRHO) const
		{
			Quaternion qRet(*this);
			return (qRet += i_cRHO);
		}

		Quaternion & operator -= (const Quaternion & i_cRHO)
		{
			fVal[1] -= i_cRHO.fVal[1];
			fVal[2] -= i_cRHO.fVal[2];
			fVal[3] -= i_cRHO.fVal[3];
			fVal[0] -= i_cRHO.fVal[0];
			return *this;
		}
		Quaternion operator - (const Quaternion & i_cRHO) const
		{
			Quaternion qRet(*this);
			return (qRet -= i_cRHO);
		}

		Quaternion & operator *= (float i_fScalar)
		{
			fVal[1] *= i_fScalar;
			fVal[2] *= i_fScalar;
			fVal[3] *= i_fScalar;
			fVal[0] *= i_fScalar;
			return *this;
		}
		Quaternion & operator /= (float i_fScalar)
		{
			float fInv = 1.0 / i_fScalar;
			fVal[1] *= fInv;
			fVal[2] *= fInv;
			fVal[3] *= fInv;
			fVal[0] *= fInv;
			return *this;
		}
		Quaternion operator * (float i_fScalar) const
		{
			Quaternion qRet(*this);
			return (qRet *= i_fScalar);
		}
		Quaternion operator / (float i_fScalar)
		{
			Quaternion qRet(*this);
			return (qRet /= i_fScalar);
		}

		Quaternion invert (void) const
		{
			float fMagnitude = fVal[0] * fVal[0] + fVal[1] * fVal[1] + fVal[2] * fVal[2] + fVal[3] * fVal[3];
			float fInv_Magnitude = 1.0 / fMagnitude;

			Quaternion qRevised(fVal[0] * fInv_Magnitude,
								-fVal[1] * fInv_Magnitude,
								-fVal[2] * fInv_Magnitude,
								-fVal[3] * fInv_Magnitude
								);

			return qRevised;
		}
		Quaternion operator * (const Quaternion & i_cRHO) const
		{
			Quaternion qRevised(fVal[0] * i_cRHO.fVal[0] - fVal[1] * i_cRHO.fVal[1] - fVal[2] * i_cRHO.fVal[2] - fVal[3] * i_cRHO.fVal[3],
								fVal[0] * i_cRHO.fVal[1] + i_cRHO.fVal[0] * fVal[1] + fVal[2] * i_cRHO.fVal[3] - fVal[3] * i_cRHO.fVal[2],
								fVal[0] * i_cRHO.fVal[2] + i_cRHO.fVal[0] * fVal[2] + fVal[3] * i_cRHO.fVal[1] - fVal[1] * i_cRHO.fVal[3],
								fVal[0] * i_cRHO.fVal[3] + i_cRHO.fVal[0] * fVal[3] + fVal[1] * i_cRHO.fVal[2] - fVal[2] * i_cRHO.fVal[1]
								);

			return qRevised;
		}
		Quaternion operator / (const Quaternion & i_cRHO) const
		{
			return (*this * i_cRHO.invert());
		}

		Quaternion & operator *= (const Quaternion & i_cRHO)
		{
			return (*this = Quaternion(*this) * i_cRHO.invert());
		}
		Quaternion & operator /= (const Quaternion & i_cRHO)
		{
			return (*this *= i_cRHO.invert());
		}


		void loadRotationRadians(float i_fAngle, float i_fAxis_X, float i_fAxis_Y, float i_fAxis_Z)
		{
			float fSinAng = std::sin(i_fAngle * 0.5);
			fVal[0] = std::cos(i_fAngle * 0.5);
			fVal[1] = i_fAxis_X * fSinAng;
			fVal[2] = i_fAxis_Y * fSinAng;
			fVal[3] = i_fAxis_Z * fSinAng;
		}
		void loadRotationDegrees(float i_fAngle, float i_fAxis_X, float i_fAxis_Y, float i_fAxis_Z)
		{
			loadRotationRadians(i_fAngle * 0.017453292519943296,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
		}
	};
}

