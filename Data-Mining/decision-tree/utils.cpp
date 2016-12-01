#include "utils.h"

static mss flagMap;				// Used to map strings to numbers.
static mss labelMap;
static mss protocolMap;
static mss serviceMap;
static mss deLabelMap;

//get the mean of each column
vd getColMean(vvs &dataTable)
{
	double value,sum=0.0;
	vd result;
	for(int i=0;i<dataTable[0].size()-1;++i)
	{
		for(int j=1;j<dataTable.size();++j)
		{
			value=atof(dataTable[j][i].c_str());
			sum+=value;
		}
		result.push_back(sum/(dataTable.size()-1));
		sum=0.0;
	}
	return result;
}
//get the point mul of each column
vvd getColPointMul(vvs &dataTable)
{
	double sum=0.0;
	vvd result(dataTable[0].size()-1,vd(dataTable[0].size()-1,0.0));
	for(int i=0;i<dataTable[0].size()-1;++i)
	{
		for(int j=i+1;j<dataTable[0].size()-1;++j)
		{
			for(int k=1;k<dataTable.size();++k)
			{
				sum+=( atof(dataTable[k][i].c_str()) * atof(dataTable[k][j].c_str()) )/(dataTable.size()-1);
			}
			result[i][j]=sum;
			sum=0.0;
		}
	}
	return result;
}

//compute Covariance of every two columns
vvd computeCov(vvs &dataTable)
{
	vvd result(dataTable[0].size()-1,vd(dataTable[0].size()-1,0.0));
	vvd pointMul=getColPointMul(dataTable);
	vd mean=getColMean(dataTable);
	for(int i=0;i<dataTable[0].size()-1;++i)
	{
		for(int j=1;j<dataTable[0].size()-1;++j)
		{
			result[i][j]=pointMul[i][i]*pointMul[i][j]-mean[i]*mean[j];
		}
	}
	return result;
}
//print the Covariance matrix
void printCov(vvd &cov)
{
	for(int i=0;i<cov[0].size();++i)
	{
		for(int j=i+1;j<cov[0].size();++j)
		{
			cout<<cov[i][j]<<", ";
		}
		cout<<endl;
	}
}

pp getMaxCov(vvs &dataTable)
{
	vvd cov=computeCov(dataTable);
	double minVal=DBL_MAX;
	//bool update=false;
	int tmp_i=0,tmp_j;
	for(int i=0;i<cov[0].size();++i)
	{
		for(int j=i+1;j<cov[0].size();++j)
		{
			if((minVal-cov[i][j])<1e-6)
			{
				//update=true;
				minVal=cov[i][j];
				tmp_i=i;tmp_j=j;
			}
		}
	}
	return make_pair(tmp_i,tmp_j);
}

string deCalssLabelMap(string label)
{
	if(deLabelMap.size()==0)
	{
		deLabelMap["0"]="normal.";
		deLabelMap["1"]="probe.";
		deLabelMap["2"]="dos.";
		deLabelMap["3"]="u2r.";
		deLabelMap["4"]="r2l.";
	}
	return deLabelMap[label];
}

string getProcessFlag (string flag /*, mss &flagMap */ )
{
	if (flagMap.size () == 0)	// If the map has not been created.
	{
		flagMap["SF"] = "0";
		flagMap["S2"] = "1";
		flagMap["S1"] = "2";
		flagMap["S3"] = "3";
		flagMap["OTH"] = "4";
		flagMap["REJ"] = "5";
		flagMap["RSTO"] = "6";
		flagMap["S0"] = "7";
		flagMap["RSTR"] = "8";
		flagMap["RSTOS0"] = "9";
		flagMap["SH"] = "10";
	}
	return flagMap[flag];
}

