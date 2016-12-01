#include "pre_process.h"

static map<string, int> flagMap;     // Used to map strings to numbers.
static map<string, int> labelMap;
static map<string, int> protocolMap;
static map<string, int> serviceMap;

int preProcessLabel(string label)
{
    if(labelMap.size() == 0) // If the map has not been created.
    {
        labelMap["normal."] = 0;
        labelMap["back."] = 2;
        labelMap["buffer_overflow."] = 3;
        labelMap["ftp_write."] = 4;
        labelMap["guess_passwd."] = 4;
        labelMap["imap."] = 4;
        labelMap["ipsweep."] = 1;
        labelMap["land."] = 2;
        labelMap["loadmodule."] = 3;
        labelMap["multihop."] = 4;
        labelMap["neptune."] = 2;
        labelMap["nmap."] = 1;
        labelMap["perl."] = 3;
        labelMap["phf."] = 4;
        labelMap["pod."] = 2;
        labelMap["portsweep."] = 1;
        labelMap["rootkit."] = 3;
        labelMap["satan."] = 1;
        labelMap["smurf."] = 2;
        labelMap["spy."] = 4;
        labelMap["teardrop."] = 2;
        labelMap["warezclient."] = 4;
        labelMap["warezmaster."] = 4;
        labelMap["apache2."] = 2;
        labelMap["ps."] = 3;
        labelMap["mscan."] = 1;
        labelMap["sendmail."] = 4;
        labelMap["xsnoop."] = 4;
        labelMap["httptunnel."] = 3;
        labelMap["xlock."] = 4;
        labelMap["snmpguess."] = 4;
        labelMap["snmpgetattack."] = 4;
        labelMap["xterm."] = 3;
        labelMap["worm."] = 4;
        labelMap["sqlattack."] = 3;
        labelMap["processtable."] = 2;
        labelMap["saint."] = 1;
        labelMap["udpstorm."] = 2;
        labelMap["mailbomb."] = 2;
        labelMap["named."] = 4;
    }
    return labelMap[label];
}

int preProcessService(string service)
{
    if(serviceMap.size() == 0) // If the map has not been created.
    {
        serviceMap["http"] = 0;
        serviceMap["smtp"] = 1;
        serviceMap["domain_u"] = 2;
        serviceMap["auth"] = 3;
        serviceMap["finger"] = 4;
        serviceMap["telnet"] = 5;
        serviceMap["eco_i"] = 6;
        serviceMap["ftp"] = 7;
        serviceMap["ntp_u"] = 8;
        serviceMap["ecr_i"] = 9;
        serviceMap["other"] = 10;
        serviceMap["urp_i"] = 11;
        serviceMap["private"] = 12;
        serviceMap["pop_3"] = 13;
        serviceMap["ftp_data"] = 14;
        serviceMap["netstat"] = 15;
        serviceMap["daytime"] = 16;
        serviceMap["ssh"] = 17;
        serviceMap["echo"] = 18;
        serviceMap["time"] = 19;
        serviceMap["name"] = 20;
        serviceMap["whois"] = 21;
        serviceMap["domain"] = 22;
        serviceMap["mtp"] = 23;
        serviceMap["gopher"] = 24;
        serviceMap["remote_job"] = 25;
        serviceMap["rje"] = 26;
        serviceMap["ctf"] = 27;
        serviceMap["supdup"] = 28;
        serviceMap["link"] = 29;
        serviceMap["systat"] = 30;
        serviceMap["discard"] = 31;
        serviceMap["X11"] = 32;
        serviceMap["shell"] = 33;
        serviceMap["login"] = 34;
        serviceMap["imap4"] = 35;
        serviceMap["nntp"] = 36;
        serviceMap["uucp"] = 37;
        serviceMap["pm_dump"] = 38;
        serviceMap["IRC"] = 39;
        serviceMap["Z39_50"] = 40;
        serviceMap["netbios_dgm"] = 41;
        serviceMap["ldap"] = 42;
        serviceMap["sunrpc"] = 43;
        serviceMap["courier"] = 44;
        serviceMap["exec"] = 45;
        serviceMap["bgp"] = 46;
        serviceMap["csnet_ns"] = 47;
        serviceMap["http_443"] = 48;
        serviceMap["klogin"] = 49;
        serviceMap["printer"] = 50;
        serviceMap["netbios_ssn"] = 51;
        serviceMap["pop_2"] = 52;
        serviceMap["nnsp"] = 53;
        serviceMap["efs"] = 54;
        serviceMap["hostnames"] = 55;
        serviceMap["uucp_path"] = 56;
        serviceMap["sql_net"] = 57;
        serviceMap["vmnet"] = 58;
        serviceMap["iso_tsap"] = 59;
        serviceMap["netbios_ns"] = 60;
        serviceMap["kshell"] = 61;
        serviceMap["urh_i"] = 62;
        serviceMap["http_2784"] = 63;
        serviceMap["harvest"] = 64;
        serviceMap["aol"] = 65;
        serviceMap["tftp_u"] = 66;
        serviceMap["http_8001"] = 67;
        serviceMap["tim_i"] = 68;
        serviceMap["red_i"] = 69;
    }

    return serviceMap[service];
}

