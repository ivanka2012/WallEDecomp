/*
I have no idea why all of this is in Pause.cpp

Dialog_PAUSEMAIN::Dialog_PAUSEMAIN(void)	__text	000FA120	00000080	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Remove(void)	__text	000FA1A0	0000016D	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::AfterDialog(void)	__text	000FA30E	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::MenuActivated(void)	__text	000FA318	0000001F	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::GetDefaultSelectedButton(void)	__text	000FA338	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::GetDialogValidButton(void)	__text	000FA346	00000007	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Event_CancelReturnToChapterMenu(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FA34E	0000001B	0000001C	00000004	R	.	.	.	.	.	B	.	.
Dialog_TEXTBOX::Dialog_TEXTBOX(void)	__text	000FA36A	00000028	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::Remove(void)	__text	000FA392	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::DispatchMessages(void)	__text	000FA39C	00000045	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::ValidPressed(void)	__text	000FA3E2	0000001F	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::GetDefaultSelectedButton(void)	__text	000FA404	00000011	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_ESCTOMAIN::BeforeDialog(void)	__text	000FA416	0000000F	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_ESCTOMAIN::BackToGame(void)	__text	000FA426	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::Remove(void)	__text	000FA430	0000006F	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::MenuActivated(void)	__text	000FA4A0	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::BackPressed(void)	__text	000FA4A6	00000009	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::Dialog_CHANGELEVELYESNO(void)	__text	000FA4B2	00000032	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::~Dialog_CHANGELEVELYESNO()	__text	000FA4E6	00000015	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::~Dialog_CHANGELEVELYESNO()	__text	000FA4FC	00000025	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::Remove(void)	__text	000FA522	000000A1	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::MenuActivated(void)	__text	000FA5C4	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::GetDefaultSelectedButton(void)	__text	000FA5CC	0000000E	00000004	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Event_Options(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FA5DA	00000037	0000002C	00000004	R	.	.	.	.	.	B	.	.
Dialog_PAUSEMAIN::Event_BackMain(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FA612	0000008A	0000015C	00000004	R	.	.	.	.	.	B	T	.
Dialog_ESCTOMAIN::DispatchMessages(void)	__text	000FA69C	00000089	0000015C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::BeforeDialog(void)	__text	000FA726	0000006A	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::BackPressed(void)	__text	000FA790	00000082	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::DestroyMsgBoxEvents(void)	__text	000FA812	000000CB	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_ESCTOMAIN::BackToMain(void)	__text	000FA8DE	000000C5	0000003C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::GetMissionDef(CPushButton_G *)	__text	000FA9A4	00000058	0000001C	00000008	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::InitDialog(void)	__text	000FA9FC	00000057	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::Event_FinishMenu(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FAA54	000000D1	0000004C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::CallBack_BACKMAIN(void)	__text	000FAB26	0000011B	0000003C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Event_ConfirmReturnToChapterMenu(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FAC42	00000107	0000003C	00000004	R	.	.	.	.	.	B	.	.
Dialog_PAUSEMAIN::GetDialogBackButton(void)	__text	000FAD4A	00000033	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_TEXTBOX::GetDialogValidButton(void)	__text	000FAD7E	00000033	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::InitDialog(void)	__text	000FADB2	000001BA	0000003C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::UpdateColors(void)	__text	000FAF6C	0000026F	0000006C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::Event_Valid(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FB1DC	000000E0	0000002C	0000000C	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::BeforeDialog(void)	__text	000FB2BC	0000003C	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::CreateButtons(void)	__text	000FB2F8	0000066C	0000030C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::Event_LevelUp(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FB964	00000055	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::Event_LevelDown(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FB9BA	00000051	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::InitDialog(void)	__text	000FBA0C	000000DD	0000003C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::DispatchMessages(void)	__text	000FBAEA	00000328	0000004C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::Event_TeleportTo(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FBE12	00000160	0000004C	00000004	R	.	.	.	.	.	B	T	.
Dialog_UNLOCK::DispatchMessages(void)	__text	000FBF72	00000198	0000005C	00000004	R	.	.	.	.	.	B	T	.
Dialog_GAMEOVER::KeyPressed(long)	__text	000FC10A	000000E1	0000004C	00000004	R	.	.	.	.	.	B	T	.
Dialog_GAMEOVER::DispatchMessages(void)	__text	000FC1EC	00000038	0000001C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::BeforeDialog(void)	__text	000FC224	000001A9	0000004C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::Event_ChangeLevel(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FC3CE	000002B8	0000005C	00000004	R	.	.	.	.	.	B	T	.
Dialog_CHANGELEVELYESNO::DispatchMessages(void)	__text	000FC686	00000078	0000002C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Event_Controls(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FC6FE	000004A9	0000002C	00000004	R	.	.	.	.	.	B	.	.
Dialog_PAUSEMAIN::InitDialog(void)	__text	000FCBA8	0000045E	0000006C	00000004	R	.	.	.	.	.	B	T	.
Dialog_PAUSEMAIN::Event_ChangeChapter(CWindowHierarchy_G *,CUserValue_G const&)	__text	000FD006	000001FA	0000017C	00000004	R	.	.	.	.	.	B	T	.
*/