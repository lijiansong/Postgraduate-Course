#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;
#define MAX_BUF_SIZE 512
typedef unsigned char BYTE;

//feature after reduction
 typedef struct
 {
 	BYTE iProtocolType;
	BYTE iService;
	BYTE iStatusFlag;
	int iSrcBytes;
	int iDestBytes;
	int iFailedLogins;
	BYTE bRootShell;
	int iNumofRoot;
	BYTE bGuestLogin;
	int iCount;
	int iSrvCount;
	BYTE iRerrorRate;
	BYTE iSameSrvRate;
	BYTE iDiffSrvRate;
	int iDstHostSrvCount;
	BYTE iDstHostSameSrvRate;
	BYTE iDstHostDiffSrvRate;
	BYTE iDstHostSameSrcPortRate;
	BYTE iDstHostSrvDiffHostRate;
	BYTE iDstHostSrvSerrorRate;
	BYTE iLabel;
 }feature;

typedef list < feature * > feature_list;

int preProcessLabel(string);
int preProcessService(string);
int preProcessProtocol(string);
int preProcessFlag(string);

string intToString (int );
feature_list getData(FILE *);
void writeToFile(FILE *,feature_list &);


 
