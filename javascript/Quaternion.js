/** 
@brief An encapsulation of quaternion data and methods for Javascript
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License

*/

class Quaternion
{
/** 
Quaternion constructor
@param w The real scalar component
@param x The imaginary x component
@param y The imaginary y component
@param z The imaginary z component
*/
	constructor(w,x,y,z)
	{
		if (w != null)
			this._w = w;
		else
			this._w = 0;
		if (x != null)
			this._x = x;
		else
			this._x = 0;
		if (y != null)
			this._y = y;
		else
			this._y = 0;
		if (z != null)
			this._z = z;
		else
			this._z = 0;
	}

/** 
Get for the real scalar component
@returns The real scalar component (w)
*/
	get w() {return this._w;}
/** 
Get for the imaginary x component
@returns The imaginary x component
*/
	get x()  {return this._x;}
/** 
Get for the imaginary y component
@returns The imaginary y component
*/
	get y()  {return this._y;}
/** 
Get for the imaginary z component
@returns The imaginary z component
*/
	get z()  {return this._z;}

/** 
Set for the real scalar component
@param value The new value for the real scalar component (w)
@returns none
*/
	set w(value) {this._w = value;}
/** 
Set for the imaginary x component
@param value The new value for the imaginary x component
@returns none
*/
	set x(value) {this._x = value;}
/** 
Set for the imaginary y component
@param value The new value for the imaginary y component
@returns none
*/
	set y(value) {this._y = value;}
/** 
Set for the imaginary z component
@param value The new value for the imaginary z component
@returns none
*/
	set z(value) {this._z = value;}


/** 
Get the magnitude (length) of the quaternion
@returns the magnitude of the quaternion \f$(\sqrt{w^2 + x^2 + y^2 + z^2})\f$
*/
	magnitude()
	{
		return Math.sqrt(this._w * this._w + this._x * this._x  + this._y * this._y + this._z * this._z);
	}

/** 
Get the additive inverse (negative value) of the quaternion.
@returns a new Quaternion with the additive inverse (-w,-x,-y,-z)
*/
	negate ()
	{
		return new Quaternion(-this._w,-this._x,-this._y,-this._z);
	}
/** 
Add two quaternions, returning the result in a new Quaternion
@param RHO the right hand operand (RHO) to add to this quaternion
@returns a new Quaternion that is the sum of this quaternion and the RHO \f$(w_1 + w_2,x_1 + x_2, y_1 + y_2, z_1 + z_2)\f$
*/
	add(RHO)
	{
		return new Quaternion(this._w + RHO._w, this._x + RHO._x, this._y + RHO._y, this._z + RHO._z);
	}
/** 
Add two quaternions, placing the result in this Quaternion.
@param RHO the right hand operand (RHO) to add to this quaternion
@returns none
*/
	addEq(RHO)
	{
		this._w += RHO._w;
		this._x += RHO._x;
		this._y += RHO._y;
		this._z += RHO._z;
	}
/** 
Subtract one quaternion from another, returning the result in a new Quaternion.  \f$(w_1 - w_2,x_1 - x_2, y_1 - y_2, z_1 - z_2)\f$
@param RHO the right hand operand (RHO) to subtract to this quaternion
@returns a new Quaternion that is the sum of this quaternion and the additive inverse of the RHO.
*/
	subtract(RHO)
	{
		return new Quaternion(this._w - RHO._w, this._x - RHO._x, this._y - RHO._y, this._z - RHO._z);
	}
/** 
Subtract one quaternion from another, placing the result in this Quaternion. \f$(w_1 - w_2,x_1 - x_2, y_1 - y_2, z_1 - z_2)\f$
@param RHO the right hand operand (RHO) to subtract from this quaternion
@returns none
*/
	subtractEq(RHO)
	{
		this._w -= RHO._w;
		this._x -= RHO._x;
		this._y -= RHO._y;
		this._z -= RHO._z;
	}
/** 
Multiply the quaternion by a scalar factor \f$(s w, s x, s y, s z)\f$
@param scalar the factor by which to scale the quaternion
@returns a new Quaternion that is the scaled by the scalar factor s
*/
	scale(scalar)
	{
		return new Quaternion(this._w * scalar, this._x * scalar, this._y * scalar, this._z * scalar);
	}
/** 
Multiply a quaternion by a scalar factor \f$(s w, s x, s y, s z)\f$, storing the result in this quaternion
@param scalar the factor by which to scale the quaternion
@returns none
*/
	scaleEq(scalar)
	{
		this._w *= scale;
		this._x *= scale;
		this._y *= scale;
		this._z *= scale;
	}

/** 
Multiply the quaternion by a scalar factor or another Quaternion
@param factor the factor by which to multiply the quaternion
@returns a new Quaternion that is the multiplied by the factor
*/
	multiply(factor)
	{
		if (typeof(factor) == "object")
			return this.qMultiply(factor);
		else
			return this.scale(factor);
	}
/** 
Divide the quaternion by a scalar factor or another Quaternion
@param factor the factor by which to divide the quaternion
@returns a new Quaternion that is the divided by the factor
*/
	divide(factor)
	{
		if (typeof(factor) == "object")
			return this.qDivide(factor);
		else
			return this.scale(1.0 / factor);
	}

/** 
Multiply the quaternion by a scalar factor or another Quaternion, storing the result in the current Quaternion
@param factor the factor by which to multiply the quaternion
@returns none
*/
	multiplyEq(factor)
	{
		if (typeof(factor) == "Quaternion")
			return this.qMultiplyEq(factor);
		else
			return this.scaleEq(factor);
	}
/** 
Divide the quaternion by a scalar factor or another Quaternion, storing the result in the current Quaternion
@param factor the factor by which to divide the quaternion
@returns a new Quaternion that is the divided by the factor
*/
	divideEq(factor)
	{
		if (typeof(factor) == "Quaternion")
			return this.qDivideEq(factor);
		else
			return this.scaleEq(1.0 / factor);
	}

/** 
Get a quaternion that is the multiplicative inverse of the current quaternion.
@returns a new Quaternion that is the multipliciative inverse of the current quaternion.
*/
	invert ()
	{
		var fMagnitude = this._w * this._w + this._x * this._x + this._y * this._y + this._z * this._z;
		var fInv_Magnitude = 1.0 / fMagnitude;

		return new Quaternion (this._w * fInv_Magnitude,-this._x * fInv_Magnitude,-this._y * fInv_Magnitude,-this._z * fInv_Magnitude);
	}
/** 
Assigns the multiplicative inverse of the current quaternion to itself.
@returns none
*/
	invertEq ()
	{
		var fMagnitude = this._w * this._w + this._x * this._x + this._y * this._y + this._z * this._z;
		var fInv_Magnitude = 1.0 / fMagnitude;

		this._w *= fInv_Magnitude;
		this._x *= -fInv_Magnitude;
		this._y *= -fInv_Magnitude;
		this._z *= -fInv_Magnitude;
	}

/** 
Perform multiplication (Hamilton product) of two quaternions.
\f[<w_1 w_2 - \vec{x}_1 \bullet \vec{x_2}, w_1 \vec{x_2} + w_2 \vec{x}_1 + \vec{x}_1 \times \vec{x}_2]\f
@param RHO the quaternion by which to multiply this quaternion
@returns a new Quaternion that is the multiplied by the factor
*/
	qMultiply(RHO)
	{
		return new Quaternion (this._w * RHO._w - this._x * RHO._x - this._y * RHO._y - this._z * RHO._z,
							this._w * RHO._x + RHO._w * this._x + this._y * RHO._z - this._z * RHO._y,
							this._w * RHO._y + RHO._w * this._y + this._z * RHO._x - this._x * RHO._z,
							this._w * RHO._z + RHO._w * this._z + this._x * RHO._y - this._y * RHO._x);
	}
/** 
Perform multiplication (Hamilton product) of two quaternions, storing the result in this Quaternion.
\f[<w_1 w_2 - \vec{x}_1 \bullet \vec{x_2}, w_1 \vec{x_2} + w_2 \vec{x}_1 + \vec{x}_1 \times \vec{x}_2]\f
@param RHO the quaternion by which to multiply this quaternion
@returns none
*/
	qMultiplyEq(RHO)
	{
		var qNew = new Quaternion (this._w * RHO._w - this._x * RHO._x - this._y * RHO._y - this._z * RHO._z,
							this._w * RHO._x + RHO._w * this._x + this._y * RHO._z - this._z * RHO._y,
							this._w * RHO._y + RHO._w * this._y + this._z * RHO._x - this._x * RHO._z,
							this._w * RHO._z + RHO._w * this._z + this._x * RHO._y - this._y * RHO._x);
		this._x = qNew._x;
		this._y = qNew._y;
		this._z = qNew._z;
		this._w = qNew._w;
	}
/** 
Perform division of two quaternions via the multiplicative inverse and the Hamilton product \f$(\q_1 q_2^{-1})\f$.
@param RHO the quaternion by which to divide this quaternion
@returns a new Quaternion that is the divided by the right hand operator (RHO)
*/
	qDivide(RHO)
	{
		return this.qMultiply(RHO.invert());
	}
/** 
Perform division of two quaternions via the multiplicative inverse and the Hamilton product \f$(\q_1 q_2^{-1})\f$, storing the result in this Quaternion.
@param RHO the quaternion by which to divide this quaternion
@returns none
*/
	qDivideEq(RHO)
	{
		this.qMultiplyEq(RHO.invert());
	}

/** 
Loads the Quaternion with a rotation about a specified axis.
@param angle the angle (in radians) through which rotation occurs
@param axisX the x component of the axis about which rotation occurs.
@param axisY the y component of the axis about which rotation occurs.
@param axisZ the z component of the axis about which rotation occurs.
@returns none
*/
	loadRotationRadians(angle,axisX,axisY,axisZ)
	{
		var sinAng = Math.sin(angle * 0.5);
		this._w = Math.cos(angle * 0.5);
		this._x = axisX * sinAng;
		this._y = axisY * sinAng;
		this._z = axisZ * sinAng;
	}
/** 
Loads the Quaternion with a rotation about a specified axis.
@param angle the angle (in degrees) through which rotation occurs
@param axisX the x component of the axis about which rotation occurs.
@param axisY the y component of the axis about which rotation occurs.
@param axisZ the z component of the axis about which rotation occurs.
@returns none
*/
	loadRotationDegrees(angle,axisX,axisY,axisZ)
	{
		this.loadRotationRadians(angle * Math.PI / 180.0,axisX,axisY,axisZ);
	}
}


