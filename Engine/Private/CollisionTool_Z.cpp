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

#include <Types_Z.h>
#include <Math_Z.h>
#include <Vec3f_Z.h>
#include    <math.h>
#ifndef M_PI
#define M_PI          3.14159265358979323846
#endif

/* epsilon surrounding for near zero values */

#define     EQN_EPS     1e-9
#define	    IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

#define     cbrt(x)     ((x) > 0.0 ? pow((float)(x), 1.0f/3.0f) : \
                          ((x) < 0.0 ? -pow((float)-(x), 1.0f/3.0f) : 0.0))

int SolveQuadric(double *c, double *s)
{
    double p, q, D;

    /* normal form: x^2 + px + q = 0 */

    p = c[ 1 ] / (2 * c[ 2 ]);
    q = c[ 0 ] / c[ 2 ];

    D = p * p - q;

    if (IsZero(D))
    {
	s[ 0 ] = - p;
	return 1;
    }
    else if (D < 0)
    {
	return 0;
    }
    else /* if (D > 0) */
    {
	double sqrt_D = sqrt(D);

	s[ 0 ] =   sqrt_D - p;
	s[ 1 ] = - sqrt_D - p;
	return 2;
    }
}


int SolveCubic(double *c, double *s)
{
    int     i, num;
    double  sub;
    double  A, B, C;
    double  sq_A, p, q;
    double  cb_p, D;

    /* normal form: x^3 + Ax^2 + Bx + C = 0 */

    A = c[ 2 ] / c[ 3 ];
    B = c[ 1 ] / c[ 3 ];
    C = c[ 0 ] / c[ 3 ];

    /*  substitute x = y - A/3 to eliminate quadric term:
	x^3 +px + q = 0 */

    sq_A = A * A;
    p = 1.0/3 * (- 1.0/3 * sq_A + B);
    q = 1.0/2 * (2.0/27 * A * sq_A - 1.0/3 * A * B + C);

    /* use Cardano's formula */

    cb_p = p * p * p;
    D = q * q + cb_p;

    if (IsZero(D))
    {
	if (IsZero(q)) /* one triple solution */
	{
	    s[ 0 ] = 0;
	    num = 1;
	}
	else /* one single and one double solution */
	{
	    double u = cbrt(-q);
	    s[ 0 ] = 2 * u;
	    s[ 1 ] = - u;
	    num = 2;
	}
    }
    else if (D < 0) /* Casus irreducibilis: three real solutions */
    {
	double phi = 1.0/3 * acos(-q / sqrt(-cb_p));
	double t = 2 * sqrt(-p);

	s[ 0 ] =   t * cosf(phi);
	s[ 1 ] = - t * cosf(phi + M_PI / 3);
	s[ 2 ] = - t * cosf(phi - M_PI / 3);
	num = 3;
    }
    else /* one real solution */
    {
	double sqrt_D = sqrt(D);
	double u = cbrt(sqrt_D - q);
	double v = - cbrt(sqrt_D + q);

	s[ 0 ] = u + v;
	num = 1;
    }

    /* resubstitute */

    sub = 1.0/3 * A;

    for (i = 0; i < num; ++i)
	s[ i ] -= sub;

    return num;
}


int SolveQuartic(double *c, double *s)
{
    double  coeffs[ 4 ];
    double  z, u, v, sub;
    double  A, B, C, D;
    double  sq_A, p, q, r;
    int     i, num;

    /* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];

    /*  substitute x = y - A/4 to eliminate cubic term:
	x^4 + px^2 + qx + r = 0 */

    sq_A = A * A;
    p = - 3.0/8 * sq_A + B;
    q = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
    r = - 3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

    if (IsZero(r))
    {
	/* no absolute term: y(y^3 + py + q) = 0 */

	coeffs[ 0 ] = q;
	coeffs[ 1 ] = p;
	coeffs[ 2 ] = 0;
	coeffs[ 3 ] = 1;

	num = SolveCubic(coeffs, s);

	s[ num++ ] = 0;
    }
    else
    {
	/* solve the resolvent cubic ... */

	coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
	coeffs[ 1 ] = - r;
	coeffs[ 2 ] = - 1.0/2 * p;
	coeffs[ 3 ] = 1;

	(void) SolveCubic(coeffs, s);

	/* ... and take the one real solution ... */

	z = s[ 0 ];

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

	coeffs[ 0 ] = z - u;
	coeffs[ 1 ] = q < 0 ? -v : v;
	coeffs[ 2 ] = 1;

	num = SolveQuadric(coeffs, s);

	coeffs[ 0 ]= z + u;
	coeffs[ 1 ] = q < 0 ? v : -v;
	coeffs[ 2 ] = 1;

	num += SolveQuadric(coeffs, s + num);
    }

    /* resubstitute */

    sub = 1.0/4 * A;

    for (i = 0; i < num; ++i)
	s[ i ] -= sub;

    return num;
}

