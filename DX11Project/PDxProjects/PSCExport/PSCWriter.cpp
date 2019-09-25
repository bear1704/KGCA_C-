#include "pch.h"
#include "PSCWriter.h"

PSCWriter::PSCWriter()
{
}

PSCWriter::~PSCWriter()
{
}

void PSCWriter::Set(const TCHAR* name, Interface* interface_max)
{
	interface_max_ = interface_max;
	filename_ = name;
	rootnode_ = interface_max_->GetRootNode();
	PreProcess(rootnode_);
}

bool PSCWriter::Export()
{
	FILE* file = nullptr;
	_wfopen_s(&file, filename_.c_str(), _T("wb"));
	_ftprintf(file, _T("%s %d"), _T("PSCExporter100"), object_list_.size());

	for (int i = 0; i < object_list_.size(); i++)
	{
		INode* node = object_list_[i];

		GetMesh(node);
		_ftprintf(file, _T("\n%s %d"), node->GetName(),
			tri_list_.size());

		for (int iTri = 0; iTri < tri_list_.size(); iTri++)
		{
			for (int iVer = 0; iVer < 3; iVer++)
			{
				_ftprintf(file, _T("\n%10.4f %10.4f %10.4f"),
					tri_list_[iTri].v[iVer].p.x,
					tri_list_[iTri].v[iVer].p.y,
					tri_list_[iTri].v[iVer].p.z);

				_ftprintf(file, _T("\n%10.4f %10.4f %10.4f"),
					tri_list_[iTri].v[iVer].n.x,
					tri_list_[iTri].v[iVer].n.y,
					tri_list_[iTri].v[iVer].n.z);

				_ftprintf(file, _T("\n%10.4f %10.4f %10.4f"),
					tri_list_[iTri].v[iVer].c.x,
					tri_list_[iTri].v[iVer].c.y,
					tri_list_[iTri].v[iVer].c.z);

				_ftprintf(file, _T("\n%10.4f %10.4f %10.4f"),
					tri_list_[iTri].v[iVer].t.x,
					tri_list_[iTri].v[iVer].t.y);

			}
		}
	}
	
	fclose(file);

	MessageBox(GetActiveWindow(), filename_.c_str(),
		_T("Succeed!"), MB_OK);

	return true;
}
   
void PSCWriter::PreProcess(INode* node)
{
	if (node == NULL) return;
	AddObject(node);
	int numberof_children = node->NumberOfChildren();
	for (int i = 0; i < numberof_children; i++)
	{
		INode* child = node->GetChildNode(i);
		PreProcess(child);
	}

}

void PSCWriter::AddObject(INode* node)
{
	ObjectState os = node->EvalWorldState(0);

	if (!os.obj)
		return;

	if (os.obj->ClassID() == Class_ID(TARGET_CLASS_ID, 0))
		return;
	else
	{
		switch (os.obj->SuperClassID())
		{
			case GEOMOBJECT_CLASS_ID:
				object_list_.push_back(node);
				break;
			default:
				break;
		}
	}

}

void PSCWriter::GetMesh(INode* node)
{
	Matrix3 tm = node->GetObjTMAfterWSM(0);
	
	bool deleteit = false;
	TriObject* triobj = GetTriObjectFromNode(node, 0, deleteit);
	
	if (!triobj) return;

	Mesh* mesh = &triobj->GetMesh();

	if (mesh)
	{
		int numberof_face = mesh->getNumFaces();
		tri_list_.resize(numberof_face);

		for (int iFace = 0; iFace < numberof_face; iFace++)
		{
			int numberof_vert = mesh->getNumVerts();

			if (numberof_vert > 0)
			{
				Point3 v = mesh->verts[mesh->faces[iFace].v[0]] * tm;
				tri_list_[iFace].v[0].p.x = v.x;
				tri_list_[iFace].v[0].p.y = v.y;
				tri_list_[iFace].v[0].p.z = v.z;

				v = mesh->verts[mesh->faces[iFace].v[2]] * tm;
				tri_list_[iFace].v[1].p.x = v.x;
				tri_list_[iFace].v[1].p.y = v.y;
				tri_list_[iFace].v[1].p.z = v.z;

				v = mesh->verts[mesh->faces[iFace].v[1]] * tm;
				tri_list_[iFace].v[2].p.x = v.x;
				tri_list_[iFace].v[2].p.y = v.y;
				tri_list_[iFace].v[2].p.z = v.z;
			}

			int numberof_color = mesh->getNumVertCol();
			tri_list_[iFace].v[0].c = Point4(1, 1, 1, 1);
			tri_list_[iFace].v[1].c = Point4(1, 1, 1, 1);
			tri_list_[iFace].v[2].c = Point4(1, 1, 1, 1);
			if (numberof_color > 0)
			{
				tri_list_[iFace].v[0].c = mesh->vertCol[mesh->vcFace[iFace].t[0]];
				tri_list_[iFace].v[0].c = mesh->vertCol[mesh->vcFace[iFace].t[2]];
				tri_list_[iFace].v[0].c = mesh->vertCol[mesh->vcFace[iFace].t[1]];
			}

			int numberof_tex = mesh->getNumTVerts();
			if (numberof_tex)
			{
				Point2 uv = (Point2)mesh->tVerts[mesh->tvFace[iFace].t[0]];
				tri_list_[iFace].v[0].t.x = uv.x;
				tri_list_[iFace].v[0].t.y = 1.0f - uv.y;

				uv = (Point2)mesh->tVerts[mesh->tvFace[iFace].t[2]];
				tri_list_[iFace].v[1].t.x = uv.x;
				tri_list_[iFace].v[1].t.y = 1.0f - uv.y;
				
				uv = (Point2)mesh->tVerts[mesh->tvFace[iFace].t[1]];
				tri_list_[iFace].v[2].t.x = uv.x;
				tri_list_[iFace].v[2].t.y = 1.0f - uv.y;
			}

			tri_list_[iFace].v[0].n = Point3(1, 1, 1);
			tri_list_[iFace].v[1].n = Point3(1, 1, 1);
			tri_list_[iFace].v[2].n = Point3(1, 1, 1);
		}


	}

	if (deleteit) delete triobj;

}

TriObject* PSCWriter::GetTriObjectFromNode(INode* node, TimeValue timeval, bool& deleteit)
{
	Object* obj = node->EvalWorldState(timeval).obj;
	if (obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
	{
		TriObject* tri = (TriObject*)obj->ConvertToType(timeval, Class_ID(TRIOBJ_CLASS_ID, 0));
		if (obj != tri) deleteit = true;
		return tri;
	}

	return nullptr;
}