string getProcessLabel (string label /*, mss &labelMap */ )
{
	if (labelMap.size () == 0)	// If the map has not been created.
	{
		labelMap["normal."] = "0";
		labelMap["back."] = "2";
		labelMap["buffer_overflow."] = "3";
		labelMap["ftp_write."] = "4";
		labelMap["guess_passwd."] = "4";
		labelMap["imap."] = "4";
		labelMap["ipsweep."] = "1";
		labelMap["land."] = "2";
		labelMap["loadmodule."] = "3";
		labelMap["multihop."] = "4";
		labelMap["neptune."] = "2";
		labelMap["nmap."] = "1";
		labelMap["perl."] = "3";
		labelMap["phf."] = "4";
		labelMap["pod."] = "2";
		labelMap["portsweep."] = "1";
		labelMap["rootkit."] = "3";
		labelMap["satan."] = "1";
		labelMap["smurf."] = "2";
		labelMap["spy."] = "4";
		labelMap["teardrop."] = "2";
		labelMap["warezclient."] = "4";
		labelMap["warezmaster."] = "4";
		labelMap["apache2."] = "2";
        labelMap["ps."] = "3";
        labelMap["mscan."] = "1";
        labelMap["sendmail."] = "4";
        labelMap["xsnoop."] = "4";
        labelMap["httptunnel."] = "3";
        labelMap["xlock."] = "4";
        labelMap["snmpguess."] = "4";
        labelMap["snmpgetattack."] = "4";
        labelMap["xterm."] = "3";
        labelMap["worm."] = "4";
        labelMap["sqlattack."] = "3";
        labelMap["processtable."] = "2";
        labelMap["saint."] = "1";
        labelMap["udpstorm."] = "2";
        labelMap["mailbomb."] = "2";
        labelMap["named."] = "4";
	}
	return labelMap[label];
}

string getProcessProtocol (string protocol /*, mss &protocolMap */ )
{
	if (protocolMap.size () == 0)	// If the map has not been created.
	{
		protocolMap["tcp"] = "0";
		protocolMap["udp"] = "1";
		protocolMap["icmp"] = "2";
	}
	return protocolMap[protocol];
}

//map serive to integer
string getProcessService (string service /*, mss &serviceMap */ )
{
	if (serviceMap.size () == 0)	// If the map has not been created.
	{
		serviceMap["http"] = "0";
		serviceMap["smtp"] = "1";
		serviceMap["domain_u"] = "2";
		serviceMap["auth"] = "3";
		serviceMap["finger"] = "4";
		serviceMap["telnet"] = "5";
		serviceMap["eco_i"] = "6";
		serviceMap["ftp"] = "7";
		serviceMap["ntp_u"] = "8";
		serviceMap["ecr_i"] = "9";
		serviceMap["other"] = "10";
		serviceMap["urp_i"] = "11";
		serviceMap["private"] = "12";
		serviceMap["pop_3"] = "13";
		serviceMap["ftp_data"] = "14";
		serviceMap["netstat"] = "15";
		serviceMap["daytime"] = "16";
		serviceMap["ssh"] = "17";
		serviceMap["echo"] = "18";
		serviceMap["time"] = "19";
		serviceMap["name"] = "20";
		serviceMap["whois"] = "21";
		serviceMap["domain"] = "22";
		serviceMap["mtp"] = "23";
		serviceMap["gopher"] = "24";
		serviceMap["remote_job"] = "25";
		serviceMap["rje"] = "26";
		serviceMap["ctf"] = "27";
		serviceMap["supdup"] = "28";
		serviceMap["link"] = "29";
		serviceMap["systat"] = "30";
		serviceMap["discard"] = "31";
		serviceMap["X11"] = "32";
		serviceMap["shell"] = "33";
		serviceMap["login"] = "34";
		serviceMap["imap4"] = "35";
		serviceMap["nntp"] = "36";
		serviceMap["uucp"] = "37";
		serviceMap["pm_dump"] = "38";
		serviceMap["IRC"] = "39";
		serviceMap["Z39_50"] = "40";
		serviceMap["netbios_dgm"] = "41";
		serviceMap["ldap"] = "42";
		serviceMap["sunrpc"] = "43";
		serviceMap["courier"] = "44";
		serviceMap["exec"] = "45";
		serviceMap["bgp"] = "46";
		serviceMap["csnet_ns"] = "47";
		serviceMap["http_443"] = "48";
		serviceMap["klogin"] = "49";
		serviceMap["printer"] = "50";
		serviceMap["netbios_ssn"] = "51";
		serviceMap["pop_2"] = "52";
		serviceMap["nnsp"] = "53";
		serviceMap["efs"] = "54";
		serviceMap["hostnames"] = "55";
		serviceMap["uucp_path"] = "56";
		serviceMap["sql_net"] = "57";
		serviceMap["vmnet"] = "58";
		serviceMap["iso_tsap"] = "59";
		serviceMap["netbios_ns"] = "60";
		serviceMap["kshell"] = "61";
		serviceMap["urh_i"] = "62";
		serviceMap["http_2784"] = "63";
		serviceMap["harvest"] = "64";
		serviceMap["aol"] = "65";
		serviceMap["tftp_u"] = "66";
		serviceMap["http_8001"] = "67";
		serviceMap["tim_i"] = "68";
		serviceMap["red_i"] = "69";
	}
	return serviceMap[service];
}

