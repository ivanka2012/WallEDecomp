/*
MACSound_Z::Init(void)	__text	00021FA2	0000016E	0000007C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::Shut(void)	__text	00022110	00000058	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::Clean(void)	__text	00022168	00000053	0000002C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::SetMuteState(ulong)	__text	000221BC	0000009E	0000002C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::CreateSound(Sound_ZHdl &)	__text	0002225A	00000024	00000004	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::CheckTrack(long)	__text	0002227E	0000003C	00000004	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::StopSound(long)	__text	000222BA	0000006B	0000001C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::Update(float)	__text	00022326	00000215	0000006C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::FreeSound(void *)	__text	0002253C	00000077	0000002C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::PlaySound(Sound_ZHdl &,ulong,Node_ZHdl const&,BoneNode_Z *)	__text	000225B4	00000346	0000005C	00000014	R	.	.	.	.	.	B	T	.
MACSound_Z::~MACSound_Z()	__text	000228FA	0000009D	0000003C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::~MACSound_Z()	__text	00022998	00000095	0000003C	00000004	R	.	.	.	.	.	B	T	.
MACSoundBF_Z::Open(String_Z<256l> &)	__text	00022A30	00000059	0000002C	00000008	R	.	.	.	.	.	B	T	.
MACSoundBF_Z::Close(void)	__text	00022A8A	0000002B	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSoundBF_Z::Get(char const*,SBFEntry &)	__text	00022AB6	00000075	0000002C	0000000C	R	.	.	.	.	.	B	T	.
MACSoundBF_Z::Readed(long,long,long)	__text	00022B2C	00000005	00000004	00000004	R	.	.	.	.	.	B	T	.
MACSoundBF_Z::Opened(long,long,long)	__text	00022B32	00000047	0000002C	00000008	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::Release(void)	__text	00022B7C	00000032	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::Lock(ulong,ulong,uchar **,ulong *,uchar **,ulong *)	__text	00022BAE	000000BA	0000002C	0000001C	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::Init(WaveFormat const&)	__text	00022C68	000000B1	0000001C	00000008	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::Unlock(void)	__text	00022D1A	00000018	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::GetSamples(float,ulong,float *,ulong,float *,ulong,float,bool,float,float,float,float *)	__text	00022D32	000002A5	0000007C	00000034	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::~MACSoundBuffer_Z()	__text	00022FD8	00000074	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSoundBuffer_Z::MACSoundBuffer_Z(void)	__text	0002304E	00000076	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::IsMusicPlaying(void)	__text	000230C4	00000015	00000004	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::GetMusicTime(void)	__text	000230DA	00000038	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::SkipMusicQueueSize(void)	__text	00023112	0000002D	00000004	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::CloseStreamBF(void)	__text	00023140	0000002D	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::IsAnyStreamPlaying(void)	__text	0002316E	00000052	0000001C	00000004	R	.	.	.	.	.	B	T	.
MACSound_Z::GetLipSyncFromStream(Node_ZHdl const&)	__text	000231C0	00000086	00000014	00000008	R	.	.	.	.	.	B	.	.
MACSound_Z::GetTrackTime(long)	__text	00023246	00000041	00000004	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::StopMusic(float)	__text	00023288	00000071	0000002C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::GetTrackName(long,String_Z<256l> &)	__text	000232FA	000000C1	0000013C	0000000C	R	.	.	.	.	.	B	T	.
MACSound_Z::OpenStreamBF(char const*)	__text	000233BC	00000071	0000011C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::SkipMusic(Name_Z const&,Name_Z const&,ulong,bool)	__text	0002342E	000000C1	0000003C	00000011	R	.	.	.	.	.	B	T	.
MACSound_Z::IsStreamPlaying(char const*)	__text	000234F0	00000080	0000003C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::StopStreamSound(char const*)	__text	00023570	00000093	0000003C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::PlayStreamSound(char const*,ulong,Node_ZHdl const&,BoneNode_Z *,ABC_AgentHdl,int)	__text	00023604	000000EC	0000003C	0000001C	R	.	.	.	.	.	B	T	.
MACSound_Z::GetStreamSoundDuration(char const*)	__text	000236F0	00000148	0000014C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::PlayMusic(char const*,ulong,float,float)	__text	00023838	00000155	0000003C	00000014	R	.	.	.	.	.	B	T	.
MACSound_Z::LoadStreamSound(char const*)	__text	0002398E	00000338	0000017C	00000008	R	.	.	.	.	.	B	T	.
MACSound_Z::LoadMusic(char const*)	__text	00023CC6	00000412	0000027C	00000008	R	.	.	.	.	.	B	T	.
*/