/*
I have no idea what this could've been named separately.
MissionTemplate_G::CheckAutoStart(void)	__text	0014F16C	0000001F	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::PlayerEnterVolume(MissionVolumeAgent_G &,Agent_ZHdl const&)	__text	0014F18C	00000005	00000004		R	.	.	.	.	.	B	.	.
MissionTemplate_G::PlayerDelayedEnterVolume(MissionVolumeAgent_G &,Agent_ZHdl const&)	__text	0014F192	00000018	00000004	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::CheckStart(void)	__text	0014F1AA	0000002B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::EndGameActivation(void)	__text	0014F1D6	0000001A	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionAfterMissionWon(void)	__text	0014F1F0	0000001B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::CanMissionBeStarted(void)	__text	0014F20C	00000078	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionMenuLost(void)	__text	0014F284	0000004B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionMenuWon(void)	__text	0014F2D0	0000004B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MissionDisabled(void)	__text	0014F31C	00000128	0000023C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionBeforeMission(void)	__text	0014F444	000001F0	0000003C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionMissionWon(void)	__text	0014F634	00000139	0000003C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionMissionLost(void)	__text	0014F76E	000000B5	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionAfterMission(bool)	__text	0014F824	000000B3	0000002C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::TransitionAfterMissionLost(void)	__text	0014F8D8	00000117	0000003C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MissionOver(bool)	__text	0014F9F0	0000024E	0000004C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::CheckVolumeAnims(void)	__text	0014FC40	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::ComputeScreenBaseInWorldCoordinate(Player_G *,Float3 &,Float3 &,Float3 &,Float3 &)	__text	0014FC46	00000009	00000004		R	.	.	.	.	.	B	.	.
MissionTemplate_G::GetTutorialSound(long,long &)	__text	0014FC52	00000070	000000AC	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::PushTutorial(void)	__text	0014FCC2	0000002B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetInGamePlayer(long)	__text	0014FCEE	00000043	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::EnableInput(PCCOMMAND_ENUM,long)	__text	0014FD32	00000041	0000001C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::SplineCoordToRoundCoord(float,float &)	__text	0014FD74	000000DF	00000004	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::CountRound(Player_G *,float &)	__text	0014FE54	00000085	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::SetPlayerState(CREATURES_STATES,long)	__text	0014FEDA	00000041	0000001C	0000000C	R	.	.	.	.	.	B	.	.
MissionTemplate_G::DisableAllInputs(long)	__text	0014FF1C	00000032	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::EnableAllInputs(long)	__text	0014FF4E	00000032	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::DisableInput(PCCOMMAND_ENUM,long)	__text	0014FF80	00000041	0000001C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::GetNodeInMap(Name_Z const&)	__text	0014FFC2	00000080	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetNbTutorial(void)	__text	00150042	000000DD	000001CC	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::NeedTutorial(void)	__text	00150120	0000005B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetTutorial(long,long &,Name_Z &)	__text	0015017C	000000F9	000001CC	00000010	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UpdateCamera(float)	__text	00150276	00000107	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UnSetUpCamera(void)	__text	0015037E	00000155	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetRay(Vec2f const&,Player_G *,Float3 const&,Float3 const&,Float3 const&,Float3 const&)	__text	001504D6	00000309	0000009C	0000001C	R	.	.	.	.	.	B	.	.
MissionTemplate_G::ParseSubTree(bool)	__text	001507E0	000000B7	0000024C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetNbObjectsCloned(Name_Z const&,bool)	__text	00150898	000000A4	0000023C	00000009	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetObjectClonedId(Name_Z const&,long,bool)	__text	0015093C	000000AB	0000023C	0000000D	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetObjectSonId(Name_Z const&,long)	__text	001509E8	00000056	0000001C	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetNbVolume(Name_Z const&)	__text	00150A3E	0000007F	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetVolumeId(long,Name_Z const&)	__text	00150ABE	000000AF	0000003C	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::SetFixCamera(uchar,float,float)	__text	00150B70	0000039B	0000014C	00000010	R	.	.	.	.	.	B	T	.
MissionTemplate_G::Update2DLaserViseur(long,float,Vec2f &,float,float)	__text	00150F0C	000004D4	0000011C	00000018	R	.	.	.	.	.	B	.	.
MissionTemplate_G::TeleportPlayerToNode(Node_ZHdl const&)	__text	001513E0	00000071	0000003C	00000008	R	.	.	.	.	.	B	.	.
*/