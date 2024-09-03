/*
Filename is a wild guess. This might as well be an engine file
CF_Void(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170434	0000000A	00000004		R	.	.	.	.	.	B	.	.
CF_Skip(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	0017043E	0000000A	00000004		R	.	.	.	.	.	B	.	.
CF_SetDof(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170448	000000A5	0000001C	00000004	R	.	.	.	.	.	B	.	.
CF_SetCameraForceTrav(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001704F0	0000000A	00000004		R	.	.	.	.	.	B	.	.
CF_PosVehicule_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001704FA	00000007	00000004		R	.	.	.	.	.	B	.	.
CF_Wait_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170502	00000044	0000002C	00000009	R	.	.	.	.	.	B	T	.
CF_WaitGoto_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170546	00000091	0000001C	00000009	R	.	.	.	.	.	B	.	.
CF_UnHideAllCreatures(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001705D8	00000019	0000001C		R	.	.	.	.	.	B	.	.
CF_StartRtcFX(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001705F4	000001BB	0000001C	00000008	R	.	.	.	.	.	B	.	.
CF_ChangeSmoothAnim(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001707B0	0000003A	00000004	00000008	R	.	.	.	.	.	B	.	.
CF_PlaySound(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001707EA	00000037	0000001C	00000009	R	.	.	.	.	.	B	T	.
CF_StartCountDown(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170822	0000005C	0000001C	00000004	R	.	.	.	.	.	B	.	.
CF_AddStrip(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	0017087E	00000052	0000002C		R	.	.	.	.	.	B	.	.
CF_RemoveStrip(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001708D0	0000005C	0000002C		R	.	.	.	.	.	B	.	.
CF_SetText_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	0017092C	00000076	0000002C	00000009	R	.	.	.	.	.	B	T	.
CF_PlayDialog_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001709A4	00000258	0000016C	00000009	R	.	.	.	.	.	B	T	.
CF_ClearText(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170BFC	00000031	0000001C		R	.	.	.	.	.	B	.	.
CF_FadeFromWhite_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170C2E	000000CD	0000003C	00000009	R	.	.	.	.	.	B	T	.
CF_FadeToBlack_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170CFC	00000150	0000005C	00000009	R	.	.	.	.	.	B	T	.
CF_FadeFromBlack_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170E4C	0000010A	0000004C	00000009	R	.	.	.	.	.	B	T	.
CF_FadeToWhite_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00170F56	000000CD	0000003C	00000009	R	.	.	.	.	.	B	T	.
CF_SetCameraDialog(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171024	000000D8	0000009C	00000008	R	.	.	.	.	.	B	.	.
CF_SetCameraChase(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001710FC	0000007F	0000008C	00000008	R	.	.	.	.	.	B	.	.
CF_SetCameraGame(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	0017117C	000000BC	0000009C	00000008	R	.	.	.	.	.	B	.	.
CF_SetCameraFocus(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171238	000000D8	0000009C	00000008	R	.	.	.	.	.	B	.	.
CF_SetCameraTravelling(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171310	000000D8	0000009C	00000008	R	.	.	.	.	.	B	.	.
CF_SetCameraForced(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001713E8	000000A8	0000009C	00000008	R	.	.	.	.	.	B	.	.
CF_CameraCut(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171490	00000086	0000001C	00000008	R	.	.	.	.	.	B	.	.
CF_CameraSmooth(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171516	0000008C	0000001C	00000009	R	.	.	.	.	.	B	.	.
CF_StartKeyFrame(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001715A2	000000A9	0000003C	00000008	R	.	.	.	.	.	B	.	.
CF_OrientNodes(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	0017164C	00000104	0000003C	00000008	R	.	.	.	.	.	B	.	.
CF_HideNode(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171750	00000093	0000001C	00000004	R	.	.	.	.	.	B	.	.
CF_UnHideNode(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	001717E4	00000094	0000001C	00000004	R	.	.	.	.	.	B	.	.
CF_PlayAnim(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171878	000000B7	0000004C	00000009	R	.	.	.	.	.	B	T	.
CF_Goto(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171930	00000177	0000004C	00000009	R	.	.	.	.	.	B	T	.
CF_PosPerso_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171AA8	000003C9	000000FC	00000008	R	.	.	.	.	.	B	T	.
CF_WaitAnim_B(RtcScriptCmd_Z *,RtcScriptAgent_G *,bool)	__text	00171E72	000000CB	0000004C	00000009	R	.	.	.	.	.	B	T	.
*/