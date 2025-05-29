/*
Vec3f_S16_Z::Get(Vec4f &)	__text	00092BCC	00000057	00000004	00000008	R	.	.	.	.	.	B	.	.
Vec3f_S16_Z::Get(Vec3f_S16_Z const&,Vec3f_S16_Z const&,Vec3f_S16_Z const&,Vec4f &,Vec4f &,Vec4f &)	__text	00092C24	000000F9	00000010	00000018	R	.	.	.	.	.	B	.	.
SolveQuadric(double *,double *)	__text	00092D1E	00000094	00000004	00000008	R	.	.	.	.	.	B	T	.
sub_92DB4	__text	00092DB4	000001ED	0000008C		R	.	.	.	.	.	B	.	.
cullPoints(int,float *,int,int,int *)	__text	00092FA4	0000026A	000000AC	00000014	R	.	.	.	.	.	B	T	.
dLineClosestApproach(float const*,float const*,float const*,float const*,float *,float *)	__text	0009320E	00000112	0000001C	00000018	R	.	.	.	.	.	B	T	.
PointVsBox(Float3 const&,Box_Z const&)	__text	00093320	000000CF	00000014	00000008	R	.	.	.	.	.	B	.	.
SegmentVsBoxOld(Segment_Z const&,Box_Z const&,CollisionReport_Z &)	__text	000933F2	000002C1	0000002C	0000000C	R	.	.	.	.	.	B	.	.
SphereVsCapsule(Sphere_Z const&,Capsule_Z const&)	__text	000936B6	00000160	0000001C	00000008	R	.	.	.	.	.	B	.	.
SegmentVsBoxNew(Segment_Z const&,Box_Z const&,CollisionReport_Z &)	__text	00093816	00000327	0000007C	0000000C	R	.	.	.	.	.	B	.	.
SegmentVsBox(Segment_Z const&,Box_Z const&,CollisionReport_Z &)	__text	00093B3E	00000024	0000001C	0000000C	R	.	.	.	.	.	B	.	.
IsPointInNPoly(Vec2f const&,Vec2f const*,long)	__text	00093B62	0000017E	00000038	0000000C	R	.	.	.	.	.	B	.	.
SphereVsCone(Sphere_Z const&,Cone_Z const&)	__text	00093CE0	00000183	00000018	00000008	R	.	.	.	.	.	B	.	.
CylinderSphereVsCapsule(Sphere_Z const&,Capsule_Z const&)	__text	00093E64	00000193	00000044	00000008	R	.	.	.	.	.	B	.	.
CylinderSphereVsSegment(Sphere_Z const&,Segment_Z const&)	__text	00093FF8	000000DE	00000010	00000008	R	.	.	.	.	.	B	.	.
sub_940D6	__text	000940D6	000001BC	0000002C	00000010	R	.	.	.	.	.	B	.	.
SolveCubic(double *,double *)	__text	00094292	000003F4	0000009C	00000008	R	.	.	.	.	.	B	T	.
SolveQuartic(double *,double *)	__text	00094686	00000314	000000BC	00000008	R	.	.	.	.	.	B	T	.
inttor(Float3,Float3,float,float,float,int *,double *)	__text	0009499A	000001A8	0000006C	0000002C	R	.	.	.	.	.	B	T	.
SphereVsSphere(Sphere_Z const&,Sphere_Z const&,CollisionReport_Z &)	__text	00094B42	0000013F	0000007C	0000000C	R	.	.	.	.	.	B	.	.
MovingSphereVsQuad(Capsule_Z const&,Vec4f const&,Vec4f const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	00094C82	000006FE	0000008C	00000018	R	.	.	.	.	.	B	.	.
SphereVsBox(Sphere_Z const&,Box_Z const&,CollisionReport_Z &)	__text	00095380	000003B2	000000CC	0000000C	R	.	.	.	.	.	B	.	.
FastBoxVsFastBox3(FastBoxVsCol *)	__text	00095732	00001E76	0000035C	00000004	R	.	.	.	.	.	B	T	.
FastBoxVsFastBox(FastBoxVsCol *)	__text	000975A8	00000009	00000004		R	.	.	.	.	.	B	.	.
CompSphereVsFastTriPen(Sphere_Z const&,CollisionFastTriangle_Z const&,PENETRATION &,bool,float)	__text	000975B4	0000065D	0000007C	0000000D	R	.	.	.	.	.	B	.	.
CollisionFastTriangle_Z::ComputeOptims(void)	__text	00097C14	00000586	0000006C	00000004	R	.	.	.	.	.	B	T	.
FastBoxVsTriangleNew(FastBoxVsTriCol *)	__text	0009819A	00001FB0	000004DC	00000004	R	.	.	.	.	.	B	.	.
FastBoxVsTriangle(FastBoxVsTriCol *)	__text	0009A14A	00000009	00000004		R	.	.	.	.	.	B	.	.
SegmentVsInfinySeg(Segment_Z const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009A154	00000542	0000014C	00000010	R	.	.	.	.	.	B	.	.
MovingSphereVsVertex(Capsule_Z const&,Vec4f const&,CollisionReport_Z &)	__text	0009A696	00000212	0000004C	0000000C	R	.	.	.	.	.	B	.	.
MovingSphereVsSphere(Capsule_Z const&,Sphere_Z const&,CollisionReport_Z &)	__text	0009A8A8	00000274	0000005C	0000000C	R	.	.	.	.	.	B	.	.
SegmentVsSphere(Segment_Z const&,Sphere_Z const&,CollisionReport_Z &)	__text	0009AB1C	000001E0	0000008C	0000000C	R	.	.	.	.	.	B	.	.
SegmentVsTri(Segment_Z const&,Vec4f const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009ACFC	00000517	000000FC	00000014	R	.	.	.	.	.	B	.	.
SegmentVsTri(Segment_Z const&,Vec3f_S16_Z const&,Vec3f_S16_Z const&,Vec3f_S16_Z const&,CollisionReport_Z &)	__text	0009B214	00000060	0000006C	00000014	R	.	.	.	.	.	B	.	.
MovingSphereVsTri(Capsule_Z const&,Vec4f const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009B274	00000881	000001CC	00000014	R	.	.	.	.	.	B	.	.
MovingSphereVsTri(Capsule_Z const&,Vec3f_S16_Z const&,Vec3f_S16_Z const&,Vec3f_S16_Z const&,CollisionReport_Z &)	__text	0009BAF6	00000068	0000006C	00000014	R	.	.	.	.	.	B	.	.
MovingSphereVsFaceInfinyUp(Capsule_Z const&,Vec4f &,Vec4f &,Vec4f const&,CollisionReport_Z &)	__text	0009BB5E	0000085B	000001AC	00000014	R	.	.	.	.	.	B	.	.
SphereVsEdge(Sphere_Z const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009C3BA	000004E0	000001AC	00000010	R	.	.	.	.	.	B	.	.
SphereVsCylindre(Sphere_Z const&,Cylindre_Z const&,CollisionReport_Z &)	__text	0009C89C	0000064C	000000DC	0000000C	R	.	.	.	.	.	B	.	.
MovingSphereVsEdgeInfinyUp(Capsule_Z const&,Segment_Z const&,CollisionReport_Z &)	__text	0009CEE8	000004E3	000000BC	0000000C	R	.	.	.	.	.	B	.	.
MovingSphereVsDirEdge(Capsule_Z const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009D3CC	0000059B	000000FC	00000010	R	.	.	.	.	.	B	.	.
MovingSphereVsEdge(Capsule_Z const&,Vec4f const&,Vec4f const&,CollisionReport_Z &)	__text	0009D968	0000053B	000000EC	00000010	R	.	.	.	.	.	B	.	.
MovingSphereVsBox(Capsule_Z const&,Box_Z const&,CollisionReport_Z &)	__text	0009DEA4	0000020F	0000011C	0000000C	R	.	.	.	.	.	B	.	.
MovingSphereVsCylindre(Capsule_Z const&,Cylindre_Z const&,CollisionReport_Z &)	__text	0009E0B4	000014B3	0000031C	0000000C	R	.	.	.	.	.	B	.	.
SegmentVsCylindre(Segment_Z const&,Cylindre_Z const&,CollisionReport_Z &)	__text	0009F568	00000826	000000EC	0000000C	R	.	.	.	.	.	B	.	.
*/