int preProcessProtocol(string protocol)
{
    if(protocolMap.size() == 0) // If the map has not been created.
    {
		protocolMap["icmp"] = 1;
		protocolMap["tcp"] = 2;
		protocolMap["udp"] = 3;

    }
    return protocolMap[protocol];
}

int preProcessFlag(string flag)
{
    if(flagMap.size() == 0) // If the map has not been created.
    {
        flagMap["SF"] = 0;
        flagMap["S2"] = 1;
        flagMap["S1"] = 2;
        flagMap["S3"] = 3;
        flagMap["OTH"] = 4;
        flagMap["REJ"] = 5;
        flagMap["RSTO"] = 6;
        flagMap["S0"] = 7;
        flagMap["RSTR"] = 8;
        flagMap["RSTOS0"] = 9;
        flagMap["SH"] = 10;
    }
    return flagMap[flag];
}

string intToString (int num)
{
	stringstream ss;
	ss<<num;
	return  ss.str();
}

feature_list getData(FILE *pInFile)
{
	char szBuf[MAX_BUF_SIZE];
	int iRcdCount = 0;
	char szSeps[] = ",\r\n";

	feature *pRecord;
	feature_list RecordList;
	string strTmp;
	int i;
	while (fgets (szBuf, MAX_BUF_SIZE, pInFile) != NULL)
	{
		if (++iRcdCount % 10000 == 0)
			cout << setiosflags (ios::left) << "============ " << setw (8) << iRcdCount << " lines have been read ============" << endl;

		pRecord = new feature;
		//skip the first column
		strtok (szBuf, szSeps);
		//protocol_type
		strTmp = strtok (NULL, szSeps);
		pRecord->iProtocolType=preProcessProtocol(strTmp);

		//service
		strTmp = strtok (NULL, szSeps);
		pRecord->iService=preProcessService(strTmp);
		
		//flag
		strTmp = strtok (NULL, szSeps);
		pRecord->iStatusFlag=preProcessFlag(strTmp);

		//src_bytes
		strTmp = strtok (NULL, szSeps);
		pRecord->iSrcBytes = atoi (strTmp.c_str ());

		//dst_bytes
		strTmp = strtok (NULL, szSeps);
		pRecord->iDestBytes = atoi (strTmp.c_str ());

		//skip 7 8 9 10 column
		for (i = 0; i < 4; i++)
			strtok (NULL, szSeps);

		//num_failed_logins
		strTmp = strtok (NULL, szSeps);
		pRecord->iFailedLogins = atoi (strTmp.c_str ());

		//skip 12 13 column
		strtok (NULL, szSeps);// 12
		strtok (NULL, szSeps);// 13

		//root_shell
		strTmp = strtok (NULL, szSeps);
		pRecord->bRootShell = atoi (strTmp.c_str ());

		//skip 15 column
		strtok (NULL, szSeps);

		//num_root
		strTmp = strtok (NULL, szSeps);
		pRecord->iNumofRoot = atoi (strTmp.c_str ());

		//skip 17 18 19 20 21 column
		for (i = 0; i < 5; ++i)
			strtok (NULL, szSeps);
		//is_guest_login
		strTmp = strtok (NULL, szSeps);
		pRecord->bGuestLogin = atoi (strTmp.c_str ());

		//count
		strTmp = strtok (NULL, szSeps);
		pRecord->iCount = atoi (strTmp.c_str ());

		//srv_count
		strTmp = strtok (NULL, szSeps);
		pRecord->iSrvCount = atoi (strTmp.c_str ());

		//skip 25 26 columns
		strtok (NULL, szSeps);
		strtok (NULL, szSeps);
		//rerror_rate
		strTmp = strtok (NULL, szSeps);
		//change rate [0..1] to [0..100]
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iRerrorRate = atoi (strTmp.c_str ());
		// pRecord->iRerrorRate = atoi (strTmp.c_str ())*100;

		//skip 28 column
		strtok (NULL, szSeps);
		//same_srv_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iSameSrvRate = atoi (strTmp.c_str ());

		//diff_srv_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDiffSrvRate = atoi (strTmp.c_str ());

		//skip 31 32
		strtok (NULL, szSeps);
		strtok (NULL, szSeps);

		//dst_host_srv_count
		strTmp = strtok (NULL, szSeps);
		pRecord->iDstHostSrvCount = atoi (strTmp.c_str ());

		//dst_host_same_srv_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSameSrvRate = atoi (strTmp.c_str ());

		//dst_host_diff_srv_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostDiffSrvRate = atoi (strTmp.c_str ());

		//dst_host_same_src_port_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSameSrcPortRate = atoi (strTmp.c_str ());

		//dst_host_srv_diff_host_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSrvDiffHostRate = atoi (strTmp.c_str ());

		//skip 38
		strtok (NULL, szSeps);
		//dst_host_srv_serror_rate
		strTmp = strtok (NULL, szSeps);
		strTmp[1] = strTmp[2];
		strTmp[2] = strTmp[3];
		strTmp[3] = '\0';
		pRecord->iDstHostSrvSerrorRate = atoi (strTmp.c_str ());

		//skip 40 41
		strtok (NULL, szSeps);
		strtok (NULL, szSeps);
		strTmp.clear ();

		strTmp = strtok (NULL, szSeps);
		pRecord->iLabel=preProcessLabel(strTmp);

		RecordList.push_back (pRecord);
	}
	cout << "All records have been read ! Total " << iRcdCount << " records !" << endl;
	return RecordList;
}