int	inttor(
			Float3	raybase,		// Base of the intersection ray
			Float3	raycos,			// Direction cosines of the ray
			Float	radius,			// Major radius of the torus
			Float	rplane,			// Minor planer radius
			Float	rnorm,			// Minor normal radius
			int *	nhits,			// Number of intersections
			double	rhits[4]		// Intersection distances
		 )
{
	Float3	Base, Dcos;		/* Transformed intersection ray	*/
	Float	rho, a0, b0;		/* Related constants		*/
	Float	f, l, t, g, q, m, u;	/* Ray dependent terms		*/
	double	C[5];			/* Quartic coefficients		*/

	*nhits  = 0;

/*	Transform the intersection ray					*/

	Base = raybase;
	Dcos = raycos;

/*	Compute constants related to the torus.				*/

	rho = rplane*rplane / (rnorm*rnorm);
	a0  = 4.f * radius*radius;
	b0  = radius*radius - rplane*rplane;

/*	Compute ray dependent terms.					*/

	f = 1.f - Dcos.y*Dcos.y;
	l = 2.f * (Base.x*Dcos.x + Base.z*Dcos.z);
	t = Base.x*Base.x + Base.z*Base.z;
	g = f + rho * Dcos.y*Dcos.y;
	q = a0 / (g*g);
	m = (l + 2.f*rho*Dcos.y*Base.y) / g;
	u = (t +    rho*Base.y*Base.y + b0) / g;

/*	Compute the coefficients of the quartic.			*/

	C[4] = 1.f;
	C[3] = 2.f * m;
	C[2] = m*m + 2.f*u - q*f;
	C[1] = 2.f*m*u - q*l;
	C[0] = u*u - q*t;
	
/*	Use quartic root solver found in "Graphics Gems" by Jochen	*/
/*	Schwarze.							*/
	*nhits = SolveQuartic (C,rhits);

/*	SolveQuartic returns root pairs in reversed order.		*/
	m = Float(rhits[0]); u = Float(rhits[1]); rhits[0] = u; rhits[1] = m;
	m = Float(rhits[2]); u = Float(rhits[3]); rhits[2] = u; rhits[3] = m;

	return (*nhits != 0);
}

struct CollisionReport_Z{
	Vec4f m_vInter; //+0x00
	Vec4f m_vNormal; //+0x10
	int unk1; //+0x20
	int unk1; //+0x24
	float m_fDist; //+0x28
};

Bool SphereVSSphere(const Sphere_Z &Sph1,const Sphere_Z &Sph2,CollisionReport_Z &Result)
{

	Vec3f Diff = Sph1.Center - Sph2.Center;
	Float RadSum = Sph1.Radius + Sph2.Radius , SqrNorm = Diff.GetNorm2();
	if( SqrNorm < RadSum*RadSum)
	{
		Float	Norm=sqrt(SqrNorm);
		Float	Dist=Norm - Sph2.Radius;

		if(Dist<Result.m_fDist)
		{
			Result.m_fDist			=Dist;
			Result.m_vNormal		= Vec4f(Diff/Norm, 1.f);
			Result.m_vInter		= Vec4f(Sph2.Center + Result.m_vNormal * Sph2.Radius, 1.f);
			return	TRUE;
		}
	}
	return	FALSE;
}