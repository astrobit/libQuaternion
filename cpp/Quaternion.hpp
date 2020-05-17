/** 
@brief Quaternion class for c++
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License

*/

#pragma once

#include <cmath>
/** 
namespace for the quaternion library
*/
namespace libQuaternion
{
/** 
Container class and methods for quaternion manipuation
*/
	class Quaternion
	{
	private:
/** values of the components: fVal[0] = w, fVal[1] = x, fVal[2] = y, fVal[3] = z */
		float fVal[4]; 
	public:
/** 
Quaternion void constructor; sets all components to 0
*/
		Quaternion(void)
		{
			fVal[0] = 0.0;
			fVal[1] = 0.0;
			fVal[2] = 0.0;
			fVal[3] = 0.0;
		}
/** 
Quaternion initializing constructor
@param i_fW The real scalar component
@param i_fX The imaginary x component
@param i_fY The imaginary y component
@param i_fZ The imaginary z component
*/
		Quaternion(float i_fW, float i_fX, float i_fY, float i_fZ)
		{
			fVal[0] = i_fW;
			fVal[1] = i_fX;
			fVal[2] = i_fY;
			fVal[3] = i_fZ;
		}

/** 
Get for the real scalar component
@returns The real scalar component (w)
*/
		float w(void) const {return fVal[0];}
/** 
Get for the imaginary x component
@returns The imaginary x component
*/
		float x(void) const  {return fVal[1];}
/** 
Get for the imaginary y component
@returns The imaginary y component
*/
		float y(void) const  {return fVal[2];}
/** 
Get for the imaginary z component
@returns The imaginary z component
*/
		float z(void) const  {return fVal[3];}

/** 
Set for the real scalar component
@param i_fVal The new value for the real scalar component (w)
@returns none
*/
		void setW(float i_fVal) {fVal[0] = i_fVal;}
/** 
Set for the imaginary x component
@param i_fVal The new value for the imaginary x component
@returns none
*/
		void setX(float i_fVal) {fVal[1] = i_fVal;}
/** 
Set for the imaginary y component
@param i_fVal The new value for the imaginary y component
@returns none
*/
		void setY(float i_fVal) {fVal[2] = i_fVal;}
/** 
Set for the imaginary z component
@param i_fVal The new value for the imaginary z component
@returns none
*/
		void setZ(float i_fVal) {fVal[3] = i_fVal;}


/** 
Get the magnitude (length) of the quaternion
@returns the magnitude of the quaternion \f$(\sqrt{w^2 + x^2 + y^2 + z^2})\f$
*/
		float magnitude(void) {return std::sqrt(fVal[0] * fVal[0] + fVal[1] * fVal[1]  + fVal[2] * fVal[2] + fVal[3] * fVal[3]);}

/** 
Get the additive inverse (negative value) of the quaternion.
@returns a Quaternion with the additive inverse (-w,-x,-y,-z)
*/
		Quaternion operator - (void) const
		{
			return Quaternion(-fVal[0],-fVal[1],-fVal[2],-fVal[3]);
		}
/** 
Add two quaternions, placing the result in this Quaternion.
@param i_cRHO the right hand operand (RHO) to add to this quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator += (const Quaternion & i_cRHO)
		{
			fVal[1] += i_cRHO.fVal[1];
			fVal[2] += i_cRHO.fVal[2];
			fVal[3] += i_cRHO.fVal[3];
			fVal[0] += i_cRHO.fVal[0];
			return *this;
		}
/** 
Add two quaternions, returning the result as a Quaternion
@param i_cRHO the right hand operand (RHO) to add to this quaternion
@returns a Quaternion that is the sum of this quaternion and the RHO \f$(w_1 + w_2,x_1 + x_2, y_1 + y_2, z_1 + z_2)\f$
*/
		Quaternion operator + (const Quaternion & i_cRHO) const
		{
			Quaternion qRet(*this);
			return (qRet += i_cRHO);
		}

/** 
Subtract one quaternion from another, placing the result in this Quaternion. \f$(w_1 - w_2,x_1 - x_2, y_1 - y_2, z_1 - z_2)\f$
@param i_cRHO the right hand operand (RHO) to subtract from this quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator -= (const Quaternion & i_cRHO)
		{
			fVal[1] -= i_cRHO.fVal[1];
			fVal[2] -= i_cRHO.fVal[2];
			fVal[3] -= i_cRHO.fVal[3];
			fVal[0] -= i_cRHO.fVal[0];
			return *this;
		}
/** 
Subtract one quaternion from another, returning the result as a Quaternion.  \f$(w_1 - w_2,x_1 - x_2, y_1 - y_2, z_1 - z_2)\f$
@param i_cRHO the right hand operand (RHO) to subtract to this quaternion
@returns a Quaternion that is the sum of this quaternion and the additive inverse of the RHO.
*/
		Quaternion operator - (const Quaternion & i_cRHO) const
		{
			Quaternion qRet(*this);
			return (qRet -= i_cRHO);
		}


/** 
Get a quaternion that is the multiplicative inverse of the current quaternion.
@returns a Quaternion that is the multipliciative inverse of the current quaternion.
*/
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
/** 
Perform multiplication (Hamilton product) of two quaternions.
\f[<w_1 w_2 - \vec{x}_1 \bullet \vec{x}_2, w_1 \vec{x}_2 + w_2 \vec{x}_1 + \vec{x}_1 \times \vec{x}_2>\f]
@param i_cRHO the quaternion by which to multiply this quaternion
@returns a Quaternion that is the multiplied by the factor
*/
		Quaternion operator * (const Quaternion & i_cRHO) const
		{
			Quaternion qRevised(fVal[0] * i_cRHO.fVal[0] - fVal[1] * i_cRHO.fVal[1] - fVal[2] * i_cRHO.fVal[2] - fVal[3] * i_cRHO.fVal[3],
								fVal[0] * i_cRHO.fVal[1] + i_cRHO.fVal[0] * fVal[1] + fVal[2] * i_cRHO.fVal[3] - fVal[3] * i_cRHO.fVal[2],
								fVal[0] * i_cRHO.fVal[2] + i_cRHO.fVal[0] * fVal[2] + fVal[3] * i_cRHO.fVal[1] - fVal[1] * i_cRHO.fVal[3],
								fVal[0] * i_cRHO.fVal[3] + i_cRHO.fVal[0] * fVal[3] + fVal[1] * i_cRHO.fVal[2] - fVal[2] * i_cRHO.fVal[1]
								);

			return qRevised;
		}
/** 
Perform division of two quaternions via the multiplicative inverse and the Hamilton product \f$(q_1 q_2^{-1})\f$.
@param i_cRHO the quaternion by which to divide this quaternion
@returns a Quaternion that is the divided by the right hand operator (RHO)
*/
		Quaternion operator / (const Quaternion & i_cRHO) const
		{
			return (*this * i_cRHO.invert());
		}

/** 
Perform multiplication (Hamilton product) of two quaternions, storing the result in this Quaternion.
\f[<w_1 w_2 - \vec{x}_1 \bullet \vec{x}_2, w_1 \vec{x}_2 + w_2 \vec{x}_1 + \vec{x}_1 \times \vec{x}_2>\f]
@param i_cRHO the quaternion by which to multiply this quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator *= (const Quaternion & i_cRHO)
		{
			return (*this = Quaternion(*this) * i_cRHO.invert());
		}
/** 
Perform division of two quaternions via the multiplicative inverse and the Hamilton product \f$(q_1 q_2^{-1})\f$, storing the result in this Quaternion.
@param i_cRHO the quaternion by which to divide this quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator /= (const Quaternion & i_cRHO)
		{
			return (*this *= i_cRHO.invert());
		}

/** 
Multiply a quaternion by a scalar factor \f$(s w, s x, s y, s z)\f$, storing the result in this quaternion
@param i_fScalar the factor by which to scale the quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator *= (float i_fScalar)
		{
			fVal[1] *= i_fScalar;
			fVal[2] *= i_fScalar;
			fVal[3] *= i_fScalar;
			fVal[0] *= i_fScalar;
			return *this;
		}
/** 
Divide a quaternion by a scalar factor \f$(w\div s, x\div s, y\div s, z\div s)\f$, storing the result in this quaternion
@param i_fScalar the factor by which to scale the quaternion
@returns a reference to this Quaternion
*/
		Quaternion & operator /= (float i_fScalar)
		{
			float fInv = 1.0 / i_fScalar;
			fVal[1] *= fInv;
			fVal[2] *= fInv;
			fVal[3] *= fInv;
			fVal[0] *= fInv;
			return *this;
		}
/** 
Multiply the quaternion by a scalar factor \f$(s w, s x, s y, s z)\f$
@param i_fScalar the factor by which to scale the quaternion
@returns a Quaternion that is the scaled by the scalar factor s
*/
		Quaternion operator * (float i_fScalar) const
		{
			Quaternion qRet(*this);
			return (qRet *= i_fScalar);
		}
/** 
Divide the quaternion by a scalar factor \f$(w/s, x/s, y/s, z/s)\f$
@param i_fScalar the factor by which to scale the quaternion
@returns a Quaternion that is the divided by the scalar factor s
*/
		Quaternion operator / (float i_fScalar)
		{
			Quaternion qRet(*this);
			return (qRet /= i_fScalar);
		}

/** 
Loads the Quaternion with a rotation about a specified axis.
@param i_fAngle the angle (in radians) through which rotation occurs
@param i_fAxis_X the x component of the axis about which rotation occurs.
@param i_fAxis_Y the y component of the axis about which rotation occurs.
@param i_fAxis_Z the z component of the axis about which rotation occurs.
@returns none
*/
		void loadRotationRadians(float i_fAngle, float i_fAxis_X, float i_fAxis_Y, float i_fAxis_Z)
		{
			float fSinAng = std::sin(i_fAngle * 0.5);
			fVal[0] = std::cos(i_fAngle * 0.5);
			fVal[1] = i_fAxis_X * fSinAng;
			fVal[2] = i_fAxis_Y * fSinAng;
			fVal[3] = i_fAxis_Z * fSinAng;
		}
/** 
Loads the Quaternion with a rotation about a specified axis.
@param i_fAngle the angle (in degrees) through which rotation occurs
@param i_fAxis_X the x component of the axis about which rotation occurs.
@param i_fAxis_Y the y component of the axis about which rotation occurs.
@param i_fAxis_Z the z component of the axis about which rotation occurs.
@returns none
*/
		void loadRotationDegrees(float i_fAngle, float i_fAxis_X, float i_fAxis_Y, float i_fAxis_Z)
		{
			loadRotationRadians(i_fAngle * 0.017453292519943296,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
		}
	};
}

