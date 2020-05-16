class Quaternion
{
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

	get w() {return this._w;}
	get x()  {return this._x;}
	get y()  {return this._y;}
	get z()  {return this._z;}

	set w(value) {this._w = value;}
	set x(value) {this._x = value;}
	set y(value) {this._y = value;}
	set y(value) {this._z = value;}


	function magnitude() {return Math.sqrt(this._w * this._w + this._x * this._x  + this._y * this._y + this._z * this._z);}

	function negate ()
	{
		return new Quaternion(-this._w,-this._x,-this._y,-this._z);
	}
	function add(i_cRHO)
	{
		return new Quaternion(this._w + i_cRHO._w, this._x + i_cRHO._x, this._y + i_cRHO._y, this._z + i_cRHO._z);
	}
	function addEq(i_cRHO)
	{
		this._w += i_cRHO._w;
		this._x += i_cRHO._x;
		this._y += i_cRHO._y;
		this._z += i_cRHO._z;
	}
	function subtract(i_cRHO)
	{
		return new Quaternion(this._w - i_cRHO._w, this._x - i_cRHO._x, this._y - i_cRHO._y, this._z - i_cRHO._z);
	}
	function subtractEq(i_cRHO)
	{
		this._w -= i_cRHO._w;
		this._x -= i_cRHO._x;
		this._y -= i_cRHO._y;
		this._z -= i_cRHO._z;
	}
	function scale(scalar)
	{
		return new Quaternion(this._w * scale, this._x * scale, this._y * scale, this._z * scale);
	}
	function scaleEq(scalar)
	{
		this._w *= scale;
		this._x *= scale;
		this._y *= scale;
		this._z *= scale;
	}

	function multiply(factor)
	{
		if (typeof(factor) == "Quaternion"))
			return qMultiply(factor);
		else
			return scale(factor);
	}
	function divide(factor)
	{
		if (typeof(factor) == "Quaternion"))
			return qDivide(factor);
		else
			return scale(1.0 / factor);
	}

	function multiplyEq(factor)
	{
		if (typeof(factor) == "Quaternion"))
			return qMultiplyEq(factor);
		else
			return scaleEq(factor);
	}
	function divideEq(factor)
	{
		if (typeof(factor) == "Quaternion"))
			return qDivideEq(factor);
		else
			return scaleEq(1.0 / factor);
	}

	function invert ()
	{
		var fMagnitude = this._w * this._w + this._x * this._x + this._y * this._y + this._z * this._z;
		var fInv_Magnitude = 1.0 / fMagnitude;

		return new Quaternion (this._w * fInv_Magnitude,-this._x * fInv_Magnitude,-this._y * fInv_Magnitude,-this._z * fInv_Magnitude);
	}
	function invertEq ()
	{
		var fMagnitude = this._w * this._w + this._x * this._x + this._y * this._y + this._z * this._z;
		var fInv_Magnitude = 1.0 / fMagnitude;

		this._w *= fInv_Magnitude;
		this._x *= -fInv_Magnitude;
		this._y *= -fInv_Magnitude;
		this._z *= -fInv_Magnitude;
	}
	function qMultiply(RHO)
	{
		return new Quaternion (this._w * RHO._w - this._x * RHO._x - this._y * RHO._y - this._z * RHO._z,
							this._w * RHO._x + RHO._w * this._x + this._y * RHO._z - this._z * RHO._y,
							this._w * RHO._y + RHO._w * this._y + this._z * RHO._x - this._x * RHO._z,
							this._w * RHO._z + RHO._w * this._z + this._x * RHO._y - this._y * RHO._x);
	}
	function qMultiplyEq(RHO)
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
	function qDivide(RHO)
	{
		return qMultiply(RHO.invert());
	}
	function qDivideEq(RHO)
	{
		return qMultiplyEq(RHO.invert());
	}

	function loadRotationRadians(angle,axisX,axisY,axisZ)
	{
		var sinAng = Math.sin(angle * 0.5);
		this._w = Math.cos(angle * 0.5);
		this._x = axisX * sinAng;
		this._y = axisY * sinAng;
		this._z = axisZ * sinAng;
	}
	function loadRotationDegrees(angle,axisX,axisY,axisZ)
	{
		loadRotationRadians(angle * 0.017453292519943296,axisX,axisY,axisZ);
	}
}


