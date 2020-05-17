
function test(i_cQuat, i_fW, i_fX, i_fY, i_fZ)
{
	var fEpsilon = 1.0e-7;
	return Math.abs(i_cQuat.w - i_fW) < fEpsilon && Math.abs(i_cQuat.x - i_fX) < fEpsilon && Math.abs(i_cQuat.y - i_fY) < fEpsilon && Math.abs(i_cQuat.z - i_fZ) < fEpsilon;
}
function testAndReport(bSilent_Pass, i_psTest, i_cQuat, i_fW, i_fX, i_fY, i_fZ)
{
	var iRet = 0;
	var sSuccess = "Pass";
	var bPrint = !bSilent_Pass;
	if (!test(i_cQuat,i_fW,i_fX,i_fY,i_fZ))
	{
		iRet = 1;
		bPrint = true;
		sSuccess = "Fail";
	}
	if (bPrint)
	{
		console.log(sSuccess + ":  " + i_psTest + ": w=" + i_cQuat.w + " (" + i_fW + ") x=" + i_cQuat.x + " (" + i_fX + ") y=" + i_cQuat.y + " (" + i_fY + ") z=" + i_cQuat.z + " (" + i_fZ + ")");
	}
	return iRet;
}
function printQ(i_cQuat)
{
	console.log("<" + i_cQuat.w + ", " + i_cQuat.x + ", " + i_cQuat.y + ", " + i_cQuat.z + ">");
}

