#include <string>
#include <deque>
#include <Windows.h>

void bfs(const std::string& path)
{
	std::string dirPath = path;
	std::deque<std::string> q;
	q.push_back(dirPath);

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	std::deque<std::string> delDir;

	while (!q.empty()) {
		dirPath = q.front();
		q.pop_front();
		delDir.push_back(dirPath);
		std::string tmp = dirPath + "\\*";
		hFind = FindFirstFile(tmp.c_str(), &win32fd);
		if (hFind == INVALID_HANDLE_VALUE) {
			return;
		}

		do {
			if ((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				std::string filePath = dirPath + "\\";
				filePath += win32fd.cFileName;
				::DeleteFile(filePath.c_str());
			} else {
				if ((strcmp(win32fd.cFileName, ".") == 0) ||
					(strcmp(win32fd.cFileName, "..") == 0)) {
					continue;
				}
				std::string childDir = dirPath + "\\";
				childDir += win32fd.cFileName;
				q.push_back(childDir);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}

	while (!delDir.empty()) {
		std::string d = delDir.back();
		::RemoveDirectory(d.c_str());
		delDir.pop_back();
	}
}

int main()
{
	std::string path = "C:\\file\\path";
	bfs(path);

	return 0;
}
