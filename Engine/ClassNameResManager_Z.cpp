/*
ClassNameResManager_Z::GetObjectInClass(long,long)	__text	0003F5DA	00000066	0000002C	00000010	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::RemoveClassId(long)	__text	0003F640	0000005B	0000002C	00000008	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::Minimize(void)	__text	0003F69C	00000088	0000001C	00000004	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::Shut(void)	__text	0003F724	0000007B	0000001C	00000004	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::GetClassID(Name_Z const&,Name_Z const&,long &,bool)	__text	0003F7A0	000000BF	0000004C	00000011	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::RemoveClassId(Name_Z const&,Name_Z const&)	__text	0003F860	00000048	0000003C	0000000C	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::MarkHandlesFromClass(Name_Z const&,Name_Z const&)	__text	0003F8A8	0000004A	0000003C	0000000C	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::UpdateLinks(Name_Z const&,Name_Z const&)	__text	0003F8F2	0000004A	0000003C	0000000C	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::Load(Name_Z const&,Name_Z const&,void **)	__text	0003F93C	0000004D	0000003C	00000010	R	.	.	.	.	.	B	T	.
ClassNameResManager_Z::MarkHandles(void)	__text	0003F98A	00000072	0000001C	00000004	R	.	.	.	.	.	B	T	.
*/

#include <ClassNameResManager_Z.h>
#include <Sys_Z.h>
#include <Program_Z.h>

void ClassNameResManager_Z::Shut() {
    m_ClassHT.Flush();

    for (S32 i = m_ClassResHA.FindFirst(); i >= 0; i = m_ClassResHA.FindNext(i)) {
        m_ClassResHA[i].Flush();
    }
}

void ClassNameResManager_Z::Load(const Name_Z& i_Name, const Name_Z& i_FileName, void** i_Data) {
    S32 l_ClassID;
    GetClassID(i_Name, i_FileName, l_ClassID);
    m_ClassResHA[l_ClassID].Load(i_Data);
}

void ClassNameResManager_Z::UpdateLinks(const Name_Z& i_Name, const Name_Z& i_FileName) {
    S32 l_ClassID;
    GetClassID(i_Name, i_FileName, l_ClassID);
    m_ClassResHA[l_ClassID].UpdateLinks();
}

Bool ClassNameResManager_Z::GetClassID(const Name_Z& i_Name, const Name_Z& i_FileName, S32& o_ClassID, bool i_AddClass) {
    o_ClassID = m_ClassResHA.FindFirst();

    while (o_ClassID >= 0) {
        if (i_Name == m_ClassResHA[o_ClassID].m_Name && i_FileName == m_ClassResHA.Get((U32)o_ClassID).m_FileName) {
            return TRUE;
        }

        o_ClassID = m_ClassResHA.FindNext(o_ClassID);
    }

    if (i_AddClass) {
        o_ClassID = m_ClassResHA.Add();
        m_ClassResHA[o_ClassID].m_Name = i_Name;
        m_ClassResHA[o_ClassID].m_FileName = i_FileName;
    }

    return FALSE;
}

Bool ClassNameResManager_Z::MarkHandles() {
    S32 l_ClassID;
    l_ClassID = m_ClassResHA.FindFirst();

    while (l_ClassID >= 0) {
        m_ClassResHA[l_ClassID].MarkHandles();
        l_ClassID = m_ClassResHA.FindNext(l_ClassID);
    }
    return TRUE;
}

void ClassNameResManager_Z::MarkHandlesFromClass(const Name_Z& i_Name, const Name_Z& i_FileName) {
    S32 l_ClassID;
    if (GetClassID(i_Name, i_FileName, l_ClassID, FALSE)) {
        m_ClassResHA[l_ClassID].MarkHandles();
    }
}

Bool ClassNameResManager_Z::Minimize() {
    S32 l_ClassID;
    m_ClassHT.Minimize();
    m_ClassResHA.Minimize();
    l_ClassID = m_ClassResHA.FindFirst();
    while (l_ClassID >= 0) {
        m_ClassResHA[l_ClassID].Minimize();
        l_ClassID = m_ClassResHA.FindNext(l_ClassID);
    }
    return TRUE;
}

void ClassNameResManager_Z::RemoveClassId(const S32 i_ClassID) {
    if (!m_ClassResHA.IsElement(i_ClassID)) {
        return;
    }

    m_ClassResHA[i_ClassID].Flush();
    m_ClassResHA.Remove(i_ClassID);
}

void ClassNameResManager_Z::RemoveClassId(const Name_Z& i_Name, const Name_Z& i_FileName) {
    S32 l_ClassID;
    if (GetClassID(i_Name, i_FileName, l_ClassID, FALSE)) {
        RemoveClassId(l_ClassID);
    }
}

BaseObject_ZHdl ClassNameResManager_Z::GetObjectInClass(const S32 i_ClassID, const S32 i_EnumID) {
    const S32Hash_Z l_HashElt(i_EnumID);
    const S32Hash_Z* l_Result = m_ClassResHA[i_ClassID].m_ResourceHT.Search(l_HashElt);

    if (!l_Result) {
        //return HANDLE_NULL;
        return 0;
    }
    else {
        //return gData.ClassMgr->U32ToHandle(l_Result->m_Ref);
        return 0;
    }
}

void ClassNameRes_Z::Load(void** i_Data) {
    S32 l_NbHashElt;
    S32Hash_Z l_HashElt;
    *i_Data = Sys_Z::MemCpyFrom(&l_NbHashElt, *i_Data, 4);

    for (S32 i = 0; i < l_NbHashElt; i++) {
        *i_Data = Sys_Z::MemCpyFrom(&l_HashElt, *i_Data, 4);
        //gData.ClassMgr->LoadLinkId(&l_HashElt.m_Ref, i_Data);
        m_ResourceHT.Insert(l_HashElt);
    }

    return;
}

void ClassNameRes_Z::UpdateLinks() {
    m_ResourceHT.InitScan();

    S32Hash_Z* l_HashElt = m_ResourceHT.NextScan();

    while (l_HashElt) {
        BaseObject_ZHdl l_Hdl;

        //gData.ClassMgr->UpdateLinkFromId(l_Hdl, l_HashElt->m_Ref);

        //l_HashElt->m_Ref = gData.ClassMgr->HandleToU32(l_Hdl);
        l_HashElt = m_ResourceHT.NextScan();
    }
}

void ClassNameRes_Z::MarkHandles() {
    m_ResourceHT.InitScan();

    S32Hash_Z* l_HashElt = m_ResourceHT.NextScan();

    while (l_HashElt) {
        BaseObject_ZHdl l_Hdl;
        //gData.ClassMgr->MarkU32Handle(l_HashElt->m_Ref);
        l_HashElt = m_ResourceHT.NextScan();
    }
}

static const char* s_Unused = "Unknow Enum Symbol..";