/**
 * I bet all of these were stolen from the web or from books and none of these functions are Asobo programmers' own work.
 */

#include <CollisionTool_Z.h>
#include <Types_Z.h>
#include <Math_Z.h>
#include <math.h>
#include "odemath.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* epsilon surrounding for near zero values */

#define EQN_EPS 1e-9
#define IsZero(x) ((x) > -EQN_EPS && (x) < EQN_EPS)

#define cbrt(x) ((x) > 0.0 ? pow((float)(x), 1.0f / 3.0f) : ((x) < 0.0 ? -pow((float)-(x), 1.0f / 3.0f) : 0.0))

int SolveQuadric(double *c, double *s)
{
	double p, q, D;

	/* normal form: x^2 + px + q = 0 */

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];

	D = p * p - q;

	if (IsZero(D))
	{
		s[0] = -p;
		return 1;
	}
	else if (D < 0)
	{
		return 0;
	}
	else /* if (D > 0) */
	{
		double sqrt_D = sqrt(D);

		s[0] = sqrt_D - p;
		s[1] = -sqrt_D - p;
		return 2;
	}
}

int SolveCubic(double *c, double *s)
{
	int i, num;
	double sub;
	double A, B, C;
	double sq_A, p, q;
	double cb_p, D;

	/* normal form: x^3 + Ax^2 + Bx + C = 0 */

	A = c[2] / c[3];
	B = c[1] / c[3];
	C = c[0] / c[3];

	/*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

	sq_A = A * A;
	p = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
	q = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

	/* use Cardano's formula */

	cb_p = p * p * p;
	D = q * q + cb_p;

	if (IsZero(D))
	{
		if (IsZero(q)) /* one triple solution */
		{
			s[0] = 0;
			num = 1;
		}
		else /* one single and one double solution */
		{
			double u = cbrt(-q);
			s[0] = 2 * u;
			s[1] = -u;
			num = 2;
		}
	}
	else if (D < 0) /* Casus irreducibilis: three real solutions */
	{
		double phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
		double t = 2 * sqrt(-p);

		s[0] = t * cosf(phi);
		s[1] = -t * cosf(phi + M_PI / 3);
		s[2] = -t * cosf(phi - M_PI / 3);
		num = 3;
	}
	else /* one real solution */
	{
		double sqrt_D = sqrt(D);
		double u = cbrt(sqrt_D - q);
		double v = -cbrt(sqrt_D + q);

		s[0] = u + v;
		num = 1;
	}

	/* resubstitute */

	sub = 1.0 / 3 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

int SolveQuartic(double *c, double *s)
{
	double coeffs[4];
	double z, u, v, sub;
	double A, B, C, D;
	double sq_A, p, q, r;
	int i, num;

	/* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	A = c[3] / c[4];
	B = c[2] / c[4];
	C = c[1] / c[4];
	D = c[0] / c[4];

	/*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

	sq_A = A * A;
	p = -3.0 / 8 * sq_A + B;
	q = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
	r = -3.0 / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;

	if (IsZero(r))
	{
		/* no absolute term: y(y^3 + py + q) = 0 */

		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;

		num = SolveCubic(coeffs, s);

		s[num++] = 0;
	}
	else
	{
		/* solve the resolvent cubic ... */

		coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2 * p;
		coeffs[3] = 1;

		(void)SolveCubic(coeffs, s);

		/* ... and take the one real solution ... */

		z = s[0];

		/* ... to build two quadric equations */

		u = z * z - r;
		v = 2 * z - p;

		if (IsZero(u))
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return 0;

		if (IsZero(v))
			v = 0;
		else if (v > 0)
			v = sqrt(v);
		else
			return 0;

		coeffs[0] = z - u;
		coeffs[1] = q < 0 ? -v : v;
		coeffs[2] = 1;

		num = SolveQuadric(coeffs, s);

		coeffs[0] = z + u;
		coeffs[1] = q < 0 ? v : -v;
		coeffs[2] = 1;

		num += SolveQuadric(coeffs, s + num);
	}

	/* resubstitute */

	sub = 1.0 / 4 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

int inttor(
	Float3 raybase, // Base of the intersection ray
	Float3 raycos,	// Direction cosines of the ray
	Float radius,	// Major radius of the torus
	Float rplane,	// Minor planer radius
	Float rnorm,	// Minor normal radius
	int *nhits,		// Number of intersections
	double rhits[4] // Intersection distances
)
{
	Float3 Base, Dcos;		   /* Transformed intersection ray	*/
	Float rho, a0, b0;		   /* Related constants		*/
	Float f, l, t, g, q, m, u; /* Ray dependent terms		*/
	double C[5];			   /* Quartic coefficients		*/

	*nhits = 0;

	/*	Transform the intersection ray					*/

	Base = raybase;
	Dcos = raycos;

	/*	Compute constants related to the torus.				*/

	rho = rplane * rplane / (rnorm * rnorm);
	a0 = 4.f * radius * radius;
	b0 = radius * radius - rplane * rplane;

	/*	Compute ray dependent terms.					*/

	f = 1.f - Dcos.y * Dcos.y;
	l = 2.f * (Base.x * Dcos.x + Base.z * Dcos.z);
	t = Base.x * Base.x + Base.z * Base.z;
	g = f + rho * Dcos.y * Dcos.y;
	q = a0 / (g * g);
	m = (l + 2.f * rho * Dcos.y * Base.y) / g;
	u = (t + rho * Base.y * Base.y + b0) / g;

	/*	Compute the coefficients of the quartic.			*/

	C[4] = 1.f;
	C[3] = 2.f * m;
	C[2] = m * m + 2.f * u - q * f;
	C[1] = 2.f * m * u - q * l;
	C[0] = u * u - q * t;

	/*	Use quartic root solver found in "Graphics Gems" by Jochen	*/
	/*	Schwarze.							*/
	*nhits = SolveQuartic(C, rhits);

	/*	SolveQuartic returns root pairs in reversed order.		*/
	m = Float(rhits[0]);
	u = Float(rhits[1]);
	rhits[0] = u;
	rhits[1] = m;
	m = Float(rhits[2]);
	u = Float(rhits[3]);
	rhits[2] = u;
	rhits[3] = m;

	return (*nhits != 0);
}

struct Sphere_Z
{
	Vec3f Center;
	float Radius;
};

struct CollisionReport_Z
{
	Vec4f m_vIntersection;		//+0x00
	Vec4f m_vNormal;			//+0x10
	int unk1;					//+0x20
	int unk2;					//+0x24
	float m_fCollisionDistance; //+0x28
};

// Confirmed to match on 2024-12-08T19:51:20Z
Bool SphereVsSphere(const Sphere_Z &Sph1, const Sphere_Z &Sph2, CollisionReport_Z &Result)
{
	/**
	 * This function took me a good few fucking hours to decompile
	 *  Do you know the difference between an implicit copy constructor and an explicitly declared one? Well, the implicit copy constructor for Vec4f in GCC 4.0 results in an extra copy right after the scalar multiplication as marked below.
	 *  Also Asobo is absolutely handling the happy path in the "else" branch, not in the "if" in the nested if-else.
	 */
	Vec3f Diff = Sph1.Center - Sph2.Center;
	Float RadSum = Sph1.Radius + Sph2.Radius, SqrNorm = Diff.GetNorm2();
	if (SqrNorm < RadSum * RadSum)
	{
		Float Norm = sqrt(SqrNorm);
		Float Dist = Norm - Sph2.Radius;

		if (Dist > Result.m_fCollisionDistance)
		{
			return FALSE;
		}
		else
		{
			Result.m_fCollisionDistance = Dist;
			Result.m_vNormal = Diff / Norm;
			Result.m_vIntersection = Sph2.Center + Result.m_vNormal * Sph2.Radius; // Right here after the multiplication!
			return TRUE;
		}
	}
	return FALSE;
}

struct Capsule_Z
{
	Vec3f Org;	  //+0x00
	Float Len;	  //+0x0C
	Vec3f Dir;	  //+0x10
	Float Radius; //+0x1C
};

/**
 * TODO: look over this function and see why the variables are in a different order;
 * 
 * A few things excluded:
 * - A common "return" tail function. That simply does not get inlined even with "inline" if it is only called in this function, and even with always_inline there are differences
 * - Negation. That doesn't count in this function. Or does it?
 * - Structure layout. That is fixed here.
 * - Constructors. Nope! No change at all.
 * - Constructing CollisionReport_Z and then copying it to "report". Just more code.
 *  
 * It's always something so damn obvious...
 * 
 * Update 2025-01-25T18:22:52Z: Well, it's not THAT obvious. Make sure to take out p1.xyz(), that Vec3f has a copy constructor AND the Vec3f subtract operator to not take a reference but a regular Vec3f. I am not convinced that this is what Asobo did but it is semantically identical to their solution. Now let's see how this broke the other functions...
 * 
 */
Bool MovingSphereVsQuad(const Capsule_Z &Cap, const Vec4f &p1, const Vec4f &p2, const Vec4f &p3, const Vec4f &p4,
						CollisionReport_Z &Report)
{
	/**
	 * This function is a strange cookie. Apparently Asobo decided here that the Vec4fs were no good, so they instead casted every Vec4f to a Vec3f and perform operations on those.
	 * Manual CSE vs Compiler CSE are two *****very***** different things and the programmer who wrote this subroutine clearly knew that. You can clearly see the manual CSE when it tries the edges of the quad themselves.
	 */

	// Calc plane equation
	Vec3f normal;
	normal.x = p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z);
	normal.y = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x);
	normal.z = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	Float Norm = normal.GetNorm();
	if (Norm <= Float_Eps)
		return FALSE;
	normal /= Norm;
	// Test If Exit Collision
	Float Ex = Cap.Dir * normal;
	if (Ex >= 0.f)
		return FALSE;
	// Test si la face est arriere
	Float3 p1xyz = p1.xyz();
	Float d = -(normal * p1xyz);
	Float Dp = normal * Cap.Org + d;
	if (Dp <= 0.f)
		return FALSE;
	if (Dp <= Cap.Radius)
	{
		Vec3f edge1 = p1xyz - Cap.Org;
		Vec3f edge2 = p2.xyz() - Cap.Org;
		if ((((edge1) ^ (edge2)) * normal) < -Float_Eps_Col)
			return FALSE;
		Vec3f edge3 = p3.xyz() - Cap.Org;
		if ((((edge2) ^ (edge3)) * normal) < -Float_Eps_Col)
			return FALSE;
		Vec3f edge4 = p4.xyz() - Cap.Org;
		if ((((edge3) ^ (edge4)) * normal) < -Float_Eps_Col)
			return FALSE;
		if ((((edge4) ^ (edge1)) * normal) < -Float_Eps_Col)
			return FALSE;

		Report.m_fCollisionDistance = 0.f;
		Report.m_vIntersection = Cap.Org;
		Report.m_vNormal = normal;
		return TRUE;
	}
	// Intersection avec le plan
	Float dist = -(Float)((Dp - Cap.Radius) / (normal * Cap.Dir));
	if (dist > Report.m_fCollisionDistance || dist < 0.f || dist > Cap.Len)
		return FALSE;
	Vec3f intersection = Cap.Dir * dist + Cap.Org;

	// Check si l'intersection est dans le triangle

	Vec3f edge1 = p1xyz - intersection;
	Vec3f edge2 = p2.xyz() - intersection;
	if ((((edge1) ^ (edge2)) * normal) < -Float_Eps_Col)
		return FALSE;
	Vec3f edge3 = p3.xyz() - intersection;
	if ((((edge2) ^ (edge3)) * normal) < -Float_Eps_Col)
		return FALSE;
	Vec3f edge4 = p4.xyz() - intersection;
	if ((((edge3) ^ (edge4)) * normal) < -Float_Eps_Col)
		return FALSE;
	if ((((edge4) ^ (edge1)) * normal) < -Float_Eps_Col)
		return FALSE;

	Report.m_fCollisionDistance = dist;
	Report.m_vIntersection = intersection;
	Report.m_vNormal = normal;
	return TRUE;
}


