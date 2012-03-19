#include "Header.h"

void main()
{
	//Create reg-key
	HKEY   hKey;
	RegCreateKeyExA(HKEY_LOCAL_MACHINE, "SAM\\Saveli", 0, NULL, 0, KEY_ALL_ACCESS , NULL, &hKey,0);

	//Read and Show data from file 
	fstream file("out.txt",ios::in);
	vector<string> strData;
	char tmp[29];
	
	cout << "====Data from File====\n";
	for(int i = 0; i < 12; i++) {
		file.getline(tmp,29);
		strData.push_back(tmp);
		cout << strData[i].c_str() << endl;
	}
	file.close();

	//Set all values in Register and show them
	string var, value;
	int index = 0;

	cout << "\n====Data from Registry====\n";
	for(int i = 0; i < 12; i++) {
		index = strData[i].find_first_of(" ");
		var = strData[i].substr(0,index-1);
		value = strData[i].substr(index+1,-1);	
		DWORD size = value.size() + 1;

		RegSetValueExA(hKey,var.c_str(),0,REG_SZ,(const BYTE*)value.c_str(),size);

		value.clear();
		RegQueryValueExA(hKey,var.c_str(),NULL,NULL,(BYTE*)value.c_str(),&size);
		cout << var.c_str() << ": " << value.c_str() << endl;
	}

	
	RegCloseKey(hKey);
	system("pause");
} 


