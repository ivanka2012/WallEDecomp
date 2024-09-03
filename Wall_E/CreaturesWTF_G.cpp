/*
Guess you need creativity to figure this shit out.

PST_TOOLS_InitNormalState(CreaturesMove_G *)	__text	00188110	00000021	00000004	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_CalcDynParam(Float3 &,Float3 const&,Float3 const&,float,float,float)	__text	00188132	0000017C	0000007C	00000018	R	.	.	.	.	.	B	.	.
IsInActiveStreamZone(Float3 const&)	__text	001882AE	0000009A	0000002C	00000004	R	.	.	.	.	.	B	.	.
IsStreamActive(void)	__text	00188348	0000006A	0000001C		R	.	.	.	.	.	B	T	.
PST_TOOLS_RemoveAllEffects(CreaturesMove_G *)	__text	001883B4	00000083	0000004C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_ManageEffects(CreaturesMove_G *,float,ulong long)	__text	00188438	00000005	00000004		R	.	.	.	.	.	B	T	.
PST_TOOLS_GetPlayerNodeFromNode(Node_Z *)	__text	00188440	00000073	0000001C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_GetWaterDepth(CreaturesMove_G *)	__text	001884B4	00000078	0000003C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_IsGroundUnderFeetNow(CreaturesMove_G *)	__text	0018852C	0000004F	0000002C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_ForceHSpeed(CreaturesMove_G *,float,Float3 const&,bool)	__text	0018857C	00000130	0000005C	0000000D	R	.	.	.	.	.	B	T	.
PST_TOOLS_UpdateWalkSpeed(CreaturesMove_G *,float,float,bool)	__text	001886AC	0000066F	000000DC	0000000D	R	.	.	.	.	.	B	T	.
PST_TOOLS_ResetHSpeed(CreaturesMove_G *,float)	__text	00188D1C	00000075	0000003C	00000008	R	.	.	.	.	.	B	T	.
GetPlayerDist(Float3 const&)	__text	00188D92	00000074	0000002C	00000004	R	.	.	.	.	.	B	.	.
PST_TOOLS_IsInCone(float,float,float,Float3 const&,Float3 const&,Float3 const&,float,Float3&)	__text	00188E06	000000BE	0000003C	00000018	R	.	.	.	.	.	B	.	.
PST_TOOLS_IsInPie(float,float,float,Float3 const&,Float3 const&,Float3 const&,float,Float3&)	__text	00188EC4	00000175	0000005C	00000020	R	.	.	.	.	.	B	.	.
PST_TOOLS_MoveTread(Player_G *,float,Skel_Z *,long,long,long,float *,float *,float)	__text	0018903C	0000028B	0000009C	00000020	R	.	.	.	.	.	B	T	.
PST_TOOLS_AnimTreads(Player_G *,float,float)	__text	001892C8	0000079B	0000036C	0000000C	R	.	.	.	.	.	B	T	.
PST_TOOLS_SetMixAnim(CreaturesMove_G *,long,long)	__text	00189A64	0000004B	0000002C	0000000C	R	.	.	.	.	.	B	T	.
PST_GETCURANIMDURATION(CreaturesMove_G *)	__text	00189AB0	0000009B	0000001C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_SetAnimEx(CreaturesMove_G *,long,float,float,bool,bool)	__text	00189B4C	00000124	0000006C	00000015	R	.	.	.	.	.	B	T	.
PST_TOOLS_SetAnimEx2(CreaturesMove_G *,long,float,float,bool,bool)	__text	00189C70	000000FC	0000006C	00000015	R	.	.	.	.	.	B	T	.
PST_TOOLS_SetAnim(CreaturesMove_G *,long)	__text	00189D6E	00000073	0000002C	00000008	R	.	.	.	.	.	B	T	.
PST_TOOLS_StopAllAnims(CreaturesMove_G *)	__text	00189DE4	00000089	0000001C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_SetAnimSpeed(CreaturesMove_G *,float)	__text	00189E6E	0000004D	0000001C	00000008	R	.	.	.	.	.	B	T	.
PST_TOOLS_SwitchAnimSmoothNoLag(CreaturesMove_G *,long,float)	__text	00189EBE	00000074	0000002C	0000000C	R	.	.	.	.	.	B	T	.
PST_TOOLS_InsideMessagesInAnim(CreaturesMove_G *,long,long)	__text	00189F32	00000193	0000005C	0000000C	R	.	.	.	.	.	B	T	.
PST_TOOLS_CanHitFromAnim(CreaturesMove_G *)	__text	0018A0C6	00000026	0000001C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_IsAfterMsgInAnim(CreaturesMove_G *,long)	__text	0018A0EC	0000016B	0000004C	00000008	R	.	.	.	.	.	B	T	.
PST_TOOLS_IsInfiniteAnimation(CreaturesMove_G *)	__text	0018A258	00000041	0000001C	00000004	R	.	.	.	.	.	B	T	.
PST_TOOLS_GetAnimLength(CreaturesMove_G *,long,float)	__text	0018A29A	00000128	0000005C	0000000C	R	.	.	.	.	.	B	T	.
CS_Class_BUMPERSLINK::LastFrameInState(StatesMachineParams_G *)	__text	0018A3C2	00000029	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSEJECT::FirstFrameInState(StatesMachineParams_G *)	__text	0018A3EC	00000084	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSJUMP::LastFrameInState(StatesMachineParams_G *)	__text	0018A470	00000009	00000004		R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSLINK::FirstFrameInState(StatesMachineParams_G *)	__text	0018A47A	00000097	0000003C	00000008	R	.	.	.	.	.	B	.	.
PST_Tools_IsBumperOK(CreaturesMove_G *,PInput_G *)	__text	0018A512	000000B2	0000002C	00000008	R	.	.	.	.	.	B	T	.
PST_Tools_LinkPersoOnBumper(CreaturesMove_G *,bool)	__text	0018A5C4	00000027	0000003C	00000004	R	.	.	.	.	.	B	T	.
CS_Class_BUMPERSEJECT::Update(StatesMachineParams_G *)	__text	0018A5EC	00000060	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSLINK::Update(StatesMachineParams_G *)	__text	0018A64C	00000175	0000003C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSJUMP::FirstFrameInState(StatesMachineParams_G *)	__text	0018A7C2	000000BA	0000002C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_BUMPERSJUMP::Update(StatesMachineParams_G *)	__text	0018A87C	0000023F	0000004C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYDROPEND::LastFrameInState(StatesMachineParams_G *)	__text	0018AABC	0000004C	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYTHROW::FirstFrameInState(StatesMachineParams_G *)	__text	0018AB08	00000098	0000002C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYTHROW::Update(StatesMachineParams_G *)	__text	0018ABA0	00000079	0000001C	00000008	R	.	.	.	.	.	B	.	.
PST_TOOLS_CanThrowDynObjects(CreaturesMove_G *,PInput_G *)	__text	0018AC1A	00000036	00000004	00000008	R	.	.	.	.	.	B	T	.
CS_Class_DYNCARRYDROP::Update(StatesMachineParams_G *)	__text	0018AC50	0000004A	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYDROPEND::Update(StatesMachineParams_G *)	__text	0018AC9A	00000076	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYSTART::Update(StatesMachineParams_G *)	__text	0018AD10	00000077	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYPICKUP::FirstFrameInState(StatesMachineParams_G *)	__text	0018AD88	00000086	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYDROP::LastFrameInState(StatesMachineParams_G *)	__text	0018AE0E	00000031	0000001C	00000008	R	.	.	.	.	.	B	.	.
PST_TOOLS_CanDropDynObjects(CreaturesMove_G *,PInput_G *)	__text	0018AE40	0000004B	00000004	00000008	R	.	.	.	.	.	B	T	.
PST_TOOLS_GetJunkByEnnemiesDynObjects(CreaturesMove_G *,PInput_G *)	__text	0018AE8C	00000154	0000004C	00000004	R	.	.	.	.	.	B	T	.
CS_Class_DYNCARRYPICKUP::LastFrameInState(StatesMachineParams_G *)	__text	0018AFE0	00000079	0000001C	00000008	R	.	.	.	.	.	B	.	.
PST_TOOLS_CanCarryDynObjects(CreaturesMove_G *,PInput_G *)	__text	0018B05A	000000C5	0000001C	00000008	R	.	.	.	.	.	B	T	.
PST_TOOLS_GetJunkCarryDynObjects(CreaturesMove_G *,PInput_G *)	__text	0018B120	00000159	0000004C	00000004	R	.	.	.	.	.	B	T	.
CS_Class_DYNCARRYSTART::FirstFrameInState(StatesMachineParams_G *)	__text	0018B27A	000000CC	0000002C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYPICKUP::Update(StatesMachineParams_G *)	__text	0018B346	00000088	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYDROP::FirstFrameInState(StatesMachineParams_G *)	__text	0018B3CE	0000007F	0000001C	00000008	R	.	.	.	.	.	B	.	.
CS_Class_DYNCARRYDROPEND::FirstFrameInState(StatesMachineParams_G *)	__text	0018B44E	000000AA	0000002C	00000008	R	.	.	.	.	.	B	.	.
*/