Float fBestDepth;
Vec4f vBestNormal;
int iBestAxis;

// The following few subroutines look vaguely similar to the ones found in ~2006 in OpenDynamicsEngine but there are some important changes in this version, notably the introduction of epsilons.

static Bool _cldTestEdge(Float fp0, Float fp1, Float fR,
						 const Float *vNormal, int iAxis)
{
	Float fMin, fMax;

	// calculate min and max interval values
	if (fp0 < fp1)
	{
		fMin = fp0;
		fMax = fp1;
	}
	else
	{
		fMin = fp1;
		fMax = fp0;
	}

	// check if we overlapp
	Float fDepthMin = fR - fMin;
	Float fDepthMax = fMax + fR;

	// ASOBO: Take the multiplication and see if that's close enough to zero. Saved some branches!
	if ((fDepthMin * fDepthMax) < 1e-10f)
	{
		// do nothing
		return FALSE;
	}

	// calculate normal's length
	// This pointer cast is dirty as hell, but it's what Asobo does here (or something close to it).
	Float fLength = Vec4_GetNorm(*(Vec4f *)(vNormal));

	// if long enough
	if (fLength > 1e-5f)
	{

		// normalize depth
		Float fOneOverLength = 1.0f / fLength;
		if (fDepthMin > fDepthMax)
		{
			fDepthMax *= fOneOverLength;

			// if lower depth than best found so far (favor face over edges)
			if (fDepthMax * 1.5f < fBestDepth)
			{
				fOneOverLength = -fOneOverLength;
				// remember current axis as best axis
				vBestNormal[0] = vNormal[0] * fOneOverLength;
				vBestNormal[1] = vNormal[1] * fOneOverLength;
				vBestNormal[2] = vNormal[2] * fOneOverLength;
				vBestNormal[3] = vNormal[3] * fOneOverLength;
				iBestAxis = iAxis;
				// dAASSERT(fDepth>=0);
				fBestDepth = fDepthMax;
			}
		}
		else
		{
			fDepthMin *= fOneOverLength;

			// if lower depth than best found so far (favor face over edges)
			if (fDepthMin * 1.5f < fBestDepth)
			{
				// remember current axis as best axis
				vBestNormal[0] = vNormal[0] * fOneOverLength;
				vBestNormal[1] = vNormal[1] * fOneOverLength;
				vBestNormal[2] = vNormal[2] * fOneOverLength;
				vBestNormal[3] = vNormal[3] * fOneOverLength;
				iBestAxis = iAxis;
				// dAASSERT(fDepth>=0);
				fBestDepth = fDepthMin;
			}
		}
	}

	return TRUE;
}

