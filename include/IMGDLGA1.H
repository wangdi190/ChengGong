#if !defined(AFX_IMGDLGA_H__INCLUDED_)
#define AFX_IMGDLGA_H__INCLUDED_

#ifdef  IMGOPEN_EXPORTS
#define IMGOPEN_API __declspec(dllexport)
#else
#define IMGOPEN_API __declspec(dllimport)
#endif

BOOL IMGOPEN_API GetImgFile(char *filename,char *filter,HWND hWndParent);

#endif