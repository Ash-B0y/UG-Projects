#include<iostream>
#include<fstream>
#include<string.h>
#include<iterator>
#include<vector>
#include<sstream>
#include<malloc.h>
#include<ctime>
#include "SSUApi.h"
using namespace std;
int main(int argc,char *argv[])
{
	unsigned int version;
    unsigned int devSN;
    char devModel[16];
	const unsigned char pwd[4];
	unsigned int customNo;
	unsigned char* tag=(unsigned char*)malloc(SSU_TAGID_MAXSIZE);
	int *tagByts;
	int bank;
	int offset;
	int words;
	unsigned char *data=(unsigned char*)malloc(words*2);
	char antNo;
	SSUDevInfo *devinfo;
	devinfo->version=version;
	devinfo->devSN=devSN;
	strcpy(devinfo->devModel,devModel);


	string line;
	fstream cfgfile;
	cfgfile.open(argv[1],ios::in);
	while(getline(cfgfile,line))
	{
		string ip,port;
		int freq;
	
		istringstream buf(line);
		istream_iterator<string> begin(buf), end;
		vector<string> element(begin, end);
		ip=element[3];
		port=element[4];
		freq=stoi(element[5]);
		
		string a=ip+":"+port;
		char *x=new char[a.size()+1];
		copy(a.begin(),a.end(),x);
		x[a.size()]='\0';
		const char* b=(const char*)x;
		
		cout<<b<<"\n";
		cout<<"Time out : "<<freq<<"\t\n\n\n";
		
		SSUCtx *ctx;
		ctx=SSUConnect(b, SSU_ADDR_TCP,freq, pwd,customNo,devinfo);
		int word=SSUTagRead(ctx,pwd,tag,tagByts,bank,offset,words,data,antNo);


		if(word<0)
		{
			char date [10];
			string t,d,rfid[7];
			_strdate(date);
			 d=date;
			 char time [10];
			_strtime(time);
			t=time;
			ofstream myfile (argv[3]); 
			if (myfile.is_open())
			{
				for(int count = 0; count < 5; count ++)
				{    
					myfile << element[count] << " " ;   
				}
				myfile<<d<<" ";
				myfile<<t<<" ";
				myfile<<"status"<<"\n";
			}
		}
		else
		{
			char date [10];
			string t,d,rfid[7];
			_strdate(date);
			 d=date;
			 char time [10];
			_strtime(time);
			t=time;
			ofstream myfile (argv[2]); 
			if (myfile.is_open())
			{
				for(int count = 0; count < 5; count ++)
				{    
					myfile << element[count] << " " ;   
				}
			myfile<<d<<" ";
			myfile<<t<<" ";
			myfile<<data;
			myfile<<"\n";
			}
		}
	}
	return 0;
}
