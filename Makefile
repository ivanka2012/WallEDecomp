CC = gcc
CXX = g++
CCFLAGS = -mdynamic-no-pic -fpascal-strings -Wall -arch i386 -fasm-blocks -Os -IEngine/includes
CXXFLAGS = -mdynamic-no-pic -fpascal-strings -Wall -arch i386 -fvisibility-inlines-hidden -fasm-blocks -Os -IEngine/includes -fpermissive

ENGINE_CXXSRC = \
	LibMAC/AssertMAC_Z.cpp \
	LibMAC/FontMAC_Z.cpp \
	LibMAC/FlareMAC_Z.cpp \
	LibMAC/HID_Util/HID_Config_Utilities.c \
	LibMAC/HID_Util/HID_Error_Handler.c \
	LibMAC/HID_Util/HID_Name_Lookup.c \
	LibMAC/HID_Util/HID_Queue_Utilities.c \
	LibMAC/HID_Util/HID_Transaction_Utilities.c \
	LibMAC/HID_Util/HID_Utilities.c \
	LibMAC/HID_Util/ImmrHIDUtilAddOn.c \
	LibMAC/ImaAdpcmCodec.cpp \
	LibMAC/InGameObjectsMAC_Z.cpp \
	LibMAC/LodMAC_Z.cpp \
	LibMAC/LowLevelTools_Z.cpp \
	LibMAC/LowMemoryManager_Z.cpp \
	LibMAC/MACConsole_Z.cpp \
	LibMAC/MACFile_Z.cpp \
	LibMAC/MACFrustum_Z.cpp \
	LibMAC/MACInput_Z.cpp \
	LibMAC/MACMain_Z.cpp \
	LibMAC/MACMovie_Z.cpp \
	LibMAC/MACMovieManipulator_Z.cpp \
	LibMAC/MACMutex_Z.cpp \
	LibMAC/MACRenderer2D_Z.cpp \
	LibMAC/MACRenderer_Z.cpp \
	LibMAC/MACRendererPrimitive3D_Z.cpp \
	LibMAC/MACRenderTarget_Z.cpp \
	LibMAC/MACShader_Z.cpp \
	LibMAC/MACShaderConstant_Z.cpp \
	LibMAC/MACShaderContext_Z.cpp \
	LibMAC/MACSoundStream_Z.cpp \
	LibMAC/MACSound_Z.cpp \
	LibMAC/MACStream_Z.cpp \
	LibMAC/MACStreamManager_Z.cpp \
	LibMAC/MACStreamManager_Z.cpp \
	LibMAC/MACString_Z.cpp \
	LibMAC/MaterialMAC_Z.cpp \
	LibMAC/MathMAC_Z.cpp \
	LibMAC/RotShapeMAC_Z.cpp \
	LibMAC/SaveGameMAC_Z.cpp \
	LibMAC/SkelMAC_Z.cpp \
	LibMAC/SkinMAC_Z.cpp \
	LibMAC/StreamMAC_Z.cpp \
	LibMAC/SurfaceMAC_Z.cpp \
	LibMAC/TimeMAC_Z.cpp \
	LibMAC/tinyxml/tinystr.cpp \
	LibMAC/tinyxml/tinyxml.cpp \
	LibMAC/tinyxml/tinyxmlerror.cpp \
	LibMAC/tinyxml/tinyxmlparser.cpp \
	LibMAC/WarpMAC_Z.cpp \
	Engine/ABC_Agent.cpp \
	Engine/ABC_Behavior.cpp \
	Engine/ABC_CategoryData.cpp \
	Engine/ABC_ScriptManager.cpp \
	Engine/Agent_Z.cpp \
	Engine/AnimatedAgent_Z.cpp \
	Engine/AnimatedMsgAgent_Z.cpp \
	Engine/Animation_Z.cpp \
	Engine/AnimationManager_Z.cpp \
	Engine/AnimationMesh_Z.cpp \
	Engine/AnimFrame_Z.cpp \
	Engine/BaseObject_Z.cpp \
	Engine/BitArray_Z.cpp \
	Engine/Bitmap_Z.cpp \
	Engine/BoneNode_Z.cpp \
	Engine/Breakable_Z.cpp \
	Engine/Camera_Z.cpp \
	Engine/CameraAgent_Z.cpp \
	Engine/CameraEngine_Z.cpp \
	Engine/CameraEngineZoneCapture_Z.cpp \
	Engine/CameraOccluder_Z.cpp \
	Engine/CameraStream_Z.cpp \
	Engine/CameraUser_Z.cpp \
	Engine/CameraZone_Z.cpp \
	Engine/ClassNameRes_Z.cpp \
	Engine/ClassNameResManager_Z.cpp \
	Engine/CodePreprocessor_Z.cpp \
	Engine/CollisionVol_Z.cpp \
	Engine/Console_Z.cpp \
	Engine/ConsoleCommand_Z.cpp \
	Engine/ConsoleInterp_Z.cpp \
	Engine/ConsoleMessage_Z.cpp \
	Engine/Debug_Z.cpp \
	Engine/DebugCommands_Z.cpp \
	Engine/DXT_Z.cpp \
	Engine/Emitter_Z.cpp \
	Engine/ErrorTab_Z.cpp \
	Engine/Flare_Z.cpp \
	Engine/Fonts_Z.cpp \
	Engine/Frustum_Z.cpp \
	Engine/Game_Z.cpp \
	Engine/GameManager_Z.cpp \
	Engine/GameManagerDebug_Z.cpp \
	Engine/GameManagerRTC_Z.cpp \
	Engine/GameManipulator_Z.cpp \
	Engine/GameObj_Z.cpp \
	Engine/GameRTC_Z.cpp \
	Engine/GameSubWorld_Z.cpp \
	Engine/GaussConvolution_Z.cpp \
	Engine/Graph_Z.cpp \
	Engine/GraphLevel_Z.cpp \
	Engine/GraphLoad_Z.cpp \
	Engine/GraphVertex_Z.cpp \
	Engine/Handle_Z.cpp \
	Engine/HFog_Z.cpp \
	Engine/InGameDatas_Z.cpp \
	Engine/InGameObjects_Z.cpp \
	Engine/InGameObjectsManipulator_Z.cpp \
	Engine/InputAction_Z.cpp \
	Engine/InputActionContext_Z.cpp \
	Engine/InputPlatform_Z.cpp \
	Engine/KSys_Z.cpp \
	Engine/Language_Z.cpp \
	Engine/Light_Z.cpp \
	Engine/Lod_Z.cpp \
	Engine/LodAgent_Z.cpp \
	Engine/LodCollision_Z.cpp \
	Engine/LodDynAgent_Z.cpp \
	Engine/LodMove_Z.cpp \
	Engine/Main_Z.cpp \
	Engine/Manipulator_Z.cpp \
	Engine/Material_Z.cpp \
	Engine/MaterialAnim_Z.cpp \
	Engine/MaterialManager_Z.cpp \
	Engine/Memory_Z.cpp \
	Engine/Menu_Z.cpp \
	Engine/Mesh_Z.cpp \
	Engine/MeshCollision_Z.cpp \
	Engine/MeshDraw_Z.cpp \
	Engine/MetaFile_Z.cpp \
	Engine/MovieManipulator_Z.cpp \
	Engine/MovingAgent_Z.cpp \
	Engine/Name_Z.cpp \
	Engine/Node_Z.cpp \
	Engine/Object_Z.cpp \
	Engine/ObjectGame_Z.cpp \
	Engine/ObjectMove_Z.cpp \
	Engine/ObjectsBounce_Z.cpp \
	Engine/ObjectsBreak_Z.cpp \
	Engine/ObjectsGame_Z.cpp \
	Engine/ObjectsGameClip_Z.cpp \
	Engine/ObjectsGameSkelCol_Z.cpp \
	Engine/ObjectsMove_Z.cpp \
	Engine/ObjectThrow_Z.cpp \
	Engine/OccludedSeadHandle_Z.cpp \
	Engine/Omni_Z.cpp \
	Engine/Pack_Z.cpp \
	Engine/Parameters_Z.cpp \
	Engine/Particles_Z.cpp \
	Engine/ParticlesAgent_Z.cpp \
	Engine/ParticlesDraw_Z.cpp \
	Engine/PhysAgent_Z.cpp \
	Engine/PhysicObj_Z.cpp \
	Engine/PhysicWorld_Z.cpp \
	Engine/PlayAnim_Z.cpp \
	Engine/PlayParticles_Z.cpp \
	Engine/PopupMenu_Z.cpp \
	Engine/Private/AnimationCamera_Z.cpp \
	Engine/Private/AnimationLoad_Z.cpp \
	Engine/Private/AnimationManager_Z.cpp \
	Engine/Private/AnimationMaterial_Z.cpp \
	Engine/Private/AnimationMorph_Z.cpp \
	Engine/Private/AnimationNode_Z.cpp \
	Engine/Private/AnimationOmni_Z.cpp \
	Engine/Private/AnimFrameLoad_Z.cpp \
	Engine/Private/BigFileManager_Z.cpp \
	Engine/Private/BitmapLoad_Z.cpp \
	Engine/Private/CameraDraw_Z.cpp \
	Engine/Private/CameraZoneDraw_Z.cpp \
	Engine/Private/CameraZoneLoad_Z.cpp \
	Engine/Private/ClassManager_Z.cpp \
	Engine/Private/CollisionTool_Z.cpp \
	Engine/Private/CollisionVolDraw_Z.cpp \
	Engine/Private/CollisionVolLoad_Z.cpp \
	Engine/Private/DynamicAnim_Z.cpp \
	Engine/Private/EffectManager_Z.cpp \
	Engine/Private/Emitter_Z.cpp \
	Engine/Private/File_Z.cpp \
	Engine/Private/FileDraw_Z.cpp \
	Engine/Private/Ghost_Z.cpp \
	Engine/Private/HFieldCache_Z.cpp \
	Engine/Private/HFogDraw_Z.cpp \
	Engine/Private/HFogLoad_Z.cpp \
	Engine/Private/Keyframer_Z.cpp \
	Engine/Private/KeyframerLoad_Z.cpp \
	Engine/Private/KeyframerValue_Z.cpp \
	Engine/Private/LightDraw_Z.cpp \
	Engine/Private/LightLoad_Z.cpp \
	Engine/Private/LodDraw_Z.cpp \
	Engine/Private/LodLighting_Z.cpp \
	Engine/Private/LodLoad_Z.cpp \
	Engine/Private/LodMoveColl_Z.cpp \
	Engine/Private/MaterialAnimLoad_Z.cpp \
	Engine/Private/MaterialLoad_Z.cpp \
	Engine/Private/MaterialObj_Z.cpp \
	Engine/Private/Matrix_Z.cpp \
	Engine/Private/MatrixCache_Z.cpp \
	Engine/Private/MeshCollisionTools_Z.cpp \
	Engine/Private/MeshLoad_Z.cpp \
	Engine/Private/MeshMorpherLoad_Z.cpp \
	Engine/Private/MeshVolume_Z.cpp \
	Engine/Private/MeshVolumeLoad_Z.cpp \
	Engine/Private/Movie_Z.cpp \
	Engine/Private/NodeLoad_Z.cpp \
	Engine/Private/ObjectBankManager_Z.cpp \
	Engine/Private/ObjectCollision_Z.cpp \
	Engine/Private/ObjectMove_Z.cpp \
	Engine/Private/ObjectsBreak_Z.cpp \
	Engine/Private/ObjectsMove_Z.cpp \
	Engine/Private/ObjectThrow_Z.cpp \
	Engine/Private/Occluder_Z.cpp \
	Engine/Private/Omni_Z.cpp \
	Engine/Private/Particles_Z.cpp \
	Engine/Private/Points_Z.cpp \
	Engine/Private/PointsLoad_Z.cpp \
	Engine/Private/Random_Z.cpp \
	Engine/Private/Renderer_Z.cpp \
	Engine/Private/RendererPrimitiveBuffers_Z.cpp \
	Engine/Private/ResourceObject_Z.cpp \
	Engine/Private/RotShapeLoad_Z.cpp \
	Engine/Private/Rtc_Z.cpp \
	Engine/Private/RtcAnimationNode_Z.cpp \
	Engine/Private/RtcLoad_Z.cpp \
	Engine/Private/RtcPlayer_Z.cpp \
	Engine/Private/SelfRunning_Z.cpp \
	Engine/Private/SkelLoad_Z.cpp \
	Engine/Private/SkinColl_Z.cpp \
	Engine/Private/SkinDraw_Z.cpp \
	Engine/Private/SkinLoad_Z.cpp \
	Engine/Private/Sound_Z.cpp \
	Engine/Private/SoundLoad_Z.cpp \
	Engine/Private/SplineDraw_Z.cpp \
	Engine/Private/SplineLoad_Z.cpp \
	Engine/Private/SplineZoneDraw_Z.cpp \
	Engine/Private/SplineZoneLoad_Z.cpp \
	Engine/Private/StreamFile_Z.cpp \
	Engine/Private/StreamManager_Z.cpp \
	Engine/Private/String_Z.cpp \
	Engine/Private/Surface_Z.cpp \
	Engine/Private/SurfaceColl_Z.cpp \
	Engine/Private/SurfaceLoad_Z.cpp \
	Engine/Private/Sys_Z.cpp \
	Engine/Private/Txt_Z.cpp \
	Engine/Private/Viewport_Z.cpp \
	Engine/Private/WarpLoad_Z.cpp \
	Engine/Private/WorldDraw_Z.cpp \
	Engine/Private/WorldLoad_Z.cpp \
	Engine/RotShape_Z.cpp \
	Engine/RotShapeDraw_Z.cpp \
	Engine/RtcAgent_Z.cpp \
	Engine/Scattering.cpp \
	Engine/Sead_Z.cpp \
	Engine/SeadIndex_Z.cpp \
	Engine/SequenceAnim_Z.cpp \
	Engine/SequenceMixAnim_Z.cpp \
	Engine/Skel_Z.cpp \
	Engine/SkelColl_Z.cpp \
	Engine/Skin_Z.cpp \
	Engine/SkinAgent_Z.cpp \
	Engine/SoundManager_Z.cpp \
	Engine/Spline_Z.cpp \
	Engine/SplineZone_Z.cpp \
	Engine/StreamAgent_Z.cpp \
	Engine/SubLevelVolumeAgent_Z.cpp \
	Engine/SubWorld_Z.cpp \
	Engine/SubWorldLeaf_Z.cpp \
	Engine/SuperSpray_Z.cpp \
	Engine/SuperSprayParticles_Z.cpp \
	Engine/SurfaceCollision_Z.cpp \
	Engine/SystemDatas_Z.cpp \
	Engine/Throwable_Z.cpp \
	Engine/Tokenizer_Z.cpp \
	Engine/UnPack_Z.cpp \
	Engine/UserDefine_Z.cpp \
	Engine/VehiculeMove_Z.cpp \
	Engine/VolatileMgr_Z.cpp \
	Engine/VolumeAgent_Z.cpp \
	Engine/Warp_Z.cpp \
	Engine/WaterHeightMap_Z.cpp \
	Engine/World_Z.cpp \
	Engine/WorldAnim_Z.cpp \
	Engine/WorldCollision_Z.cpp \
	Engine/WorldData_Z.cpp \
	Engine/WorldLighting_Z.cpp \
	Wall_E/BackGlobalInGameData_G.cpp \
	Wall_E/BaseAgent_G.cpp \
	Wall_E/CameraInterpol_G.cpp \
	Wall_E/CharsData_G.cpp \
	Wall_E/CreaturesBoneManip.cpp \
	Wall_E/CreaturesJump_G.cpp \
	Wall_E/CreaturesMove_G.cpp \
	Wall_E/CreaturesPipe_G.cpp \
	Wall_E/CreaturesRun_G.cpp \
	Wall_E/CreaturesState_G.cpp \
	Wall_E/CreaturesStatesMachine_G.cpp \
	Wall_E/CreaturesWait_G.cpp \
	Wall_E/CubeStateMove_G.cpp \
	Wall_E/DetectVolumeAgent_G.cpp \
	Wall_E/Dialog_G.cpp \
	Wall_E/Dialog_InfosText.cpp \
	Wall_E/Dialog_LifeGauge.cpp \
	Wall_E/Dialog_MC_Base.cpp \
	Wall_E/Dialog_Minimap.cpp \
	Wall_E/Dialog_Timer.cpp \
	Wall_E/DialogGroup_G.cpp \
	Wall_E/DialogInGame_G.cpp \
	Wall_E/DialogMenu_G.cpp \
	Wall_E/Dialogs_Credits.cpp \
	Wall_E/Dialogs_MainMenu.cpp \
	Wall_E/Dialogs_Pause.cpp \
	Wall_E/Dialogs_Popup.cpp \
	Wall_E/DummyEnemies.cpp \
	Wall_E/DummyGen.cpp \
	Wall_E/DummyGenerator_G.cpp \
	Wall_E/EndMissionVolumeAgent_G.cpp \
	Wall_E/Enemies_G.cpp \
	Wall_E/EnemyState_G.cpp \
	Wall_E/EvenementVolAgent_G.cpp \
	Wall_E/FadeManager_G.cpp \
	Wall_E/FootPrints_G.cpp \
	Wall_E/FrontGlobalInGameData_G.cpp \
	Wall_E/FXVolumeAgent_G.cpp \
	Wall_E/Game_ParticleMgr.cpp \
	Wall_E/Game_SoundMgr.cpp \
	Wall_E/GameLogicAgent_G.cpp \
	Wall_E/GameMgr_G.cpp \
	Wall_E/GUI/Event.cpp \
	Wall_E/GUI/GuiAnimations_G.cpp \
	Wall_E/GUI/LogicComponents/Bitmap_G.cpp \
	Wall_E/GUI/LogicComponents/Box_G.cpp \
	Wall_E/GUI/LogicComponents/ButtonBase_G.cpp \
	Wall_E/GUI/LogicComponents/Checkbox_G.cpp \
	Wall_E/GUI/LogicComponents/DynTextPushButton_G.cpp \
	Wall_E/GUI/LogicComponents/Frame_G.cpp \
	Wall_E/GUI/LogicComponents/Gauge_G.cpp \
	Wall_E/GUI/LogicComponents/LockButton_G.cpp \
	Wall_E/GUI/LogicComponents/PushButton_G.cpp \
	Wall_E/GUI/LogicComponents/RadioButton_G.cpp \
	Wall_E/GUI/LogicComponents/StaticText_G.cpp \
	Wall_E/GUI/LogicComponents/Window_G.cpp \
	Wall_E/Horatio.cpp \
	Wall_E/ImpactVolumeAgent_G.cpp \
	Wall_E/InGameCreatures_G.cpp \
	Wall_E/InGameFX_G.cpp \
	Wall_E/InGamePlayer_G.cpp \
	Wall_E/InGameSounds_G.cpp \
	Wall_E/InputDef_G.cpp \
	Wall_E/International.cpp \
	Wall_E/IsToBePlayed.cpp \
	Wall_E/IT_Bumper.cpp \
	Wall_E/IT_CollectMove_G.cpp \
	Wall_E/IT_Condition.cpp \
	Wall_E/IT_Dyn_WallE_G.cpp \
	Wall_E/IT_Dyn_WallEMove_G.cpp \
	Wall_E/IT_DynObj_G.cpp \
	Wall_E/IT_DynObjMove_G.cpp \
	Wall_E/IT_SOUND.cpp \
	Wall_E/IT_Stone_G.cpp \
	Wall_E/IT_SWITCH_G.cpp \
	Wall_E/ItemMgr_G.cpp \
	Wall_E/Language.cpp \
	Wall_E/Laser_G.cpp \
	Wall_E/LevelAdvancement_G.cpp \
	Wall_E/LevelAgent_G.cpp \
	Wall_E/LevelData_G.cpp \
	Wall_E/LevelManipulator_G.cpp \
	Wall_E/LevelMenu_G.cpp \
	Wall_E/LightVolumeAgent_G.cpp \
	Wall_E/LiquidFlow_G.cpp \
	Wall_E/LoadingDraw_C.cpp \
	Wall_E/LogicAgent_G.cpp \
	Wall_E/MapVolumeAgent_G.cpp \
	Wall_E/MemoryCardManager_C.cpp \
	Wall_E/Menu3D.cpp \
	Wall_E/MenuManager_G.cpp \
	Wall_E/MenuParser.cpp \
	Wall_E/MenuPerspective.cpp \
	Wall_E/Mission_Checkerboard.cpp \
	Wall_E/Mission_Collect.cpp \
	Wall_E/Mission_Container.cpp \
	Wall_E/Mission_Example.cpp \
	Wall_E/Mission_Global.cpp \
	Wall_E/Mission_Memory.cpp \
	Wall_E/Mission_MultiTemplate_G.cpp \
	Wall_E/Mission_Simon.cpp \
	Wall_E/Mission_SquareShooting.cpp \
	Wall_E/Mission_Switch.cpp \
	Wall_E/MissionInfo_G.cpp \
	Wall_E/MissionManager_G.cpp \
	Wall_E/MissionTemplate_G.cpp \
	Wall_E/MissionTemplateCondition_G.cpp \
	Wall_E/MissionTemplateTheBoringStuff_G.cpp \
	Wall_E/MissionTemplateVolume_G.cpp \
	Wall_E/MissionVolumeAgent_G.cpp \
	Wall_E/Multiplayer.cpp \
	Wall_E/MusicManager_G.cpp \
	Wall_E/NodeSmooth.cpp \
	Wall_E/NodeVolumeAgent_G.cpp \
	Wall_E/ObjectAgent_G.cpp \
	Wall_E/PaddleChecker_G.cpp \
	Wall_E/PermanentDraw_G.cpp \
	Wall_E/PersoLight_G.cpp \
	Wall_E/PhysicItem.cpp \
	Wall_E/PhysicObj_G.cpp \
	Wall_E/Player_G.cpp \
	Wall_E/PlayerMove_G.cpp \
	Wall_E/PointJump_G.cpp \
	Wall_E/ProGroundMgr_G.cpp \
	Wall_E/Purchase.cpp \
	Wall_E/PurchaseCheat.cpp \
	Wall_E/Ropes_G.cpp \
	Wall_E/RTCManager_G.cpp \
	Wall_E/RtcScriptAgent_G.cpp \
	Wall_E/RTCScripted_G.cpp \
	Wall_E/RTCScriptInstruction.cpp \
	Wall_E/SaveVolumeAgent_G.cpp \
	Wall_E/Script_G.cpp \
	Wall_E/ScriptManager_G.cpp \
	Wall_E/Shop.cpp \
	Wall_E/ShowerVolumeAgent_G.cpp \
	Wall_E/StatesMachine_G.cpp \
	Wall_E/StateTemplate_G.cpp \
	Wall_E/StreamGameAgent_G.cpp \
	Wall_E/TextGameDraw_G.cpp \
	Wall_E/ThrownMove_G.cpp \
	Wall_E/UnLock_G.cpp \
	Wall_E/UserCommand_G.cpp \
	Wall_E/VibrationManager_C.cpp \
	Wall_E/VolumeDelayedStart_G.cpp \
	Wall_E/VolumeDelayedStartMove_G.cpp \
	Wall_E/VolumeRTC_G.cpp \
	Wall_E/VolumeRTCMove_G.cpp \
	Wall_E/CreaturesCube_G.cpp \
	Wall_E/Creatures_G.cpp \
	Wall_E/CreaturesWTF_G.cpp \
	Wall_E/CameraChase.cpp \
	Wall_E/BaseInGameDatas_G.cpp \
	Wall_E/Classes.cpp \
	Wall_E/ScriptManager_G.cpp \
	Wall_E/AutoCompletion_G.cpp \
	Wall_E/BaseInGame3D.cpp \
	Wall_E/IT_COLLECT_G.cpp \
	Wall_E/CheckpointVolAgent_G.cpp \
	Wall_E/Spline_G.cpp \
	Wall_E/ChangeLevelVolumeAgent_G.cpp \
	Wall_E/CreaturesDynState_G.cpp \
	Wall_E/ActionHelper_G.cpp \
	Engine/Private/Tree_Z.cpp \
	Wall_E/CommandStatesMachine_G.cpp \
	Wall_E/CommandStateTemplate_G.cpp \
	Wall_E/CameraAgent_G.cpp \
	Wall_E/CameraMove_G.cpp \
	Wall_E/CameraMoveClass_G.cpp \
	Wall_E/CameraMoveRTC_G.cpp \
	Wall_E/CameraMoveSpline_G.cpp \
	Wall_E/Dialog_BoxGauge.cpp \
	Wall_E/Dialog_Collect.cpp \
	Wall_E/Dialog_EnergyCollect.cpp \
	Wall_E/Dialog_FirstPersonView.cpp \
	Wall_E/IT_Gauge_G.cpp \
	Wall_E/IT_JunkGenerator_G.cpp \
	Wall_E/IT_Shower_G.cpp \
	Wall_E/BufferPack_G.cpp \
	Wall_E/BufferSave_G.cpp  \
	Wall_E/BuyableVolumeAgent_G.cpp  \
	Wall_E/Dialog_EnterProfileName.cpp  \
	Wall_E/Dialog_LaserGauge.cpp \
	Wall_E/Dialog_LegalText.cpp  \
	Wall_E/Dialog_MainMenuFirst.cpp  \
	Wall_E/IT_BNLMove_G.cpp \
	Wall_E/IT_BNL_G.cpp \
	Wall_E/Dialog_TargetEnemy.cpp \
	Wall_E/Explosion_G.cpp \
	Wall_E/ExplosionLightning_G.cpp \
	Wall_E/GUI/LogicComponents/HGauge_G.cpp \
	Wall_E/GUI/LogicComponents/VGauge_G.cpp \
	Wall_E/CreaturesHit_G.cpp \
	Wall_E/CreaturesWeird_G.cpp \
	Wall_E/Dialog_PressStart.cpp \
	Wall_E/Dialog_Trame.cpp \
	Engine/Private/MetaStreamFile_Z.cpp \
	Wall_E/CreaturesEve_G.cpp \
	Wall_E/CreaturesMoveLinkedObjs_G.cpp \
	Wall_E/DarkZoneMove_G.cpp \
	Wall_E/DarkZoneVolumeAgent_G.cpp \
	Wall_E/Dialog_AimCrosshair.cpp \
	Wall_E/Dialog_AimDirection.cpp \
	Wall_E/Dialog_ArtifactCollect.cpp \
	Wall_E/Dialog_Delete.cpp \
	Wall_E/Dialog_EnterPlayerName.cpp \
	Wall_E/Dialog_EveCollect.cpp \
	Wall_E/Dialog_InputString.cpp \
	Wall_E/Dialog_LaserTarget.cpp \
	Wall_E/Dialog_Load.cpp \
	Wall_E/Dialog_MissionFailed.cpp \
	Wall_E/Dialog_MissionSuccess.cpp \
	Wall_E/Dialog_MultiCollect.cpp \
	Wall_E/Dialog_MultiMiniGame.cpp \
	Wall_E/Dialog_MultiRace.cpp \
	Wall_E/Dialog_MultiResistance.cpp \
	Wall_E/Dialog_MultiSuccess.cpp \
	Wall_E/Dialog_Options.cpp \
	Wall_E/Dialog_OptionsGame.cpp \
	Wall_E/Dialog_OptionsMain.cpp \
	Wall_E/Dialog_OptionsSound.cpp \
	Wall_E/Dialog_OptionsVideo.cpp \
	Wall_E/Dialog_Profiles.cpp \
	Wall_E/Dialog_StartLang.cpp \
	Wall_E/DialogTarget.cpp \
	Wall_E/ExtrasParser.cpp \
	Wall_E/FakeMagnetismVolumeAgent_G.cpp \
	Wall_E/FrogComponentAgent_G.cpp \
	Wall_E/FrogComponentSpline_G.cpp \
	Wall_E/FrogPlayer_G.cpp \
	Wall_E/FrogPlayerMoveMgr_G.cpp \
	Wall_E/IT_CheckbColorAgent_G.cpp \
	Wall_E/IT_Dyn_EveMove_G.cpp \
	Wall_E/IT_DynCube_WallEMove_G.cpp \
	Wall_E/IT_LaserCutManager_G.cpp \
	Wall_E/IT_MsgAnimatedAgent_G.cpp \
	Wall_E/IT_Target_G.cpp \
	Wall_E/LevelEvent_G.cpp \
	Wall_E/LevelEventBreak.cpp \
	Wall_E/LevelEventBuyableVolume.cpp \
	Wall_E/LevelEventCollect.cpp \
	Wall_E/LevelEventCube.cpp \
	Wall_E/LevelEventEnemy.cpp \
	Wall_E/LevelEventFakeMagnetism.cpp \
	Wall_E/LevelEventStack_G.cpp \
	Wall_E/Mission_AllArtefacts.cpp \
	Wall_E/Mission_AllBnlCoins.cpp \
	Wall_E/Mission_Baja.cpp \
	Wall_E/Mission_BnlCoins.cpp \
	Wall_E/Mission_Chrono.cpp \
	Wall_E/Mission_CollectEve.cpp \
	Wall_E/Mission_CubeVolume.cpp \
	Wall_E/Mission_Descent.cpp \
	Wall_E/Mission_Enemy.cpp \
	Wall_E/Mission_Follow.cpp \
	Wall_E/Mission_Frog.cpp \
	Wall_E/Mission_Goffer.cpp \
	Wall_E/Mission_LaserCut.cpp \
	Wall_E/Mission_Machine_G.cpp \
	Wall_E/Mission_MiniGame.cpp \
	Wall_E/Mission_MultiCollect.cpp \
	Wall_E/Mission_MultiFrog.cpp \
	Wall_E/Mission_MultiRace.cpp \
	Wall_E/Mission_MultiResistance.cpp \
	Wall_E/Mission_Preart.cpp \
	Wall_E/Mission_Resistance.cpp \
	Wall_E/Mission_Sensitive.cpp \
	Wall_E/Mission_ShootChase.cpp \
	Wall_E/Mission_Slot.cpp \
	Wall_E/Mission_Speedway.cpp \
	Wall_E/SaveStructs_G.cpp \
	Wall_E/GUI/WindowHierarchy_G.cpp \
	Wall_E/GUI/LogicComponents/BitmapPushButton_G.cpp \
	Wall_E/GUI/LogicComponents/ListBox_G.cpp \
	Wall_E/GUI/LogicComponents/ScrollBar_G.cpp \
	Wall_E/GUI/LogicComponents/VScrollBar_G.cpp  \
	Wall_E/Dialog_MC_Base_PC.cpp \
	Wall_E/GUI/WallEComponents/WE_VScrollBar_G.cpp \
	Wall_E/Dialog_Artifacts.cpp \
	Wall_E/Dialog_Bonus.cpp \
	Wall_E/Dialog_Cheats.cpp \
	Wall_E/Dialog_Shop.cpp \
	Engine/Private/VertexBufferExtLoad_Z.cpp \
	Engine/Private/IndexBufferExtLoad_Z.cpp  \
	Engine/Private/MeshBuffersLoad_Z.cpp \
	Wall_E/CheatManager_G.cpp \
	Wall_E/Dialog_BoostPlayer.cpp  \
	Wall_E/Dialog_ChangeLevel.cpp \
	Wall_E/Dialog_ChangeLevelCategory.cpp \
	Wall_E/Dialog_MenuMultiCrossing.cpp \
	Wall_E/Dialog_MenuMultiPlantCollect.cpp \
	Wall_E/Dialog_MenuMultiRaces.cpp \
	Wall_E/Dialog_MenuMultiResistance.cpp \
	Wall_E/Dialog_MenuMultiSpeedWays.cpp \
	Wall_E/Dialog_MissionListing.cpp \
	Wall_E/Dialog_MsgBox.cpp \
	Wall_E/Dialog_Pause.cpp \
	Wall_E/Dialog_WrongWay.cpp \
	Wall_E/IT_DynObjCube_G.cpp \
	Wall_E/IT_DynObjCubeMove_G.cpp \
	Wall_E/LevelEventDynObj.cpp \
	Wall_E/Teleport_G.cpp \
	Wall_E/WakePhysicUpVolume_G.cpp \
	Wall_E/Dialog_Championship.cpp \
	Wall_E/Dialog_Championships.cpp \
	Wall_E/Dialog_EndChampionship.cpp \
	Wall_E/Dialog_InfoMission.cpp \
	Wall_E/Dialog_InGameMap.cpp \
	Wall_E/Dialog_MenuChampCheckerboard.cpp \
	Wall_E/Dialog_MenuChampCombo.cpp \
	Wall_E/Dialog_MenuChampDescend.cpp \
	Wall_E/Dialog_MenuChampSpeedWay.cpp \
	Wall_E/Dialog_MissionListingSoloMulti.cpp \
	Wall_E/Dialog_MultiMiniGames.cpp \
	Wall_E/Dialog_Music.cpp \
	Wall_E/Dialog_NextPlayer.cpp \
	Wall_E/Dialog_NextRound.cpp \
	Wall_E/Dialog_Tutorial.cpp \
	Wall_E/Dialog_VirtualPad.cpp \
	Wall_E/IT_ObjectPath_G.cpp \
	Wall_E/MovingPosition_G.cpp \
	Wall_E/SunBeamVolumeAgent_G.cpp \
	Engine/Endian_Z.cpp \
	Engine/MemoryBank_Z.cpp \
	Engine/MemoryBlock_Z.cpp \
	Wall_E/GUI/LogicComponents/NumericUpDown_G.cpp \
	Wall_E/Blink_G.cpp \
	Wall_E/BreakObject_G.cpp \
	Wall_E/CreaturesRun2_G.cpp \
	Wall_E/Dialog_BluePrints.cpp \
	Wall_E/Dialog_MiniGames.cpp \
	Wall_E/Dialog_MultiTarget.cpp \
	Wall_E/Dialog_PlayerCountChoice.cpp \
	Wall_E/Dialog_RotatingListHelper.cpp \
	Wall_E/Dialog_RoundCountChoice.cpp \
	Wall_E/EnemiesStates.cpp \
	Wall_E/Gopher.cpp \
	Wall_E/IT_BNLCounter_G.cpp \
	Wall_E/IT_Dyn_Break_G.cpp \
	Wall_E/IT_Dyn_BreakMove_G.cpp \
	Wall_E/IT_ResistanceBreak_G.cpp \
	Wall_E/IT_StdBreak_G.cpp \
	Wall_E/IT_Tools_G.cpp \
	Wall_E/Mission_AllBreak.cpp \
	Wall_E/Mission_Break.cpp \
	Wall_E/Mission_Buyable.cpp \
	Wall_E/Mo.cpp \
	Wall_E/Scope.cpp \
	Wall_E/Steward.cpp \
	Wall_E/UnlockVolumeAgent_G.cpp \
	Wall_E/UnlockVolumeMove_G.cpp \
	Wall_E/GUI/LogicComponents/Movie_G.cpp  \
	Wall_E/GUI/LogicComponents/RotatingList_G.cpp  \
	Wall_E/GUI/GuiLinearAnimation_G.cpp  \
	Wall_E/GUI/GuiSmoothAnimation_G.cpp \
	Engine/Binary_Z.cpp \
	Wall_E/Action_G.cpp \
	Wall_E/GUI/LogicComponents/LockCheckbox_G.cpp \
	Wall_E/Dialog_ExtraMaterials.cpp \
	Wall_E/CreaturesFall_G.cpp \
	Wall_E/Dialog_IGOptionsGame.cpp \
	Wall_E/Dialog_IGOptionsMain.cpp \
	Wall_E/Dialog_IGOptionsSound.cpp \
	Wall_E/Dialog_IGOptionsVideo.cpp \
	Wall_E/IT_CheckbColorMove_G.cpp \
	Wall_E/Artefact_G.cpp \
	Wall_E/Dialog_BreakCollect.cpp \
	Wall_E/Dialog_CountDown.cpp \
	Wall_E/Dialog_RegenGauge.cpp \
	Wall_E/IT_GeneratedCollect_G.cpp \
	Wall_E/IT_SavedObjects.cpp \
	Wall_E/LevelEventSavedObjects.cpp \
	Wall_E/Dialog_IGDelete.cpp \
	Wall_E/Dialog_MissionSumUp.cpp \
	Wall_E/Dialog_Rewards.cpp \
	Wall_E/Dialog_SaveAdvancement.cpp \
	Wall_E/MaterialLibHelper_G.cpp \
	Wall_E/Mission_AllLevelArtefact.cpp \
	Wall_E/Mission_Artefact.cpp \
	Wall_E/Mission_Casino.cpp \
	Wall_E/Mission_CollectPlant.cpp \
	Wall_E/Satellite.cpp \
	Wall_E/ScriptManagerEnergy_G.cpp \
	Wall_E/ScriptManagerUserCommand_G.cpp  \
	Wall_E/ScriptManagerUserMisc_G.cpp \
	Wall_E/Appear.cpp \
	Engine/GlobalVarMgr_Z.cpp \
	Wall_E/GUI/LogicComponents/Counter_G.cpp \
	Wall_E/Chapter_G.cpp \
	Wall_E/Dialog_ChangeChapter.cpp \
	Wall_E/Dialog_MapHelper.cpp \
	Wall_E/Dialog_MissionsHelper.cpp \
	Engine/Mat3x3_Z.cpp \
	Engine/Mat4x4_Z.cpp \
	Engine/Quat_Z.cpp \
	Engine/UserDefineCmd_Z.cpp \
	Engine/Vec2f_Z.cpp \
	Engine/Vec3f_Z.cpp \
	Engine/Vec4f_Z.cpp \
	Wall_E/CheckerCell.cpp \
	Wall_E/Dialog_AdjustScreen.cpp \
	Wall_E/Dialog_AllArtifacts.cpp \
	Wall_E/Dialog_AllBreak.cpp \
	Wall_E/Dialog_ControlsDescend.cpp \
	Wall_E/Dialog_ControlsSpeed.cpp \
	Wall_E/Dialog_EveBoost.cpp \
	Wall_E/Dialog_MenuOptionsVideo.cpp \
	Wall_E/CreaturesMoveOmni_G.cpp \
	Wall_E/Dialog_RaceNumber.cpp \
	Wall_E/CheckerAnim_G.cpp \
	Wall_E/CheckerLamp.cpp \
	Wall_E/Dialog_CheatsMain.cpp \
	Wall_E/Dialog_Controls.cpp \
	Wall_E/Dialog_EndChapter.cpp \
	Wall_E/Dialog_EveLifeGauge.cpp \
	Wall_E/Dialog_Result.cpp \
	Wall_E/Dialog_ScreenFormatChoice.cpp \
	Wall_E/Dialog_StoryMissionSuccess.cpp \
	Wall_E/Dialog_ViewImage.cpp \
	Wall_E/Dialog_ViewMovie.cpp \
	Wall_E/Dialog_WalleLifeGauge.cpp \
	Wall_E/EnemiesObject_G.cpp \
	Wall_E/Mission_Spirou.cpp \
	Wall_E/Mission_TigPlay.cpp \
	Wall_E/GUI/WallEComponents/WE_ChapterButton_G.cpp \
	Wall_E/GUI/WallEComponents/WE_ChapterPreview_G.cpp \
	Wall_E/GUI/LogicComponents/PreviewList_G.cpp \
	Wall_E/CheckerComponent_G.cpp \
	Wall_E/Dialog_ContextualAction.cpp \
	Wall_E/DefibBot.cpp \
	Wall_E/EnemiesStatesSight.cpp \
	Wall_E/LightBot.cpp \
	Wall_E/MouseBot.cpp \
	Wall_E/ObjectOnPath_G.cpp \
	Wall_E/ObjectResistance_G.cpp \
	Wall_E/RejectedStates.cpp \
	Wall_E/ResistanceStep_G.cpp \
	Wall_E/StoryMovie.cpp \
	Wall_E/StoryMovieManager.cpp \
	Wall_E/Tornado.cpp \
	Wall_E/TraceDraw_G.cpp \
	Wall_E/Trajectory_G.cpp \
	Wall_E/UmbrellaBot.cpp \
	Wall_E/VacuumBot.cpp \
	Wall_E/Mission_MultiContainer.cpp \
	Engine/PackerArith_Z.cpp \
	Engine/ArithmeticCoderC.cpp \
	Engine/ModelOrder0C.cpp  \
	Engine/ModelOrder1C.cpp \
	Engine/PackerArith_Z.cpp \
	Engine/PackerModel.cpp  \
	Engine/ProbaTable.cpp \
	Wall_E/MassageBot.cpp \
	Wall_E/Checkerboard_G.cpp \
	Wall_E/ColorAndOmni_G.cpp \
	Wall_E/Dialog_PlayerTitle.cpp \
	Wall_E/Dialog_WaitPlayer.cpp \
	Wall_E/CreaturesMoveColl_G.cpp \
	Wall_E/Dialog_Vignetage.cpp \
	Wall_E/OptimVolumeAgent_G.cpp \
	Wall_E/Dialog_Baja.cpp \
	Wall_E/Dialog_SavedGames.cpp \
	Wall_E/Dialog_PGCrates.cpp \
	Wall_E/IT_Debris_G.cpp \
	Wall_E/Dialog_FinishMenu.cpp \
	Wall_E/WayPath_G.cpp \
	Wall_E/Dialog_PCControls.cpp \
	Wall_E/GUI/WallEComponents/WE_KeyInfos_G.cpp \
	Wall_E/Dialog_TrailerMovies.cpp \
	Wall_E/Dialog_SplashScreen.cpp \
	Wall_E/Dialog_Overwrite.cpp \
	Wall_E/Dialog_ControlsShoot.cpp \
	Wall_E/Dialog_ControlsFrog.cpp \
	Wall_E/Dialog_ControlsHTHRace.cpp \
	Wall_E/Dialog_ControlsHTHShoot.cpp \
	Wall_E/Dialog_ControlsSpeedBonus.cpp \
	Wall_E/Dialog_ControlsBonusCheck.cpp \
	Wall_E/Dialog_ControlsBonusDescent.cpp
