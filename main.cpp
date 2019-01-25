// new site creation.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream>
#include <fstream>
#include<string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int i = 0, config = 4, j = 0, L = 0, x = 0, freqtest = 1, inputHolder = 0, REF_CELL = 500, TRX_TOTAL = 24, n = 0, bsctype = 1;
	string MIP, CPIP, SRCIP1 , SRCIP2 , SRCIP3 = "0.0.0.0", SRCIP4; string bcsutype, etptype;
int b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, w = 0, u = 0, ci = 0, abistype = 0, sctpport = 0,BCS=1, BCS1 = 1, BCS2=0,SMMP = 30, SMCUP = 30;
	int BCF=15,BTS=0,CID=1145,NCC[6],BCC[6],HSN[6],LAC=211,BAND=0,BCSU,SECTOR[6];
	int E1_1=779,E1_2=780,E1_3=781,E1_4,X,y=1,Z=30,P=31,Q=31,R=31,TMSLT2=0,TMSLT3=0,TMSLT4=0,TMSLT1=0,S=1;//y =TEI and X is a variable used to toggle e1s.
	char name [30]="NoNameGiven",r[2]="T";int vlan=3020,DIFF=900;
	char a [37]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int z=0;//used to add bts on name eg namez=name1 for cell 1 naming
	int RAC=0,DAP,DAP1,DAP2,cells,REALBCF=0;
	int F1=78,F2=24,F3=3,M=500,N=0,ETPE,smmp=30,smcup=30;
	int TRX_FRQ[6][8],NO_OF_E1S=0,o=0;
	cout<<"Welcome to erlalcy the terrible's mml generator it assumes you are an engineer who can follow simple instruction with a strict GIGO policy....garbage in garbage out :) \n"<<endl;
	cout << "Enter BCF \n"; cin >> BCF; REALBCF = BCF;
	cout<<"Enter site ID\n";cin>>CID;
	cout << "Press 1 if BSC is MCBC and 0 if FBSC\n"; cin >> bsctype;
	if (bsctype == 1)
	{
		bcsutype = "BCXU";
		etptype = "ETME";
	}
	else 
	{
		bcsutype = "BCSU";
		etptype = "ETP";
	}

	ci=CID*10;
	cout<<"Kindly enter number of cells \n";cin>>cells;
	if (cells<6)
	{cout<<"Enter the cell IDs sequentially pressing enter after each entry\n";
	for(i=0;i<cells;i++)
		cin>>SECTOR[i];}
	else
		{for(i=0;i<cells;i++)
		{SECTOR[i]=ci++;}
		for(i=3;i<=cells;i++)
		{SECTOR[i]++;}}

	cout<<"Define tx mode ? press \n 1 for packet abis new site creation  \n 2 for TDM new site creation \n 3 for TDM to  packet abis conversion\n";
	cin>>abistype;
	if (abistype == 1)
	{
		cout << "Enter the name of this site in upper case \n"; cin >> name;
		cout << "Enter management ip as issued \n"; cin >> MIP;
		cout << "Enter control plane  ip\n"; cin >> CPIP;
		cout << "Enter VLAN ID  (ZQRI:ETPE) \n"; cin >> vlan;
		cout << "Enter Subnet for  control plane  ip (e.g. 30)\n"; cin >> smcup;
		cout << "Enter Subnet for  management plane  ip (e.g. 30)\n"; cin >> smmp;
		cout << "RUN ZUSI ETPE and enter etpe number to be used. \n Compare with other BCFs to determine which ETPE is to be used\n"; cin >> ETPE;
		cout << " Enter BCSU to be used \n"; cin >> BCS1;

		cout << "Run ZQRI Comamnd on BCSU: " << BCS1 << "  and enter BCSU OMUSIG IP \n"; cin >> SRCIP1;
		cout << "Run ZQRI Comamnd on BCSU: " << BCS1 << "  and enter BCSU TRXSIG IP \n"; cin >> SRCIP2;

		cout << " Enter a seconf BCSU to be used \n"; cin >> BCS2;
		cout << "Run ZQRI Comamnd on BCSU: " << BCS2 << "  and enter BCSU TRXSIG IP \n"; cin >> SRCIP4;


		if (cells == 6)
		{
			cout << "Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n" << "1\n" << "2\n" << "4\n" << "5\n" << "6\n" << endl;
			cin >> g >> b >> c >> d >> e >> f;
			TRX_TOTAL = g + b + c + d + e + f;
		}
		else if (cells == 5)
		{
			cout << "Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n" << "1\n" << "2\n" << "4\n" << "5" << endl;
			cin >> g >> b >> c >> d >> e;
			TRX_TOTAL = g + b + c + d + e;
		}
		else if (cells == 4)
		{
			cout << "Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n" << "1\n" << "2\n" << "4" << endl;
			cin >> g >> b >> c >> d;
			TRX_TOTAL = g + b + c + d;
		}
		else if (cells == 3)
		{
			cout << "Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n" << "1\n" << "2" << endl;
			cin >> g >> b >> c;
			TRX_TOTAL = g + b + c;
		}
		else if (cells == 2)
		{
			cout << "Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n" << "1\n" << "2" << endl;
			cin >> g >> b;
			TRX_TOTAL = g + b;
		}
		else if (cells == 1)
		{
			cout << "Enter The total number of TRXs of the cell \n" << endl;
			cin >> g; TRX_TOTAL = g;
		}
		//cout<<"Enter Refefence BTS.  This sould be a "<<cells<<" cell site  \n";
		//cin>>M;	
		cout << "Run ZOYV command and enter the next free sctp port number. \n  This value should be btwn 49152-63535 and ENSURE EACH SITE HAS 36 SO SKIP 40 FROM OMU SCTP OF LAST SITE allow for trx expansion" << endl;
		cin >> sctpport;
		ofstream myfile;
		myfile.open("MML.txt");
		{
			myfile << "\n";
			myfile << "\n";
			myfile << "ZOYX:BCF0" << BCF << "OMU:IUA:S:" << bcsutype << "," << BCS << ":PACKETABIS:64:;\n";
			myfile << "ZOYP:IUA:BCF0" << BCF << "OMU:\"" << SRCIP1 << "\",," << sctpport << ":\"" << MIP << "\"," << smmp << ",,," << sctpport << ":;\n";
			myfile << "ZDWP:P" << BCF << ":" << bcsutype << "," << BCS << ":62,1:BCF0" << BCF << "OMU,;\n";
			myfile << "ZOYS:IUA:BCF0" << BCF << "OMU:ACT:;\n";

			myfile << "\n";
			myfile << "\n";
			sctpport = sctpport + 1;
			for (i = 1; i <= TRX_TOTAL; i++)
			{
				if (i % 2 == 0) { BCS = BCS1; SRCIP3 = SRCIP2; }
				else
				{
					BCS = BCS2; SRCIP3 = SRCIP4;
				}

				myfile << "ZOYX:BCF0" << REALBCF << "TRX0" << i << ":IUA:S:" << bcsutype << "," << BCS << ":PACKETABIS::; \n";
				myfile << "ZOYP:IUA:BCF0" << REALBCF << "TRX0" << i << ":\"" << SRCIP3 << "\",," << sctpport << ":\"" << CPIP << "\"," << smcup << ",,," << sctpport << ";\n";
				if (BCF < 1000)
				{
					myfile << "ZDWP:S" << BCF << a[i] << ":" << bcsutype << "," << BCS << ":0," << i << ":BCF0" << REALBCF << "TRX0" << i << ",:;\n"; DIFF = BCF;
				}
				else if ((BCF >= 1000)&(BCF < 2000))
				{
					DIFF = BCF - 900;
					myfile << "ZDWP:S" << DIFF << a[i] << ":" << bcsutype << "," << BCS << ":0," << i << ":BCF0" << REALBCF << "TRX0" << i << ",:;\n";

				}
				else if ((BCF >= 2000)&(BCF <= 3000))
				{
					DIFF = BCF - 1900;
					myfile << "ZDWP:S" << DIFF << a[i] << ":" << bcsutype << "," << BCS << ":0," << i << ":BCF0" << REALBCF << "TRX0" << i << ",:;\n";

				}

				myfile << "\n"; sctpport++;
			}

			//y=0;


			REF_CELL = M;
			//y=0;
			for (i = 1; i <= TRX_TOTAL; i++)
			{
				myfile << "ZOYS:IUA:BCF0" << REALBCF << "TRX0" << i << ":ACT:;\n";
			}
			myfile << "\n";

			int MR10 = 1;
			cout << "is the site MR10 or flexi multi radio? press 1 for MR 10 and 2 for flexi MR\n";
			cin >> MR10;
			BCF = REALBCF;
			if (MR10 == 1)
				myfile << "ZEFC:" << BCF << ",M,R,2:DNAME=P" << BCF << ",:::::BMIP=" << MIP << ",SMMP=" << smmp << "," << etptype << "ID=" << ETPE << ":;\n";// creating bcf
			else
				myfile << "ZEFC:" << BCF << ",M,F,2:DNAME=P" << BCF << ",:::::BMIP=" << MIP << ",SMMP=" << smcup << "," << etptype << "GID=" << ETPE << ":;\n";// creating bcf
			myfile << "ZEFM:" << BCF << "::T200F=400,T200S=1200;\n";
			myfile << "ZEFM:" << BCF << "::::VLANID=" << vlan << ",;\n";
			myfile << "ZEFM:" << BCF << "::::BCUIP=" << CPIP << ",SMCUP=" << smcup << ",:;\n";
			myfile << "\n";
			cout << "Enter the LAC for this site." << endl << "CROSSCHECK THE PARAMETERS YOU HAVE ENTERED BEFORE PRESSING ENTER \n";
			cin >> LAC;
			if (cells <= 3)
			{
				cout << "Enter the band for this cells: either 900 or 1800)" << endl;
				cin >> BAND;
			}
			cout << "Enter Refefence BCF.\n";
			cin >> N;
			if (LAC <= 256)RAC = LAC;
			else
			{
				cout << "Enter RAC for this site.\n";
				cin >> RAC;
			}L = BAND;
			TMSLT1 = 1; TMSLT2 = 1; TMSLT3 = 1;
			BTS = BCF; // getting bts parameters amd creating btss)*/

			ifstream myData("NCC.txt");
			if (!myData) { cout << "Couldn't open file!\n"; }
			for (i = 0; i < cells; i++) {
				myData >> inputHolder;
				NCC[i] = inputHolder;
			}

			{ ifstream myData("BCC.txt");
			if (!myData) { cout << "Couldn't open file!\n"; }
			for (i = 0; i < cells; i++) {
				myData >> inputHolder;
				BCC[i] = inputHolder;
			}}

			{ifstream myData("HSN.txt");
			if (!myData) { cout << "Couldn't open file!\n"; }
			for (i = 0; i < cells; i++) {
				myData >> inputHolder;
				HSN[i] = inputHolder;
			}}
			M = N;
			if (cells > 3)

			{
				for (z = 0; z < cells; z++)
				{
					if (z < 3) { BAND = 900; x = z; }
					else { BAND = 1800; x = z + 1; }

					myfile << "ZEQC:BCF=" << BCF << ",BTS=" << BTS << ",NAME=" << name << x << ",SEG=" << BTS << ",SEGNAME=" << name << x << ",REF=" << M << ":CI=" << SECTOR[z] << ",BAND=" << BAND << ":NCC=" << NCC[z] << ",BCC=" << BCC[z] << ":MCC=639,MNC=02,LAC=" << LAC << ":HOP=RF,HSN1=" << HSN[z] << ",:GENA=Y,RAC=" << RAC << ",:;\n";
					BTS++; x++; M++;
				}
			}
			else //multi bcf implementation
			{
				x = 4;
				for (z = 0; z < cells; z++)
				{


					myfile << "ZEQC:BCF=" << BCF << ",BTS=" << BTS << ",NAME=" << name << x << ",SEG=" << BTS << ",SEGNAME=" << name << x << ",REF=" << M << ":CI=" << SECTOR[z] << ",BAND=" << BAND << ":NCC=" << NCC[z] << ",BCC=" << BCC[z] << ":MCC=639,MNC=02,LAC=" << LAC << ":HOP=RF,HSN1=" << HSN[z] << ",:GENA=Y,RAC=" << RAC << ",:;\n";
					BTS++; x++;
				}
			}
			myfile << "\n"; myfile << "\n";
			BTS = BCF; myfile << endl;
			x = 0; i = 0; j = 0; u = 0;

			{ifstream myData("frequency.txt");
			{ if (!myData) { cout << "Couldn't open file!\n"; } i = 0;
			for (i = 0; i < cells; i++)
			{ { if (i == 0) u = g; else if (i == 1) u = b; else if (i == 2) u = c; else if (i == 3) u = d; else if (i == 4) u = e; else if (i == 5) u = f; else u = 6; }
			for (j = 0; j < u; j++)
			{
				myData >> inputHolder;
				TRX_FRQ[i][j] = 0;
				TRX_FRQ[i][j] = inputHolder;
			}
			}}}
			i = 0;
			for (i = 0; i < cells; i++)
			{
				if (cells < 3) BAND = L;
				else { if (i < 3) BAND = 900; else BAND = 1800; }
				if (i == 0) w = g - 1; else if (i == 1) w = b - 1; else if (i == 2) w = c - 1; else if (i == 3) w = d - 1; else if (i == 4) w = e - 1; else if (i == 5) w = f - 1;
				if (w == 8)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << "&" << TRX_FRQ[i][4] << "&" << TRX_FRQ[i][5] << "&" << TRX_FRQ[i][6] << "&" << TRX_FRQ[i][7] << "&" << TRX_FRQ[i][8] << ";" << endl;
				if (w == 7)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << "&" << TRX_FRQ[i][4] << "&" << TRX_FRQ[i][5] << "&" << TRX_FRQ[i][6] << "&" << TRX_FRQ[i][7] << ";" << ";" << endl;
				if (w == 6)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << "&" << TRX_FRQ[i][4] << "&" << TRX_FRQ[i][5] << "&" << TRX_FRQ[i][6] << ";" << endl;
				if (w == 5)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << "&" << TRX_FRQ[i][4] << "&" << TRX_FRQ[i][5] << ";" << endl;
				if (w == 4)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << "&" << TRX_FRQ[i][4] << ";" << endl;
				if (w == 3)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << "&" << TRX_FRQ[i][3] << ";" << endl;
				if (w == 2)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << "&" << TRX_FRQ[i][2] << ";" << endl;
				if (w == 1)
					myfile << "ZEBE:MAL," << BTS << "," << BAND << ":FREQ=" << TRX_FRQ[i][1] << ";" << endl;
				BTS++;
			}
			BTS = BCF; myfile << endl;
			for (i = 0; i < cells; i++)
			{
				myfile << "ZEQA:BTS=" << BTS << ":MAL=" << BTS << ",MO=0,MS=1;\n";
				BTS++;
			}
			myfile << "\n";
			DAP1 = BCF; DAP2 = BCF + 1;
			S = 1; TMSLT1 = 1; TMSLT2 = 1; TMSLT3 = 1; TMSLT4 = 1; o = 0; z = 0;


















			for (y = 1; y <= TRX_TOTAL; y++)
			{



				if ((y == 1) || (y == (g + 1)) || (y == (g + b + 1)) || (y == (b + b + c + 1)) || (y == (g + b + c + d + 1)) || (y == (g + b + c + d + e + 1)))
				{
					

					
					
					
					o = 0;
					if (y <= g)
					{
						BTS = BCF; n = g;
					}

					else if (y <= (g + b))
					{
						BTS = BCF + 1; n = b;
					}
					else if (y <= (g + b + c))
					{
						BTS = BCF + 2; n = c;
					}
					else if (y <= (g + b + c + d))
					{
						BTS = BCF + 3; n = d;
					}
					else if (y <= (g + b + c + d + e))
					{
						BTS = BCF + 4; n = e;
					}
					else if (y <= TRX_TOTAL)
					{
						BTS = BCF + 5; n = f;
					}
					z = BTS - BCF;
					myfile << endl; o = 0;
					if (TRX_FRQ[z][o] == ((9 || 10 || 11 || 12 || 13 || 14 || 15 || 16 || 17 || 18 || 19 || 20 || 21 || 22 || 23 || 24 || 763 || 764 || 765 || 766 || 767 || 768 || 769 || 770 || 771 || 772 || 773 || 774 || 813 || 814 || 815 || 816 || 817 || 818 || 819 || 820 || 821 || 824)))
					{


						myfile << "ZERC:BTS=" << BTS << ",TRX=" << y << ":PREF=P,GTRX=Y,:FREQ=" << TRX_FRQ[z][o] << ",TSC=" << BCC[z] << ",:DNAME=S" << DIFF << a[y] << ":CH0=MBCCH,CH1=SDCCH,CH2=CCCHE,CH3=SDCCH,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
					}

					else
					{
						//cout << "crosscheck your BCCH Frequencies press 1 to continue" << endl; cin >> freqtest;
						myfile.open("error_log.txt");
						myfile << TRX_FRQ[z][o] << "  is not allowed in BCCH list" << endl;
						myfile.close();

					}


					
					
				}
				else if ((y == 2) || (y == (g + 2)) || (y == (b + g + 2)) || (y == (c + b + g + 2)) || (y == (c + b + g + d + 2)) || (y == (b + c + d + g + e + 2)))
				{
					myfile << "ZERC:BTS=" << BTS << ",TRX=" << y << ":GTRX=Y:FREQ=" << TRX_FRQ[z][o] << ",TSC=" << BCC[z] << ":DNAME=S" << DIFF << a[y] << ":CH0=SDCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
				}


				else
					myfile << "ZERC:BTS=" << BTS << ",TRX=" << y << ":GTRX=N:FREQ=" << TRX_FRQ[z][o] << ",TSC=" << BCC[z] << ":DNAME=S" << DIFF << a[y] << ":CH0=TCHD,CH1=TCHD,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
				o++;
			}


			BTS = BCF; M = N;
			myfile << "\n";
			for (z = 0; z < cells; z++)
			{
				myfile << "ZEQV:BTS=" << BTS << ":CDED=20,CDEF=70,CMAX=100;\n";

				BTS++;
			}
			BTS = BCF; myfile << "\n";
			for (z = 0; z < cells; z++)
			{
				myfile << "ZEQV:BTS=" << BTS << ":GENA=Y;\n";
				myfile << "ZEQM:BTS=" << BTS << ":RDIV=Y,;\n";
				BTS++;
			}REF_CELL = M;
			BTS = BCF; myfile << "\n";
			for (z = 0; z < cells; z++)
			{
				myfile << "ZEUC:BTS=" << BTS << ",REF=" << M << ":;\n";
				BTS++; M++;
			}BTS = BCF; myfile << "\n"; M = N;
			for (z = 0; z < cells; z++)
			{
				myfile << "ZEHC:BTS=" << BTS << ",REF=" << M << ":;\n";
				BTS++; M++;






			}BTS = BCF; myfile << "\n";
			X = 1;
			for (y = 0; y < TRX_TOTAL; y++)
			{
				if (y <= g)
				{
					BTS = BCF; n = g; X = 1;
				}

				else if (y <= (g + b))
				{
					BTS = BCF + 1; n = (g + b); X = g + 1;
				}
				else if (y <= (g + b + c))
				{
					BTS = BCF + 2; n = (g + b + c); X = g + b + 1;
				}
				else if (y <= (g + b + c + d))
				{
					BTS = BCF + 3; n = (g + b + c + d); X = g + b + c + 1;
				}
				else if (y <= (g + b + c + d + e))
				{
					BTS = BCF + 4; n = (g + b + c + d + e); X = g + b + c + d + 1;
				}
				else if (y <= TRX_TOTAL)
				{
					BTS = BCF + 5; n = TRX_TOTAL; X = g + b + c + d + e + 1;
				}
				if ((y == 1) || (y == (g + 1)) || (y == (g + b + 1)) || (y == (g + b + c + 1)) || (y == (g + b + c + d + 1)) || (y == (g + b + c + d + e + 1)))
					myfile << "ZERS:BTS=" << BTS << ",TRX=" << X << "&&" << n << ",:U:;\n";
			}

			BTS = BCF; myfile << "\n";
			for (z = 0; z < cells; z++)
			{
				myfile << "ZEQS:BTS=" << BTS << ":U;\n";
				BTS++;
			}myfile << "\n";
			for (z = 1; z < 19; z++)
			{
				if (z == 6 || z == 3 || z == 5 || z == 14 || z == 16 || z == 18)
				{
					myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << z << ",SEV=AL3:;\n";
				}
				else if (z == 1)
				{
					ci = 30; myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << ci << ",SEV=AL3:;\n";
				}
				else if (z == 10) { ci = 32; myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << ci << ",SEV=AL3:;\n"; }
				else if (z == 12) {
					ci = 31;
					myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << ci << ",SEV=AL2:;\n";
				}
				else if (z == 2 || z == 7 || z == 4)
					myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << z << ",SEV=AL1:;\n";
				else if (z == 15)
					myfile << "ZEFX:" << BCF << ":INBR=" << z << ":ROU=ACT,POL=OPEN,:TID=" << z << ",SEV=AL2:;\n";
			}
			myfile << "\n"; myfile << "\n";
			myfile << "\n"; myfile << "\n";
			myfile << "\n"; myfile << "\n";
			//myfile <<"/*please remember to attach software to BCF ZEWA,  confirm alarm TID if matching corresponding alarm text as this may vary per BSC*/\n";
			myfile.close(); }
	}


	else if (abistype==2)
	
	{cout<<"How e1s does this site have?Type in number eg 2 or 3 for 2 or 3 e1s \n";cin>>NO_OF_E1S;
if (NO_OF_E1S==4)
	{cout<<"Hi kindly type in the:   "<<NO_OF_E1S<<" ETs for this site.press enter after each entry \n";cin>>E1_1>>E1_2>>E1_3>>E1_4;}
else if (NO_OF_E1S==3)
	{cout<<"Hi kindly type in the:  "<<NO_OF_E1S<<"  ETs for this site.press enter after each entry \n";
cin>>E1_1>>E1_2>>E1_3;}
else if (NO_OF_E1S==2)
	{cout<<"Hi kindly type in the:   "<<NO_OF_E1S<<" ETs for this site.press enter after each entry \n";
cin>>E1_1>>E1_2;}
else if (NO_OF_E1S==1)
	{cout<<"Hi kindly type in the:   "<<NO_OF_E1S<<"  ETs for this site.to press enter after each entry \n";
cin>>E1_1;}
else cout<<"The number of E1s for this site is incorrect!\n";
		cout<<"Enter the name of this site in upper case \n";cin>>name;
		//cout<<"Enter site ID\n";cin>>CID;
		if (cells==6)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4\n"<<"5\n"<<"6\n"<<endl;
		cin>>g>>b>>c>>d>>e>>f;
		TRX_TOTAL=g+b+c+d+e+f;}
		else if (cells==5)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4\n"<<"5"<<endl;
		cin>>g>>b>>c>>d>>e;
		TRX_TOTAL=g+b+c+d+e;}
		else if (cells==4)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4"<<endl;
		cin>>g>>b>>c>>d;
		TRX_TOTAL=g+b+c+d;}
		else if (cells==3)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2"<<endl;
		cin>>g>>b>>c;
		TRX_TOTAL=g+b+c;}
		else if (cells==2)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2"<<endl;
		cin>>g>>b;
	TRX_TOTAL=g+b;}
		else if (cells==1)
		{cout<<"Enter The total number of TRXs of the cell \n"<<endl;
		cin>>g;TRX_TOTAL=g;}
		//cout<<"Enter Refefence BTS.  This sould be a "<<cells<<" cell site  \n";
		//cin>>M;	
  ofstream myfile;
  myfile.open ("MML.txt");
  {
	myfile <<"\n";
		myfile <<"\n";
myfile << "ZDSE:B"<<BCF<<",:BCSU,1:62,1:64,"<<E1_1<<"-31::; \n";
myfile <<"ZDTC:B"<<BCF<<":WO;\n";
myfile <<"\n";
y=0;
if (NO_OF_E1S==4)
	for (y=1;y<=TRX_TOTAL;y++)  
	{
	{if (((y%4==0)||(y==1)||(y==(g+b+c+1))||(y==(g+b+c+d+e+1)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)))
			{X=E1_1;BCSU=0;
		myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Z<<","<<TMSLT1<<"::;\n";
		if (TMSLT1==0)TMSLT1=+4;
		else
		{TMSLT1=0;Z--;}}
		else if((y%3==0||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+d+1)))&&(y!=TRX_TOTAL)&&(y!=(g+b+c+d+e))&&(y!=g))
			{X=E1_2;BCSU=1;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<P<<","<<TMSLT2<<"::;\n";
		if (TMSLT2==0)TMSLT2=+4;
		else
		{TMSLT2=0;P--;}}
	else if((y%4==0))
			{X=E1_3;BCSU=1;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<R<<","<<TMSLT2<<"::;\n";
		if (TMSLT4==0)TMSLT4=+4;
		else
		{TMSLT4=0;P--;}}
		else {X=E1_4;BCSU=2;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Q<<","<<TMSLT3<<"::;\n";
		if (TMSLT3==0)TMSLT3=+4;
		else
		{TMSLT3=0;Q--;}}}}