//encode the non-continuous attribute
void encode(vvs &dataTable)
{
	int i,j;
	for (i = 0; i < dataTable[0].size (); ++i)
	{
		string columnName = dataTable[0][i];
		if(columnName=="protocol_type")
		{
			for(int j=1;j<dataTable.size();++j)
			{
				dataTable[j][i]=getProcessProtocol(dataTable[j][i]);
			}
		}
		else if(columnName=="service")
		{
			for(int j=1;j<dataTable.size();++j)
			{
				dataTable[j][i]=getProcessService(dataTable[j][i]);
			}
		}
		else if(columnName=="flag")
		{
			for(int j=1;j<dataTable.size();++j)
			{
				dataTable[j][i]=getProcessFlag(dataTable[j][i]);
			}
		}
		else if(columnName=="label")
		{
			for (int j = 1; j < dataTable.size (); ++j)
			{
				//string classLabel=dataTable[j][dataTable[0].size()-1];
				dataTable[j][dataTable[0].size()-1]=getProcessLabel(dataTable[j][dataTable[0].size()-1]);
			}
		}

	}
}

//process the rate in [0..1] to [0..100]
void preProcessRate(vvs &dataTable)
{
	int i,j;
	for (i = 0; i < dataTable[0].size ()-1; ++i)
	{
		string columnName = dataTable[0][i];
		if(columnName.find("rate")!=std::string::npos)
		{
			for (int j = 1; j < dataTable.size (); ++j)
			{
				string strVal=dataTable[j][i];
				double rate=atof(strVal.c_str())*100.0;
				stringstream ss;
				ss<<rate;
				ss>>strVal;
				dataTable[j][i]=strVal;
			}
		}
	}
}

//get the spilit value by computing entropy
string getSplitValue (int columnIndex, vvs & dataTable /*, vvs &tableInfo */ )
{
	msi tempMap;
	vi counts = countDistinct (dataTable, columnIndex);
	vd entropyList;
	int splitValue = 0;
	string colName = dataTable[0][columnIndex];
	//for (int k = 1; k < dataTable.size (); ++k)
	for(int k=0;k<counts.size();++k)
	{
		for (int i = 1; i < dataTable.size (); ++i)
		{
			double entropy = 0.0;
			if (tempMap.find (dataTable[i][columnIndex]) != tempMap.end ())
			{
				++tempMap[dataTable[i][columnIndex]];
			}
			else
			{
				tempMap[dataTable[i][columnIndex]] = 1;
				//find all the table tuple needed
				vvs tempTable = pruneTable (dataTable, colName, dataTable[i][columnIndex]);
				vi classCounts = countDistinct (tempTable, tempTable[0].size () - 1);
				int j;
				for (j = 0; j < classCounts.size (); j++)
				{
					double temp = (double) classCounts[j];
					entropy -= (temp / classCounts[classCounts.size () - 1]) * (log (temp / classCounts[classCounts.size () - 1]) / log (2));
				}
				entropyList.push_back (entropy);
				entropy = 0.0;
			}
		}

		double columnEntropy = 0.0;
		double minEntropy = DBL_MAX;
		for (int i = 0; i < counts.size () - 1; ++i)
		{
			columnEntropy += ((double) counts[i] * (double) entropyList[i]);
		}

		if (columnEntropy <= minEntropy)
		{
			minEntropy = columnEntropy;
			splitValue = k;
		}
	}
	return dataTable[splitValue][columnIndex];
}

