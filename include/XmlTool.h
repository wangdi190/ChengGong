
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XMLTOOL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XMLTOOL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef XMLTOOL_EXPORTS
#define XMLTOOL_API __declspec(dllexport)
#else
#define XMLTOOL_API __declspec(dllimport)
#endif

#include <vector>
#define FLAG_LENGTH_MAX 64 // 最大标志长度

class XMLTOOL_API IXmlNode  
{
public:
	//通过标志返回子节点
	virtual IXmlNode* GetSubNodeByFlag(char* pFlag,std::vector<IXmlNode*>* pSubVtr)=0;
	//通过标志返回子节点值
	virtual const char* GetSubValueByFlag(char* pFlag)=0;
	//返回首个子节点位置
	virtual int GetFirstSubNode()=0;
	//返回当前子节点
	virtual IXmlNode* GetNextSubNode()=0;
	//返回首个属性位置
	virtual int GetFirstProp()=0;
	//返回当前属性
	virtual int GetNextProp(const char** pName,const char** pValue)=0;

	//取属性值
	virtual const char* GetPropValue(char* pName)=0;
	//是否节点标志
	virtual int IsKindof(const char* pFlag)=0;
	//返回标志
	virtual const char* GetFlag()=0;
	//按字符串取值
	virtual const char* GetValue()=0;


	IXmlNode(){};
	virtual ~IXmlNode(){};
};

typedef std::vector<IXmlNode*> XMLTOOL_API XMLNODEVTR;
typedef std::vector<IXmlNode*>::iterator XMLTOOL_API XMLITERATOR;

//解析XML文件
XMLTOOL_API int XMLAPI_Parse(const char* pXmlFile,XMLNODEVTR* pNodeVtr,const char* pRoot=NULL);
//解析XML字符串
XMLTOOL_API int XMLAPI_Parse(const char* pXmlFile,int len,XMLNODEVTR* pNodeVtr,const char* pRoot=NULL);
//释放名字
XMLTOOL_API void XMLAPI_Release();

