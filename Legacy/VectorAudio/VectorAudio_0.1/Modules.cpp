
#include "Include\Modules.h"

void Pipeline::Process(ModuleBase *module)
{
#ifdef DEBUG
	std::cout << "Pipeline::Process\n";
#endif
	ProcessQueue = ModuleList;

	struct
	{
		bool operator()(ModuleBase *a, ModuleBase *b) const
		{
			//lowest y first; if y is the same: lowest x first;
			if (a->Position[1] == b->Position[1])
			{
				return a->Position[0] < b->Position[0];
			}
			else
			{
				return a->Position[1] < b->Position[1];
			}
		}
	} compare;

	std::sort(ProcessQueue.begin(), ProcessQueue.end(), compare);

	for (int i = 0; i < ProcessQueue.size(); i++)
	{
		ProcessQueue[i]->Process();
	}
}

void Pipeline::AddModule(ModuleBase *module)
{
	ModuleList.push_back(module);
}

void Pipeline::RemoveModule(ModuleBase *module)
{
#ifdef DEBUG
	std::cout << "Pipeline::RemoveModule\n";
	int removeCount = 0;
#endif
	for (int i = 0; i < ModuleList.size(); i++)
	{
		if (ModuleList[i] == module)
		{
			ModuleList.erase(ModuleList.begin() + i); i--;
			//i = ModuleList.size();
			//line removed; reason: will remove all instances of that object in case of duplicates
#ifdef DEBUG
			removeCount++;
#endif
		}
	}
#ifdef DEBUG
	std::cout << "Remove Count:" << removeCount << "\n";
#endif
}

void Pipeline::ProcessToHere(ModuleBase *module)
{

}


void ModuleBase::DrawModule()
{
	
}

void ModuleBase::Process()
{

}