//data pre-process, data discretization by entropy
void preDiscretization ( /*const string columnName, */ vvs & dataTable /*, vvs &tableInfo */ )
{
	// if((columnName=="duration")||(columnName=="src_bytes")||(columnName=="dst_bytes")||(columnName=="wrong_fragment")||(columnName=="urgent")||(columnName=="hot")||(columnName=="num_failed_logins")||(columnName=="num_compromised")||(columnName=="root_shell")||(columnName=="su_attempted")||(columnName=="num_root")||(columnName=="num_file_creations")||(columnName=="num_shells")||(columnName=="num_access_files")||(columnName=="num_outbound_cmds")||(columnName=="count")||(columnName=="srv_count")||(columnName=="serror_rate")||(columnName=="srv_serror_rate")||(columnName=="rerror_rate")||(columnName=="srv_rerror_rate")||(columnName=="same_srv_rate")||(columnName=="diff_srv_rate")||(columnName=="srv_diff_host_rate")||(columnName=="dst_host_count")||(columnName=="dst_host_srv_count")||(columnName=="dst_host_same_srv_rate")||(columnName=="dst_host_diff_srv_rate")||(columnName=="dst_host_same_src_port_rate")||(columnName=="dst_host_srv_diff_host_rate")||(columnName=="dst_host_serror_rate")||(columnName=="dst_host_srv_serror_rate")||(columnName=="dst_host_rerror_rate")||(columnName=="dst_host_srv_rerror_rate"))
	// {
	// }
	//vvs tableInfo=generateTableInfo(dataTable);
	int i, j;
	//each attribute has two values, update them by entropy
	for (i = 0; i < dataTable[0].size (); ++i)
	{
		string columnName = dataTable[0][i];
		//for continuous attribute
		if ((columnName == "duration") || (columnName == "src_bytes") || (columnName == "dst_bytes") || (columnName == "wrong_fragment") || (columnName == "urgent") || (columnName == "hot")
			|| (columnName == "num_failed_logins") || (columnName == "num_compromised") || (columnName == "root_shell") || (columnName == "su_attempted") || (columnName == "num_root")
			|| (columnName == "num_file_creations") || (columnName == "num_shells") || (columnName == "num_access_files") || (columnName == "num_outbound_cmds") || (columnName == "count")
			|| (columnName == "srv_count") || (columnName == "serror_rate") || (columnName == "srv_serror_rate") || (columnName == "rerror_rate") || (columnName == "srv_rerror_rate")
			|| (columnName == "same_srv_rate") || (columnName == "diff_srv_rate") || (columnName == "srv_diff_host_rate") || (columnName == "dst_host_count") || (columnName == "dst_host_srv_count")
			|| (columnName == "dst_host_same_srv_rate") || (columnName == "dst_host_diff_srv_rate") || (columnName == "dst_host_same_src_port_rate") || (columnName == "dst_host_srv_diff_host_rate")
			|| (columnName == "dst_host_serror_rate") || (columnName == "dst_host_srv_serror_rate") || (columnName == "dst_host_rerror_rate") || (columnName == "dst_host_srv_rerror_rate"))
		{
			//int columnIndex=returnColumnIndex(columnName,tableInfo);
			string splitValue = getSplitValue ( /*columnIndex */ i, dataTable /*,tableInfo */ );
			//cout << "+++++" << dataTable[0][i] << "+++++++++++++++++++++++splitValue: " << splitValue << endl << endl;
			double spValue = atof (splitValue.c_str ());
			for (int j = 1; j < dataTable.size (); ++j)
			{
				double value = atof (dataTable[j][i].c_str ());
				double tmpVal;
				if ((value - spValue) <= 1e-6)
				{
					tmpVal = 0;
					//cout<<"+++++true"<<endl;
				}
				else
				{
					tmpVal = 1;
					//cout<<"+++++false"<<endl;
				}
				stringstream ss;
				ss << tmpVal;
				string strVal;
				ss >> strVal;
				ss.clear ();
				dataTable[j][i] = strVal;
			}
		}
		// //for non-continuous attribute
		// else if(columnName=="label")
		// {
		// 	for (int j = 1; j < dataTable.size (); ++j)
		// 	{
		// 		//string classLabel=dataTable[j][dataTable[0].size()-1];
		// 		dataTable[j][dataTable[0].size()-1]=getProcessLabel(dataTable[j][dataTable[0].size()-1]);
		// 	}

		// }
		// else if(columnName=="protocol_type")
		// {
		// 	//int columnIndex=returnColumnIndex()
		// 	for(int j=1;j<dataTable.size();++j)
		// 	{
		// 		dataTable[j][i]=getProcessProtocol(dataTable[j][i]);
		// 	}
		// }
		// else if(columnName=="service")
		// {
		// 	for(int j=1;j<dataTable.size();++j)
		// 	{
		// 		dataTable[j][i]=getProcessService(dataTable[j][i]);
		// 	}
		// }
		// else if(columnName=="flag")
		// {
		// 	for(int j=1;j<dataTable.size();++j)
		// 	{
		// 		dataTable[j][i]=getProcessFlag(dataTable[j][i]);
		// 	}
		// }
	}

}