else if (NO_OF_E1S==3)
	for (y=1;y<=TRX_TOTAL;y++)  
	{
	{if (((y%4==0)||(y==1)||(y==(g+b+c+1))||(y==(g+b+c+d+e+1)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)))
			{X=E1_1;BCSU=0;
		myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Z<<","<<TMSLT1<<"::;\n";
		if (TMSLT1==0)TMSLT1=+4;
		else
		{TMSLT1=0;Z--;}}
		else if ((y%3==0||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+d+1)))&&(y!=TRX_TOTAL)&&(y!=(g+b+c+d+e))&&(y!=g))
			{X=E1_2;BCSU=1;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<P<<","<<TMSLT2<<"::;\n";
		if (TMSLT2==0)TMSLT2=+4;
		else
		{TMSLT2=0;P--;}}
		else {X=E1_3;BCSU=2;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Q<<","<<TMSLT3<<"::;\n";
		if (TMSLT3==0)TMSLT3=+4;
		else
		{TMSLT3=0;Q--;}}}}
	else if (NO_OF_E1S==2)
	for (y=1;y<=TRX_TOTAL;y++) 
			{if(((y%2==0)||(y==1)||(y==(g+b+c+d+e+1))||(y==(g+b+c+d+e+f)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)&&((y!=(g+b+c+1)))&&((y!=(g+b+c+d+1)))))
			{X=E1_1;BCSU=0;
		myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Z<<","<<TMSLT1<<"::;\n";
		if (TMSLT1==0)TMSLT1=+4;
		else
		{TMSLT1=0;Z--;}}
		else {X=E1_2;BCSU=1;myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Q<<","<<TMSLT2<<"::;\n";
		if (TMSLT2==0)TMSLT2=+4;
		else
		{TMSLT2=0;Q--;}}}
	
	else if (NO_OF_E1S==1)
	for (y=1;y<=TRX_TOTAL;y++) 
			{X=E1_1;
				if(((y%2==0)||(y==1)||(y==(g+b+c+d+e+1))||(y==(g+b+c+d+e+f)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)&&((y!=(g+b+c+1)))&&((y!=(g+b+c+d+1)))))
				{BCSU=0;}else BCSU=1;
		myfile <<"ZDSE:T"<<BCF<<a[y]<<",:BCSU,"<<BCSU<<":0,"<<y<<":32,"<<X<<"-"<<Z<<","<<TMSLT1<<"::;\n";
		if (TMSLT1==0)TMSLT1=+4;
		else
		{TMSLT1=0;Z--;}}
		



	myfile <<"\n";
	REF_CELL=M;
	y=0;
  for (y=1;y<=TRX_TOTAL;y++)
  {myfile <<"ZDTC:T"<<BCF<<a[y]<<":WO;\n";}
  	myfile <<"\n";
  int MR10=1;
	cout<<"is the site MR10 or flexi multi radio? press 1 for MR 10 and 2 for flexi MR\n";
	cin>>MR10;
	if (MR10==1)
  myfile<<"ZEFC:"<<BCF<<",M,R,0:DNAME=B"<<BCF<<",::::;\n";// creating bcf
	else
