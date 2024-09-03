/*
PhysicObj_Z::InitDurFlag(void)	__text	00079EDC	000000AB	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetAbsDynSphereDur(Sphere_Z &,long &)	__text	00079F88	000000C5	0000001C	0000000C	R	.	.	.	.	.	B	.	.
ComputeNormalVel(PENETRATION *,PhysicObj_Z *,PhysicObj_Z *)	__text	0007A04E	00000118	00000014	0000000C	R	.	.	.	.	.	B	.	.
ComputeNormalImpulse(PENETRATION *,float,float &)	__text	0007A166	00000086	00000018	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetAbsDynBoxDur(FastBox_Z &,long &)	__text	0007A1EC	000000CA	0000001C	0000000C	R	.	.	.	.	.	B	.	.
ComputeNormalImpact(PENETRATION *)	__text	0007A2B6	00000168	0000004C	00000004	R	.	.	.	.	.	B	.	.
PhysicObj_Z::DoesTouchSphere(Sphere_Z *)	__text	0007A41E	000000A2	0000005C	00000008	R	.	.	.	.	.	B	.	.
PhysicObj_Z::LocalizeDynDur(void)	__text	0007A4C0	000003E5	0000004C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitDynDur(void)	__text	0007A8A6	00000354	000000FC	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::ComputeLinkImpact(int)	__text	0007ABFA	0000157E	000001CC	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::ComputeLinkImpacts(void)	__text	0007C178	0000005E	0000003C	00000004	R	.	.	.	.	.	B	T	.
DynSphereVsBox(Sphere_Z *,FastBox_Z *,PENETRATION *)	__text	0007C1D6	000003D9	0000005C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetGroundBoxCol(void)	__text	0007C5B0	00000688	000001AC	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetGroundSphereCol(void)	__text	0007CC38	000003F0	0000007C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::MaximizeDepth(void)	__text	0007D028	0000031E	0000032C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::HarmonizeDepth(void)	__text	0007D346	00000355	0000035C	00000004	R	.	.	.	.	.	B	T	.
ComputeFriction(PENETRATION *,Vec4f &,Vec4f const&,Vec4f const&,float,float,float,float,float,float,float,float)	__text	0007D69E	00000261	0000007C	00000030	R	.	.	.	.	.	B	.	.
ComputeContact(PENETRATION *)	__text	0007D900	00000940	000000EC	00000004	R	.	.	.	.	.	B	.	.
ComputeTangentImpact(PENETRATION *)	__text	0007E240	000005A9	000000BC	00000004	R	.	.	.	.	.	B	.	.
PWorldGroup::PrecalcObjectData(void)	__text	0007E7EA	00000958	0000029C	00000004	R	.	.	.	.	.	B	T	.
PWorldGroup::InitCollisionInfo(void)	__text	0007F142	000004F9	000040BC	00000004	R	.	.	.	.	.	B	T	.
PWorldGroup::InitObjectInfo(void)	__text	0007F63C	0000003B	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::StabilizeHeight(bool)	__text	0007F678	0000010E	0000007C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SpecialSphereCol(Node_Z *,PhysicObj_Z*,DYN_SPECIALSPH *,PENETRATION *,bool)	__text	0007F786	000003B8	0000009C	00000018	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetCollisionsSphere(PhysicObj_Z*,PENETRATION *)	__text	0007FB3E	00000271	0000005C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetSpecialCollisionsSphere(PhysicObj_Z*,PENETRATION *)	__text	0007FDB0	0000022B	0000005C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetCollisionsBox(PhysicObj_Z*,PENETRATION *)	__text	0007FFDC	00000433	0000006C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetCollisions(PhysicObj_Z*)	__text	00080410	0000028B	0000003C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetGroundSpecialSphereCol(void)	__text	0008069C	00000514	0000007C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetGroundCollisions(void)	__text	00080BB0	0000004B	0000001C	00000004	R	.	.	.	.	.	B	T	.
PWorldGroup::UpdateInteractionInfo(bool)	__text	00080BFC	000002EA	0000005C	00000005	R	.	.	.	.	.	B	T	.
PWorldGroup::StabilizeHeight(void)	__text	00080EE6	00000100	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::TestStreamGroundUnderFeed(void)	__text	00080FE8	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SetDepthOrigin(float)	__text	00080FF2	00000018	00000004	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SetDepthValue(float)	__text	0008100A	00000011	00000004	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::BeforeUpdate(DYN_STATE const&,float)	__text	0008101E	00000005	00000004		R	.	.	.	.	.	B	.	.
PhysicObj_Z::AfterUpdate(DYN_STATE const&,float)	__text	00081024	00000005	00000004		R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetForces(void)	__text	0008102C	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::PhysWakeUp(void)	__text	00081034	00000011	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::PhysSleep(void)	__text	00081046	00000011	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::WakeItem(void)	__text	00081058	00000022	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SleepItem(void)	__text	0008107A	0000009D	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::WakeAgent(void)	__text	00081118	0000003F	0000001C	00000004	R	.	.	.	.	.	B	T	.
GetWaveHeight(Float3 const&,float,float,float)	__text	00081158	0000004C	00000004	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::Damping(void)	__text	000811A4	000000E4	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetCurrentGroup(void)	__text	00081288	00000059	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::WakeMe(void)	__text	000812E2	0000004A	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::WakeMeExt(void)	__text	0008132C	00000054	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::LimitSpeed(DYN_STATE &)	__text	00081380	000000D2	0000003C	00000008	R	.	.	.	.	.	B	.	.
PhysicObj_Z::Integration1a(DYN_STATE &,DYN_STATE const&,DYN_STATE const&,float)	__text	00081452	00000076	0000003C	00000014	R	.	.	.	.	.	B	.	.
PhysicObj_Z::FlushLastCollidedNode(void)	__text	000814C8	00000042	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::StepFrameLastCollidedNode(void)	__text	0008150A	00000066	0000000C	00000004	R	.	.	.	.	.	B	T	.
dMassRotate(dMass *,float const*)	__text	00081570	0000007D	0000006C	00000008	R	.	.	.	.	.	B	T	.
dMassTranslate(dMass *,float,float,float)	__text	000815EE	000001A3	000000EC	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::InitSleepItem(void)	__text	00081792	00000096	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::ExitSleepItem(void)	__text	00081828	0000009D	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::UpdateWorldInertia(void)	__text	000818C6	000000BD	000000BC	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitAccurateWaterParams(void)	__text	00081984	000002B5	0000012C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::AddForce(DYN_STATE const&,DYN_FORCES &,Vec4f const&,Vec4f const&)	__text	00081C3A	00000060	00000004	00000014	R	.	.	.	.	.	B	.	.
dMassSetBoxTotal(dMass *,float,float,float,float)	__text	00081C9A	00000095	00000004	00000014	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ComputeImpacts(void)	__text	00081D32	0000003A	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetLastCollidedNode(void)	__text	00081D6C	0000003E	00000008	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitFrameLastCollidedNode(void)	__text	00081DAA	00000070	0000000C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SetNoDepthFound(void)	__text	00081E1A	00000019	00000004	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::UpdateLighting(float)	__text	00081E34	000002B0	0000002C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitPosition(void)	__text	000820E4	000000C5	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitMyPosAndRot(Float3 const&,Quat const&)	__text	000821AA	0000005B	0000001C	0000000C	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetBoundingDimensions(Float3 &,Float3 &)	__text	00082206	000002A3	0000015C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::UpdateEngineWorldPos(void)	__text	000824AA	000000A4	0000005C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SleepMe(void)	__text	0008254E	00000038	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SleepAgent(void)	__text	00082586	00000045	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetDepthNonPlanarOrigin(Float3 const&,Float3&,Float3&)	__text	000825CC	000000D9	00000014	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ConvertForces(void)	__text	000826A8	000002BF	00000008	00000004	R	.	.	.	.	.	B	T	.
PreparePenImpactData(PENETRATION *)	__text	00082968	000003C4	00000018	00000004	R	.	.	.	.	.	B	.	.
PhysicObj_Z::PrepareImpactData(void)	__text	00082D2C	00000032	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::~PhysicObj_Z()	__text	00082D5E	00000293	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::Integration1b(DYN_STATE &,DYN_STATE const&,DYN_STATE const&,float)	__text	00082FF4	00000148	0000004C	00000014	R	.	.	.	.	.	B	T	.
PhysicObj_Z::AddForceLimited(DYN_STATE const&,DYN_FORCES &,Vec4f const&,Vec4f const&)	__text	0008313C	000001B4	0000003C	00000014	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ComputeForceFieldsMax(ulong &,float)	__text	000832F0	00000140	0000005C	0000000C	R	.	.	.	.	.	B	T	.
AddGlobalPenetrationResult(PhysicObj_Z *,PhysicObj_Z *,Node_Z *,PENETRATION &)	__text	00083430	0000041E	0000007C	00000010	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetLocalSpeed3(DYN_STATE const&,Float3 const&,Float3&)	__text	0008384E	00000066	0000004C	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::TestSleeping(float)	__text	000838B4	0000035C	000000CC	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::IsSleeping(float)	__text	00083C10	000000AD	0000002C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetTimeStep(bool,float)	__text	00083CBE	00000126	0000005C	0000000C	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitUpdateDT(float)	__text	00083DE4	000002DF	0000010C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::GetSlowDepthNonPlanarOrigin(Float3 const&,Float3&,Float3&)	__text	000840C4	00000235	0000013C	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::GetWorldDepthOrigin(Float3 const&,Float3&,Float3&)	__text	000842FA	00000115	0000004C	00000010	R	.	.	.	.	.	B	.	.
PhysicObj_Z::WaterArchimedePoint(DYN_STATE const&,DYN_FORCES &,Vec4f const&,float,float,float,float,float,float)	__text	00084410	00000496	000000EC	00000028	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ComputeWaterArchimede(float,float,float,float,float)	__text	000848A6	00000E4A	0000018C	00000014	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SwimEffects(DYN_STATE const&)	__text	000856F0	000000A5	0000007C	00000008	R	.	.	.	.	.	B	.	.
PhysicObj_Z::PloufEffects(DYN_STATE const&)	__text	00085796	0000009E	0000007C	00000008	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ComputeIntegratorAccel(void)	__text	00085834	000000D1	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SetLastCollidedNode(Node_ZHdl,PENETRATION *)	__text	00085906	00000196	0000007C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::UpdateBoundingRay(void)	__text	00085A9C	000001DF	0000015C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::UpdateObjectDimensions(void)	__text	00085C7C	000000B1	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::Init(void)	__text	00085D2E	0000082A	0000003C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::Reset(void)	__text	00086558	00000525	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::WaterEffects(DYN_STATE const&,float)	__text	00086A7E	00000155	0000007C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ExitIntegrator(float)	__text	00086BD4	00000536	0000009C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::ResetAndSetPos(Float3 const&)	__text	0008710A	00000099	0000001C	00000008	R	.	.	.	.	.	B	T	.
PhysicObj_Z::SetMyPosAndRot(Float3 const&,Quat const&)	__text	000871A4	00000058	0000002C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::ResetAndSetPosAndRot(Float3 const&,Quat const&)	__text	000871FC	0000003F	0000002C	0000000C	R	.	.	.	.	.	B	.	.
PhysicObj_Z::UpdateMasse(void)	__text	0008723C	00000638	0000020C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitGCenterDependent(void)	__text	00087874	00000027	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitObject(void)	__text	0008789C	0000004C	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::InitPhysics(void)	__text	000878E8	00000095	0000001C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::PhysicObj_Z(void)	__text	0008797E	0000021B	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::PhysicObj_Z(void)	__text	00087B9A	0000021B	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::~PhysicObj_Z()	__text	00087DB6	0000028B	0000002C	00000004	R	.	.	.	.	.	B	T	.
PhysicObj_Z::~PhysicObj_Z()	__text	00088042	0000028B	0000002C	00000004	R	.	.	.	.	.	B	T	.
DebugDynamicInfo(void)	__text	000882D0	00000011	00000004		R	.	.	.	.	.	B	T	.
ShowSurfaceBox(void)	__text	000882E2	00000018	00000004		R	.	.	.	.	.	B	T	.
PauseDynamics(void)	__text	000882FA	00000018	00000004		R	.	.	.	.	.	B	T	.
*/