#include "pch.h"
#include "readchecklist.h"

bool IsNumber(const string& s) {
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void ReadCheckList() {
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcat_s(path, "\\rules");

	if (PathFileExistsA(path)) {
		strcat_s(path, "\\rules.csv");

		if (PathFileExistsA(path)) {
			ifstream f(path);
			if (!f.is_open()) {
				MessageBoxA(NULL, "failed to open rules/rules.csv", "Error", MB_OK | MB_ICONERROR);
				return;
			}
			
			string l;
			string d = ",";
			while (getline(f, l)) {
				string apiname = l.substr(0, l.find(d));
				int isChecked = stoi(l.substr(apiname.length()+d.length(), l.find(d)));
				
				for (int i = 0; i < hooklist.size(); i++) {
					if (hooklist[i].isOrdinal) {
						if (IsNumber(apiname)) {
							if (hooklist[i].func.ordinal == stoi(apiname)) {
								hooklist[i].isChecked = isChecked;
							}
						}
						else continue;
					}
					else {
						if (hooklist[i].func.name == apiname) {
							hooklist[i].isChecked = isChecked;
						}
					}
				}
			}
		}
		else {
			MessageBoxA(NULL, "rules/rules.csv doesn't exists", "Erorr", MB_OK | MB_ICONERROR);
			return;
		}
	}
}