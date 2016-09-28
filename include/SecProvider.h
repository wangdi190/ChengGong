// SecProvider.h: interface for the SecProvider class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_)
#define AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//导入模型数据文件
BOOL WINAPI ImpModelData(LPCSTR lpPath);

//导出模型数据文件
BOOL WINAPI ExpModelData(LPCSTR lpDB,LPCSTR lpPath);

//导入断面表
BOOL WINAPI ImpSection(LPCSTR lpPath);

//导出断面表
BOOL WINAPI ExpSection(LPCSTR lpPath);

#endif // !defined(AFX_SECPROVIDER_H__09D80750_B862_4138_8233_DB7523D0BD51__INCLUDED_)
