#include "VolumeInfo.h"
VolumeInfo::VolumeInfo(uint32_t volumeSize)
{
	this->_Signature = 0x24534D50;
	this->_NumberOfEntry = 0;
	this->_SizeEntryTable = 0;
	this->_OffsetEntryTable = 0;
	this->_VolumeSize = volumeSize;
}
bool VolumeInfo::checkPassword(string pw) {
	SHA256 sha256;
	string pwToCheck = sha256(pw);
	return (this->volPass.compare(pwToCheck) == 0);
}
void VolumeInfo::writeVolInfo(FILE* f)
{
	fwrite(&this->_Signature, 1, sizeof(this->_Signature), f);
	fwrite(&this->_SizeEntryTable, 1, sizeof(this->_SizeEntryTable), f);
	fwrite(&this->_NumberOfEntry, 1, sizeof(this->_NumberOfEntry), f);
	fwrite(&this->_OffsetEntryTable, 1, sizeof(this->_OffsetEntryTable), f);
	fwrite(&this->_VolumeSize, 1, sizeof(this->_VolumeSize), f);
	SHA256 pw256;
	string pw = pw256(this->volPass);
	this->volPass = pw;
	this->volPassSize = this->volPass.size();
	fwrite(&this->volPassSize, 1, sizeof(this->volPassSize), f);
	fwrite(this->volPass.c_str(), 1, this->volPassSize, f);
	fclose(f);
}
void VolumeInfo::readVolInfo(FILE* f)
{
	fread(&this->_Signature, 1, sizeof(this->_Signature), f);
	fread(&this->_SizeEntryTable, 1, sizeof(this->_SizeEntryTable), f);
	fread(&this->_NumberOfEntry, 1, sizeof(this->_NumberOfEntry), f);
	fread(&this->_OffsetEntryTable, 1, sizeof(this->_OffsetEntryTable), f);
	fread(&this->_VolumeSize, 1, sizeof(this->_VolumeSize), f);
	fread(&this->volPassSize, 1, sizeof(this->volPassSize), f);
	string password(this->volPassSize, '\0');
	fread(&password[0], sizeof(char), this->volPassSize, f);
	this->volPass = password;
}
void VolumeInfo::UpdateVol(FILE* f) {
	fseek(f, sizeof(this->_Signature), SEEK_SET);
	fwrite(&this->_SizeEntryTable, 1, sizeof(this->_Signature), f);
	fwrite(&this->_NumberOfEntry, 1, sizeof(this->_NumberOfEntry), f);
}