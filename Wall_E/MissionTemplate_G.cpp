/*
MissionTemplate_G::SetMissionVolume(MissionVolumeAgent_G *)	__text	0014D8E8	000000AC	0000022C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UnSetPlayerStatic(Player_G *)	__text	0014D994	0000006C	0000002C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UnSetUpHUD(bool)	__text	0014DA00	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::FrontInGameDataParsed(void)	__text	0014DA06	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::BackInGameDataParsed(void)	__text	0014DA0C	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::PlayerInGameDataParsed(void)	__text	0014DA12	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MenuDataParsed(void)	__text	0014DA18	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UpdatePreparing(float,bool)	__text	0014DA1E	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UpdateWaiting(float,bool)	__text	0014DA28	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetMissionSuccessMenu(void)	__text	0014DA2E	0000000A	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::PlayerEnterCheckPoint(Creatures_G *,CheckpointVolAgent_G *)	__text	0014DA38	0000001D	00000004	00000004	R	.	.	.	.	.	B	.	.
MissionTemplate_G::ChangeState(MISSION_STATE)	__text	0014DA56	00000077	0000001C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::ConditionToDo(CONDITION_ACTION)	__text	0014DACE	000000F2	0000001C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::MpegEnded(Name_Z const&)	__text	0014DBC0	0000002F	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::RtcShut(Name_Z const&)	__text	0014DBF0	0000002F	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::RegisterPlayer(Player_G *)	__text	0014DC20	0000002F	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MenuEnded(MENU_TYPE)	__text	0014DC50	0000003F	0000001C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::GetTextState(void)	__text	0014DC90	00000012	00000004	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::CallMenu(MENU_TYPE,bool,MenuParams *)	__text	0014DCA2	000001C2	0000004C	00000010	R	.	.	.	.	.	B	.	.
MissionTemplate_G::GameActivated(Game_ZHdl)	__text	0014DE64	0000004A	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::CheckHOrientation(Float3 const&,Float3 const&,float,bool &,Float3&,Float3&)	__text	0014DEAE	0000019B	0000005C	0000001C	R	.	.	.	.	.	B	.	.
MissionTemplate_G::ObjectAnimFinished(Node_ZHdl)	__text	0014E04A	00000039	0000002C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::RestartMission(void)	__text	0014E084	0000005C	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UpdateTutorial(float)	__text	0014E0E0	0000006B	0000001C	00000008	R	.	.	.	.	.	B	T	.
MissionTemplate_G::SetPlayerStatic(Player_G *,long)	__text	0014E14C	0000007F	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MissionTemplate_G(void)	__text	0014E1CE	000000C6	0000001C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UnSetUpMission(bool,bool)	__text	0014E294	000000F8	0000004C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetEditedTotalTime(void)	__text	0014E38C	0000004E	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::GetEditedAddedTime(void)	__text	0014E3DA	0000004E	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::CleanMission(void)	__text	0014E428	0000007D	0000002C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::Wait4ConditionObjsAnimEnd(COND_TYPE)	__text	0014E4A6	00000121	0000004C	00000008	R	.	.	.	.	.	B	.	.
MissionTemplate_G::SetPlayerToNode(Player_G *,Node_ZHdl const&,float)	__text	0014E5C8	00000162	0000003C	00000010	R	.	.	.	.	.	B	.	.
MissionTemplate_G::SetUpMission(bool)	__text	0014E72A	00000111	0000003C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::SetUpHUD(bool)	__text	0014E83C	00000067	0000001C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::StartMission(bool)	__text	0014E8A4	000000F9	0000003C	00000005	R	.	.	.	.	.	B	T	.
MissionTemplate_G::UpdateRunning(float,bool)	__text	0014E99E	0000010C	0000002C	00000009	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MissionSuccess(void)	__text	0014EAAA	000003BB	0000004C	00000004	R	.	.	.	.	.	B	T	.
MissionTemplate_G::MissionFailure(void)	__text	0014EE66	0000014F	0000003C	00000004	R	.	.	.	.	.	B	T	.
*/