// read a single line from the input file and store the info into a matrix
void getData (string & someString, vvs & attributeTable)
{
	int attributeCount = 0;
	vs vectorOfStrings;
	while (someString.length () != 0 && someString.find (',') != string::npos)
	{
		size_t pos;
		string singleAttribute;
		pos = someString.find_first_of (',');
		singleAttribute = someString.substr (0, pos);
		if(singleAttribute=="")
		{
			vectorOfStrings.clear();
			return ;
		}
		vectorOfStrings.push_back (singleAttribute);
		//cout<<"-----------singleAttribute ***********"<<singleAttribute<<endl;
		someString.erase (0, pos + 1);
	}
	vectorOfStrings.push_back (someString);
	attributeTable.push_back (vectorOfStrings);
	vectorOfStrings.clear ();
}

// print a data table
void printAttributeTable (vvs & attributeTable)
{
	int inner, outer;
	for (outer = 0; outer < attributeTable.size (); ++outer)
	{
		for (inner = 0; inner < attributeTable[outer].size (); ++inner)
		{
			cout << attributeTable[outer][inner] << ",";
		}
		cout << endl;
	}
}

// get the sub-table
vvs pruneTable (vvs & attributeTable, string & colName, string value)
{
	int i, j;
	vvs prunedTable;
	int column = -1;
	vs headerRow;
	for (i = 0; i < attributeTable[0].size (); ++i)
	{
		if (attributeTable[0][i] == colName)
		{
			column = i;
			break;
		}
	}
	for (i = 0; i < attributeTable[0].size (); ++i)
	{
		if (i != column)
		{
			headerRow.push_back (attributeTable[0][i]);
		}
	}
	prunedTable.push_back (headerRow);
	for (i = 0; i < attributeTable.size (); ++i)
	{
		vs auxRow;
		if (attributeTable[i][column] == value)
		{
			for (j = 0; j < attributeTable[i].size (); ++j)
			{
				if (j != column)
				{
					auxRow.push_back (attributeTable[i][j]);
				}
			}
			prunedTable.push_back (auxRow);
		}
	}
	return prunedTable;
}

// builds the decision tree based on the table it is passed
node *buildDecisionTree (vvs & table, node * nodePtr, vvs & tableInfo)
{
	if (tableIsEmpty (table))
	{
		return NULL;
	}
	if (isSameClass (table))
	{
		nodePtr->isLeaf = true;
		nodePtr->label = table[1][table[1].size () - 1];
		return nodePtr;
	}
	else
	{
		string splittingCol = decideSplittingColumn (table);
		nodePtr->splitOn = splittingCol;
		int colIndex = returnColumnIndex (splittingCol, tableInfo);
		int i;
		for (i = 1; i < tableInfo[colIndex].size (); ++i)
		{
			node *newNode = (node *) new node;
			newNode->label = tableInfo[colIndex][i];
			nodePtr->childrenValues.push_back (tableInfo[colIndex][i]);
			newNode->isLeaf = false;
			newNode->splitOn = splittingCol;
			vvs auxTable = pruneTable (table, splittingCol, tableInfo[colIndex][i]);
			nodePtr->children.push_back (buildDecisionTree (auxTable, newNode, tableInfo));
		}
	}
	return nodePtr;
}

