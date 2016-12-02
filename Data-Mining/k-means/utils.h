#ifndef UTILS_H 
#define UTILS_H

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
#include <valarray>// for valarray
#include <fstream>
#include <ctime>

using namespace std;
#define  MAX_BUF_SIZE 512
#define	 MAXDIMENSION	20
#define	 MAXCLUSTER		10
#define  MAXLABEL  5
#define  CLUSTER_PRECISION  0.1
#define  MAXLEVEL  8
#define  INTERLEVEL  3
typedef unsigned char BYTE;

//feature after reduction
 typedef struct
 {
	float fProtocolType;
	float fService;
	float fStatusFlag;
	float fSrcBytes;
	float fDestBytes;
	float fFailedLogins;
	float fNumofRoot;
	float fCount;
	float fSrvCount;
	float fRerrorRate;
	float fSameSrvRate;
	float fDiffSrvRate;
	float fDstHostSrvCount;
	float fDstHostSameSrvRate;
	float fDstHostDiffSrvRate;
	float fDstHostSameSrcPortRate;
	float fDstHostSrvDiffHostRate;
	float fDstHostSrvSerrorRate;
	int   iLabel;
}feature;

typedef list < feature * > feature_list;

//int preProcessLabel(string);
//int preProcessService(string);
//int preProcessProtocol(string);
//int preProcessFlag(string);

string intToString (int );
//feature_list getData(FILE *);
//void writeToFile(FILE *,feature_list &);

#endif

 