myfile<<"ZEFC:"<<BCF<<",M,F,0:DNAME=B"<<BCF<<",::::;\n";// creating bcf
  myfile<<"ZEFM:"<<BCF<<"::T200F=400,T200S=1200;\n";
  if (NO_OF_E1S==3)
myfile<<"ZEFM:"<<BCF<<":::TRS2=1,:::;\n";
  	myfile <<"\n";
  cout<<"Enter the LAC for this site."<<endl<<"CROSSCHECK THE PARAMETERS YOU HAVE ENTERED BEFORE PRESSING ENTER \n";
  cin>>LAC;
  if (cells<=3)
  {cout<<"Enter the band for this cells: either 900 or 1800)"<<endl;
  cin>>BAND;}
    cout<<"Enter Refefence BCF.\n";
		cin>>N;	
  if (LAC<=256)RAC=LAC;
		else {cout<<"Enter RAC for this site./n";
		cin>>RAC;};L=BAND;
		TMSLT1=1;TMSLT2=1;TMSLT3=1;
  BTS=BCF; // getting bts parameters amd creating btss)
  
ifstream myData("NCC.txt");
 if (!myData)   {cout << "Couldn't open file!\n";}  
 for (i=0;i<cells;i++){
	myData >>inputHolder;
		NCC[i]=inputHolder;}

