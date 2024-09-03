/*
CameraMove_G::CAM_Chase_ComputeCurrentFar(CameraContext &,Float3 const&,float,bool)	__text	001A7058	00000092	0000003C	00000011	R	.	.	.	.	.	B	T	.
CameraMove_G::UpdateAutoWantedCam(float)	__text	001A70EA	000000B9	00000014	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::CancelAutoWantedCam(void)	__text	001A71A4	00000012	00000004	00000004	R	.	.	.	.	.	B	T	.
SpeedSmooth(float,float,float,float,float &,float &,float,float,float)	__text	001A71B8	000000F0	0000004C	00000024	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_GetRelativeTarget(CameraContext &)	__text	001A72A8	00000081	00000004	0000000C	R	.	.	.	.	.	B	.	.
ConstrainTangentSpace(Float3 const&,Float3 const&)	__text	001A732C	000000B2	0000002C	0000000C	R	.	.	.	.	.	B	T	.
ConstrainInsideTangentSpace(Float3 const&,Float3 const&)	__text	001A73DE	000000BD	0000002C	0000000C	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_ComputeInitialPosition(CameraContext &,Float3)	__text	001A749C	00000109	0000006C	00000018	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_GetPersoSol(CameraContext &,float,bool)	__text	001A75A6	000000C2	0000003C	0000000C	R	.	.	.	.	.	B	T	.
CameraMove_G::RebuildParameters(void)	__text	001A7668	0000021C	0000007C	00000004	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_Reset(void)	__text	001A7884	00000116	0000002C	00000004	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_Init(void)	__text	001A799A	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_FinalSmoothStep(CameraContext &,Sphere_Z const&,Float3 const&,float,bool)	__text	001A79A4	00000270	0000005C	00000015	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_ComputeRelativeTarget(CameraContext &,float,bool)	__text	001A7C14	000000AA	0000005C	00000011	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_ComputeTarget(CameraContext &,float,bool)	__text	001A7CBE	000001CE	0000009C	00000011	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_ConvertDistToNear(float)	__text	001A7E8C	00000137	0000003C	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_GetLodMoveNode(Node_Z **,Player_G **,LodMove_Z **)	__text	001A7FC4	0000015F	0000003C	00000010	R	.	.	.	.	.	B	.	.
CameraMove_G::SetCameraTransition(float,CameraInterpol_G *)	__text	001A8124	000000F7	0000003C	0000000C	R	.	.	.	.	.	B	T	.
CameraMove_G::SetCameraTransition(float,Camera_Z *)	__text	001A821C	00000040	0000004C	0000000C	R	.	.	.	.	.	B	T	.
CameraMove_G::SetSmoothToNearestCamera(Camera_Z *)	__text	001A825C	00000044	0000001C	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::RestoreCollision(CameraContext &)	__text	001A82A2	000000EB	0000407C	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::DisableCollision(CameraContext &)	__text	001A838E	00000072	0000002C	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_Test_SphereCol(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&,float,bool)	__text	001A8400	000000CD	0000405C	00000014	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_ComputeMinimumNear(SeadZone_Z &,CameraContext &,Float3 const&,float,bool)	__text	001A84CE	000001D7	0000405C	00000015	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_HardConstrainToBallCloseDir(CameraContext &,Float3,Float3,float,float)	__text	001A86A6	000001C0	0000006C	00000028	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_HardConstrainToBallClose(CameraContext &,Float3,Float3 const&,float,float)	__text	001A8866	0000017C	000000AC	00000024	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_HardConstrainToBallCloseDiag(CameraContext &,Float3,Float3 const&,float,float)	__text	001A89E2	00000164	000000BC	00000024	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_GetBlurFactor(CameraContext &,float,bool,float,float)	__text	001A8B46	00000135	0000005C	00000018	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_InitCameraContext(SeadZone_Z &,CameraContext &,float,bool)	__text	001A8C7C	000015F0	0000012C	00000011	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_PlayerMove(CameraContext &,Float3,Sphere_Z const&,float,bool)	__text	001AA26C	000009AE	0000014C	00000021	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_PreferredMove(CameraContext &,Float3,Sphere_Z const&,float,bool)	__text	001AAC1A	000001D5	0000006C	00000020	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_ConstrainToBall(CameraContext &,Float3,float,float,bool)	__text	001AADF0	000001F3	0000007C	00000021	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_HardConstrainToBallFar(CameraContext &,Float3,float,float)	__text	001AAFE4	00000083	00000004	0000001C	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_IsPersoHidden(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&)	__text	001AB068	00000109	000000AC	00000014	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_IsPersoHiddenFront(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&,float)	__text	001AB174	0000010F	000000AC	00000018	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_IsPersoHiddenUp(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&,float &)	__text	001AB284	00000163	000000BC	00000018	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_ConstrainToCollision(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&,float,bool)	__text	001AB3E8	00000995	000040AC	0000001D	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_PushCamForCollision(SeadZone_Z &,CameraContext &,Sphere_Z const&,Float3 const&,float,bool)	__text	001ABD7E	00001E15	0000029C	0000001D	R	.	.	.	.	.	B	T	.
CameraMove_G::CAM_Chase_MoveBehind(CameraContext &,Float3,float,bool)	__text	001ADB94	00000626	0000011C	0000001D	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_HardConstrainToBallUpDown(CameraContext &,Float3,float)	__text	001AE1BA	000001B3	000000BC	00000018	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_ComputePosition(SeadZone_Z &,CameraContext &,Sphere_Z const&,float,bool)	__text	001AE36E	000006AB	0000017C	00000019	R	.	.	.	.	.	B	.	.
CameraMove_G::CAM_Chase_Update(float)	__text	001AEA1A	00000887	000041BC	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::Reset(void)	__text	001AF2A4	000000F9	0000001C	00000004	R	.	.	.	.	.	B	T	.
CameraMove_G::MarkHandles(void)	__text	001AF39E	00000033	0000001C	00000004	R	.	.	.	.	.	B	T	.
CameraMove_G::Update(float)	__text	001AF3D2	000001AC	0000002C	00000008	R	.	.	.	.	.	B	T	.
CameraMove_G::SendCAMCommand(long,CAM_COMMUNICATION *)	__text	001AF57E	00000333	0000002C	0000000C	R	.	.	.	.	.	B	.	.
CameraMove_G::Init(void)	__text	001AF8B2	00000137	0000001C	00000004	R	.	.	.	.	.	B	T	.
*/