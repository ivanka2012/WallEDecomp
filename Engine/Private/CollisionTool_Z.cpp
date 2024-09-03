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