{ ifstream myData("BCC.txt");
 if (!myData)   {cout << "Couldn't open file!\n";}  
 for (i=0;i<cells;i++){
	myData >>inputHolder;
	BCC[i]=inputHolder;}}

 {ifstream myData("HSN.txt");
 if (!myData)   {cout << "Couldn't open file!\n";}  
 for (i=0;i<cells;i++){
	myData >>inputHolder;
	HSN[i]=inputHolder;}}
 M=N;
 if (cells>3)

	{for (z=0;z<cells;z++)
  { 
	 if (z<3){BAND=900;x=z;}else {BAND=1800;x=z+1;}

   myfile << "ZEQC:BCF="<<BCF<<",BTS="<<BTS<<",NAME="<<name<<x<<",SEG="<<BTS<<",SEGNAME="<<name<<x<<",REF="<<M<<":CI="<<SECTOR[z]<<",BAND="<<BAND<<":NCC="<<NCC[z]<<",BCC="<<BCC[z]<<":MCC=639,MNC=02,LAC="<<LAC<<":HOP=RF,HSN1="<<HSN[z]<<",:GENA=N,RAC="<<RAC<<",:;\n";
   BTS++;x++;M++;}}
 else //multi bcf implementation
	  {x=4;
		  for (z=0;z<cells;z++)
  { 
	 

   myfile << "ZEQC:BCF="<<BCF<<",BTS="<<BTS<<",NAME="<<name<<x<<",SEG="<<BTS<<",SEGNAME="<<name<<x<<",REF="<<M<<":CI="<<SECTOR[z]<<",BAND="<<BAND<<":NCC="<<NCC[z]<<",BCC="<<BCC[z]<<":MCC=639,MNC=02,LAC="<<LAC<<":HOP=RF,HSN1="<<HSN[z]<<",:GENA=N,RAC="<<RAC<<",:;\n";
   BTS++;x++;}}
 myfile <<"\n";myfile <<"\n";
  if(NO_OF_E1S==1)
  { myfile <<"ZESE:ID="<<BCF<<",PSEI=0,CRCT="<<E1_1<<"-21,SIZE=5:;\n";}
 else if (TRX_TOTAL>20&&NO_OF_E1S<3){
  myfile <<"ZESE:ID="<<BCF<<",PSEI=0,CRCT="<<E1_1<<"-23,SIZE=3:;\n";
 myfile <<"ZESE:ID="<<BCF+1<<",PSEI=0,CRCT="<<E1_2<<"-23,SIZE=3:;\n";}
 else
	  {myfile <<"ZESE:ID="<<BCF<<",PSEI=0,CRCT="<<E1_1<<"-21,SIZE=5:;\n";
 myfile <<"ZESE:ID="<<BCF+1<<",PSEI=0,CRCT="<<E1_2<<"-21,SIZE=5:;\n";}
  BTS=BCF;myfile <<endl;
  x=0;i=0;j=0;u=0;
  
  {ifstream myData("frequency.txt");
{ if (!myData)   {cout << "Couldn't open file!\n";} i=0; 
 for (i=0;i<cells;i++)
{ { if (i==0) u=g;else if (i==1) u=b; else if (i==2) u=c; else if (i==3) u=d;else if (i==4) u=e;else if (i==5) u=f;else u=6;}
		for (j=0;j<u;j++)
	{myData >>inputHolder;
 TRX_FRQ[i][j]=0;
 TRX_FRQ[i][j]=inputHolder;}}}}
  i=0;
  for (i=0;i<cells;i++)
  {
	  if(cells<3) BAND=L;
	  else{ if (i<3) BAND=900; else BAND=1800;}
if (i==0) w=g-1;else if (i==1) w=b-1;else if (i==2) w=c-1;else if (i==3) w=d-1;else if (i==4) w=e-1;else if (i==5) w=f-1;
if (w==8)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<"&"<<TRX_FRQ[i][4]<<"&"<<TRX_FRQ[i][5]<<"&"<<TRX_FRQ[i][6]<<"&"<<TRX_FRQ[i][7]<<"&"<<TRX_FRQ[i][8]<<";"<<endl;
if (w==7)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<"&"<<TRX_FRQ[i][4]<<"&"<<TRX_FRQ[i][5]<<"&"<<TRX_FRQ[i][6]<<"&"<<TRX_FRQ[i][7]<<";"<<";"<<endl;
if (w==6)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<"&"<<TRX_FRQ[i][4]<<"&"<<TRX_FRQ[i][5]<<"&"<<TRX_FRQ[i][6]<<";"<<endl;
if (w==5)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<"&"<<TRX_FRQ[i][4]<<"&"<<TRX_FRQ[i][5]<<";"<<endl;
if (w==4)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<"&"<<TRX_FRQ[i][4]<<";"<<endl;
if (w==3)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<"&"<<TRX_FRQ[i][3]<<";"<<endl;
if (w==2)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<"&"<<TRX_FRQ[i][2]<<";"<<endl;
if (w==1)
   myfile <<"ZEBE:MAL,"<<BTS<<","<<BAND<<":FREQ="<<TRX_FRQ[i][1]<<";"<<endl;
   BTS++;} 
  BTS=BCF;myfile <<endl;
  for (i=0;i<cells;i++)
  {
   myfile <<"ZEQA:BTS="<<BTS<<":MAL="<<BTS<<",MO=0,MS=1;\n";
   BTS++;} 
  	myfile <<"\n";
  DAP1=BCF;DAP2=BCF+1;
  S=1;TMSLT1=1;TMSLT2=1;TMSLT3=1;TMSLT4=1;o=0;
  for (y=1;y<=TRX_TOTAL;y++)
  {
	  if((y==1)||(y==(g+1))||(y==(g+b+1))||(y==(b+b+c+1))||(y==(g+b+c+d+1))||(y==(g+b+c+d+e+1)))
		  o=0;
if (y<=g)
{ BTS=BCF;n=g;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=b;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=c;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=d;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=e;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=f;}
  
  if(NO_OF_E1S==4)

 {if (((y%4==0)||(y==1)||(y==(g+b+c+1))||(y==(g+b+c+d+e+1)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)))
 {X=E1_1;}
		else if ((y%3==0||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+d+1)))&&(y!=TRX_TOTAL)&&(y!=(g+b+c+d+e))&&(y!=g))
		{X=E1_2;}
		else if ((y%5==0))
		{X=E1_3;}
		else {X=E1_4;}
  }

 else if(NO_OF_E1S==3)
 { if (((y%4==0)||(y==1)||(y==(g+b+c+1))||(y==(g+b+c+d+e+1)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)))
 {X=E1_1;}
		else if ((y%3==0||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+d+1)))&&(y!=TRX_TOTAL)&&(y!=(g+b+c+d+e))&&(y!=g))
		{X=E1_2;}
		else {X=E1_3;}}

 else if(NO_OF_E1S==2)
 {if (((y%2==0)||(y==1)||(y==(g+b+c+d+e+1))||(y==(g+b+c+d+e+f)))&&((y!=(g+b+1))&&(y!=TRX_TOTAL)&&((y!=(g+b+c+1)))&&((y!=(g+b+c+d+1)))))
 {X=E1_1;}
		else 
		{X=E1_2;}
		}
 else
