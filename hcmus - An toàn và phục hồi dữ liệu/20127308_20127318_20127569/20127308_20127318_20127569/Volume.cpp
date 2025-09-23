#include"Volume.h"

void Volume::initVolume(string name, int volumeSize) {
	FILE *fp = nullptr;
	errno_t err = fopen_s(&fp, name.c_str(), "wb+");
	if (fp) {
		fseek(fp, volumeSize - 1, SEEK_SET);
		fwrite("", 1, 1, fp);
		fclose(fp);
	}
	err = fopen_s(&fp, name.c_str(), "rb+");
	if (fp) {
		string pw1, pw2;
		VolumeInfo* v = new VolumeInfo(volumeSize);
		while (true) {
			cout << "Please enter the password: "; cin >> pw1;
			cout << "Again: "; cin >> pw2;
			if (pw1.compare(pw2) == 0) {
				v->SetVolPass(pw1);
				break;
			}
			else
				cout << "NOT MATCH!";
		}
		v->writeVolInfo(fp);
		// CREATE FAT TABLE
		err = fopen_s(&fp, name.c_str(), "rb+");
		fseek(fp,v->volumeInfoSize(), SEEK_SET);
		int sizeTable = (volumeSize - sizeof(VolumeInfo)) / (CLUSTER_SIZE + 1);
		for (int i = 0; i < sizeTable; i++)
			fwrite("0", 1, 1, fp);
	}
	fclose(fp);
}
VolumeInfo* Volume::readVolumeInfo(FILE *fp) {
	VolumeInfo *v = new VolumeInfo();
	v->readVolInfo(fp);
	return v;
}
vector<char> Volume::readFatTable(FILE *fp, VolumeInfo* v) {
	vector<char> result;
	fseek(fp, v->volumeInfoSize(), SEEK_SET);
	int sizeTable = (v->VolumeSize() - v->volumeInfoSize()) / (CLUSTER_SIZE + 1);
	for (int i = 0; i < sizeTable; i++) {
		char c;
		fread(&c, 1, 1, fp);
		result.push_back(c);
	}
	return result;
}
vector<Entry*> Volume::listEntry(FILE *f, VolumeInfo *v, vector<char> fatTable) {
	vector<Entry*> res;
	int size = v->volumeInfoSize() + fatTable.size();
	for (int i = 0; i < v->NumberOfEntry(); i++) {
		fseek(f, size, SEEK_SET);
		Entry *e = new Entry();
		e->read(f);
		res.push_back(e);
		e->FindParent(res,i);
		size += CLUSTER_SIZE;
	}
	return res;
}
void Volume::ListEntryFreeMemory(vector<Entry*>& entries) {
	for (int i = 0; i < entries.size(); ++i)
		delete entries[i];
	entries.resize(0);
}
bool isEnoughSapce(int numberOfCluster, vector<char> fatTable, int k) {
	int noClus = numberOfCluster;
	bool found = true;
	for (int i = k; numberOfCluster > 0; i--, numberOfCluster--)
		if (fatTable[i] != '0')
			found = false;
	if (!found)
		for (int i = k; noClus > 0; i--, noClus--)
			if (fatTable[i] == '1')
				return false;
	return true;
}
int sizeOfFile(FILE *f) {
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
}
int Volume::FindEmptyCluster(vector<char> &fatTable, int size) {
	int numberOfClusters = size / CLUSTER_SIZE;
	int positionEnd = -1;
	for (int i = fatTable.size() - 1; i >= 0; i--) {
		if (fatTable[i] == '0') {
			if (isEnoughSapce(numberOfClusters, fatTable, i)) {
				positionEnd = i;
				break;
			}
			else
				i -= numberOfClusters;
		}
	}
	int positionStart = positionEnd - numberOfClusters;
	for (int i = positionStart; i <= positionEnd; i++)
		fatTable[i] = '1';
	return positionStart;
}
bool Volume::saveFileToData(FILE *&fp, VolumeInfo *&v, vector<char> &fatTable, string sourcePath, string targetName, 
	string password) {
	//Entries cua cac file hoac folder doc duoc khi import
	vector<Entry*> entries;
	//Ten File/Folder
	string sourceName = targetName;
	//Thong tin day du cua File/Folder
	WIN32_FIND_DATAA fileData;
	HANDLE handle = nullptr;
	//path o ngoai windows
	string pathOutside;
	//path trong volume
	string path;
	string parentPath;
	bool isFolder = false;
	//queue chua thong tin entry va Windows path cua folder
	queue<pair<Entry*,string>> s;

	handle = FindFirstFileA(sourcePath.c_str(), &fileData);
	FindClose(handle);
	if (handle == INVALID_HANDLE_VALUE)
		return false;
	//Neu la folder
	if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		isFolder = true;
		pathOutside = sourcePath;
		path = sourceName;
		Entry* e = new Entry(targetName.length(), password.length(), path.length(), isFolder, false, path, 
			targetName, password);
		entries.push_back(e);
		pathOutside += "\\*";
		s.push(make_pair(e,pathOutside));
		while (!s.empty()) {
			Entry* folder = s.front().first;
			parentPath = s.front().second;
			s.pop();
			handle = FindFirstFileA(parentPath.c_str(), &fileData);
			if (handle == INVALID_HANDLE_VALUE)
				return false;
			//Ignore 2 special directory . and ..
			FindNextFileA(handle, &fileData);
			//Check xem folder co trong hay khong
			bool notEmptyFolder = FindNextFileA(handle, &fileData);
			if (!notEmptyFolder)
				break;
			do {
				//path trong volume
				path =	sourceName
						+ parentPath.substr(sourcePath.length(), parentPath.length() - sourcePath.length() - 1)
						+ fileData.cFileName;
				//Neu la folder
				if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					isFolder = true;
					pathOutside = parentPath.substr(0,parentPath.length()-1) + fileData.cFileName + "\\*";
					Entry* e = new Entry(targetName.length(), password.length(), path.length(), isFolder, false, path,
						targetName, password);
					entries.push_back(e);
					folder->AddSubEntry(e);
					s.push(make_pair(e,pathOutside));
				}
				//Nguoc lai neu la file
				else {
					isFolder = false;
					FILE* source = nullptr;
					pathOutside = parentPath.substr(0,parentPath.length()-1) + fileData.cFileName;
					errno_t err = fopen_s(&source,pathOutside.c_str(), "rb+");
					if (err == EINVAL) {
						cout << "Cant open file\n";
						return false;
					}
					int size = sizeOfFile(source);
					char ch;
					//tim vi tri cluster trong
					int positionStart = FindEmptyCluster(fatTable, size);
					fseek(fp, v->volumeInfoSize() + fatTable.size() + 2048 * positionStart, SEEK_SET);
					//chep file
					char buffer[CLUSTER_SIZE];
					int n = size / CLUSTER_SIZE;
					for (int i = 0; i < n; ++i) {
						fread(buffer, 1, CLUSTER_SIZE, source);
						fwrite(buffer, 1, CLUSTER_SIZE, fp);
					}
					fread(buffer, 1, size % CLUSTER_SIZE,source);
					fwrite(buffer, 1, size % CLUSTER_SIZE, fp);
					Entry* e = new Entry(targetName.length(), password.length(), path.length(), isFolder, false,
						path, targetName, password, size, positionStart);
					folder->AddSubEntry(e);
					entries.push_back(e);
					fclose(source);
				}
			} while (FindNextFileA(handle, &fileData));
			FindClose(handle);
		}
	}
	//Nguoc lai neu la file
	else {
		string path = sourceName;
		isFolder = false;
		FILE* source = nullptr;
		errno_t err = fopen_s(&source, sourcePath.c_str(), "rb+");
		if (err == EINVAL) {
			cout << "Cant open file\n";
			return false;
		}
		size_t size = sizeOfFile(source);
		//Tim cluster trong
		int positionStart = FindEmptyCluster(fatTable, size);
		fseek(fp, v->volumeInfoSize() + fatTable.size() + 2048 * positionStart, SEEK_SET);
		//Chep file
		char buffer[CLUSTER_SIZE];
		int n = size / CLUSTER_SIZE;
		for (int i = 0; i < n; ++i) {
			fread(buffer, 1, CLUSTER_SIZE, source);
			fwrite(buffer, 1, CLUSTER_SIZE, fp);
		}
		fread(buffer, 1, size % CLUSTER_SIZE, source);
		fwrite(buffer, 1, size % CLUSTER_SIZE, fp);
		Entry* e = new Entry(targetName.length(), password.length(), path.length(), isFolder, false,
			path, targetName, password, size, positionStart);
		entries.push_back(e);
		fclose(source);
	}
	//Ghi entry vao volume
	for (int i = 0; i < entries.size(); ++i)
		entries[i]->add(fp, v, fatTable);
	//cap nhap fat table
	fseek(fp, v->volumeInfoSize(), SEEK_SET);
	for (int i = 0; i < fatTable.size(); i++) {
		char ch = fatTable[i];
		fputc(ch, fp);
	}
	ListEntryFreeMemory(entries);
	return true;
}
bool Volume::deleteFile(FILE* fp, VolumeInfo* v, vector<char>& fatTable, string name, vector<Entry*> listEntry) {
	bool isFound = false;
	Entry* e = nullptr;
	for (int i = 0; i < listEntry.size(); i++) {
		if (name == listEntry[i]->Name()) {
			isFound = true;
			e = listEntry[i];
			break;
		}
	}
	if (!isFound)
		return false;

	string pw;
	cin.ignore();
	cout << "Nhap mat khau file can xoa: "; getline(cin, pw);
	if (!e->checkPassword(pw))
		return false;

	e->SetIsDeleted(true);
	v->SetNumberOfEntry(v->NumberOfEntry() - 1);
	fatTable[e->FatPosition()] = '2';
	int numberOfCluster = e->SizeData() / CLUSTER_SIZE;
	int clusterStart = e->OffsetData();
	for (int i = clusterStart; i <= clusterStart + numberOfCluster; i++) {
		fatTable[i] = '2';
	}
	//cap nhap volume info
	//VolumeInfo* newvol = new Volume(v->)

	//cout << v->checkPassword("1") << endl;
	//cout << v->getvolPass() << endl;
	fseek(fp, 30, SEEK_SET);
	//long currentPosition = ftell(fp);
	//cout << currentPosition << endl;
	fwrite(v->VolPass().c_str(), 1, v->volPassLen(), fp);
	//cout << v->volPassLen() << endl;
	//cout << "qua duoc write" << endl;

	//currentPosition = ftell(fp);
	//cout << currentPosition << endl;

	//fwrite(v, 1, v->volumeInfoSize(), fp);
	//cout << sizeof(VolumeInfo) << " " << v->volumeInfoSize() << endl;
	//cout << "Pass afer delete: " << endl;
	//cout << readVolumeInfo(fp)->getvolPass() << endl;
	//cout << readVolumeInfo(fp)->checkPassword("1") << endl;
	//cap nhap fat table
	//fseek(fp, v->volumeInfoSize(), SEEK_SET);
	//cout << currentPosition << endl;
	for (int i = 0; i < fatTable.size(); i++) {
		char ch = fatTable[i];
		fputc(ch, fp);
	}
	//cap nhap entry
	fseek(fp, v->volumeInfoSize() + fatTable.size() + e->FatPosition() * CLUSTER_SIZE, SEEK_SET);
	fwrite(e, 1, sizeof(e), fp);
	return true;
}
//bool Volume::deleteFile(FILE *fp, VolumeInfo *v, vector<char> &fatTable, string name, vector<Entry*> listEntry) {
//	bool isFound = false;
//	Entry* e = nullptr;
//	for (int i = 0; i < listEntry.size(); i++) {
//		if (name == listEntry[i]->Name()) {
//			isFound = true;
//			e = listEntry[i];
//			break;
//		}
//	}
//	if (!isFound)
//		return false;
//
//	string pw;
//	cin.ignore();
//	cout << "Please enter the password: : "; getline(cin, pw);
//	if(!e->checkPassword(pw))
//		return false;
//
//	e->SetIsDeleted(true);
//	v->SetNumberOfEntry(v->NumberOfEntry() - 1);
//	fatTable[e->FatPosition()] = '2';
//	int numberOfCluster = e->SizeData() / CLUSTER_SIZE;
//	int clusterStart = e->OffsetData();
//	for (int i = clusterStart; i <= clusterStart + numberOfCluster; i++) {
//		fatTable[i] = '2';
//	}
//	//cap nhap volume info
//	fseek(fp, 0, SEEK_SET);
//	fwrite(v, 1, sizeof(VolumeInfo), fp);
//	//cap nhap fat table
//	fseek(fp, v->volumeInfoSize(), SEEK_SET);
//	for (int i = 0; i < fatTable.size(); i++) {
//		char ch = fatTable[i];
//		fputc(ch, fp);
//	}
//	//cap nhap entry
//	fseek(fp, sizeof(VolumeInfo) + fatTable.size() + e->FatPosition()*CLUSTER_SIZE, SEEK_SET);
//	fwrite(e, 1, sizeof(e), fp);
//	return true;
//}
bool Volume::exportFile(FILE *fp, VolumeInfo *v, const vector<char> &fatTable, const vector<Entry*> &listEntry, 
	string sourcePath, string targetPath) {
	bool isFound = false;
	Entry* exportingEntry = nullptr;
	queue<Entry*> s;
	//Path trong volume
	string path;
	//Path de ghi ben ngoai Windows
	string outputPath;
	for (int i = 0; i < listEntry.size(); i++) {
		if (sourcePath == listEntry[i]->Path()) {
			isFound = true;
			exportingEntry = listEntry[i];
			break;
		}
	}
	if (!isFound)
		return false;

	string pw;
	cout << "Please enter the password: "; getline(cin, pw);
	if (!exportingEntry->checkPassword(pw))
		return false;

	//Neu la folder
	if (exportingEntry->IsFolder()) {
		//root path
		string rootPath = exportingEntry->Path();
		string rootFolder;
		int pos = rootPath.find_last_of("\\");
		if (pos != string::npos) {
			outputPath = targetPath + "\\" + rootPath.substr(pos + 1);
			rootFolder = rootPath.substr(pos + 1);
		}
		else {
			outputPath = targetPath + "\\" + rootPath;
			rootFolder = rootPath;
		}
		int err = _mkdir(outputPath.c_str());
		if (err != 0) {
			cout << "Cannot create folder\n";
			return false;
		}
		s.push(exportingEntry);
		while (!s.empty()) {
			Entry* e = s.front();	
			s.pop();
			path = e->Path();
			//Path ngoai Windows nam trong directory muon export toi
			string parentPath;
			if (path.length() == rootPath.length())
				parentPath = rootFolder;
			else
				parentPath = rootFolder + path.substr(rootPath.length(), path.length() - rootPath.length());
			vector<Entry*> subEntryList = e->SubEntryList();
			for (int i = 0; i < subEntryList.size(); ++i) {
				//Neu la folder
				if (subEntryList[i]->IsFolder()) {
					path = subEntryList[i]->Path();
					outputPath = targetPath + "\\" + parentPath + path.substr(path.find_last_of("\\"));
					int err = _mkdir(outputPath.c_str());
					if (err != 0) {
						cout << "Cannot create folder\n";
						return false;
					}
					s.push(subEntryList[i]);
				}
				//Neu la file
				else {
					fseek(fp, v->volumeInfoSize() + fatTable.size() + subEntryList[i]->OffsetData() * CLUSTER_SIZE, SEEK_SET);
					int size = subEntryList[i]->SizeData();
					path = subEntryList[i]->Path();
					outputPath = targetPath + "\\" + parentPath + path.substr(path.find_last_of("\\"));
					FILE* target = nullptr;
					errno_t err = fopen_s(&target, outputPath.c_str(), "wb+");
					//Ghi file
					char buffer[BUFFER_SIZE];
					int n = size / BUFFER_SIZE;
					for (int i = 0; i < n; ++i) {
						fread(buffer, 1, BUFFER_SIZE, fp);
						fwrite(buffer, 1, BUFFER_SIZE, target);
					}
					fread(buffer, 1, size % BUFFER_SIZE, fp);
					fwrite(buffer, 1, size % BUFFER_SIZE, target);
					fclose(target);
				}
			}
		}
	}
	//Neu la file
	else {
		fseek(fp, v->volumeInfoSize() + fatTable.size() + exportingEntry->OffsetData() * CLUSTER_SIZE, SEEK_SET);
		int size = exportingEntry->SizeData();
		path = exportingEntry->Path();
		int pos = path.find_last_of("\\");
		if (pos != string::npos)
			outputPath = targetPath + "\\" + path.substr(pos + 1);
		else
			outputPath = targetPath + "\\" + path;
		FILE* target = nullptr;
		errno_t err = fopen_s(&target, outputPath.c_str(), "wb+");
		//Ghi file
		char buffer[BUFFER_SIZE];
		int n = size / BUFFER_SIZE;
		for (int i = 0; i < n; ++i) {
			fread(buffer, 1, BUFFER_SIZE, fp);
			fwrite(buffer, 1, BUFFER_SIZE, target);
		}
		fread(buffer, 1, size % BUFFER_SIZE, fp);
		fwrite(buffer, 1, size % BUFFER_SIZE, target);
		fclose(target);
	}
	return true;
}