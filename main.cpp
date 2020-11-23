#include <bits/stdc++.h>
#include <sstream>
#include <bitset>
#include "include/cache.h"
#include "include/dm.h"
#include "include/sa.h"

using namespace std;

int main(){

	/* Declaring cache space for both caches */
	string mem_dm[65536] = {"000000000000000000000000000000000"};
	string ** mem_sa = new string *[65536];
	for(int i = 0; i < 65536; i++){
		mem_sa[i] = new string[4];
		for(int j = 0; j < 4; j++){
			mem_sa[i][j] = "000000000000000000000000000000000";
		}
	}

	int ** eviction_table = new int *[65536];
	for(int i = 0; i < 65536; i++){
		eviction_table[i] = new int[4];
	}

	/* Test input trace files */
	string files[] = {"test/traces/gcc.trace","test/traces/gzip.trace","test/traces/mcf.trace","test/traces/swim.trace", "test/traces/twolf.trace"};

	/* Input and processing */
	char action;
	string address;
	int twy;
	fstream fout;
	fout.open("output.log", ios::out);
	if(!fout){
		cerr << "ERR: Could not create log file" << endl;
		return 1; 
	}
	for(string file: files){
		/* Cache objects */
		DirectMapped * dm = new DirectMapped(mem_dm, 65536, 4);
		SetAssociative * sa = new SetAssociative(mem_sa, 65536, 4, 4, eviction_table);

		/* Helper data */
		unsigned int hits_dm = 0;
		unsigned int misses_dm = 0;

		unsigned int hits_sa = 0;
		unsigned int misses_sa = 0;
		ifstream test(file);
		while(test >> action >> address >> twy){
			
			stringstream ss;
			ss << hex << address;
			unsigned int n;
			ss >> n;
			bitset<32> b(n);
			string bitfield = b.to_string();
			if(sa->load(bitfield)) hits_sa++;
			else misses_sa++;

			if(dm->load(bitfield)) hits_dm++;
			else misses_dm++;
		}

		/* Output */

		fout << "FILE: " << file << endl << endl;
		fout << "	DirectMapped: " << endl;
		fout << "		Hits: " << hits_dm << endl;
		fout << "		Misses: " << misses_dm << endl;
		fout << "		Hit %: " << 100 * (float)hits_dm/float(hits_dm + misses_dm) << endl;
		fout << "		Miss %: " << 100 * (1 - ((float)hits_dm/float(hits_dm + misses_dm))) << endl;
		fout << "		Hit/Miss: " << (float)hits_dm/float(hits_dm + misses_dm) / (1 - ((float)hits_dm/float(hits_dm + misses_dm))) << endl << endl;

		fout << "	SetAssociative: " << endl;
		fout << "		Hits: " << hits_sa << endl;
		fout << "		Misses: " << misses_sa << endl;
		fout << "		Hit %: " << 100 * (float)hits_sa/float(hits_sa + misses_sa) << endl;
		fout << "		Miss %: " << 100 * (1 - ((float)hits_sa/float(hits_sa + misses_sa))) << endl;
		fout << "		Hit/Miss: " << (float)hits_sa/float(hits_sa + misses_sa) / (1 - ((float)hits_sa/float(hits_sa + misses_sa))) << endl << endl;

		fout << "	Total: " << hits_dm + misses_dm << endl << endl;

		cout << "FILE: " << file << endl << endl;
		cout << "	DirectMapped: " << endl;
		cout << "		Hits: " << hits_dm << endl;
		cout << "		Misses: " << misses_dm << endl;
		cout << "		Hit %: " << 100 * (float)hits_dm/float(hits_dm + misses_dm) << endl;
		cout << "		Miss %: " << 100 * (1 - ((float)hits_dm/float(hits_dm + misses_dm))) << endl;
		cout << "		Hit/Miss: " << (float)hits_dm/float(hits_dm + misses_dm) / (1 - ((float)hits_dm/float(hits_dm + misses_dm))) << endl << endl;

		cout << "	SetAssociative: " << endl;
		cout << "		Hits: " << hits_sa << endl;
		cout << "		Misses: " << misses_sa << endl;
		cout << "		Hit %: " << 100 * (float)hits_sa/float(hits_sa + misses_sa) << endl;
		cout << "		Miss %: " << 100 * (1 - ((float)hits_sa/float(hits_sa + misses_sa))) << endl;
		cout << "		Hit/Miss: " << (float)hits_sa/float(hits_sa + misses_sa) / (1 - ((float)hits_sa/float(hits_sa + misses_sa))) << endl << endl;

		cout << "	Total: " << hits_dm + misses_dm << endl << endl;
	}
	fout.close();
	cout << "Output log saved to output.log" << endl;
	return 0;
}