X=E1_1;

z=BTS-BCF;
if (X==E1_1)
{DAP=DAP1;S=TMSLT1;TMSLT1=TMSLT1+2;}
else if (X==E1_2)
{DAP=DAP2;S=TMSLT2;TMSLT2=TMSLT2+2;}
else if (X==E1_3)
{S=TMSLT3;TMSLT3=TMSLT3+2;}
else
{S=TMSLT4;TMSLT4=TMSLT4+2;}
if (o>=n)
	{o=0;

 if ((y==1)||(y==(g+1))||(y==(b+g+1))||(y==(c+b+g+1))||(y==(c+b+g+d+1))||(y==(b+c+d+g+e+1))||(y==(b+c+d+g+e+f+1)))
 {myfile <<endl;o=0;
 myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":PREF=P,GTRX=Y,DAP="<<DAP<<",:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=MBCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
 }else if ((y==2)||(y==(g+2))||(y==(b+g+2))||(y==(c+b+g+2))||(y==(c+b+g+d+2))||(y==(b+c+d+g+e+2)))
  {myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=SDCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";}
 
 
 else  myfile <<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=TCHD,CH1=TCHD,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
o++;}
else
	{
  
  if ((y==1)||(y==(g+1))||(y==(b+g+1))||(y==(c+b+g+1))||(y==(c+b+g+d+1))||(y==(b+c+d+g+e+1))){
	  myfile <<endl;
   myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":PREF=P,GTRX=Y,DAP="<<DAP<<",:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=MBCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
  o=0;}
  else if ((y==2)||(y==(g+2))||(y==(b+g+2))||(y==(c+b+g+2))||(y==(c+b+g+d+2))||(y==(b+c+d+g+e+2)))
  {myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=SDCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";}
 else
{myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",PCMTSL="<<X<<"-"<<S<<":DNAME=T"<<BCF<<a[y]<<":CH0=TCHD,CH1=TCHD,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
  }o++;
  

  
   
  }
  }
  }

  BTS=BCF;M=N;
  myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEQV:BTS="<<BTS<<":CDED=20,CDEF=70,CMAX=100;\n";
  BTS++;
  }
  BTS=BCF;myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEQV:BTS="<<BTS<<":GENA=Y;\n";
  myfile <<"ZEQM:BTS="<<BTS<<":RDIV=Y,;\n";
  BTS++;}REF_CELL=M;
  BTS=BCF;myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEUC:BTS="<<BTS<<",REF="<<M<<":;\n";
  BTS++;M++;}BTS=BCF;myfile <<"\n";M=N;
   for (z=0;z<cells;z++)
 {myfile <<"ZEHC:BTS="<<BTS<<",REF="<<M<<":;\n";
  BTS++;M++;
   
   
   
   
   
   
   }BTS=BCF;myfile <<"\n";
