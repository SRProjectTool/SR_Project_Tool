#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ConvertRelativePath(CString strFileFullPath);
	static DWORD FileCount(const wstring& wstrFilePath);
};

