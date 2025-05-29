/*
UserDefineCmd_Z::MakeCommandList(void)	__text	0022BE24	000000B4	0000003C	00000004	R	.	.	.	.	.	B	T	.
UserDefineCmd_Z::GetNextCommand(ulong &)	__text	0022BED8	0000006B	0000000C	00000008	R	.	.	.	.	.	B	T	.
UserDefineCmd_Z::GetFirstCommand(ulong &)	__text	0022BF44	00000016	00000004	00000004	R	.	.	.	.	.	B	T	.
*/

#include <UserDefineCmd_Z.h>
#include <Memory_Z.h>

void UserDefineCmd_Z::MakeCommandList() {
    Char* l_CurrentChar;
    S32 l_NewDataSize = 0;
    int i;
    for (i = 0; i < m_DataSize; i++) {
        if (m_UserDatas[i] == '[' || m_UserDatas[i] == ']') 
            continue;
        if (m_UserDatas[i] == ';')
            l_NewDataSize++;

        l_NewDataSize++;
    }
    Char* l_NewUserData = (Char*)Alloc_Z(l_NewDataSize + 1);
    int j = 0;
    for (i = 0; i < m_DataSize; i++) {
        if (m_UserDatas[i] == '[' || m_UserDatas[i] == ']') 
            continue;
        if (m_UserDatas[i] == ';') {
            l_NewUserData[j++] = '\n';
            l_NewUserData[j++] = '\r';
            continue;
        }

        l_NewUserData[j++] = m_UserDatas[i];
    }
    l_NewUserData[j] = 0;
    Free_Z(m_UserDatas);
    m_UserDatas = l_NewUserData;
    m_DataSize = l_NewDataSize;

}

Char *UserDefineCmd_Z::GetFirstCommand(U32 &o_Length)
{
    m_CurLen = 0;
    return GetNextCommand(o_Length);
}

Char* UserDefineCmd_Z::GetNextCommand(U32& o_Length)
{
    o_Length= 0;

    if (m_CurLen>=m_DataSize)
        return NULL;

    for (int i=m_CurLen; i<m_DataSize; i++)
    {
        if (m_UserDatas[i]=='\n')
            break;
        o_Length++;
    }

    m_CurLen += o_Length;
    S32 l_Pos=m_CurLen-o_Length;

    while ((m_CurLen < m_DataSize) && ((m_UserDatas[m_CurLen] == 13) || (m_UserDatas[m_CurLen] == 10) || (m_UserDatas[m_CurLen] == 32)))    m_CurLen++;

    return &m_UserDatas[l_Pos];
}