X=1;
 for (y=0;y<TRX_TOTAL;y++)
 {if (y<=g)
{ BTS=BCF;n=g;X=1;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=(g+b);X=g+1;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=(g+b+c);X=g+b+1;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=(g+b+c+d);X=g+b+c+1;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=(g+b+c+d+e);X=g+b+c+d+1;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=TRX_TOTAL;X=g+b+c+d+e+1;}
 if ((y==1)||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+1))||(y==(g+b+c+d+1))||(y==(g+b+c+d+e+1)))
	 myfile <<"ZERS:BTS="<<BTS<<",TRX="<<X<<"&&"<<n<<",:U:;\n";
  }
 
 BTS=BCF;myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEQS:BTS="<<BTS<<":U;\n";
  BTS++;}myfile <<"\n";
   for (z=1;z<19;z++)
	   {if(z==6||z==3||z==5||z==14||z==16||z==18)
	   {
		   myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<z<<",SEV=AL3:;\n";}
	   else if(z==1)
	   {ci=30;myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<ci<<",SEV=AL3:;\n";}
	   else if(z==10){ ci=32;myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<ci<<",SEV=AL3:;\n";}
	   else if(z==12) {ci=31;
	   myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<ci<<",SEV=AL2:;\n";}
	   else if(z==2||z==7||z==4)
   myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<z<<",SEV=AL1:;\n";
     else if(z==15)
   myfile <<"ZEFX:"<<BCF<<":INBR="<<z<<":ROU=ACT,POL=OPEN,:TID="<<z<<",SEV=AL2:;\n";
   }
  myfile <<"\n";myfile <<"\n";
  myfile <<"\n";myfile <<"\n";
  myfile <<"\n";myfile <<"\n";
  //myfile <<"/*please remember to attach software to BCF ZEWA,  confirm alarm TID if matching corresponding alarm text as this may vary per BSC*/\n";
  myfile.close();}


  else if (abistype==3)
		{
	cout<<"Enter the name of this site in upper case \n";cin>>name;
		cout<<"Enter management ip as issued \n";cin>>MIP;
		cout<<"Enter control plane  ip\n";cin>>CPIP;
		cout<<"Enter Subnet for  control plane  ip (e.g. 30)\n";cin>>smcup;
		cout<<"Enter Subnet for  management plane  ip (e.g. 30)\n";cin>>smmp;
			cout<<"Enter VLAN ID  (ZQRI:ETPE) \n";cin>>vlan;
		cout<<"RUN ZUSI ETPE and enter etpe number to be used. \n Compare with other BCFs to determine which ETPE is to be used\n";cin>>ETPE;
		cout<<" Enter BCSU to be used \n";cin>>BCS;
		cout<<"Run ZQRI Comamnd on BCSU: "<<BCS<<"  and enter BCSU VLAN400 IP \n";cin>>SRCIP1;
		cout<<"Run ZQRI Comamnd on BCSU: "<<BCS<<"  and enter BCSU VLAN410 IP \n";cin>>SRCIP2;
		
		if (cells==6)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4\n"<<"5\n"<<"6\n"<<endl;
		cin>>g>>b>>c>>d>>e>>f;
		TRX_TOTAL=g+b+c+d+e+f;}
		else if (cells==5)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4\n"<<"5"<<endl;
		cin>>g>>b>>c>>d>>e;
		TRX_TOTAL=g+b+c+d+e;}
		else if (cells==4)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2\n"<<"4"<<endl;
		cin>>g>>b>>c>>d;
		TRX_TOTAL=g+b+c+d;}
		else if (cells==3)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2"<<endl;
		cin>>g>>b>>c;
		TRX_TOTAL=g+b+c;}
		else if (cells==2)
		{cout<<"Enter The total number of TRXs per cell pressing enter after each entry for cell :     0\n"<<"1\n"<<"2"<<endl;
		cin>>g>>b;
	TRX_TOTAL=g+b;}
		else if (cells==1)
		{cout<<"Enter The total number of TRXs of the cell \n"<<endl;
		cin>>g;TRX_TOTAL=g;}
		
		cout<<"Run ZOYV command and enter the next free sctp port number. \n  This value should be btwn 49152-63535 and ENSURE EACH SITE HAS 36 SO SKIP 40 FROM OMU SCTP OF LAST SITE allow for trx expansion"<<endl;
		cin>>sctpport;
  ofstream myfile;
  myfile.open (("Packet-Abis MML.txt"));
  {
	myfile <<"\n";
		myfile <<"\n";
		BTS=BCF;myfile <<"\n";

		for (z=0;z<cells;z++)
 {myfile <<"ZEQS:BTS="<<BTS<<":L;\n";
  BTS++;}myfile <<"\n";BTS=BCF;
   for (z=0;z<cells;z++)
 {myfile <<"ZEQV:BTS="<<BTS<<":GENA=N;\n";
  BTS++;}
   X=1;
 for (y=0;y<TRX_TOTAL;y++)
 {if (y<=g)
{ BTS=BCF;n=g;X=1;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=(g+b);X=g+1;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=(g+b+c);X=g+b+1;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=(g+b+c+d);X=g+b+c+1;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=(g+b+c+d+e);X=g+b+c+d+1;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=TRX_TOTAL;X=g+b+c+d+e+1;}
 if ((y==1)||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+1))||(y==(g+b+c+d+1))||(y==(g+b+c+d+e+1)))
	 myfile <<"ZERS:BTS="<<BTS<<",TRX="<<1<<"&&"<<36<<",:L:;\n";
  }
 

