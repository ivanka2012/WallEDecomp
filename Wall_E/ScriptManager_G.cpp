/*
ScriptManager_G::SetShowFocusDialog(bool)	__text	00192CF6	00000011	00000004	00000005	R	.	.	.	.	.	B	T	.
ScriptManager_G::IsFocusDialogShowed(void)	__text	00192D08	0000000F	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::Shut(void)	__text	00192D18	00000017	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::IsDemoMode(DEMO_TYPE,DEMO_TYPE)	__text	00192D30	0000002B	00000004	0000000C	R	.	.	.	.	.	B	.	.
ScriptManager_G::AreVibrationsEnabled(void)	__text	00192D5E	00000028	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::SetCurrentChapter(Chapter_GHdl)	__text	00192D86	00000013	00000004	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetLevelMenu(long)	__text	00192D9A	0000001A	00000004	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetArtefactInfos(long)	__text	00192DB4	00000017	00000004	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::LockAbility(ulong)	__text	00192DCC	00000013	00000004	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetFlagGameState(void)	__text	00192DE0	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetFlagAbility(void)	__text	00192DEE	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::CheckUnlock(bool)	__text	00192DFC	00000085	0000001C	00000005	R	.	.	.	.	.	B	T	.
ScriptManager_G::ResetObjectTextInfo(DynArray_Z<CloneClassTextInfo,2,true,true,4> &)	__text	00192E82	00000022	00000008	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetDemoType(char const*)	__text	00192EA4	000000D5	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::SetGameTSCFolder(char *,char *)	__text	00192F7A	0000004E	0000001C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::IsMotPasJoli(char const*)	__text	00192FC8	00000048	0000001C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetCheatManager(void)	__text	00193010	0000000D	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetStoryMovieManager(void)	__text	0019301E	0000000D	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLevelDataId(LevelData_GHdl)	__text	0019302C	0000003A	0000000C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetCurrentChapter(void)	__text	00193066	0000001B	00000004	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetChapterId(Chapter_GHdl)	__text	00193082	0000003A	0000000C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetChapter(long)	__text	001930BC	0000003D	00000008	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::StopMenuSound(long)	__text	001930FA	00000063	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddChapter(void)	__text	00193160	00000060	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::CloneClassDone(void)	__text	001931C0	000000BA	0000004C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddArtefactInfos(ArtefactInfos_G const&)	__text	0019327A	00000114	000000BC	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::DisplayObjectTextInfo(Name_Z const&,long,float,DynArray_Z<CloneClassTextInfo,2,true,true,4> &)	__text	0019338E	0000009E	0000012C	00000014	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetLevelMenuByName(char *)	__text	0019342C	00000067	0000003C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetNbPlayer(void)	__text	00193494	0000003B	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetMainPlayer(long)	__text	001934D0	0000007B	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::ScriptManager_G(void)	__text	0019354C	00000710	000000AC	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddLogicAgent(LogicAgent_GHdl const&,Game_ZHdl const&)	__text	00193C5E	0000009E	0000002C	0000000C	R	.	.	.	.	.	B	.	.
ScriptManager_G::RemoveLogicAgent(Game_ZHdl const&)	__text	00193CFC	000000F1	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLogicAgent(Game_ZHdl const&)	__text	00193DEE	00000084	0000003C	0000000C	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetGameLogicAgent(void)	__text	00193E72	000000A6	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddInGameDialog(Name_Z &,float,float,float,float,bool)	__text	00193F1A	000000CF	0000003C	00000019	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddTTDialog(long,long)	__text	00193FEA	00000066	0000002C	00000009	R	.	.	.	.	.	B	T	.
ScriptManager_G::PlayVibration(long,long,uchar)	__text	00194050	0000004D	0000001C	0000000D	R	.	.	.	.	.	B	T	.
ScriptManager_G::StopVibration(long)	__text	0019409E	00000036	0000001C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::StopAllVibrations(void)	__text	001940D4	0000002B	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::DeactivateVibrations(void)	__text	00194100	00000066	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::ActivateVibrations(void)	__text	00194166	00000047	0000001C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::~ScriptManager_G()	__text	001941AE	0000040B	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::~ScriptManager_G()	__text	001945BA	00000413	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetIdCharacter(Name_Z const&)	__text	001949CE	0000007A	0000003C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetIdCharacter(char *)	__text	00194A48	000000C0	0000014C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::AreAllBnlCoinsCollected(void)	__text	00194B08	00000101	0000004C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetChapter(char *)	__text	00194C0A	000000A8	0000003C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::UnlockAllChapters(void)	__text	00194CB2	000000BD	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLogicAdvancement(void)	__text	00194D70	00000118	0000005C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::Update(float)	__text	00194E88	000001D6	0000003C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveOldLevel(void)	__text	00195060	0000014F	0000002C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveCharacter(long)	__text	001951B0	000000EC	0000013C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveAllPlayableCharacters(void)	__text	0019529C	00000112	0000013C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::LoadCharacter(long,bool,bool)	__text	001953AE	00000245	0000015C	0000000D	R	.	.	.	.	.	B	T	.
ScriptManager_G::UnlockAbility(ulong,bool)	__text	001955F6	000000B8	0000001C	00000009	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetMenuManager(void)	__text	001956AE	000000AB	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::PlayMenuSound(long)	__text	0019575A	0000007F	0000003C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::Minimize(void)	__text	001957DA	000000E3	0000002C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::MarkHandles(void)	__text	001958BE	00000637	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::EndFrame(void)	__text	00195EF6	000000D2	0000004C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetMission(char *,char *)	__text	00195FC8	00000080	000000EC	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::AddLevelData(void)	__text	00196048	000000AD	0000004C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetMenuLevelData(long)	__text	001960F6	00000089	0000003C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLevelDataForMission(MissionDef_G *)	__text	00196180	000000F3	0000004C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLevelDataIdForMission(MissionDef_G *)	__text	00196274	000000C6	0000004C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLevelData(char *)	__text	0019633A	00000125	0000013C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetLevelEvent(LEVELEVENT_TYPE,ulong,bool)	__text	00196460	000000C0	0000002C	0000000D	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetFirstChapterForLevel(char *)	__text	00196520	000000BC	0000004C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::LaunchChapter(Chapter_GHdl const&,LAUNCHER const&)	__text	001965DC	000005A5	0000007C	0000000C	R	.	.	.	.	.	B	.	.
ScriptManager_G::ChangePerso(char *,char *)	__text	00196B82	0000018B	0000022C	0000000C	R	.	.	.	.	.	B	T	.
ScriptManager_G::MakeRTCBF(char *)	__text	00196D0E	000001D3	0000024C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::PushCommandToLoadLevel(LevelData_GHdl,long,long *)	__text	00196EE2	000005CA	0000025C	00000010	R	.	.	.	.	.	B	T	.
ScriptManager_G::MakeAllLevelsBF(bool,bool,long)	__text	001974AC	00000248	0000014C	00000010	R	.	.	.	.	.	B	T	.
ScriptManager_G::PlayLevel(char *,long,long *,char *,char *)	__text	001976F4	0000072A	0000025C	00000018	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveAllMaterialLib(Name_Z const&,bool)	__text	00197E1E	0000009B	0000004C	00000009	R	.	.	.	.	.	B	T	.
ScriptManager_G::UnlockAll(void)	__text	00197EBA	000001AE	0000004C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::ResetNonGlobalLevelEvent(void)	__text	00198068	00000072	0000003C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::ResetAdvancement(bool)	__text	001980DA	000000E9	0000004C	00000005	R	.	.	.	.	.	B	T	.
ScriptManager_G::UnlockAllPreviousChapter(Chapter_GHdl)	__text	001981C4	000000CF	0000002C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::Init(void)	__text	00198294	00000EA5	0000015C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetMemoryStats(void)	__text	0019913A	00000141	0000016C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::CreateNewLevelEvent(LEVELEVENT_TYPE,ulong,bool)	__text	0019927E	000000C0	0000002C	0000000D	R	.	.	.	.	.	B	T	.
ScriptManager_G::ReadEnumFromFiles(void)	__text	00199340	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::NoteTrackInterpMessage(StaticArray_Z<Param_Z,16,true,true> &,Message_Z &)	__text	00199346	00000005	00000004		R	.	.	.	.	.	B	.	.
ScriptManager_G::MateriaRemoveColFlag(char const*)	__text	0019934C	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::MateriaInterpColFlag(char const*)	__text	00199354	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::MateriaInterpObjFlag(char const*)	__text	0019935C	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::InterCameraZoneFlag(char const*)	__text	00199364	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::ActivateGame(Game_ZHdl const&)	__text	0019936C	00000080	0000002C	00000004	R	.	.	.	.	.	B	.	.
ScriptManager_G::GameReseted(Game_ZHdl const&)	__text	001993EC	00000009	00000004		R	.	.	.	.	.	B	.	.
FXOmni::~FXOmni()	__text	001993F8	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveAIDummies(Game_ZHdl const&)	__text	001993FE	00000039	0000001C	00000004	R	.	.	.	.	.	B	.	.
ScriptManager_G::GameAgentSet(Game_ZHdl const&)	__text	00199438	00000159	0000003C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GetOmniForNode(Node_ZHdl const&)	__text	00199592	0000004E	00000014	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::RemoveOmniForNode(Node_ZHdl const&)	__text	001995E0	00000073	0000002C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::InterpKeyframeMsg(RegMessage_Z const&)	__text	00199654	00000294	0000014C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::UpdateIndependentResources(World_ZHdl const&)	__text	001998E8	000000C4	0000003C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::SetLevelObjectsFromSave(void)	__text	001999AC	0000007A	0000002C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::EndOfGameLogicActivation(Game_ZHdl const&)	__text	00199A28	00000406	0000003C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::ActivateGameLevel(Game_ZHdl const&)	__text	00199E2E	00000078	0000001C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::GameSet(Game_ZHdl const&)	__text	00199EA6	00000360	0000003C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::DeleteOmniForFX(void)	__text	0019A206	000000AE	0000002C	00000004	R	.	.	.	.	.	B	T	.
ScriptManager_G::RemoveGame(Game_ZHdl const&)	__text	0019A2B4	000001E2	0000002C	00000008	R	.	.	.	.	.	B	T	.
ScriptManager_G::GetFreeOmni(Game_ZHdl const&)	__text	0019A496	00000230	0000003C	00000008	R	.	.	.	.	.	B	.	.
ScriptManager_G::AddOmniFlash(Game_ZHdl const&,Float3 const&,Float3 const&,float,float,OmniType,bool)	__text	0019A6C6	00000280	0000003C	00000021	R	.	.	.	.	.	B	.	.
ScriptManager_G::UpdateOmnis(float)	__text	0019A948	00000340	0000008C	00000008	R	.	.	.	.	.	B	T	.
*/