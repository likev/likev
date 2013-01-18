#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void trans()
{
	std::ifstream fin1("idname.txt"), fin2("jsname.txt");

	std::string id, name, jsstr;
	std::vector<std::string> ids, names;

	while(fin1>>id)
	{
		fin1>>name>>name>>name>>name>>name>>name;
		ids.push_back(id);
		names.push_back(name);
	}
	fin1.close();

	std::getline(fin2, jsstr);

	for(size_t i = 0; i != names.size(); i++)
	{
		size_t pos = jsstr.find(names[i]);

		if(std::string::npos != pos)
		{
			size_t pos1 = jsstr.find('"',pos);
			jsstr.insert(pos1, '-'+ids[i]);
		}
	}

	std::ofstream fout("out.txt");

	fout<<jsstr;
	fout.close();

}


int main()
{
	trans();
	return 0;
}