myfile << "ZOYX:BCF0"<<BCF<<"OMU:IUA:S:" << bcsutype << ","<<BCS<<":PACKETABIS:64:;\n";
myfile<<"ZOYP:IUA:BCF0"<<BCF<<"OMU:\""<<SRCIP1<<"\",,"<<sctpport<<":\""<<MIP<<"\","<<smmp<<",,,"<<sctpport<<":;\n";
myfile <<"ZDWP:P"<<BCF<<":" << bcsutype << ","<<BCS<<":62,1:BCF0"<<BCF<<"OMU,;\n";
	myfile <<"ZOYS:IUA:BCF0"<<BCF<<"OMU:ACT:;\n";

myfile <<"\n";
		myfile <<"\n";
sctpport=sctpport+1;
  for (y=1;y<=TRX_TOTAL;y++)
{myfile << "ZOYX:BCF0"<<BCF<<"TRX0"<<y<<":IUA:S:" << bcsutype << ","<<BCS<<":PACKETABIS::; \n";
myfile<<"ZOYP:IUA:BCF0"<<BCF<<"TRX0"<<y<<":\""<<SRCIP2<<"\",,"<<sctpport<<":\""<<CPIP<<"\","<<smcup<<",,,"<<sctpport<<";\n";
{if( BCF<1000)
myfile <<"ZDWP:S"<<BCF<<a[y]<<":" << bcsutype << ","<<BCS<<":0,"<<y<<":BCF0"<<BCF<<"TRX0"<<y<<",:;\n";
else if (BCF>=1000)
{
BCF=BCF-1000;
myfile <<"ZDWP:M"<<BCF<<a[y]<<":" << bcsutype << ","<<BCS<<":0,"<<y<<":BCF0"<<BCF<<"TRX0"<<y<<",:;\n";
}
myfile <<"\n";sctpport++;}}

  for (i=1;i<=TRX_TOTAL;i++)
  {myfile <<"ZOYS:IUA:BCF0"<<BCF<<"TRX0"<<i<<":ACT:;\n";}
  	myfile <<"\n";
	
	int MR10=1;
	myfile <<"ZEFS:"<<BCF<<":L;\n";
  for (y=1;y<=TRX_TOTAL;y++)
  {
	 
		{  o=0;
if (y<=g)
{ BTS=BCF;n=g;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=b;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=c;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=d;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=e;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=f;}
  z=BTS-BCF;
 {
 myfile <<"ZERD:BTS="<<BTS<<",TRX="<<y<<":;\n";
 }}}
 myfile<<"ZEFM:"<<BCF<<":AICT=2,DNAME=P"<<BCF<<",:::ETPGID="<<ETPE<<",SMCUP="<<smcup<<",BMIP="<<MIP<<",BCUIP="<<CPIP<<",SMMP="<<smmp<<",VLANID="<<vlan<<",;\n";// creating bcf
	
  	myfile <<"\n";
 

