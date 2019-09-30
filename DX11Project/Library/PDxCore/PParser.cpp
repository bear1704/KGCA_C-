#include "PParser.h"
#include <codecvt>

PParser::PParser()
{
}

PParser::~PParser()
{
}

int PParser::XmlParse(std::string path, std::vector<std::pair<string, string>>* data_map)
{
	std::ifstream in_stream(path);
	//char buffer[kParsingLineMaxSize];
	std::string str;
	if (in_stream.is_open())
	{
		while (!in_stream.eof())
		{
			std::string type_string;
			std::string type_endstring;
			std::string middle_string;
			size_t start_position = 0; // 미들스트링의 첫번째
			size_t end_position = 0; // 미들스트링의 마지막
			bool is_comment_line = false; //코멘트 라인인지 체크
			
			std::getline(in_stream, str);

			if (str == "\t" || str == "") //공백감지
				continue;
			
			std::regex type_start("<[a-zA-Z0-9_]*>");
			std::regex type_end("<[\/]+[a-zA-Z0-9_]*>");
			std::regex comment("<!--[a-zA-Z0-9-_\.\:\!\?\\s\(\)\']*-->");

			std::sregex_iterator it_start(str.begin(), str.end(), type_start);
			std::sregex_iterator end;
			std::sregex_iterator it_end(str.begin(), str.end(), type_end);
			std::sregex_iterator it_comment(str.begin(), str.end(), comment);
		
			while (it_comment != end && it_start == end && it_end == end) //라인 주석검사
			{
				is_comment_line = true;
				it_comment++;
			}
			if (is_comment_line) //주석 무효 
			{
				is_comment_line = false;
				continue;
			}

			while(it_start != end)
			{
				std::smatch m = *it_start;
				type_string = m.str(0).substr(1, m.str().size() - 2); //<>를 제외하고 호출        
				start_position = m.position() + m.str().size();
				it_start++;
			}			
			while(it_end != end)
			{
				std::smatch m = *it_end;
				type_endstring = m.str(0).substr(1, m.str().size() - 2); //<>를 제외하고 호출
				end_position = m.position();
				it_end++;
			}
		
		
			if(end_position > 0 && start_position > 0) //미드스트링 존재, 삽입가능
			{
				middle_string = str.substr(start_position, end_position - start_position);
				middle_string.erase(remove_if(middle_string.begin(), middle_string.end(), isspace), middle_string.end()); //공백제거
				auto pair = std::make_pair(type_string, middle_string);
				data_map->emplace_back(pair);
				//std::cout << "type : " << type_string << " | midstring :" << middle_string << std::endl;
			}
			else //미드스트링이 없음
			{
				if (start_position == 0)//미드스트링이 없음, end
				{
					auto pair = std::make_pair("END", type_endstring);
					data_map->emplace_back(pair);
					//std::cout << "type(end) : " << type_endstring << std::endl;
				}
				else //미드스트링이 없음, start
				{
					auto pair = std::make_pair("START", type_string);
					data_map->emplace_back(pair);
					//std::cout << "type(start) : " << type_string << std::endl;
				}
			}
			
		}
	}
	else
	{
		std::cout << "파일 읽기 오류" << std::endl;
	}

	in_stream.close();
	return 0;

}

