/*
MissionManager_G::InitMissionInfos(void)	__text	0014AC7E	0000004E	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::Init(void)	__text	0014ACCC	0000004E	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::Reset(void)	__text	0014AD1A	00000017	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::IsMissionLaunchedFrom(void)	__text	0014AD32	0000000B	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::SetMissionLaunchedFrom(LAUNCHER)	__text	0014AD3E	0000000E	00000004	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::Minimize(void)	__text	0014AD4C	0000000D	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::CheckVolumeAnims(void)	__text	0014AD5A	00000036	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::ArtefactJustBeenDetected(Player_G *,Artefact_G *)	__text	0014AD90	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::CheckAutoStart(void)	__text	0014ADD8	00000036	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::MissionForbidLoadingScreen(void)	__text	0014AE0E	00000050	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::SeeStartedMission(void)	__text	0014AE60	000000B4	0000004C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::EvenementVolAgentForbidden(EvenementVolAgent_G *)	__text	0014AF16	0000004D	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::GetMissionWaitingWon(void)	__text	0014AF64	00000035	0000000C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::GetIdMission(MissionDef_G *)	__text	0014AF9A	0000003F	0000000C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::GetMissionTemplate(MissionDef_G *)	__text	0014AFDA	0000002F	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::StartMission(MissionDef_G *,bool)	__text	0014B00A	00000035	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::RemoveMission(MissionTemplate_G *,bool)	__text	0014B040	000000B3	0000003C	00000009	R	.	.	.	.	.	B	T	.
MissionManager_G::IsMissionActive(MissionDef_G *)	__text	0014B0F4	0000004F	00000010	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::LoseMission(void)	__text	0014B144	0000006E	00000014	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::IsMissionActive(MISSION_TYPE,MissionTemplate_G **)	__text	0014B1B2	00000062	00000010	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::IsMissionInState(MISSION_TYPE,MissionTemplate_G **,MISSION_STATE)	__text	0014B214	00000075	00000014	00000010	R	.	.	.	.	.	B	.	.
MissionManager_G::GetHighestPriorityMission(void)	__text	0014B28A	0000006B	00000014	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::WinMission(MissionDef_G *)	__text	0014B2F6	00000059	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::StartGlobalMissions(void)	__text	0014B350	0000004F	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::ReleaseAllMissions(bool,bool)	__text	0014B3A0	000000AB	0000003C	00000009	R	.	.	.	.	.	B	T	.
MissionManager_G::~MissionManager_G()	__text	0014B44C	000000AF	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::AllMissionsRegistered(void)	__text	0014B4FC	00000262	0000005C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::Update(float)	__text	0014B75E	000001ED	0000013C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::AllocMission(MISSION_TYPE,MissionTemplate_G **)	__text	0014B94C	00000CAA	0000001C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::AllocGlobalMissions(void)	__text	0014C5F6	00000138	0000004C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::RegisterVolume(MissionVolumeAgent_G &)	__text	0014C72E	000000E0	0000004C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::~MissionManager_G()	__text	0014C80E	000000A7	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::StartGameActivation(void)	__text	0014C8B8	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::SendMessageToMissions(int,float,BaseObject_ZHdl,IT_MsgAnimatedAgent_G *)	__text	0014C8BE	0000006C	0000005C	00000014	R	.	.	.	.	.	B	.	.
MissionManager_G::MenuEnded(MENU_TYPE)	__text	0014C92A	00000055	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerCollidedWithCube(Player_G *,IT_DynObjCube_G *)	__text	0014C980	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerCollidedWithFrogEnemy(Player_G *)	__text	0014C9C8	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerHitByExplosion(Player_G *)	__text	0014CA08	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerCollidedWithPlayer(Player_G *,Float3 const&)	__text	0014CA48	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerWasHitByLaser(LaserObj_G *,IT_Dyn_Player_G *,float)	__text	0014CA90	00000052	0000002C	00000010	R	.	.	.	.	.	B	.	.
MissionManager_G::LaserHasCollided(LaserObj_G *,Node_Z *,Float3 const&,Float3 const&)	__text	0014CAE2	00000058	0000003C	00000014	R	.	.	.	.	.	B	.	.
MissionManager_G::CollectReachedEndPos(IT_COLLECT_G *)	__text	0014CB3A	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::DynObjHasStoppedMoving(IT_DynObj_G *)	__text	0014CB7A	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::MenuActivated(void)	__text	0014CBBA	00000039	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::FrontInGameDataParsed(void)	__text	0014CBF4	00000039	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::BackInGameDataParsed(void)	__text	0014CC2E	00000039	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::PlayerInGameDataParsed(void)	__text	0014CC68	00000039	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::MenuDataParsed(void)	__text	0014CCA2	00000039	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::RegisterPlayer(Player_G *)	__text	0014CCDC	00000044	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::MessageRtcDeath(RtcScriptAgent_G *,RegMessage_Z const&)	__text	0014CD20	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::RTCCantBeLaunched(Name_Z const&)	__text	0014CD68	0000004D	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::GameActionInRtc(RtcScriptAgent_G *,RegMessage_Z &)	__text	0014CDB6	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::MessageRtcWon(RtcScriptAgent_G *)	__text	0014CDFE	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::CheckPointInRtc(RtcScriptAgent_G *,RegMessage_Z &)	__text	0014CE3E	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::RtcWillStart(Name_Z const&)	__text	0014CE86	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::RtcStarted(Name_Z const&)	__text	0014CEC6	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::RtcShut(Name_Z const&)	__text	0014CF06	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::MpegEnded(Name_Z const&)	__text	0014CF46	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::EndGameActivation(void)	__text	0014CF86	0000003D	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::MissionByPassRtcDeath(Player_G *,PLAYER_DEATH_TYPE)	__text	0014CFC4	00000054	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerDied(Creatures_G *,PLAYER_DEATH_TYPE)	__text	0014D018	000000C8	0000005C	0000000C	R	.	.	.	.	.	B	T	.
MissionManager_G::GameActivated(Game_ZHdl)	__text	0014D0E0	0000005C	0000004C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::EnemyAttackPlayer(CreaturesMove_G *,PCCOMMAND_ENUM)	__text	0014D13C	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::EnemyGenerated(long)	__text	0014D184	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::EnemyKilled(long)	__text	0014D1C4	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::EnemyDisappear(Creatures_G *)	__text	0014D204	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::MissionJustOpen(MissionDef_G *)	__text	0014D244	00000040	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::MissionJustStarted(MissionTemplate_G *)	__text	0014D284	0000004A	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::MissionJustWon(MissionTemplate_G *)	__text	0014D2CE	0000004A	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::StaticActionEnded(Creatures_G *)	__text	0014D318	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerToCheckPoint(Creatures_G *)	__text	0014D358	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerEnterCheckPoint(Creatures_G *,CheckpointVolAgent_G *)	__text	0014D398	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::SwitchOn(IT_SWITCH_G *,IT_DynObjCube_G *)	__text	0014D3E0	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::SwitchOn(IT_SWITCH_G *,Creatures_G *)	__text	0014D428	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::CollectedObject(IT_COLLECT_G *,Player_G *)	__text	0014D470	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::BreakObject(BreakObject_G *)	__text	0014D4B8	00000040	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerEnterVolume(MissionVolumeAgent_G &,Agent_ZHdl const&)	__text	0014D4F8	00000044	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerDelayedEnterVolume(MissionVolumeAgent_G &,Agent_ZHdl const&)	__text	0014D53C	00000044	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::PlayerExitingVolume(MissionVolumeAgent_G &,Agent_ZHdl const&)	__text	0014D580	00000044	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::EnterEndMissionVolume(EndMissionVolumeAgent_G *,Agent_ZHdl const&)	__text	0014D5C4	00000052	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::ExitEndMissionVolume(EndMissionVolumeAgent_G *,Agent_ZHdl const&)	__text	0014D616	00000047	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::ObjectDelayedEnterEndMissionVolume(EndMissionVolumeAgent_G *,Agent_ZHdl const&)	__text	0014D65E	00000052	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::EnemyDelayedEnterEndMissionVolume(EndMissionVolumeAgent_G *,Agent_ZHdl const&)	__text	0014D6B0	00000052	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::DelayedEnterEndMissionVolume(EndMissionVolumeAgent_G *,Agent_ZHdl const&)	__text	0014D702	00000052	0000002C	0000000C	R	.	.	.	.	.	B	.	.
MissionManager_G::GameReseted(void)	__text	0014D754	0000003D	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionManager_G::LevelWillChange(long)	__text	0014D792	000000F8	0000003C	00000008	R	.	.	.	.	.	B	T	.
MissionManager_G::ObjectAnimFinished(Node_ZHdl)	__text	0014D88A	0000005B	0000004C	00000008	R	.	.	.	.	.	B	.	.
*/