void writeToFile(FILE *pOutFile, feature_list &RecordList)
{
	feature_list::iterator RecdIter,recdie;
	string StrRecord, StrTemp;
	int i=0;
	for (i = 0, RecdIter = RecordList.begin (),recdie=RecordList.end(); RecdIter != recdie; ++RecdIter)
	{
		if (++i % 10000 == 0)
		cout << setiosflags (ios::left) << "+++++++++++ " << setw (8) << i << "lines have been written +++++++++++" << endl;

		//protocol_type
		StrTemp = intToString(int ((*RecdIter)->iProtocolType));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//service
		StrTemp = intToString(int ((*RecdIter)->iService));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//flag
		StrTemp = intToString (int ((*RecdIter)->iStatusFlag));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//src_bytes
		StrTemp = intToString ((*RecdIter)->iSrcBytes);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_bytes
		StrTemp = intToString ((*RecdIter)->iDestBytes);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//num_failed_logins
		StrTemp = intToString ((*RecdIter)->iFailedLogins);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();


		//root_shell
		StrTemp = intToString (int ((*RecdIter)->bRootShell));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//num_root
		StrTemp = intToString ((*RecdIter)->iNumofRoot);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//is_guest_login
		StrTemp = intToString (int ((*RecdIter)->bGuestLogin));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//count
		StrTemp = intToString ((*RecdIter)->iCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//srv_count
		StrTemp = intToString ((*RecdIter)->iSrvCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//rerror_rate
		StrTemp = intToString (int ((*RecdIter)->iRerrorRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//same_srv_rate
		StrTemp = intToString (int ((*RecdIter)->iSameSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//diff_srv_rate
		StrTemp = intToString (int ((*RecdIter)->iDiffSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_count
		StrTemp = intToString ((*RecdIter)->iDstHostSrvCount);
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_same_srv_rate
		StrTemp = intToString (int ((*RecdIter)->iDstHostSameSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_diff_srv_rate
		StrTemp = intToString (int ((*RecdIter)->iDstHostDiffSrvRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_same_src_port_rate
		StrTemp = intToString (int ((*RecdIter)->iDstHostSameSrcPortRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_srv_diff_host_rate
		StrTemp = intToString (int ((*RecdIter)->iDstHostSrvDiffHostRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//dst_host_srv_serror_rate
		StrTemp = intToString (int ((*RecdIter)->iDstHostSrvSerrorRate));
		StrRecord += StrTemp;
		StrRecord += ",";
		StrTemp.clear ();

		//label
		StrTemp = intToString (int ((*RecdIter)->iLabel));
		StrRecord += StrTemp;
		StrTemp.clear ();
		StrRecord += "\n";

		fputs (StrRecord.c_str (), pOutFile);
		StrRecord.clear ();
	}
	cout << "All Records have been written to file!" << endl;
}