function testRotation(i_bSilent_Pass, i_fAngle, i_fAxis_X, i_fAxis_Y, i_fAxis_Z)
{
	var iRet = 0;
	var sStr = "";
	
	var dRadDeg = Math.PI / 180.0;
	var qA = new Quaternion();
	qA.loadRotationDegrees(i_fAngle,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
//	double dDegRad = 180.0 / acos(-1.0);
	sStr = i_fAngle + " rotation (" + i_fAxis_X + ", " + i_fAxis_Y + ", " + i_fAxis_Z + ")";
	iRet += testAndReport(i_bSilent_Pass,sStr,qA,Math.cos(i_fAngle * dRadDeg * 0.5),i_fAxis_X * Math.sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Y * Math.sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Z * Math.sin(i_fAngle * dRadDeg * 0.5));

	qA.loadRotationRadians(i_fAngle * dRadDeg,i_fAxis_X,i_fAxis_Y,i_fAxis_Z);
//	double dDegRad = 180.0 / acos(-1.0);
	iRet += testAndReport(i_bSilent_Pass,sStr,qA,Math.cos(i_fAngle * dRadDeg * 0.5),i_fAxis_X * Math.sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Y * Math.sin(i_fAngle * dRadDeg * 0.5),i_fAxis_Z * Math.sin(i_fAngle * dRadDeg * 0.5));
	
	return iRet;
}

var iFailures = 0;
var bSilent_Pass = true;
var qA = new Quaternion();
var qW = new Quaternion(1,0,0,0);
var qX = new Quaternion(0,1,0,0);
var qY = new Quaternion(0,0,1,0);
var qZ = new Quaternion(0,0,0,1);

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

iFailures += testAndReport(bSilent_Pass,"-W",qW.negate(),-1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"-X",qX.negate(),0,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"-Y",qY.negate(),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"-Z",qZ.negate(),0,0,0,-1);

iFailures += testAndReport(bSilent_Pass,"W + W",qW.add(qW),2,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X + X",qX.add(qX),0,2,0,0);
iFailures += testAndReport(bSilent_Pass,"Y + Y",qY.add(qY),0,0,2,0);
iFailures += testAndReport(bSilent_Pass,"Z + Z",qZ.add(qZ),0,0,0,2);
iFailures += testAndReport(bSilent_Pass,"W + X",qW.add(qX),1,1,0,0);
iFailures += testAndReport(bSilent_Pass,"W + Y",qW.add(qY),1,0,1,0);
iFailures += testAndReport(bSilent_Pass,"W + Z",qW.add(qZ),1,0,0,1);
iFailures += testAndReport(bSilent_Pass,"X + W",qX.add(qW),1,1,0,0);
iFailures += testAndReport(bSilent_Pass,"X + Y",qX.add(qY),0,1,1,0);
iFailures += testAndReport(bSilent_Pass,"X + Z",qX.add(qZ),0,1,0,1);
iFailures += testAndReport(bSilent_Pass,"Y + W",qY.add(qW),1,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y + X",qY.add(qX),0,1,1,0);
iFailures += testAndReport(bSilent_Pass,"Y + Z",qY.add(qZ),0,0,1,1);
iFailures += testAndReport(bSilent_Pass,"Z + W",qZ.add(qW),1,0,0,1);
iFailures += testAndReport(bSilent_Pass,"Z + X",qZ.add(qX),0,1,0,1);
iFailures += testAndReport(bSilent_Pass,"Z + Y",qZ.add(qY),0,0,1,1);

iFailures += testAndReport(bSilent_Pass,"W - W",qW.subtract(qW),0,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X - X",qX.subtract(qX),0,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Y - Y",qY.subtract(qY),0,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Z - Z",qZ.subtract(qZ),0,0,0,0);
iFailures += testAndReport(bSilent_Pass,"W - X",qW.subtract(qX),1,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"W - Y",qW.subtract(qY),1,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"W - Z",qW.subtract(qZ),1,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"X - W",qX.subtract(qW),-1,1,0,0);
iFailures += testAndReport(bSilent_Pass,"X - Y",qX.subtract(qY),0,1,-1,0);
iFailures += testAndReport(bSilent_Pass,"X - Z",qX.subtract(qZ),0,1,0,-1);
iFailures += testAndReport(bSilent_Pass,"Y - W",qY.subtract(qW),-1,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y - X",qY.subtract(qX),0,-1,1,0);
iFailures += testAndReport(bSilent_Pass,"Y - Z",qY.subtract(qZ),0,0,1,-1);
iFailures += testAndReport(bSilent_Pass,"Z - W",qZ.subtract(qW),-1,0,0,1);
iFailures += testAndReport(bSilent_Pass,"Z - X",qZ.subtract(qX),0,-1,0,1);
iFailures += testAndReport(bSilent_Pass,"Z - Y",qZ.subtract(qY),0,0,-1,1);

iFailures += testAndReport(bSilent_Pass,"W * 2",qW.multiply(2.0),2,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X * 2",qX.multiply(2.0),0,2,0,0);
iFailures += testAndReport(bSilent_Pass,"Y * 2",qY.multiply(2.0),0,0,2,0);
iFailures += testAndReport(bSilent_Pass,"Z * 2",qZ.multiply(2.0),0,0,0,2);

iFailures += testAndReport(bSilent_Pass,"W / 2",qW.divide(2.0),0.5,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X / 2",qX.divide(2.0),0,0.5,0,0);
iFailures += testAndReport(bSilent_Pass,"Y / 2",qY.divide(2.0),0,0,0.5,0);
iFailures += testAndReport(bSilent_Pass,"Z / 2",qZ.divide(2.0),0,0,0,0.5);

iFailures += testAndReport(bSilent_Pass,"W * W",qW.multiply(qW),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X * X",qX.multiply(qX),-1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Y * Y",qY.multiply(qY),-1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Z * Z",qZ.multiply(qZ),-1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"W * X",qW.multiply(qX),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"W * Y",qW.multiply(qY),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"W * Z",qW.multiply(qZ),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"X * W",qX.multiply(qW),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"X * Y",qX.multiply(qY),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"X * Z",qX.multiply(qZ),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"Y * W",qY.multiply(qW),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y * X",qY.multiply(qX),0,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"Y * Z",qY.multiply(qZ),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"Z * W",qZ.multiply(qW),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"Z * X",qZ.multiply(qX),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Z * Y",qZ.multiply(qY),0,-1,0,0);

iFailures += testAndReport(bSilent_Pass,"W / W",qW.divide(qW),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X / X",qX.divide(qX),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Y / Y",qY.divide(qY),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Z / Z",qZ.divide(qZ),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"W / X",qW.divide(qX),0,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"W / Y",qW.divide(qY),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"W / Z",qW.divide(qZ),0,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"X / W",qX.divide(qW),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"X / Y",qX.divide(qY),0,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"X / Z",qX.divide(qZ),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y / W",qY.divide(qW),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y / X",qY.divide(qX),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"Y / Z",qY.divide(qZ),0,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"Z / W",qZ.divide(qW),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"Z / X",qZ.divide(qX),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"Z / Y",qZ.divide(qY),0,1,0,0);

iFailures += testAndReport(bSilent_Pass,"W * W / W",qW.multiply(qW.divide(qW)),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"W * X / W",qW.multiply(qX.divide(qW)),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"W * Y / W",qW.multiply(qY.divide(qW)),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"W * Z / W",qW.multiply(qZ.divide(qW)),0,0,0,1);
iFailures += testAndReport(bSilent_Pass,"X * W / X",qX.multiply(qW.divide(qX)),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"X * X / X",qX.multiply(qX.divide(qX)),0,1,0,0);
iFailures += testAndReport(bSilent_Pass,"X * Y / X",qX.multiply(qY.divide(qX)),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"X * Z / X",qX.multiply(qZ.divide(qX)),0,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"Y * W / Y",qY.multiply(qW.divide(qY)),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Y * X / Y",qY.multiply(qX.divide(qY)),0,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"Y * Y / Y",qY.multiply(qY.divide(qY)),0,0,1,0);
iFailures += testAndReport(bSilent_Pass,"Y * Z / Y",qY.multiply(qZ.divide(qY)),0,0,0,-1);
iFailures += testAndReport(bSilent_Pass,"Z * W / Z",qZ.multiply(qW.divide(qZ)),1,0,0,0);
iFailures += testAndReport(bSilent_Pass,"Z * X / Z",qZ.multiply(qX.divide(qZ)),0,-1,0,0);
iFailures += testAndReport(bSilent_Pass,"Z * Y / Z",qZ.multiply(qY.divide(qZ)),0,0,-1,0);
iFailures += testAndReport(bSilent_Pass,"Z * Z / Z",qZ.multiply(qZ.divide(qZ)),0,0,0,1);


var fAngle;
for (fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
	iFailures += testRotation(bSilent_Pass,fAngle,0,0,0);

for (fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
	iFailures += testRotation(bSilent_Pass,fAngle,1,0,0);

for (fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
	iFailures += testRotation(bSilent_Pass,fAngle,0,1,0);

for (fAngle = 0.0; fAngle < 180.0; fAngle += 15.0)
	iFailures += testRotation(bSilent_Pass,fAngle,0,0,1);

console.log("PASS: " + (197 - iFailures) + " FAIL: " + iFailures);	