// returns true if all instances in a subtable at a node have the same class label
bool isSameClass (vvs & table)
{
	int i;
	int lastCol = table[0].size () - 1;
	string firstValue = table[1][lastCol];
	for (i = 1; i < table.size (); ++i)
	{
		if (firstValue != table[i][lastCol])
		{
			return false;
		}
	}
	return true;
}

// return the nums of an attribute/column's value
vi countDistinct (vvs & table, int column)
{
	vs vectorOfStrings;
	vi counts;
	bool found = false;
	int foundIndex;
	for (int i = 1; i < table.size (); ++i)
	{
		for (int j = 0; j < vectorOfStrings.size (); ++j)
		{
			if (vectorOfStrings[j] == table[i][column])
			{
				found = true;
				foundIndex = j;
				break;
			}
			else
			{
				found = false;
			}
		}
		if (!found)
		{
			counts.push_back (1);
			vectorOfStrings.push_back (table[i][column]);
		}
		else
		{
			++counts[foundIndex];
		}
	}
	int sum = 0;
	for (int i = 0; i < counts.size (); ++i)
	{
		sum += counts[i];
	}
	counts.push_back (sum);
	return counts;
}

// returns the spilit attribute
string decideSplittingColumn (vvs & table)
{
	int column, i;
	double minEntropy = DBL_MAX;
	int splittingColumn = 0;
	//vi entropies;
	for (column = 0; column < table[0].size () - 1; ++column)
	{
		string colName = table[0][column];
		msi tempMap;
		vi counts = countDistinct (table, column);
		vd attributeEntropy;
		double columnEntropy = 0.0;
		for (i = 1; i < table.size () - 1; ++i)
		{
			double entropy = 0.0;
			if (tempMap.find (table[i][column]) != tempMap.end ())
			{
				++tempMap[table[i][column]];
			}
			else
			{
				// if attribute is found first time in a column, then process it and calculate its entropy
				tempMap[table[i][column]] = 1;
				vvs tempTable = pruneTable (table, colName, table[i][column]);
				vi classCounts = countDistinct (tempTable, tempTable[0].size () - 1);
				int j;
				for (j = 0; j < classCounts.size (); ++j)
				{
					double temp = (double) classCounts[j];
					entropy -= (temp / classCounts[classCounts.size () - 1]) * (log (temp / classCounts[classCounts.size () - 1]) / log (2));
				}
				attributeEntropy.push_back (entropy);
				entropy = 0.0;
			}
		}
		for (i = 0; i < counts.size () - 1; ++i)
		{
			columnEntropy += ((double) counts[i] * (double) attributeEntropy[i]);
		}
		columnEntropy = columnEntropy / ((double) counts[counts.size () - 1]);
		if (columnEntropy <= minEntropy)
		{
			minEntropy = columnEntropy;
			splittingColumn = column;
		}
	}
	return table[0][splittingColumn];
}

// returns the index of a column in a subtable
int returnColumnIndex (string & columnName, vvs & tableInfo)
{
	int i;
	for (i = 0; i < tableInfo.size (); ++i)
	{
		if (tableInfo[i][0] == columnName)
		{
			return i;
		}
	}
	return -1;
}

// returns true if a subtable is empty
bool tableIsEmpty (vvs & table)
{
	return (table.size () == 1);
}

// recursively prints decision tree
void printDecisionTree (node * nodePtr)
{
	if (nodePtr == NULL)
	{
		return;
	}
	if (!nodePtr->children.empty ())
	{
		cout << " Value: " << nodePtr->label << endl;
		cout << "Split on: " << nodePtr->splitOn;
		int i;
		for (i = 0; i < nodePtr->children.size (); ++i)
		{
			cout << "\t";
			printDecisionTree (nodePtr->children[i]);
		}
		return;
	}
	else
	{
		cout << "Predicted class = " << nodePtr->label<<endl;
		return;
	}
}

