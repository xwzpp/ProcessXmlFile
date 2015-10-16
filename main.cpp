#include "tinystr.h"
#include "tinyxml.h"
#include "string"
#include <map>
#include <iostream>
#include  <direct.h>  
#include  <stdio.h>  
      
using namespace std;

//定义的缓冲区 
char   buffer[MAX_PATH];
//存放配置文件的参数名和参数值的映射关系。 
map<string,string> parameter;

void readXml(string filename)
{
	//获取当前的工作目录 
    getcwd(buffer, MAX_PATH);   
    string seperator = "\\";
    string fullPath = buffer+seperator+filename;
    //判断文件是否存在
	if(access(fullPath.c_str(),0)==-1)
	{
		//文件不存在，下面直接略过
		cerr<<"配置文件"+fullPath+"不存在"<<endl; 
		return; 
	} 
	
    //读取配置文件xml 
    TiXmlDocument doc(fullPath.c_str());
    bool loadOk = doc.LoadFile();
    if (!loadOk)
    {
            cout << "could load:" << doc.ErrorDesc() << endl;
    }
    
    //输出整个配置文件的内容 
    TiXmlPrinter printer;//提供的工具类,目的是将xml的数据按格式输出
    doc.Accept(&printer);
    cout  << printer.CStr() << endl;//输出
    
    //获得根元素<Configuration> 
	TiXmlElement* rootElement =doc.RootElement();

	//循环处理<property>节点
	TiXmlElement* nextElement=rootElement->FirstChildElement();
    while(nextElement!=NULL)
    {
  		//获取其中<name>节点 
	    TiXmlElement* nameElement=nextElement->FirstChildElement();
	    //获取其中<value>节点 
	    TiXmlElement* valueElement=nameElement->NextSiblingElement();
	    //获取上述节点的值 
	    //cout<<nextElement->Value()<<endl;
	   // cout<<nameElement->FirstChild()->Value()<<endl;
	    parameter[nameElement->FirstChild()->Value()]=valueElement->FirstChild()->Value();
	    //cout<<valueElement->FirstChild()->Value()<<endl;
	    nextElement=nextElement->NextSiblingElement(); 
    }
    
    //循环遍历parameter中的参数,进行输出 
	map<string, string>::iterator  iter;
    for(iter = parameter.begin(); iter != parameter.end(); iter++)
	{
 		cout<<iter->first<<"  "<<iter->second<<endl;
	} 
		
} 

int main(int argc, char *argv[])
{
	//读取默认的配置文件gis-default.xml 
	readXml("conf\\gis-default.xml");
	
	cout<<endl;
	 
	//读取自定义的配置文件gis-site.xml 
    readXml("conf\\gis-site.xml");
			    
    return 0;
}
