#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disacle:4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LEN  20


typedef struct _Building Building;
struct _Building
{
	int num;
	char name[MAX_NAME_LEN];
	char dept[MAX_NAME_LEN];
	char add[MAX_NAME_LEN];
};

#define DEF_FNAME  "data.bui"

#define MAX_BUILDING 50
Building *buies[MAX_BUILDING];

void Init();
void Run();
void Exit();
int main()
{
	Init();
	Run();
	Exit();
	return 0;
}
void Init()
{
	FILE *fp = fopen(DEF_FNAME, "r");
	if (fp)
	{
		int i = 0;
		while (1)
		{
			if (fread(&i, sizeof(int), 1, fp) < 1)
			{
				break;
			}
			buies[i] = (Building *)malloc(sizeof(Building));
			fread(buies[i], sizeof(Building), 1, fp);
		}
		fclose(fp);
	}
}

int SelectMenu();
void AddBuilding();
void AddDept();
void AddAdd();
/*void Modif();*/
void RemoveBuilding();
void FindBuilding();
void ViewAll();
void Run()
{
	int key = 0;
	while ((key = SelectMenu()) != 0)
	{
		switch (key)
		{
		case 1: AddBuilding(); break;
		case 2: AddDept(); break;
		case 3: AddAdd(); break;
		/*case 4: Modif(); break;*/
		case 5: RemoveBuilding(); break;
		case 6: FindBuilding(); break;
		case 7: ViewAll(); break;
		default: printf("No number.\n"); break;
		}
	}
}
int getnum();
int SelectMenu()
{
	printf("Building Management Program 0:EXIT\n");
	printf("1: Add Building 2: Add Department Name 3: Add Address 4: Modify Information 5: Delete 6: Search 7: View all\n");
	return getnum();
}
int getnum()
{
	int num = 0;
	if (scanf("%d", &num) == 0)
	{
		char buf[256];
		gets(buf, sizeof(buf));
	}
	return num;
}

void InitDept(Building *bui1);
void AddBuilding()
{
	int num = 0;
	Building *bui1 = 0;

	printf("Building number to add(1~%d):", MAX_BUILDING);
	num = getnum();
	if ((num < 1) || (num > MAX_BUILDING))
	{
		printf("Out of range.\n");
		return;
	}

	bui1 = buies[num - 1];
	if (bui1)
	{
		printf("There are already materials.\n");
		return;
	}
	bui1 = (Building *)malloc(sizeof(Building));
	bui1->num = num;
	printf("Name:");
	scanf_s("%s", bui1->name, MAX_NAME_LEN);
	InitDept(bui1);
	buies[num - 1] = bui1;
}
void InitDept(Building *bui2)
{
	int s = 0;
	for (s = 0; s < MAX_NAME_LEN; s++)
	{
		bui2->dept[s] = -1;
	}
}
void AddDept()
{
	int num = 0;
	Building *bui2 = 0;

	printf("Building number to enter department name(1~%d):", MAX_BUILDING);
	num = getnum();
	if ((num < 1) || (num > MAX_BUILDING))
	{
		printf("Out of range.\n");
		return;
	}

	bui2 = buies[num - 1];
	if (bui2 == 0)
	{
		printf("There are already materials.\n");
		return;
	}
	bui2 = (Building *)malloc(sizeof(Building));
	bui2->num = num;
	printf("Department name:");
	scanf_s("%s", bui2->dept, MAX_NAME_LEN);
	InitDept(bui2);
	buies[num - 1] = bui2;
}
void AddAdd()
{
	int num = 0;
	Building *bui3 = 0;

	printf("Building number to enter building address(1~%d):", MAX_BUILDING);
	num = getnum();
	if ((num < 1) || (num > MAX_BUILDING))
	{
		printf("Out of range.\n");
		return;
	}

	bui3 = buies[num - 1];
	if (bui3 == 0)
	{
		printf("There are already materials.\n");
		return;
	}
	bui3 = (Building *)malloc(sizeof(Building));
	bui3->num = num;
	printf("Building address:");
	scanf_s("%s", bui3->add, MAX_NAME_LEN);
	InitDept(bui3);
	buies[num - 1] = bui3;
}

void RemoveBuilding()
{
	int num = 0;
	Building *bui1 = 0;
	Building *bui2 = 0;
	Building *bui3 = 0;

	printf("Building number to delete(1~%d):", MAX_BUILDING);
	num = getnum();
	if ((num < 1) || (num > MAX_BUILDING))
	{
		printf("Out of range.\n");
		return;
	}

	bui1 = buies[num - 1]; bui2 = buies[num - 1]; bui3 = buies[num - 1];
	if ((bui1 == 0) || (bui2 == 0) || (bui3 == 0))
	{
		printf("Building data not added. Please add Building data first.\n");
		return;
	}
	free(bui1);
	free(bui2);
	free(bui3);
	buies[num - 1] = 0;
}

void ViewBuilding(Building *bui);
void FindBuilding()
{
	int num = 0;
	Building *bui = 0;

	printf("검색할 건물 번호(1~%d):", MAX_BUILDING);
	num = getnum();
	if ((num < 1) || (num > MAX_BUILDING))
	{
		printf("Building number to search.\n");
		return;
	}

	bui = buies[num - 1];
	if (bui == 0)
	{
		printf("Building data not added. Please add Building data first.\n");
		return;
	}
	ViewBuilding(bui);
}

void ViewDept(Building *bui);
void ViewBuilding(Building *bui)
{
	printf("=== Number:%d Name:%s\n Department name:%s\n Building address:%s\n", bui->num, bui->name, bui->dept, bui->add);
	ViewDept(bui);
}
void ViewDept(Building *bui)
{
	int s = 0;
	for (s = 0; s < MAX_NAME_LEN; s++)
	{
		if (bui->dept[s] == -1)
		{
			printf("Not entered\n");
		}
		else
		{
			printf("%d\n", bui->dept[s]);
		}
	}             
}

void ViewAll()
{
	int i = 0;
	for (i = 0; i < MAX_BUILDING; i++)
	{
		if (buies[i])
		{
			ViewBuilding(buies[i]);
		}
	}
}
void Exit()
{
	FILE *fp = fopen(DEF_FNAME, "w");
	if (fp)
	{
		int i = 0;
		for (i = 0; i < MAX_BUILDING; i++)
		{
			if (buies[i])
			{
				fwrite(&i, sizeof(int), 1, fp);
				fwrite(buies[i], sizeof(Building), 1, fp);
				free(buies[i]);
			}
		}
		fclose(fp);
	}
}