{ ifstream myData("BCC.txt");
 if (!myData)   {cout << "Couldn't open file!\n";}  
 for (i=0;i<cells;i++){
	myData >>inputHolder;
	BCC[i]=inputHolder;}}

 
  BTS=BCF;myfile <<endl;
  x=0;i=0;j=0;u=0;
  
  {ifstream myData("frequency.txt");
{ if (!myData)   {cout << "Couldn't open file!\n";} i=0; 
 for (i=0;i<cells;i++)
{ { if (i==0) u=g;else if (i==1) u=b; else if (i==2) u=c; else if (i==3) u=d;else if (i==4) u=e;else if (i==5) u=f;else u=6;}
		for (j=0;j<u;j++)
	{myData >>inputHolder;
 TRX_FRQ[i][j]=0;
 TRX_FRQ[i][j]=inputHolder;}}}}
  i=0;
 
  BTS=BCF;myfile <<endl;
 
  for (y=1;y<=TRX_TOTAL;y++)
  {
	 if((y==1)||(y==(g+1))||(y==(g+b+1))||(y==(b+b+c+1))||(y==(g+b+c+d+1))||(y==(g+b+c+d+e+1)))
		{  o=0;
if (y<=g)
{ BTS=BCF;n=g;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=b;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=c;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=d;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=e;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=f;}
  z=BTS-BCF;
 {myfile <<endl;o=0;
 myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":PREF=P,GTRX=Y,:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<",:DNAME=S"<<BCF<<a[y]<<":CH0=MBCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
 }}
 else if ((y==2)||(y==(g+2))||(y==(b+g+2))||(y==(c+b+g+2))||(y==(c+b+g+d+2))||(y==(b+c+d+g+e+2)))
  {myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<":DNAME=S"<<BCF<<a[y]<<":CH0=SDCCH,CH1=SDCCH,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";}
 
 
 else 
	 myfile <<"ZERC:BTS="<<BTS<<",TRX="<<y<<":GTRX=N:FREQ="<<TRX_FRQ[z][o]<<",TSC="<<BCC[z]<<":DNAME=S"<<BCF<<a[y]<<":CH0=TCHD,CH1=TCHD,CH2=TCHD,CH3=TCHD,CH4=TCHD,CH5=TCHD,CH6=TCHD,CH7=TCHD;\n";
o++;}

  }
  
BTS=BCF;M=N;
  myfile <<"\n";
  BTS=BCF;myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEQV:BTS="<<BTS<<":GENA=Y;\n";
   //myfile <<"ZEQM:BTS="<<BTS<<":RDIV=Y,;\n";
  BTS++;}REF_CELL=M;
  BTS=BCF;myfile <<"\n";
 

X=1;
 for (y=0;y<TRX_TOTAL;y++)
 {if (y<=g)
{ BTS=BCF;n=g;X=1;}

  else if (y<=(g+b))
  {BTS=BCF+1;n=(g+b);X=g+1;}
 else if (y<=(g+b+c))
 {BTS=BCF+2;n=(g+b+c);X=g+b+1;}
 else if (y<=(g+b+c+d))
 {BTS=BCF+3;n=(g+b+c+d);X=g+b+c+1;}
 else if (y<=(g+b+c+d+e))
 { BTS=BCF+4;n=(g+b+c+d+e);X=g+b+c+d+1;}
 else if (y<=TRX_TOTAL)
 {BTS=BCF+5;n=TRX_TOTAL;X=g+b+c+d+e+1;}
 if ((y==1)||(y==(g+1))||(y==(g+b+1))||(y==(g+b+c+1))||(y==(g+b+c+d+1))||(y==(g+b+c+d+e+1)))
	 myfile <<"ZERS:BTS="<<BTS<<",TRX="<<X<<"&&"<<n<<",:U:;\n";
  }
 
 BTS=BCF;myfile <<"\n";
  for (z=0;z<cells;z++)
 {myfile <<"ZEQS:BTS="<<BTS<<":U;\n";
  BTS++;}myfile <<"\n";
   
  myfile <<"\n";myfile <<"\n";
  myfile <<"\n";myfile <<"\n";
  myfile <<"\n";myfile <<"\n";
  //myfile <<"/*please remember to attach software to BCF ZEWA,  confirm alarm TID if matching corresponding alarm text as this may vary per BSC*/\n";
  myfile.close();

}


  return 0;
}
  
  
