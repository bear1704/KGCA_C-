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
			size_t start_position = 0; // �̵齺Ʈ���� ù��°
			size_t end_position = 0; // �̵齺Ʈ���� ������
			bool is_comment_line = false; //�ڸ�Ʈ �������� üũ
			
			std::getline(in_stream, str);

			if (str == "\t" || str == "") //���鰨��
				continue;
			
			std::regex type_start("<[a-zA-Z0-9_]*>");
			std::regex type_end("<[\/]+[a-zA-Z0-9_]*>");
			std::regex comment("<!--[a-zA-Z0-9-_\.\:\!\?\\s\(\)\']*-->");

			std::sregex_iterator it_start(str.begin(), str.end(), type_start);
			std::sregex_iterator end;
			std::sregex_iterator it_end(str.begin(), str.end(), type_end);
			std::sregex_iterator it_comment(str.begin(), str.end(), comment);
		
			while (it_comment != end && it_start == end && it_end == end) //���� �ּ��˻�
			{
				is_comment_line = true;
				it_comment++;
			}
			if (is_comment_line) //�ּ� ��ȿ 
			{
				is_comment_line = false;
				continue;
			}

			while(it_start != end)
			{
				std::smatch m = *it_start;
				type_string = m.str(0).substr(1, m.str().size() - 2); //<>�� �����ϰ� ȣ��        
				start_position = m.position() + m.str().size();
				it_start++;
			}			
			while(it_end != end)
			{
				std::smatch m = *it_end;
				type_endstring = m.str(0).substr(1, m.str().size() - 2); //<>�� �����ϰ� ȣ��
				end_position = m.position();
				it_end++;
			}
		
		
			if(end_position > 0 && start_position > 0) //�̵彺Ʈ�� ����, ���԰���
			{
				middle_string = str.substr(start_position, end_position - start_position);
				middle_string.erase(remove_if(middle_string.begin(), middle_string.end(), isspace), middle_string.end()); //��������
				auto pair = std::make_pair(type_string, middle_string);
				data_map->emplace_back(pair);
				//std::cout << "type : " << type_string << " | midstring :" << middle_string << std::endl;
			}
			else //�̵彺Ʈ���� ����
			{
				if (start_position == 0)//�̵彺Ʈ���� ����, end
				{
					auto pair = std::make_pair("END", type_endstring);
					data_map->emplace_back(pair);
					//std::cout << "type(end) : " << type_endstring << std::endl;
				}
				else //�̵彺Ʈ���� ����, start
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
		std::cout << "���� �б� ����" << std::endl;
	}

	in_stream.close();
	return 0;

}

int PParser::CharacterSheetParse(std::wstring filepath, OUT_ std::vector<StringPair>* data_map)
{


	FILE* infile = nullptr;
	_tfopen_s(&infile, filepath.c_str(), _T("rb"));
	bool is_first_line = false;

	while (_fgetts(wch_t, kDoubledLineMaxSize, infile) != NULL)
	{
		std::string str;
		std::wstring wstr;
		size_t start_position = 0;
		size_t string_endposition = 0;
		

		wstr = wch_t;
		if (!is_first_line)
		{
			str.assign(wstr.begin() + 1, wstr.end()); //ucs-2 bom���� ù ���� ù���ڿ� bom byte�� ���� ���� �߻����� ����..
			is_first_line = true;
		}
		else
			str.assign(wstr.begin(), wstr.end()); 

		std::string type_string;
		std::string value_string;
		bool is_comment_line = false;

		if (str == "\t" || str == "") //���鰨��
			continue;

		
		std::regex type_start("\\[([a-zA-Z0-9_]*)\\]");
		std::regex comment("\/[/]+.*");
		//std::regex value(".*^[^\/]+");
		std::regex value(".*(?=\/\/)");

		std::sregex_iterator it_start(str.begin(), str.end(), type_start);
		std::sregex_iterator end;
		std::sregex_iterator it_comment(str.begin(), str.end(), comment);

		while (it_comment != end && it_start == end) //���� �ּ��˻�
		{
			is_comment_line = true;
			it_comment++;
		}
		if (is_comment_line) //�ּ� ��ȿ 
		{
			is_comment_line = false;
			continue;
		}

		while (it_start != end)
		{
			std::smatch m = *it_start;
			type_string = m.str(0).substr(1, m.str(0).size() - 2); //<>�� �����ϰ� ȣ��        
			start_position = m.position() + m.str(0).size(); // [regex] ��, [�� 0, x�� 5, ]�� 6.  �� +2 �ϸ� 7��°���� ã�� �� ����
			it_start++;
		}

		if (start_position > 0) //�̵彺Ʈ�� ����, ���԰���
		{
			value_string = str.substr(start_position, str.size() - 1); //���� : -1�� ���� ���ΰ�?
			value_string.erase(remove_if(value_string.begin(), value_string.end(), isspace), value_string.end()); //��������
			
			std::sregex_iterator real_val(value_string.begin(), value_string.end(), value);

			if (real_val != end)
			{
				std::smatch r = *real_val;
				value_string = r.str(0);
			}			

			auto pair = std::make_pair(type_string, value_string);
			data_map->emplace_back(pair);
		}
	}
	fclose(infile);
	return 0;
}

