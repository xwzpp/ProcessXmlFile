#include "tinystr.h"
#include "tinyxml.h"
#include "string"
#include <windows.h>
#include <map>
#include <iostream>
#include  <direct.h>  
#include  <stdio.h>  
      
using namespace std;

//����Ļ����� 
char   buffer[MAX_PATH];
//��������ļ��Ĳ������Ͳ���ֵ��ӳ���ϵ�� 
map<string,string> parameter;

void readXml(string filename)
{
	//��ȡ��ǰ�Ĺ���Ŀ¼ 
    getcwd(buffer, MAX_PATH);   
    string seperator = "\\";
    string fullPath = buffer+seperator+filename;
    //�ж��ļ��Ƿ����
	if(access(fullPath.c_str(),0)==-1)
	{
		//�ļ������ڣ�����ֱ���Թ�
		cerr<<"�����ļ�"+fullPath+"������"<<endl; 
		return; 
	} 
	
    //��ȡ�����ļ�xml 
    TiXmlDocument doc(fullPath.c_str());
    bool loadOk = doc.LoadFile();
    if (!loadOk)
    {
            cout << "could load:" << doc.ErrorDesc() << endl;
    }
    
    //������������ļ������� 
    TiXmlPrinter printer;//�ṩ�Ĺ�����,Ŀ���ǽ�xml�����ݰ���ʽ���
    doc.Accept(&printer);
    cout  << printer.CStr() << endl;//���
    
    //��ø�Ԫ��<Configuration> 
	TiXmlElement* rootElement =doc.RootElement();

	//ѭ������<property>�ڵ�
	TiXmlElement* nextElement=rootElement->FirstChildElement();
    while(nextElement!=NULL)
    {
  		//��ȡ����<name>�ڵ� 
	    TiXmlElement* nameElement=nextElement->FirstChildElement();
	    //��ȡ����<value>�ڵ� 
	    TiXmlElement* valueElement=nameElement->NextSiblingElement();
	    //��ȡ�����ڵ��ֵ 
	    //cout<<nextElement->Value()<<endl;
	   // cout<<nameElement->FirstChild()->Value()<<endl;
	    parameter[nameElement->FirstChild()->Value()]=valueElement->FirstChild()->Value();
	    //cout<<valueElement->FirstChild()->Value()<<endl;
	    nextElement=nextElement->NextSiblingElement(); 
    }
    
    //ѭ������parameter�еĲ���,������� 
	map<string, string>::iterator  iter;
    for(iter = parameter.begin(); iter != parameter.end(); iter++)
	{
 		cout<<iter->first<<"  "<<iter->second<<endl;
	} 
		
} 

int main(int argc, char *argv[])
{
	//��ȡĬ�ϵ������ļ�gis-default.xml 
	readXml("conf\\gis-default.xml");
	
	cout<<endl;
	 
	//��ȡ�Զ���������ļ�gis-site.xml 
    readXml("conf\\gis-site.xml");
			    
    return 0;
}