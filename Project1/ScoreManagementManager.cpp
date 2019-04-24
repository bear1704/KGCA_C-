#include "ScoreManagementManager.h"





ScoreManagementManager::ScoreManagementManager()
{
}


ScoreManagementManager::~ScoreManagementManager()
{
}

LinkedList * ScoreManagementManager::CreateInitialList()
{


		LinkedList* studentList = new LinkedList;
		
		/*Head, Tail ����*/
		studentList->SetHeadAndTail(new Node(), new Node());
		

		//studentList->getHead()->getNext() = studentList->getTail(); //Head�� ���� ���� Tail��
		//studentList->getTail()->prev = studentList->getHead(); //Taill�� ���� ���� head��
		//studentList->getHead()->prev = nullptr;
		//studentList->getTail()->next = nullptr;

		studentList->getHead()->SetNextAndPrev(studentList->getTail(), nullptr);
		studentList->getTail()->SetNextAndPrev(nullptr, studentList->getHead());

		LinkedList::index = 1;  // static index �ʱ�ȭ

		printf("\n���̺��� �����Ǿ����ϴ�\n");

		_getche();

		return studentList;


}


void ScoreManagementManager::Init()
{//Manager
	char temp = NULL;
	SELECT inputData = SELECT::NONE;

	//STUDENT* student = NULL;


	LinkedList* studentList = nullptr;
	FileIO* fileIO = new FileIO;



	while (inputData != SELECT::EXIT)
	{

		char name[25];

		system("cls");
		printf("\n1.����\n2.������ ����\n3.������ ����\n4.������ �˻� �� ����\n5.������ ����\n6.������ �ε�\n7.������ ����\n8.���� ������ ����\n0.����\n");

		scanf("%c", &temp);

		if (isdigit(temp))
			inputData = (SELECT)(temp - '0');
		else
		{
			continue;
		}

		switch (inputData)
		{
		case SELECT::CREATE:
			if (studentList)
			{
				delete studentList;
				studentList = nullptr;
			}
			studentList = CreateInitialList();
			break;
		case SELECT::INSERT:
			if (isListEmpty(studentList))
				continue;
			studentList->InsertStudent();
			break;
		case SELECT::DELETE:
			if (isListEmpty(studentList))
				continue;
			printf("������ �̸� �Է� : ");
			scanf("%s", &name);
			studentList->SearchDeleteTarget(name);
			break;
		case SELECT::SEARCH_AND_MODIFY:
			if(isListEmpty(studentList))
				continue;
			studentList->SearchModify();
			break;
		case SELECT::SAVE:
			fileIO->SaveData(studentList);
			break;
		case SELECT::LOAD:
			fileIO->LoadData(&studentList);
			break;
		case SELECT::PRINT:
			if (isListEmpty(studentList))
				continue;
			studentList->PrintData();
			break;
		case SELECT::SAMPLEDATA:
			if (isListEmpty(studentList))
				continue;
			studentList->WriteSampleData();
			break;
		case SELECT::EXIT:
			if (studentList)
				studentList->AllFree(studentList->getHead()->getNext());
			
			if(studentList)
				delete studentList;
			
			if (fileIO)
				delete fileIO;

			return;
		default:
			inputData = SELECT::NONE;
			continue;
			break;
		}

		inputData = SELECT::NONE;
		//
	}



}

bool ScoreManagementManager::isListEmpty(LinkedList* LL)
{
	if (!LL)
	{
		printf("�л� ���̺��� ����ÿ�\n");
		_getche();
		return true;
	}
	

	return false;
}



int main()
{
	ScoreManagementManager scoreManager;
	scoreManager.Init();

	//char name[25] = "aaaaaa";
	//char name2[25] = "bbbbb";
	//StudentData* stdata = new StudentData(1, name, 3, 4,5);
	//StudentData* stdata2 = new StudentData(2, name2, 7, 7, 7);
	//Node* node1 = new Node(stdata, nullptr, nullptr);
	//Node* node2 = new Node(stdata2, nullptr, nullptr);


	//std::cout << node1->getData()->getStringInfo("name") << std::endl;
	//node1 = node2;
	//std::cout << node1->getData()->getStringInfo("name") << std::endl;
	//
	///*delete node2;
	//std::cout << node1->getData()->getStringInfo("name") << std::endl;
	//*/


	//Node node1_(stdata, nullptr, nullptr);
	//Node node2_(stdata2, nullptr, nullptr);

	//node1_ = node2_;

	system("pause");





}