HEADERS = $(wildcard *.h *.hpp Engine/includes/*.h Engine/includes/*.hpp LibMAC/HID_Util/*.h LibMAC/HID_Util/*.hpp LibMAC/tinyxml/*.h LibMAC/tinyxml/*.hpp LibMAC/includes/*.h LibMAC/includes/*.hpp)
ENGINE_CXXOBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(ENGINE_CXXSRC)))
ENGINE_ASMOBJS = $(patsubst %.c,%.s,$(patsubst %.cpp,%.s,$(ENGINE_CXXSRC)))

.PHONY: all
all: objects

LibMAC/HID_Util/%.o: LibMAC/HID_Util/%.c $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS) 2> /dev/null # shut the fuck up
	
%.o: %.cpp $(HEADERS)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

LibMAC/HID_Util/%.s: LibMAC/HID_Util/%.c $(HEADERS)
	$(CXX) -c $< -S -o $@ $(CXXFLAGS) 2> /dev/null # shut the fuck up

%.s: %.cpp $(HEADERS)
	$(CXX) -c $< -S -o $@ $(CXXFLAGS)


ZOUNA: $(ENGINE_CXXOBJS) $(ENGINE_ASMOBJS)
	g++ $(ENGINE_CXXOBJS) -framework Carbon -framework IOKit -o ZOUNA.executable
	strip -o ZOUNA.stripped.executable -x ZOUNA.executable

objects: ZOUNA
