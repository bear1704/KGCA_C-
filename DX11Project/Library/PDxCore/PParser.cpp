#include "PParser.h"
#include "PTextureManager.h"

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

int PParser::MaxExportParse(OUT_ std::vector<MaxExportInfo>& info_list, std::vector<Material>& material_list,
	std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device)
{

	std::string str;
	std::wstring wstr;
	std::vector<std::string> split_str;
	std::string::size_type n;

	int vertex_count = 0;
	int index_count = 0;


	wchar_t ch[kCharMaxSize];

	FILE* infile = nullptr;

	_tfopen_s(&infile, exportfile_path.c_str(), _T("rb"));

	_fgetts(ch, kCharMaxSize, infile);


	wstr = ch;

	split_str = SplitString(wstr, ' ');  //FIRST LINE (오브젝트네임, 오브젝트사이즈) --> 무시
	//info_list[obj].obj_name = split_str[0];   //objname은 사용하지 않음


	int numberof_obj = std::stoi(split_str[1]);
	info_list.resize(numberof_obj);

	for (int obj = 0; obj < numberof_obj ; obj++)
	{
		while (_fgetts(ch, kCharMaxSize, infile) != NULL)
		{
			wstr = ch;

			if (wstr.find(L"#HEADER INFO") != std::string::npos)
			{
				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch; //header info_list[obj]. 들어가는 공간
			}
			else if (wstr.find(L"#MATERIAL INFO") != std::string::npos)
			{
				Material material;
				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				split_str = SplitString(wstr, ' ');
				material.material_name = split_str[0];
				material.submaterial_list_size = std::stoi(split_str[1]);

				if (material.submaterial_list_size > 0) //하나이상 서브마테리얼이 있음(서브마테리얼이 렌더에 필요한 정보를 가짐)
				{

					for (int i = 0; i < material.submaterial_list_size; i++)
					{
						Material submaterial;

						_fgetts(ch, kCharMaxSize, infile);
						wstr = ch;
						split_str = SplitString(wstr, ' ');
						submaterial.material_name = split_str[0];
						submaterial.texmap_size = std::stoi(split_str[1]);


						submaterial.tex_list.resize(submaterial.texmap_size);

						for (int texcount = 0; texcount < submaterial.texmap_size; texcount++)
						{
							_fgetts(ch, kCharMaxSize, infile);
							wstr = ch;
							wstr.erase(std::remove(wstr.begin(), wstr.end(), '\n'), wstr.end());
							split_str = SplitString(wstr, ' ');
							wstr.clear();
							wstr.append(split_str[1].begin(), split_str[1].end());

							PTexMap texmap;
							texmap.texmap_id = std::stof(split_str[0]);
							_tcscpy_s(texmap.texname, _countof(submaterial.own_material_texname),
								wstr.c_str());   //텍스트리스트에 추가하게 될 텍스트 이름값  (아래와 서로같음)

							submaterial.tex_list.push_back(texmap);			
							//texmap은 현재 미사용으로 추정됨.

							_tcscpy_s(submaterial.own_material_texname, _countof(submaterial.own_material_texname),
								wstr.c_str()); //서브마테리얼이 담당하게 될 텍스트 이름값
							TextureInfo texinfo;
							texinfo.width = 1.0f; texinfo.height = 1.0f;
							texinfo.uv_ltop = std::string("0.0f, 0.0f");
							texinfo.uv_rbottom = std::string("1.0f, 1.0f");

							//texinfo.tex_name = submaterial.own_material_texname;
							texinfo.tex_name = texmap.texname;
							texinfo.tex_path = texfile_path + texmap.texname;

							PTextureManager::GetInstance().LoadTextureWithoutScript(texinfo, device);
						}
						material.sub_material_list.push_back(submaterial);
					}
					material_list.push_back(material);
				}
				else //서브마테리얼 없이 루트마테리얼이 정보를 가짐
				{
					Material material;

					_fgetts(ch, kCharMaxSize, infile);
					wstr = ch;
					split_str = SplitString(wstr, ' ');
					material.material_name = split_str[0];
					material.texmap_size = std::stoi(split_str[1]);


					for (int texcount = 0; texcount < material.texmap_size; texcount++)
					{
						_fgetts(ch, kCharMaxSize, infile);
						wstr = ch;
						split_str = SplitString(wstr, ' ');
						wstr.append(split_str[1].begin(), split_str[1].end());

						PTexMap texmap;
						texmap.texmap_id = std::stof(split_str[0]);
						_tcscpy_s(texmap.texname, _countof(texmap.texname), wstr.c_str());

						material.tex_list.push_back(texmap);

						TextureInfo texinfo;
						texinfo.width = 1.0f; texinfo.height = 1.0f;
						texinfo.uv_ltop = std::string("0.0f, 0.0f");
						texinfo.uv_rbottom = std::string("1.0f, 1.0f");

						texinfo.tex_name = texmap.texname;
						texinfo.tex_path = texfile_path;

						PTextureManager::GetInstance().LoadTextureWithoutScript(texinfo, device);
					}
				}
			}
			else if (wstr.find(L"#OBJECT INFO") != std::string::npos)
			{
				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				split_str = SplitString(wstr, ' ');
				info_list[obj].meshinfo.meshlist_name = split_str[0];
				info_list[obj].meshinfo.parent_name = split_str[1];
				info_list[obj].meshinfo.material_id = std::stoi(split_str[2]);
				info_list[obj].meshinfo.numberof_submesh = std::stoi(split_str[3]);
				info_list[obj].meshinfo.trilist_size = std::stoi(split_str[4]);
			}
			else if (wstr.find(L"#WORLD MATRIX") != std::string::npos)
			{
				auto& world_mat = info_list[obj].meshinfo.world_mat;

				wstringstream sstr;

				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				sstr.str(wstr);
				sstr >> world_mat._11; sstr >> world_mat._12; sstr >> world_mat._13; sstr >> world_mat._14;

				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				sstr.clear();
				sstr.str(wstr);

				sstr >> world_mat._21; sstr >> world_mat._22; sstr >> world_mat._23; sstr >> world_mat._24;

				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				sstr.clear();
				sstr.str(wstr);

				sstr >> world_mat._31; sstr >> world_mat._32; sstr >> world_mat._33; sstr >>world_mat._34;

				_fgetts(ch, kCharMaxSize, infile);
				wstr = ch;
				sstr.clear();
				sstr.str(wstr);

				sstr >>world_mat._41; sstr >> world_mat._42; sstr >> world_mat._43; sstr >>world_mat._44;

			}
			else if (wstr.find(L"VertexList") != std::string::npos)
			{

				split_str = SplitString(wstr, ' ');

				int numberof_vertices = stoi(split_str[1]);

				info_list[obj].numberof_vertices.push_back(numberof_vertices);

				vector<Vertex_PNCT> vertices;
				vertices.reserve(numberof_vertices);

				wstringstream wsstr;

				for (int i = 0; i < numberof_vertices; i++)
				{
					Vertex_PNCT pnct;
					wsstr.str(L"");
					wsstr.clear();
					_fgetts(ch, kCharMaxSize, infile);
					wstr = ch;
					wsstr.str(wstr);
					wsstr >> pnct.pos.x; wsstr >> pnct.pos.y; wsstr >> pnct.pos.z; wsstr >> pnct.normal.x; wsstr >> pnct.normal.y; wsstr >> pnct.normal.z;
					wsstr >> pnct.color.x; wsstr >> pnct.color.y; wsstr >> pnct.color.z; wsstr >> pnct.color.w;
					wsstr >> pnct.uv.x; wsstr >> pnct.uv.y;

					vertices.push_back(pnct);
				}
				info_list[obj].vertex_list.push_back(vertices);
				vertex_count++;

				//1.6s
			}
			else if (wstr.find(L"IndexList") != std::string::npos)
			{

				split_str = SplitString(wstr, ' ');

				int numberof_indicies = std::stoi(split_str[1]);

				info_list[obj].numberof_indicies.push_back(numberof_indicies);

				vector<int> index_list;
				index_list.resize(numberof_indicies);

				for (int i = 0; i < numberof_indicies; i += 3)
				{
					_fgetts(ch, kCharMaxSize, infile);
					wstr = ch;
					wstringstream sstr;
					sstr.str(wstr);

					sstr >> index_list[i]; sstr >> index_list[i + 1]; sstr >> index_list[i + 2];
					sstr.clear();
				}
				info_list[obj].index_list.push_back(index_list);
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

std::vector<std::string> PParser::SplitString(std::wstring str, char delimiter)
{
	std::wstring::iterator str_start = str.begin();
	std::wstring::iterator str_iter;
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