//test the test dataset by decision tree
string testDataOnDecisionTree (vs & singleLine, node * nodePtr, vvs & tableInfo, string defaultClass)
{
	string prediction;
	//corner case
	if(nodePtr->isLeaf && nodePtr->children.empty())
	{
		return nodePtr->label;
	}

	while (!nodePtr->isLeaf && !nodePtr->children.empty ())
	{
		int index = returnColumnIndex (nodePtr->splitOn, tableInfo);
		string value = singleLine[index];
		int childIndex = returnIndexOfVector (nodePtr->childrenValues, value);
		if(childIndex==-1)
		{
			return defaultClass;
		}
		nodePtr = nodePtr->children[childIndex];
		if (nodePtr == NULL)
		{
			prediction = defaultClass;
			break;
		}
		prediction = nodePtr->label;
	}
	return prediction;
}

// return the index of value in stringVector
int returnIndexOfVector (vs & stringVector, string value)
{
	int i;
	for (i = 0; i < stringVector.size (); ++i)
	{
		if (stringVector[i] == value)
		{
			return i;
		}
	}
	return -1;
}

// output the predictions to file and returns the accuracy of the classification
double printPredictionsAndCalculateAccuracy (vs & givenData, vs & predictions)
{
	ofstream outputFile;
	outputFile.open ("test_data_output.txt");
	int correct = 0;
	outputFile << setw (3) << "#" << setw (16) << "Given Class" << setw (31) << right << "Predicted Class" << endl;
	outputFile << "**************************************************" << endl;
	for (int i = 0; i < givenData.size (); ++i)
	{
		outputFile << setw (3) << i + 1 << setw (16) << deCalssLabelMap(givenData[i]);
		if (givenData[i] == predictions[i])
		{
			++correct;
			outputFile << "  ------------  ";
		}
		else
		{
			outputFile << "  xxxxxxxxxxxx  ";
		}
		outputFile << deCalssLabelMap(predictions[i]) << endl;
	}
	outputFile << "**************************************************" << endl;
	outputFile << "Total number of instances in test data = " << givenData.size () << endl;
	outputFile << "Number of correctly predicted instances = " << correct << endl<<endl;
	outputFile.close ();
	return (double) correct / predictions.size() * 100;
}

// generate info about the data table which contains the value of each attribute 
vvs generateTableInfo (vvs & dataTable)
{
	vvs tableInfo;
	for (int i = 0; i < dataTable[0].size (); ++i)
	{
		vs tempInfo;
		msi tempMap;
		for (int j = 0; j < dataTable.size (); ++j)
		{
			if (tempMap.count (dataTable[j][i]) == 0)
			{
				tempMap[dataTable[j][i]] = 1;
				tempInfo.push_back (dataTable[j][i]);
			}
			else
			{
				++tempMap[dataTable[j][i]];
			}
		}
		tableInfo.push_back (tempInfo);
	}
	return tableInfo;
}

// return the most frequent class from the training data. This class is used as the default class during the testing phase
string returnMostFrequentClass (vvs & dataTable)
{
	msi trainingClasses;		// Stores the classlabels and their frequency
	for (int i = 1; i < dataTable.size (); ++i)
	{
		if (trainingClasses.count (dataTable[i][dataTable[0].size () - 1]) == 0)
		{
			trainingClasses[dataTable[i][dataTable[0].size () - 1]] = 1;
		}
		else
		{
			++trainingClasses[dataTable[i][dataTable[0].size () - 1]];
		}
	}
	msi::iterator mit = trainingClasses.begin (), mie = trainingClasses.end ();
	int highestClassCount = 0;
	string mostFrequentClass;
	for (; mit != mie; ++mit)
	{
		if (mit->second >= highestClassCount)
		{
			highestClassCount = mit->second;
			mostFrequentClass = mit->first;
		}
	}
	return mostFrequentClass;
}