int PParser::MaxExportParse(OUT_ MaxExportInfo& info, std::string path)
{

	std::string str;
	std::wstring wstr;
	std::vector<std::string> split_str;
	std::string::size_type n;
	


	//std::ifstream in_stream(path);
	//getline(in_stream, str);

	wchar_t wch[256];
	const int kWcharMaxSize = 256;

	std::wifstream in_stream(path, std::ios::binary);

	in_stream.imbue(std::locale(in_stream.getloc(),
		new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));


	int vertex_count = 0;
	int index_count = 0;

	if (in_stream.is_open())
	{
		in_stream.getline(wch, kWcharMaxSize);
		wstr = wch;
		str.append(wstr.begin(), wstr.end());

		split_str = SplitString(str, ' ');
		info.obj_name = split_str[0];
		info.numberof_obj = std::stoi(split_str[1]);

		while (!in_stream.eof())
		{
			str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
			
			if (str.find("#HEADER INFO") != std::string::npos)
			{
				str = Utf16ToString(wch, kWcharMaxSize, &in_stream); //header info가 들어가는 공간
			}
			else if (str.find("#MATERIAL INFO") != std::string::npos)
			{
				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				split_str = SplitString(str, ' ');
				info.material_name = split_str[0];
				info.submaterial_list_size = std::stoi(split_str[1]);

				for (int i = 0; i < info.submaterial_list_size; i++)
				{
					MaxExportInfo::Submaterial submaterial;
					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					split_str = SplitString(str, ' ');
					submaterial.submaterial_name = split_str[0];
					submaterial.texmap_size = std::stoi(split_str[1]);

					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					split_str = SplitString(str, ' ');
					submaterial.texmap_id = std::stof(split_str[0]);
					submaterial.texmap_name = split_str[1];

					info.submaterial.push_back(submaterial);
				}
			}
			else if (str.find("#OBJECT INFO") != std::string::npos)
			{
				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				split_str = SplitString(str, ' ');
				info.meshlist_name = split_str[0];
				info.parent_name = split_str[1];
				info.material_id = std::stoi(split_str[2]);
				info.bufferlist_size = std::stoi(split_str[3]);
				info.trilist_size = std::stoi(split_str[4]);
			}
			else if (str.find("#WORLD MATRIX") != std::string::npos)
			{			
				stringstream sstr;

				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				sstr.str(str);
				sstr >> info.world_mat._11; sstr >> info.world_mat._12; sstr >> info.world_mat._13; sstr >> info.world_mat._14;
				
				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				sstr.clear();
				sstr.str(str);
				
				sstr >> info.world_mat._21; sstr >> info.world_mat._22; sstr >> info.world_mat._23; sstr >> info.world_mat._24;
				
				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				sstr.clear();
				sstr.str(str);

				sstr >> info.world_mat._31; sstr >> info.world_mat._32; sstr >> info.world_mat._33; sstr >> info.world_mat._34;

				str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
				sstr.clear();
				sstr.str(str);

				sstr >> info.world_mat._41; sstr >> info.world_mat._42; sstr >> info.world_mat._43; sstr >> info.world_mat._44;

			}
			else if (str.find("VertexList") != std::string::npos)
			{
				split_str = SplitString(str, ' ');

				int numberof_vertices = stoi(split_str[1]);

				info.numberof_vertices.push_back(numberof_vertices);
				
				vector<PNCT> vertices;
				vertices.reserve(numberof_vertices);

				for (int i = 0; i < numberof_vertices; i++)
				{
					PNCT pnct;
					stringstream sstr;

					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					sstr.clear();
					sstr.str(str);
					sstr >> pnct.p[0] >> pnct.p[1] >> pnct.p[2];

					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					sstr.clear();
					sstr.str(str);
					sstr >> pnct.n[0] >> pnct.n[1] >> pnct.n[2];

					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					sstr.clear();
					sstr.str(str);
					sstr >> pnct.c[0] >> pnct.c[1] >> pnct.c[2] >> pnct.c[3];

					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					sstr.clear();
					sstr.str(str);
					sstr >> pnct.t[0] >> pnct.t[1];
					vertices.push_back(pnct);
				}
				info.vertex_list.push_back(vertices);
				vertex_count++;
			}
			else if (str.find("IndexList") != std::string::npos)
			{
				split_str = SplitString(str, ' ');

				int numberof_indicies = std::stoi(split_str[1]);

				info.numberof_indicies.push_back(numberof_indicies);

				vector<int> index_list;
				index_list.resize(numberof_indicies);

				for (int i = 0 ; i < numberof_indicies ; i+=3)
				{
					str = Utf16ToString(wch, kWcharMaxSize, &in_stream);
					stringstream sstr;
					sstr.str(str);
					
					sstr >> index_list[i]; sstr >> index_list[i + 1]; sstr >> index_list[i + 2];
					sstr.clear();
				}
				info.index_list.push_back(index_list);
				index_count++;
			}		
		}

	}
	return 0;
}

std::vector<std::string> PParser::SplitString(std::string str, char delimiter)
{
	std::string::iterator str_start = str.begin();
	std::string::iterator str_iter;
	std::vector<std::string> strvec;
	for (str_iter = str.begin(); str_iter != str.end(); str_iter++)
	{

		if (*str_iter == delimiter)
		{
			std::string temp_str(str_start, str_iter);

			strvec.push_back(temp_str);
			str_start = str_iter + 1;
		}

	}
	std::string temp_str(str_start, str.end());
	strvec.push_back(temp_str);
	return strvec;
}

std::string PParser::Utf16ToString(wchar_t* wchar, int max_size, std::wifstream* in)
{
	in->getline(wchar, max_size);
	std::wstring wstr(wchar);
	std::string str;
	str.append(wstr.begin(), wstr.end());
	return str;
}

