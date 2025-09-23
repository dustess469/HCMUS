#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include <direct.h>
#include <queue>
#include <fstream>
#include <Windows.h>
#include "Volume.h"
#include "VolumeInfo.h"
#include "Entry.h"
#include "SHA256.h"
void GoToXY(int x, int y) {
	COORD coords;
	coords.X = x;
	coords.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coords);
}
int RecursivePrint(Entry* e, int x, int y) {
	vector<Entry*> subEntryList = e->SubEntryList();
	if (subEntryList.size() == 0)
		return y - 1;
	for (int i = 0; i < subEntryList.size(); ++i) {
		GoToXY(x, y);
		string name = subEntryList[i]->GetFileName();
		cout << '|' << name;
		if (subEntryList[i]->IsFolder())
			if (subEntryList[i]->SubEntryList().size() != 0) {
				cout << '|';
			y = RecursivePrint(subEntryList[i], x + name.length() + 1, y + 1);
		}
		++y;
	}
	return y-1;
}
void showEntries(const vector<Entry*>& entries) {
	int x = 0;
	int y = 0;
	system("cls");
	for (int i = 0; i < entries.size(); ++i) {
		GoToXY(x, y);
		Entry* e = entries[i];

		bool hasParent = false;
		for (int j = i; j >= 0; --j)
			if (e->IsParent(entries[j])) {
				hasParent = true;
				break;
			}
		if (hasParent)
			continue;

		string name = e->GetFileName();
		cout << name;
		if (e->IsFolder())
			if (e->SubEntryList().size() != 0) {
				cout << '|';
			y = RecursivePrint(e, x + name.length(), y + 1);
			}
		++y;
	}
}
void menuVolume(FILE* fp, VolumeInfo* v, vector<char>& fatTable) {
	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		cout
			<< "1. VIEW FILE LIST\n"
			<< "2. CHANGE PASSWORD\n"
			<< "3. IMPORT FILE\n"
			<< "4. EXPORT FILE\n"
			<< "5. DELETE FILE\n"
			<< "6. CHANGE FILE PASSWORD\n"
			<< "0. RETURN MENU\n"
			<< "ENTER: ";
		cin >> choice;
		cin.ignore();
		system("cls");
		string sourcePath = "";
		string sourceName = "";
		string targetName = "";
		string password = "";
		vector<Entry*> entries;
		string nameForDel = "";
		string pw;
		SHA256 pw256;
		bool isExist = false;
		string changePWFile = "";
		switch (choice)
		{
		case 1:
			entries = Volume::listEntry(fp, v, fatTable);
			showEntries(entries);
			Volume::ListEntryFreeMemory(entries);
			cout << endl;
			system("pause");
			break;
		case 2:
			cout << "Please enter the old password: ";
			getline(cin, pw);
			if (v->checkPassword(pw)) {
				cout << "Please enter the new password: ";
				getline(cin, pw);
				v->SetVolPass(pw);
				fseek(fp, 0, SEEK_SET);
				v->writeVolInfo(fp);
				cout << "SUCCESS!\n";
			}
			else
				cout << "WRONG PASSWORD!\n";
			system("pause");
			break;
		case 3:
			cout << "Please enter the path file/folder you want to import: ";
			getline(cin, sourcePath);
			cout << "Nhap ten file luu: ";
			getline(cin, targetName);
			cout << "Please enter the password: ";
			cin >> password;
			cin.ignore();
			if (Volume::saveFileToData(fp, v, fatTable, sourcePath, targetName, password)) 
				cout << "SUCCESS!\n";
			else
				cout << "ERROR OR NOT ENOUGH CAPACITY!\n";
			system("pause");
			break;
		case 4:
			if (entries.size() == 0)
				entries = Volume::listEntry(fp, v, fatTable);
			for (int i = 0; i < entries.size(); i++) {
				cout << "Name: ";
				cout << entries[i]->Name() << endl;
				cout << "Path: ";
				cout << entries[i]->Path() << endl;
				cout << '\n';
			}
			cout << "Please enter the path file/folder you want to export\nFROM: ";
			getline(cin, sourceName);
			cout << "TO: ";
			getline(cin, targetName);
			if (Volume::exportFile(fp, v, fatTable, entries, sourceName, targetName))
				cout << "SUCCESS!\n";
			else 
				cout << "FILE NOT EXIST OR WRONG PASSWORD!\n";
			system("pause");
			break;
		case 5:
			cout << "Please enter the name of the file you want to delete: ";
			cin >> nameForDel;
			if (entries.size() == 0)
				entries = Volume::listEntry(fp, v, fatTable);
			if (Volume::deleteFile(fp, v, fatTable, nameForDel, entries)) 
				cout << "SUCCESS!\n";
			else 
				cout << "FILE NOT EXIST OR WRONG PASSWORD!\n";
			system("pause");
			break;
		case 6:
			isExist = false;
			cout << "Nhap ten file can doi mat khau: ";
			getline(cin, changePWFile);
			if (entries.size() == 0)
				entries = Volume::listEntry(fp, v, fatTable);

			for (int i = 0; i < entries.size(); ++i) {
				if (entries[i]->Name() == changePWFile) {
					isExist = true;
					cout << "Nhap mat khau cua file: ";
					getline(cin, pw);
					//mat khau dung
					if (entries[i]->checkPassword(pw)) {
						cout << "Nhap mat khau moi: "; getline(cin, pw);
						entries[i]->changePassword(pw);
						cout << "Doi mat khau thanh cong!\n";
					}
					else
						cout << "Sai mat khau!\n";
				}
			}

			if (isExist == false) {
				cout << "File khong ton tai";
			}
			system("pause");
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}
void main()
{
	FILE* f = nullptr;
	errno_t err;
	VolumeInfo* volumeInfo;
	vector<char> fatTable;
	int choice = -1;
	string name = "";
	int MB = 0; 
	while (choice != 0)
	{
		system("cls");
		cout << "1. CREATE VOLUME MyFS.DRS\n"
			 << "2. OPEN VOLUME\n"
			 << "0. EXIT\n"
			 << "ENTER: ";
		cin >> choice;
		cin.ignore();
		system("cls");
		switch (choice)	{
			case 1:
				cout << "Please enter the name of the volume you want to create: ";
				getline(cin, name);
				cout << "Please enter the size of the volume you want to create (in MB) - it should be greater than 0: ";
				cin >> MB;
				cin.ignore();

				Volume::initVolume(name, MB * 1024 * 1024);
				cout << "SUCCESS!" << endl;
				system("pause");
				break;
			case 2:
				cout << "Please enter the name of the volume you want to open: ";
				getline(cin, name);
				err = fopen_s(&f, name.c_str(), "rb+");
				if (err == 0) {
					volumeInfo = Volume::readVolumeInfo(f);
					//Check signature
					if (volumeInfo->Signature() != 0x24534D50) {
						cout << "WRONG SIGNATURE!" << endl;
						break;
					}
					//Check password
					string password;
					cout << "Please enter the password: ";
					getline(cin, password);
					if (volumeInfo->checkPassword(password)) {
						fatTable = Volume::readFatTable(f, volumeInfo);
						menuVolume(f, volumeInfo, fatTable);
					}
					else
						cout << "WRONG PASSWORD!\n";
					fclose(f);
					delete volumeInfo;
				}
				else
					cout << "NOT EXIST!" << endl;
				system("pause");
				break;
			case 0:
				if (f)
					fclose(f);
			default:
				break;
		}
	}
}