int PParser::MaxExportParse(OUT_ std::vector<MaxExportInfo>& info_list, std::vector<Material>& material_list, MaxScene& scene,
	std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device, FILE_EXTENSION_TYPE type)
{
	//extension type
	//0 = kgc
	//1 = skm
	//2 = mat

	std::string str;
	std::wstring wstr;
	std::vector<std::string> split_str;

	int vertex_count = 0;
	int index_count = 0;


	FILE* infile = nullptr;

	_tfopen_s(&infile, exportfile_path.c_str(), _T("rb"));

	_fgetts(wch_t, kCharMaxSize, infile);

	wstr = wch_t;

	split_str = SplitString(wstr, ' ');  //FIRST LINE (������Ʈ����, ������Ʈ������) --> ����
	//info_list[obj].obj_name = split_str[0];   //objname�� ������� ����


	int numberof_obj = std::stoi(split_str[1]);
	info_list.resize(numberof_obj);

	int obj = -1;

	while (_fgetts(wch_t, kCharMaxSize, infile) != NULL)
	{
		wstr = wch_t;

		if (wstr.find(L"#HEADER INFO") != std::string::npos)
		{

			ReadNextLineAndSplit(split_str, infile);

			scene.first_frame =			std::stoi(split_str[0]);
			scene.last_frame =			std::stoi(split_str[1]);
			scene.frame_rate =			std::stoi(split_str[2]);
			scene.tick_per_frame =		std::stoi(split_str[3]);
			scene.numberof_meshes =		std::stoi(split_str[4]);
			scene.numberof_materials =	std::stoi(split_str[5]);
		}
		else if (wstr.find(L"#MATERIAL INFO") != std::string::npos)
		{
			Material material;

			ReadNextLineAndSplit(split_str, infile);

			material.material_name = split_str[0];
			material.submaterial_list_size = std::stoi(split_str[1]);

			if (material.submaterial_list_size > 0) //�ϳ��̻� ���긶�׸����� ����(���긶�׸����� ������ �ʿ��� ������ ����)
			{
				material.material_id = -1;
				material.texmap_size = -1;
				for (int i = 0; i < material.submaterial_list_size; i++)
				{
					Material submaterial;

					ReadNextLineAndSplit(split_str, infile);

					submaterial.material_name = split_str[0];
					submaterial.texmap_size = std::stoi(split_str[1]);
				
					for (int texcount = 0; texcount < submaterial.texmap_size; texcount++)
					{
						_fgetts(wch_t, kCharMaxSize, infile);
						wstr = wch_t;
						wstr.erase(std::remove(wstr.begin(), wstr.end(), '\n'), wstr.end());
						split_str = SplitString(wstr, ' ');
						wstr.assign(split_str[1].begin(), split_str[1].end());

						PTexMap texmap;
						texmap.texmap_id = std::stof(split_str[0]);
						_tcscpy_s(texmap.texname, _countof(texmap.texname),
							wstr.c_str());   //�ؽ�Ʈ����Ʈ�� �߰��ϰ� �� �ؽ�Ʈ �̸���  (�Ʒ��� ���ΰ���)

						submaterial.tex_list.push_back(texmap);			

						//_tcscpy_s(submaterial.own_material_texname, _countof(submaterial.own_material_texname),
						//	wstr.c_str()); //���긶�׸����� ����ϰ� �� �ؽ�Ʈ �̸���
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
			else //���긶�׸��� ���� ��Ʈ���׸����� ������ ����
			{
				Material material;

				ReadNextLineAndSplit(split_str, infile);

				material.material_name = split_str[0];
				material.texmap_size = std::stoi(split_str[1]);


				for (int texcount = 0; texcount < material.texmap_size; texcount++)
				{
					_fgetts(wch_t, kCharMaxSize, infile);
					wstr = wch_t;
					wstr.erase(std::remove(wstr.begin(), wstr.end(), '\n'), wstr.end());
					split_str = SplitString(wstr, ' ');
					wstr.assign(split_str[1].begin(), split_str[1].end());

					PTexMap texmap;
					texmap.texmap_id = std::stof(split_str[0]);
					_tcscpy_s(texmap.texname, _countof(texmap.texname), wstr.c_str());

					material.tex_list.push_back(texmap);

					TextureInfo texinfo;
					texinfo.width = 1.0f; texinfo.height = 1.0f;
					texinfo.uv_ltop = std::string("0.0f, 0.0f");
					texinfo.uv_rbottom = std::string("1.0f, 1.0f");

					texinfo.tex_name = texmap.texname;
					texinfo.tex_path = texfile_path + texmap.texname;

					PTextureManager::GetInstance().LoadTextureWithoutScript(texinfo, device);
				}
				material_list.push_back(material);
			}
		}
		else if (wstr.find(L"#OBJECT INFO") != std::string::npos)
		{
			obj++;

			if (type == FILE_EXTENSION_TYPE::MAT)
			{
				stringstream sstr;

				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				str.assign(wstr.begin(), wstr.end());
				sstr.str(str);
				sstr >> info_list[obj].meshinfo.meshlist_name; 
				sstr >> info_list[obj].meshinfo.parent_name;
				sstr >> info_list[obj].meshinfo.numberof_face;
				sstr >> info_list[obj].bounding_box.max.x;
				sstr >> info_list[obj].bounding_box.max.z;
				sstr >> info_list[obj].bounding_box.max.y;
				sstr >> info_list[obj].bounding_box.min.x;
				sstr >> info_list[obj].bounding_box.min.z;
				sstr >> info_list[obj].bounding_box.min.y;

				info_list[obj].meshinfo.material_id = 0;
				info_list[obj].meshinfo.numberof_submesh = 0;
			}
			else //�⺻��
			{
				ReadNextLineAndSplit(split_str, infile);
				info_list[obj].meshinfo.meshlist_name = split_str[0];
				info_list[obj].meshinfo.parent_name = split_str[1];
				info_list[obj].meshinfo.material_id = std::stoi(split_str[2]);
				info_list[obj].meshinfo.numberof_submesh = std::stoi(split_str[3]);
				info_list[obj].meshinfo.numberof_face = std::stoi(split_str[4]);
			}
		}
		else if (wstr.find(L"#WORLD MATRIX") != std::string::npos)
		{
			auto& world_mat = info_list[obj].meshinfo.world_mat;

			wstringstream sstr;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.str(wstr);
			sstr >> world_mat._11; sstr >> world_mat._12; sstr >> world_mat._13; sstr >> world_mat._14;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.clear();
			sstr.str(wstr);

			sstr >> world_mat._21; sstr >> world_mat._22; sstr >> world_mat._23; sstr >> world_mat._24;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.clear();
			sstr.str(wstr);

			sstr >> world_mat._31; sstr >> world_mat._32; sstr >> world_mat._33; sstr >>world_mat._34;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
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
				_fgetts(wch_t, kDoubledLineMaxSize, infile);
				wstr = wch_t;
				wsstr.str(wstr);
			
				float iwvalue[16];
				wsstr >> pnct.pos.x; wsstr >> pnct.pos.y; wsstr >> pnct.pos.z; wsstr >> pnct.normal.x; wsstr >> pnct.normal.y; wsstr >> pnct.normal.z;
				wsstr >> pnct.color.x; wsstr >> pnct.color.y; wsstr >> pnct.color.z; wsstr >> pnct.color.w;
				wsstr >> pnct.uv.x; wsstr >> pnct.uv.y;
				
				//skm Ȯ�����϶� ����
				wsstr >> iwvalue[0]; wsstr >> iwvalue[1]; wsstr >> iwvalue[2]; wsstr >> iwvalue[3];
				wsstr >> iwvalue[4]; wsstr >> iwvalue[5]; wsstr >> iwvalue[6]; wsstr >> iwvalue[7];
				wsstr >> iwvalue[8]; wsstr >> iwvalue[9]; wsstr >> iwvalue[10]; wsstr >> iwvalue[11];
				wsstr >> iwvalue[12]; wsstr >> iwvalue[13]; wsstr >> iwvalue[14]; wsstr >> iwvalue[15];

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
				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				wstringstream sstr;
				sstr.str(wstr);

				sstr >> index_list[i]; sstr >> index_list[i + 1]; sstr >> index_list[i + 2];
				sstr.clear();
			}
			info_list[obj].index_list.push_back(index_list);
			index_count++;
		}
		else if (wstr.find(L"#ANIMATION DATA") != std::string::npos)
		{
		
			ReadNextLineAndSplit(split_str, infile);

			std::vector<PAnimTrack>& anim_pos = info_list[obj].animlist_pos;
			std::vector<PAnimTrack>& anim_rot = info_list[obj].animlist_rot;
			std::vector<PAnimTrack>& anim_scale = info_list[obj].animlist_scale;
			anim_pos.resize(std::stoi(split_str[0]));
			anim_rot.resize(std::stoi(split_str[1]));
			anim_scale.resize(std::stoi(split_str[2]));
			
			int index = 0;
			
			for (int i = 0; i < anim_pos.size(); i++)
			{
				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				wstringstream sstr;
				sstr.clear();
				sstr.str(wstr);

				sstr >> index; sstr >> anim_pos[i].tick; sstr >> anim_pos[i].p.x; sstr >> anim_pos[i].p.y; sstr >> anim_pos[i].p.z;
			}
			for (int i = 0; i < anim_rot.size(); i++)
			{
				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				wstringstream sstr;
				sstr.clear();
				sstr.str(wstr);

				sstr >> index; sstr >> anim_rot[i].tick; sstr >> anim_rot[i].q.x; sstr >> anim_rot[i].q.y; sstr >> anim_rot[i].q.z;
				sstr >> anim_rot[i].q.w;
			}
			for (int i = 0; i < anim_scale.size(); i++)
			{
				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				wstringstream sstr;
				sstr.clear();
				sstr.str(wstr);

				sstr >> index; sstr >> anim_scale[i].tick; sstr >> anim_scale[i].p.x; sstr >> anim_scale[i].p.y; sstr >> anim_scale[i].p.z;
				sstr >> anim_scale[i].q.x; sstr >> anim_scale[i].q.y; sstr >> anim_scale[i].q.z; sstr >> anim_scale[i].q.w;

			}			
		}
	}
		fclose(infile);
	
	return 0;
}


int PParser::MaxExportParse(OUT_ std::vector<MaxExportSkinInfo>& info_list, std::vector<Material>& material_list, MaxScene& scene,
	std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device, FILE_EXTENSION_TYPE type)
{
	
	if (type != FILE_EXTENSION_TYPE::SKM)
		assert(false);

	std::string str;
	std::wstring wstr;
	std::vector<std::string> split_str;
	std::string::size_type n;

	int vertex_count = 0;
	int index_count = 0;


	FILE* infile = nullptr;

	_tfopen_s(&infile, exportfile_path.c_str(), _T("rb"));

	_fgetts(wch_t, kCharMaxSize, infile);

	wstr = wch_t;

	split_str = SplitString(wstr, ' ');  //FIRST LINE (������Ʈ����, ������Ʈ������) --> ����
	//info_list[obj].obj_name = split_str[0];   //objname�� ������� ����


	int numberof_obj = std::stoi(split_str[1]);
	info_list.resize(numberof_obj);

	int obj = -1;

	while (_fgetts(wch_t, kCharMaxSize, infile) != NULL)
	{
		wstr = wch_t;

		if (wstr.find(L"#HEADER INFO") != std::string::npos)
		{

			ReadNextLineAndSplit(split_str, infile);

			scene.first_frame = std::stoi(split_str[0]);
			scene.last_frame = std::stoi(split_str[1]);
			scene.frame_rate = std::stoi(split_str[2]);
			scene.tick_per_frame = std::stoi(split_str[3]);
			scene.numberof_meshes = std::stoi(split_str[4]);
			scene.numberof_materials = std::stoi(split_str[5]);
		}
		else if (wstr.find(L"#MATERIAL INFO") != std::string::npos)
		{
			Material material;

			ReadNextLineAndSplit(split_str, infile);

			material.material_name = split_str[0];
			material.submaterial_list_size = std::stoi(split_str[1]);

			if (material.submaterial_list_size > 0) //�ϳ��̻� ���긶�׸����� ����(���긶�׸����� ������ �ʿ��� ������ ����)
			{
				material.material_id = -1;
				material.texmap_size = -1;
				for (int i = 0; i < material.submaterial_list_size; i++)
				{
					Material submaterial;

					ReadNextLineAndSplit(split_str, infile);

					submaterial.material_name = split_str[0];
					submaterial.texmap_size = std::stoi(split_str[1]);

					for (int texcount = 0; texcount < submaterial.texmap_size; texcount++)
					{
						_fgetts(wch_t, kCharMaxSize, infile);
						wstr = wch_t;
						wstr.erase(std::remove(wstr.begin(), wstr.end(), '\n'), wstr.end());
						split_str = SplitString(wstr, ' ');
						wstr.assign(split_str[1].begin(), split_str[1].end());

						PTexMap texmap;
						texmap.texmap_id = std::stof(split_str[0]);
						_tcscpy_s(texmap.texname, _countof(texmap.texname),
							wstr.c_str());   //�ؽ�Ʈ����Ʈ�� �߰��ϰ� �� �ؽ�Ʈ �̸���  (�Ʒ��� ���ΰ���)

						submaterial.tex_list.push_back(texmap);

						//_tcscpy_s(submaterial.own_material_texname, _countof(submaterial.own_material_texname),
						//	wstr.c_str()); //���긶�׸����� ����ϰ� �� �ؽ�Ʈ �̸���
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
			else //���긶�׸��� ���� ��Ʈ���׸����� ������ ����
			{
				Material material;

				ReadNextLineAndSplit(split_str, infile);

				material.material_name = split_str[0];
				material.texmap_size = std::stoi(split_str[1]);


				for (int texcount = 0; texcount < material.texmap_size; texcount++)
				{
					_fgetts(wch_t, kCharMaxSize, infile);
					wstr = wch_t;
					wstr.erase(std::remove(wstr.begin(), wstr.end(), '\n'), wstr.end());
					split_str = SplitString(wstr, ' ');
					wstr.assign(split_str[1].begin(), split_str[1].end());

					PTexMap texmap;
					texmap.texmap_id = std::stof(split_str[0]);
					_tcscpy_s(texmap.texname, _countof(texmap.texname), wstr.c_str());

					material.tex_list.push_back(texmap);

					TextureInfo texinfo;
					texinfo.width = 1.0f; texinfo.height = 1.0f;
					texinfo.uv_ltop = std::string("0.0f, 0.0f");
					texinfo.uv_rbottom = std::string("1.0f, 1.0f");

					texinfo.tex_name = texmap.texname;
					texinfo.tex_path = texfile_path + texmap.texname;

					PTextureManager::GetInstance().LoadTextureWithoutScript(texinfo, device);
				}
				material_list.push_back(material);
			}
		}
		else if (wstr.find(L"#OBJECT INFO") != std::string::npos)
		{
			ReadNextLineAndSplit(split_str, infile);

			obj++;
			info_list[obj].meshinfo.meshlist_name = split_str[0];
			info_list[obj].meshinfo.parent_name = split_str[1];
			info_list[obj].meshinfo.material_id = std::stoi(split_str[2]);
			info_list[obj].meshinfo.numberof_submesh = std::stoi(split_str[3]);
			info_list[obj].meshinfo.numberof_face = std::stoi(split_str[4]);

		}
		else if (wstr.find(L"#WORLD MATRIX") != std::string::npos)
		{
			auto& world_mat = info_list[obj].meshinfo.world_mat;

			wstringstream sstr;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.str(wstr);
			sstr >> world_mat._11; sstr >> world_mat._12; sstr >> world_mat._13; sstr >> world_mat._14;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.clear();
			sstr.str(wstr);

			sstr >> world_mat._21; sstr >> world_mat._22; sstr >> world_mat._23; sstr >> world_mat._24;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.clear();
			sstr.str(wstr);

			sstr >> world_mat._31; sstr >> world_mat._32; sstr >> world_mat._33; sstr >> world_mat._34;

			_fgetts(wch_t, kCharMaxSize, infile);
			wstr = wch_t;
			sstr.clear();
			sstr.str(wstr);

			sstr >> world_mat._41; sstr >> world_mat._42; sstr >> world_mat._43; sstr >> world_mat._44;

		}
		else if (wstr.find(L"VertexList") != std::string::npos)
		{

			split_str = SplitString(wstr, ' ');

			int numberof_vertices = stoi(split_str[1]);

			info_list[obj].numberof_vertices.push_back(numberof_vertices);

			vector<Vertex_PNCTW8I8> vertices;
			vertices.reserve(numberof_vertices);

			wstringstream wsstr;

			for (int i = 0; i < numberof_vertices; i++)
			{
				Vertex_PNCTW8I8 pnct;
				wsstr.str(L"");
				wsstr.clear();
				_fgetts(wch_t, kDoubledLineMaxSize, infile);
				wstr = wch_t;
				wsstr.str(wstr);

				float iwvalue[16];
				wsstr >> pnct.pos.x; wsstr >> pnct.pos.y; wsstr >> pnct.pos.z; wsstr >> pnct.normal.x; wsstr >> pnct.normal.y; wsstr >> pnct.normal.z;
				wsstr >> pnct.color.x; wsstr >> pnct.color.y; wsstr >> pnct.color.z; wsstr >> pnct.color.w;
				wsstr >> pnct.uv.x; wsstr >> pnct.uv.y;


				wsstr >> pnct.i0.x; wsstr >> pnct.i0.y; wsstr >> pnct.i0.z; wsstr >> pnct.i0.w;
				wsstr >> pnct.w0.x; wsstr >> pnct.w0.y; wsstr >> pnct.w0.z; wsstr >> pnct.w0.w;
				wsstr >> pnct.i1.x; wsstr >> pnct.i1.y; wsstr >> pnct.i1.z; wsstr >> pnct.i1.w;
				wsstr >> pnct.w1.x; wsstr >> pnct.w1.y; wsstr >> pnct.w1.z; wsstr >> pnct.w1.w;
				

				vertices.push_back(pnct);
			}
			info_list[obj].vertex_list.push_back(vertices);
			vertex_count++;

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
				_fgetts(wch_t, kCharMaxSize, infile);
				wstr = wch_t;
				wstringstream sstr;
				sstr.str(wstr);

				sstr >> index_list[i]; sstr >> index_list[i + 1]; sstr >> index_list[i + 2];
				sstr.clear();
			}
			info_list[obj].index_list.push_back(index_list);
			index_count++;
		}
		else if (wstr.find(L"GET_NODETM_INVERSE") != std::string::npos)
		{
			split_str = SplitString(wstr, ' ');
			int numberof_nodetm = std::stoi(split_str[1]);

			info_list[obj].bone_list.resize(numberof_nodetm);

			for (int i = 0; i < numberof_nodetm; i++)
			{
				for (int row = 0; row < 4; row++)
				{
					_fgetts(wch_t, kCharMaxSize, infile);
					wstr = wch_t;
					wstringstream sstr;
					sstr.str(wstr);

					sstr >> info_list[obj].bone_list[i].m[row][0];
					sstr >> info_list[obj].bone_list[i].m[row][1];
					sstr >> info_list[obj].bone_list[i].m[row][2];
					sstr >> info_list[obj].bone_list[i].m[row][3];

				}
			}
		}
	}

	fclose(infile);

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