const float &MinRef(const float &a, const float &b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

const float &MaxRef(const float &a, const float &b)
{
	if (a < b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

/**
 * TODO: figure out the register spill and the mixed arguments in minimum selection
 */

// Test box axis as separating axis 
static Bool _cldTestFace(Float fp0, Float fp1, Float fp2, Float fR,
						 const Float *vNormal, int iAxis)
{
	Float fMin, fMax;

	// Find a minimum and maximum
	// Note that MaxRef and MinRef take and return references.
	fMin = MinRef(fp2, MinRef(fp0, fp1));
	fMax = MaxRef(fp2, MaxRef(fp0, fp1));

	Float fDepthMin = fR - fMin;
	Float fDepthMax = fMax + fR;

	// ASOBO: Take the multiplication and see if that's close enough to zero. Saved some branches!
	// if we dont't have overlapping interval
	if ((fDepthMin * fDepthMax) < 1e-10f)
	{
		// do nothing
		return FALSE;
	}

	if (fDepthMin > fDepthMax)
	{
		if (fDepthMax < fBestDepth)
		{
			// How the fuck does negating these numbers result in a stack allocation for me but not for Asobo???
			vBestNormal[0] = -vNormal[0];
			vBestNormal[1] = -vNormal[1];
			vBestNormal[2] = -vNormal[2];
			vBestNormal[3] = -vNormal[3];
			iBestAxis = iAxis;
			fBestDepth = fDepthMax;
		}
	}
	else
	{
		if (fDepthMin < fBestDepth)
		{
			vBestNormal[0] = vNormal[0];
			vBestNormal[1] = vNormal[1];
			vBestNormal[2] = vNormal[2];
			vBestNormal[3] = vNormal[3];
			iBestAxis = iAxis;
			fBestDepth = fDepthMin;
		}
	}

	return TRUE;
}

/**
 * TODO: Another piece of shit bites the dust... This one also has the negation register spill...
 */
void dLineClosestApproach(const Float *pa, const Float *ua,
						  const Float *pb, const Float *ub,
						  Float *alpha, Float *beta)
{
	Float p[3];
	p[0] = pb[0] - pa[0];
	p[1] = pb[1] - pa[1];
	p[2] = pb[2] - pa[2];
	Float uaub = ua[0] * ub[0] + ua[1] * ub[1] + ua[2] * ub[2];
	Float q1 = ua[0] * p[0] + ua[1] * p[1] + ua[2] * p[2];
	Float q2 = -(ub[0] * p[0] + ub[1] * p[1] + ub[2] * p[2]);
	Float d = 1 - uaub * uaub;
	if (d <= 0.0001f)
	{

		*alpha = 0;
		*beta = 0;
	}
	else
	{
		d = 1.f / d;
		*alpha = (q1 + uaub * q2) * d;
		*beta = (uaub * q1 + q2) * d;
	}
}

/**
 * Oh thank god 
 * Nothing to see here! Moving on...
 */

// given n points in the plane (array p, of size 2*n), generate m points that
// best represent the whole set. the definition of 'best' here is not
// predetermined - the idea is to select points that give good box-box
// collision detection behavior. the chosen point indexes are returned in the
// array iret (of size m). 'i0' is always the first entry in the array.
// n must be in the range [1..8]. m must be in the range [1..n]. i0 must be
// in the range [0..n-1].

void cullPoints(int n, Float p[], int m, int i0, int iret[])
{
	// compute the centroid of the polygon in cx,cy
	int i, j;
	Float a, cx, cy, q;
	if (n == 1)
	{
		cx = p[0];
		cy = p[1];
	}
	else if (n == 2)
	{
		cx = Float(0.5) * (p[0] + p[2]);
		cy = Float(0.5) * (p[1] + p[3]);
	}
	else
	{
		a = 0;
		cx = 0;
		cy = 0;
		for (i = 0; i < (n - 1); i++)
		{
			q = p[i * 2] * p[i * 2 + 3] - p[i * 2 + 2] * p[i * 2 + 1];
			a += q;
			cx += q * (p[i * 2] + p[i * 2 + 2]);
			cy += q * (p[i * 2 + 1] + p[i * 2 + 3]);
		}
		q = p[n * 2 - 2] * p[1] - p[0] * p[n * 2 - 1];
		a = 1.f / (Float(3.0) * (a + q));
		cx = a * (cx + q * (p[n * 2 - 2] + p[0]));
		cy = a * (cy + q * (p[n * 2 - 1] + p[1]));
	}

	// compute the angle of each point w.r.t. the centroid
	Float A[8];
	for (i = 0; i < n; i++)
		A[i] = Atan2(p[i * 2 + 1] - cy, p[i * 2] - cx);

	// search for points that have angles closest to A[i0] + i*(2*pi/m).
	int avail[8];
	for (i = 0; i < n; i++)
		avail[i] = 1;
	avail[i0] = 0;
	iret[0] = i0;
	iret++;
	for (j = 1; j < m; j++)
	{
		a = Float(j) * (2 * M_PI / m) + A[i0];
		if (a > M_PI)
			a -= Float(2 * M_PI);
		Float maxdiff = 1e9, diff;

		for (i = 0; i < n; i++)
		{
			if (avail[i])
			{
				diff = Abs(A[i] - a);
				if (diff > M_PI)
					diff = 2 * M_PI - diff;
				if (diff < maxdiff)
				{
					maxdiff = diff;
					*iret = i;
				}
			}
		}

		avail[*iret] = 0;
		iret++;
	}
}

struct Box_Z{
	//Standard issue translation-rotation-scaling matrix...
	Mat4x4 transform;
};

struct FastBox_Z{
	Mat4x4 rotMat; //+0x00
	Mat4x4 rotMatAgain; //+0x40
	Vec4f translation; //+0x80
	Vec4f scale; //+0x90
	Float radius; //+0xA0 The radius of the sphere surrounding this box.
};

struct FastBoxVsCol{
	//Has some FastBox_Z* pointers...


	FastBox_Z* unk1; //+0x10
	FastBox_Z* unk2; //+0x14
};



int FastBoxVsFastBox3(FastBoxVsCol* col)
{
  /*const Float fudge_factor = Float(1.05);
  Float* p,pp,normalC;
  const Float *normalR = 0;
  Float A[3],B[3],R11,R12,R13,R21,R22,R23,R31,R32,R33,
    Q11,Q12,Q13,Q21,Q22,Q23,Q31,Q32,Q33,s,s2,l,expr1_val;
  int i,j,invert_normal,code;

  // get vector from centers of box 1 to box 2, relative to box 1
  p[0] = p2[0] - p1[0];
  p[1] = p2[1] - p1[1];
  p[2] = p2[2] - p1[2];
  dMULTIPLY1_331 (pp,R1,p);		// get pp = p relative to body 1

  // get side lengths / 2
  A[0] = side1[0]*Float(0.5);
  A[1] = side1[1]*Float(0.5);
  A[2] = side1[2]*Float(0.5);
  B[0] = side2[0]*Float(0.5);
  B[1] = side2[1]*Float(0.5);
  B[2] = side2[2]*Float(0.5);

  // Rij is R1'*R2, i.e. the relative rotation between R1 and R2
  R11 = dDOT44(R1+0,R2+0); R12 = dDOT44(R1+0,R2+1); R13 = dDOT44(R1+0,R2+2);
  R21 = dDOT44(R1+1,R2+0); R22 = dDOT44(R1+1,R2+1); R23 = dDOT44(R1+1,R2+2);
  R31 = dDOT44(R1+2,R2+0); R32 = dDOT44(R1+2,R2+1); R33 = dDOT44(R1+2,R2+2);

  Q11 = dFabs(R11); Q12 = dFabs(R12); Q13 = dFabs(R13);
  Q21 = dFabs(R21); Q22 = dFabs(R22); Q23 = dFabs(R23);
  Q31 = dFabs(R31); Q32 = dFabs(R32); Q33 = dFabs(R33);*/

  // for all 15 possible separating axes:
  //   * see if the axis separates the boxes. if so, return 0.
  //   * find the depth of the penetration along the separating axis (s2)
  //   * if this is the largest depth so far, record it.
  // the normal vector will be set to the separating axis with the smallest
  // depth. note: normalR is set to point to a column of R1 or R2 if that is
  // the smallest depth normal so far. otherwise normalR is 0 and normalC is
  // set to a vector relative to body 1. invert_normal is 1 if the sign of
  // the normal should be flipped.

  /*do {
#define TST(expr1,expr2,norm,cc) \
    expr1_val = (expr1); \
    s2 = Abs(expr1_val) - (expr2); \
    if (s2 > 0) return 0; \
    if (s2 > s) { \
      s = s2; \
      normalR = norm; \
      invert_normal = ((expr1_val) < 0); \
      code = (cc); \
	  if (flags & CONTACTS_UNIMPORTANT) break; \
	}

    s = -dInfinity;
    invert_normal = 0;
    code = 0;

    // separating axis = u1,u2,u3
    TST (pp[0],(A[0] + B[0]*Q11 + B[1]*Q12 + B[2]*Q13),R1+0,1);
    TST (pp[1],(A[1] + B[0]*Q21 + B[1]*Q22 + B[2]*Q23),R1+1,2);
    TST (pp[2],(A[2] + B[0]*Q31 + B[1]*Q32 + B[2]*Q33),R1+2,3);

    // separating axis = v1,v2,v3
    TST (dDOT41(R2+0,p),(A[0]*Q11 + A[1]*Q21 + A[2]*Q31 + B[0]),R2+0,4);
    TST (dDOT41(R2+1,p),(A[0]*Q12 + A[1]*Q22 + A[2]*Q32 + B[1]),R2+1,5);
    TST (dDOT41(R2+2,p),(A[0]*Q13 + A[1]*Q23 + A[2]*Q33 + B[2]),R2+2,6);

    // note: cross product axes need to be scaled when s is computed.
    // normal (n1,n2,n3) is relative to box 1.
#undef TST
#define TST(expr1,expr2,n1,n2,n3,cc) \
    expr1_val = (expr1); \
    s2 = Abs(expr1_val) - (expr2); \
    if (s2 > 0.001f) return 0; \
    l = Sqrt ((n1)*(n1) + (n2)*(n2) + (n3)*(n3)); \
    if (l > 0) { \
      s2 /= l; \
      if (s2*fudge_factor > s) { \
        s = s2; \
        normalR = 0; \
        normalC[0] = (n1)/l; normalC[1] = (n2)/l; normalC[2] = (n3)/l; \
        invert_normal = ((expr1_val) < 0); \
        code = (cc); \
        if (flags & CONTACTS_UNIMPORTANT) break; \
	  } \
	}

    // separating axis = u1 x (v1,v2,v3)
    TST(pp[2]*R21-pp[1]*R31,(A[1]*Q31+A[2]*Q21+B[1]*Q13+B[2]*Q12),0,-R31,R21,7);
    TST(pp[2]*R22-pp[1]*R32,(A[1]*Q32+A[2]*Q22+B[0]*Q13+B[2]*Q11),0,-R32,R22,8);
    TST(pp[2]*R23-pp[1]*R33,(A[1]*Q33+A[2]*Q23+B[0]*Q12+B[1]*Q11),0,-R33,R23,9);

    // separating axis = u2 x (v1,v2,v3)
    TST(pp[0]*R31-pp[2]*R11,(A[0]*Q31+A[2]*Q11+B[1]*Q23+B[2]*Q22),R31,0,-R11,10);
    TST(pp[0]*R32-pp[2]*R12,(A[0]*Q32+A[2]*Q12+B[0]*Q23+B[2]*Q21),R32,0,-R12,11);
    TST(pp[0]*R33-pp[2]*R13,(A[0]*Q33+A[2]*Q13+B[0]*Q22+B[1]*Q21),R33,0,-R13,12);

    // separating axis = u3 x (v1,v2,v3)
    TST(pp[1]*R11-pp[0]*R21,(A[0]*Q21+A[1]*Q11+B[1]*Q33+B[2]*Q32),-R21,R11,0,13);
    TST(pp[1]*R12-pp[0]*R22,(A[0]*Q22+A[1]*Q12+B[0]*Q33+B[2]*Q31),-R22,R12,0,14);
    TST(pp[1]*R13-pp[0]*R23,(A[0]*Q23+A[1]*Q13+B[0]*Q32+B[1]*Q31),-R23,R13,0,15);
#undef TST
  } while (0);

  if (!code) return 0;

  // if we get to this point, the boxes interpenetrate. compute the normal
  // in global coordinates.
  if (normalR) {
    normal[0] = normalR[0];
    normal[1] = normalR[4];
    normal[2] = normalR[8];
  }
  else {
    dMULTIPLY0_331 (normal,R1,normalC);
  }
  if (invert_normal) {
    normal[0] = -normal[0];
    normal[1] = -normal[1];
    normal[2] = -normal[2];
  }
  *depth = -s;

  // compute contact point(s)

  if (code > 6) {
    // an edge from box 1 touches an edge from box 2.
    // find a point pa on the intersecting edge of box 1
    Float* pa;
    Float sign;
    for (i=0; i<3; i++) pa[i] = p1[i];
    for (j=0; j<3; j++) {
      sign = (dDOT14(normal,R1+j) > 0) ? Float(1.0) : Float(-1.0);
      for (i=0; i<3; i++) pa[i] += sign * A[j] * R1[i*4+j];
    }

    // find a point pb on the intersecting edge of box 2
    Float* pb;
    for (i=0; i<3; i++) pb[i] = p2[i];
    for (j=0; j<3; j++) {
      sign = (dDOT14(normal,R2+j) > 0) ? Float(-1.0) : Float(1.0);
      for (i=0; i<3; i++) pb[i] += sign * B[j] * R2[i*4+j];
    }

    Float alpha,beta;
    Float* ua,ub;
    for (i=0; i<3; i++) ua[i] = R1[((code)-7)/3 + i*4];
    for (i=0; i<3; i++) ub[i] = R2[((code)-7)%3 + i*4];

    dLineClosestApproach (pa,ua,pb,ub,&alpha,&beta);
    for (i=0; i<3; i++) pa[i] += ua[i]*alpha;
    for (i=0; i<3; i++) pb[i] += ub[i]*beta;

    for (i=0; i<3; i++) contact[0].pos[i] = Float(0.5)*(pa[i]+pb[i]);
    contact[0].depth = *depth;
    *return_code = code;
    return 1;
  }

  // okay, we have a face-something intersection (because the separating
  // axis is perpendicular to a face). define face 'a' to be the reference
  // face (i.e. the normal vector is perpendicular to this) and face 'b' to be
  // the incident face (the closest face of the other box).

  const Float *Ra,*Rb,*pa,*pb,*Sa,*Sb;
  if (code <= 3) {
    Ra = R1;
    Rb = R2;
    pa = p1;
    pb = p2;
    Sa = A;
    Sb = B;
  }
  else {
    Ra = R2;
    Rb = R1;
    pa = p2;
    pb = p1;
    Sa = B;
    Sb = A;
  }

  // nr = normal vector of reference face dotted with axes of incident box.
  // anr = absolute values of nr.
  Float* normal2,nr,anr;
  if (code <= 3) {
    normal2[0] = normal[0];
    normal2[1] = normal[1];
    normal2[2] = normal[2];
  }
  else {
    normal2[0] = -normal[0];
    normal2[1] = -normal[1];
    normal2[2] = -normal[2];
  }
  dMULTIPLY1_331 (nr,Rb,normal2);
  anr[0] = dFabs (nr[0]);
  anr[1] = dFabs (nr[1]);
  anr[2] = dFabs (nr[2]);

  // find the largest compontent of anr: this corresponds to the normal
  // for the indident face. the other axis numbers of the indicent face
  // are stored in a1,a2.
  int lanr,a1,a2;
  if (anr[1] > anr[0]) {
    if (anr[1] > anr[2]) {
      a1 = 0;
      lanr = 1;
      a2 = 2;
    }
    else {
      a1 = 0;
      a2 = 1;
      lanr = 2;
    }
  }
  else {
    if (anr[0] > anr[2]) {
      lanr = 0;
      a1 = 1;
      a2 = 2;
    }
    else {
      a1 = 0;
      a2 = 1;
      lanr = 2;
    }
  }

  // compute center point of incident face, in reference-face coordinates
  Float* center;
  if (nr[lanr] < 0) {
    for (i=0; i<3; i++) center[i] = pb[i] - pa[i] + Sb[lanr] * Rb[i*4+lanr];
  }
  else {
    for (i=0; i<3; i++) center[i] = pb[i] - pa[i] - Sb[lanr] * Rb[i*4+lanr];
  }

  // find the normal and non-normal axis numbers of the reference box
  int codeN,code1,code2;
  if (code <= 3) codeN = code-1; else codeN = code-4;
  if (codeN==0) {
    code1 = 1;
    code2 = 2;
  }
  else if (codeN==1) {
    code1 = 0;
    code2 = 2;
  }
  else {
    code1 = 0;
    code2 = 1;
  }

  // find the four corners of the incident face, in reference-face coordinates
  Float quad[8];	// 2D coordinate of incident face (x,y pairs)
  Float c1,c2,m11,m12,m21,m22;
  c1 = dDOT14 (center,Ra+code1);
  c2 = dDOT14 (center,Ra+code2);
  // optimize this? - we have already computed this data above, but it is not
  // stored in an easy-to-index format. for now it's quicker just to recompute
  // the four dot products.
  m11 = dDOT44 (Ra+code1,Rb+a1);
  m12 = dDOT44 (Ra+code1,Rb+a2);
  m21 = dDOT44 (Ra+code2,Rb+a1);
  m22 = dDOT44 (Ra+code2,Rb+a2);
  {
    Float k1 = m11*Sb[a1];
    Float k2 = m21*Sb[a1];
    Float k3 = m12*Sb[a2];
    Float k4 = m22*Sb[a2];
    quad[0] = c1 - k1 - k3;
    quad[1] = c2 - k2 - k4;
    quad[2] = c1 - k1 + k3;
    quad[3] = c2 - k2 + k4;
    quad[4] = c1 + k1 + k3;
    quad[5] = c2 + k2 + k4;
    quad[6] = c1 + k1 - k3;
    quad[7] = c2 + k2 - k4;
  }

  // find the size of the reference face
  Float rect[2];
  rect[0] = Sa[code1];
  rect[1] = Sa[code2];

  // intersect the incident and reference faces
  Float ret[16];
  int n = intersectRectQuad (rect,quad,ret);
  if (n < 1) return 0;		// this should never happen

  // convert the intersection points into reference-face coordinates,
  // and compute the contact position and depth for each point. only keep
  // those points that have a positive (penetrating) depth. delete points in
  // the 'ret' array as necessary so that 'point' and 'ret' correspond.
  Float point[3*8];		// penetrating contact points
  Float dep[8];			// depths for those points
  Float det1 = dRecip(m11*m22 - m12*m21);
  m11 *= det1;
  m12 *= det1;
  m21 *= det1;
  m22 *= det1;
  int cnum = 0;			// number of penetrating contact points found
  for (j=0; j < n; j++) {
    Float k1 =  m22*(ret[j*2]-c1) - m12*(ret[j*2+1]-c2);
    Float k2 = -m21*(ret[j*2]-c1) + m11*(ret[j*2+1]-c2);
    for (i=0; i<3; i++) point[cnum*3+i] =
			  center[i] + k1*Rb[i*4+a1] + k2*Rb[i*4+a2];
    dep[cnum] = Sa[codeN] - dDOT(normal2,point+cnum*3);
    if (dep[cnum] >= 0) {
      ret[cnum*2] = ret[j*2];
      ret[cnum*2+1] = ret[j*2+1];
      cnum++;
	  if ((cnum | CONTACTS_UNIMPORTANT) == (flags & (NUMC_MASK | CONTACTS_UNIMPORTANT))) {
		  break;
	  }
    }
  }
  if (cnum < 1) { 
	  return 0;	// this should not happen, yet does at times (demo_plane2d single precision).
  }

  // we can't generate more contacts than we actually have
  int maxc = flags & NUMC_MASK;
  if (maxc > cnum) maxc = cnum;
  if (maxc < 1) maxc = 1;	// Even though max count must not be zero this check is kept for backward compatibility as this is a public function

  if (cnum <= maxc) {
    // we have less contacts than we need, so we use them all
    for (j=0; j < cnum; j++) {
      dContactGeom *con = CONTACT(contact,skip*j);
      for (i=0; i<3; i++) con->pos[i] = point[j*3+i] + pa[i];
      con->depth = dep[j];
    }
  }
  else {
    dIASSERT(!(flags & CONTACTS_UNIMPORTANT)); // cnum should be generated not greater than maxc so that "then" clause is executed
    // we have more contacts than are wanted, some of them must be culled.
    // find the deepest point, it is always the first contact.
    int i1 = 0;
    Float maxdepth = dep[0];
    for (i=1; i<cnum; i++) {
      if (dep[i] > maxdepth) {
	maxdepth = dep[i];
	i1 = i;
      }
    }

    int iret[8];
    cullPoints (cnum,ret,maxc,i1,iret);

    for (j=0; j < maxc; j++) {
      dContactGeom *con = CONTACT(contact,skip*j);
      for (i=0; i<3; i++) con->pos[i] = point[iret[j]*3+i] + pa[i];
      con->depth = dep[iret[j]];
    }
    cnum = maxc;
  }

  *return_code = code;
  return cnum;*/
}