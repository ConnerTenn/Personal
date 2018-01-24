
#include "Cell.h"
#include "Global.h"

void Initilize()
{
	for (int i = 0; i < NumUpdateThreads; i++)
	{
		UpdateThreadState[i] = 0;
	}
	for (int i = 0; i < MaxCells; i++)
	{
		CellList.push_back(new Cell());
	}

	PlantArray = new double*[PlantWidthDevisionNum];
	for (int i = 0; i < PlantWidthDevisionNum; ++i)
	{
		PlantArray[i] = new double[PlantHeightDevisionNum];
	}
	for (int x = 0; x < PlantWidthDevisionNum; x++)
	{
		for (int y = 0; y < PlantHeightDevisionNum; y++)
		{
			PlantArray[x][y] = Rand(0, 100);
		}
	}
}

void CleanUp()
{
	delete[] UpdateThreads; UpdateThreads = 0;
	delete[] UpdateThreadState; UpdateThreadState = 0;

	for (int i = 0; i < MaxCells; i++)
	{
		delete CellList[i]; CellList[i] = 0;
	}

	for (int i = 0; i < PlantWidthDevisionNum; ++i)
	{
		delete[] PlantArray[i];
	}
	delete[] PlantArray;

	delete Win; Win = 0;
}

double PreviousTime = 0;
void UpdateControl()
{
	while (!Done)
	{
		UpdateThreadDelta = static_cast<double>(clock() - PreviousTime);
		if (PreviousTime == 0) { UpdateThreadDelta = 0; }
		PreviousTime = clock();

		while (Pause && !Done) {}
		for (int x = 0; x < PlantWidthDevisionNum; x++)
		{
			for (int y = 0; y < PlantHeightDevisionNum; y++)
			{
				if (PlantArray[x][y] < 100.0) { PlantArray[x][y] += DRand(0, 0.05); }
			}
		}

		{/*Update*/}
		{
			for (int nextCell = 0; nextCell < MaxCells; nextCell++)
			{
				bool proceed = false;
				while (!proceed)
				{
					for (int i = 0; i < NumUpdateThreads; i++)
					{
						if (UpdateThreadState[i] == 0)
						{
							UpdateIndex[i] = nextCell;
							UpdateThreadState[i] = 1;
							proceed = true;
						}
					}
				}
			}
		}

		{/*Kill*/}
		{
			RenderEnableConfirm = false;
			RenderEnable = false;
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
			while (!RenderEnableConfirm && !Done) {}
			for (int nextCell = 0; nextCell < MaxCells; nextCell++)
			{
				bool proceed = false;
				while (!proceed)
				{
					for (int i = 0; i < NumUpdateThreads && !proceed; i++)
					{
						if (UpdateThreadState[i] == 0)
						{
							UpdateIndex[i] = nextCell;
							UpdateThreadState[i] = 2;
							proceed = true;
						}
					}
				}
			}
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
			RenderEnable = true;
		}

		{/*Reproduce*/} 
		{
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
			for (int nextCell = 0; nextCell < MaxCells; nextCell++)
			{
				bool proceed = false;
				while (!proceed)
				{
					for (int i = 0; i < NumUpdateThreads && !proceed; i++)
					{
						if (UpdateThreadState[i] == 0)
						{
							UpdateIndex[i] = nextCell;
							UpdateThreadState[i] = 3;
							proceed = true;
						}
					}
				}
			}
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
		}
		{/*Repopulate*/}
		{
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
			for (int nextCell = 0; nextCell < MaxCells; nextCell++)
			{
				bool proceed = false;
				while (!proceed)
				{
					for (int i = 0; i < NumUpdateThreads && !proceed; i++)
					{
						if (UpdateThreadState[i] == 0)
						{
							UpdateIndex[i] = nextCell;
							UpdateThreadState[i] = 4;
							proceed = true;
						}
					}
				}
			}
			for (int i = 0; i < NumUpdateThreads; i++) { bool proceed = false; while (!proceed) { if (UpdateThreadState[i] == 0) { proceed = true; } } }
		}
	}
	
	UpdateThreadExit = true;
	for (int i = 0; i < NumUpdateThreads; i++)
	{
		UpdateThreadState[i] = -1;
	}
}

/*
States:
-1: exit
0: waiting
1: Update
2: kill
3: reproduce
4: repopulate
*/
void Update(int threadNum)
{
	int *state = &UpdateThreadState[threadNum];
	while (!UpdateThreadExit)
	{
		while (*state == 0) {}
		if (*state == 1) 
		{ 
			CellList[UpdateIndex[threadNum]]->Update(); 
		}
		else if (*state == 2) 
		{ 
			Cell *cell = CellList[UpdateIndex[threadNum]];
			if (cell->Health == 0)
			{
				//CellList[UpdateIndex[threadNum]] = new Cell(CellList[Rand(0, MaxCells - 1)]);
				if (ActiveCell == cell) { ActiveCell = 0; ActiveNeuron = 0; }
				delete cell;
				CellList[UpdateIndex[threadNum]] = 0;

				//DeadCellList.push_back(cell);
				//if (ActiveCell == cell) { ActiveCell = 0; }
				//CellList[UpdateIndex[threadNum]]->Cleanup();
				//CellList[UpdateIndex[threadNum]]->Initilize();
			} 
		}
		else if (*state == 3)
		{
			Cell *cell = CellList[UpdateIndex[threadNum]];
			if (cell)
			{
				if (cell->Network.ReproduceOutput->Value > 500.0 && cell->Mate)
				{
					int childIndex = Rand(0, MaxCells - 1);
					{int tries = 0; while (CellList[childIndex] && tries < MaxCells) { childIndex = Rand(0, MaxCells - 1); tries++; }}
					if (!cell->Mate->Dna.Edit) { CellList[UpdateIndex[threadNum]] = new Cell(cell, cell->Mate); }
				}
			}
		}
		else if (*state == 4)
		{
			if (!CellList[UpdateIndex[threadNum]])
			{
				//int parentIndex = Rand(0, MaxCells - 1);
				//{int tries = 0; while (!CellList[parentIndex] && tries < MaxCells) { parentIndex = Rand(0, MaxCells - 1); tries++; }}
				//if (!CellList[parentIndex]->Dna.Edit) { CellList[UpdateIndex[threadNum]] = new Cell(CellList[parentIndex]); }
				int parentIndex = Rand(0, MaxCells - 1);
				bool proceed = false; int tries = 0;
				while (!proceed && tries < MaxCells)
				{
					if (CellList[parentIndex] && CellList[parentIndex]->Energy > MaxInitialCellEnergy) { proceed = true; }
					else { tries++; }
				}
				if (!proceed) { for (int i = 0; i < MaxCells; i++) { if (CellList[parentIndex]) { proceed = true; } } }
				if (!proceed) { CellList[UpdateIndex[threadNum]] = new Cell(); }
				else { CellList[UpdateIndex[threadNum]] = new Cell(CellList[parentIndex]); }
			}
		}
		*state = 0;
	}
}

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Win = new Window(1200, 600, HInstance, iCmdShow);
	Win->Name = "Survival";
	Win->Create();

	EnvironmentSurface = Win->CreateContainer(0, 0, 600, 600);
	//PlaySurface = EnvironmentSurface->CreateContainer(ViewportX, ViewportY, PlayWidth, PlayHeight);
	//PlaySurface = EnvironmentSurface->CreateContainer(0, 0, PlayWidth, PlayHeight); PlaySurface->SetShow(false);
	AttributeSurface = Win->CreateContainer(600, 0, 600, 300);
	ControlSurface = Win->CreateContainer(600, 300, 600, 300);

	Initilize();

	Win->Focus = EnvironmentSurface;

	UpdateControlThread = std::thread(UpdateControl);
	UpdateThreads = new std::thread[NumUpdateThreads];//(Update2);
	for (int i = 0; i < NumUpdateThreads; i++)
	{
		//CellUpdateThread[i] = new std::thread(CellUpdate);
		UpdateThreads[i] = std::thread(Update, i);
	}

	while (!Done)
	{
		{/*Event Handler*/}
		{
			Win->UpdateMsg();

			if (Win->State.Quit == true)
			{
				Done = true;
			}
		}

		{/*Update*/}
		{
			if (EnvironmentSurface->State.Focus)
			{
				if (Win->Input->KeyState[Win->Input->CharacterMap['W' - 65][0]].Pressed)
				{
					EnvironmentViewportY -= 1.5 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['S' - 65][0]].Pressed)
				{
					EnvironmentViewportY += 1.5 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['A' - 65][0]].Pressed)
				{
					EnvironmentViewportX -= 1.5 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['D' - 65][0]].Pressed)
				{
					EnvironmentViewportX += 1.5 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['E' - 65][0]].Pressed)
				{
					EnvironmentViewportScale * 1.02 < 2 ? EnvironmentViewportScale *= 1.02 : 0;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['Q' - 65][0]].Pressed)
				{
					(PlayWidth + 200 / EnvironmentViewportScale) * (EnvironmentViewportScale * 0.98) >= EnvironmentSurface->Width ? EnvironmentViewportScale *= 0.98 : 0;
				}

				if (Win->Input->MouseState.LClick)
				{
					ActiveCell = 0; ActiveNeuron = 0;
					double mouseX = ReverseTransform(Win->Input->MouseState.X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);
					double mouseY = ReverseTransform(Win->Input->MouseState.Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);
					for (Cell *cell : CellList)
					{
						if (cell && Dist(mouseX, mouseY, cell->X, cell->Y) < cell->Size)
						{
							ActiveCell = cell;
						}
					}
				}
			}
			if (AttributeSurface->State.Focus)
			{
				if (Win->Input->KeyState[Win->Input->CharacterMap['W' - 65][0]].Pressed)
				{
					NetworkViewportY -= 1.5 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['S' - 65][0]].Pressed)
				{
					NetworkViewportY += 1.5 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['A' - 65][0]].Pressed)
				{
					NetworkViewportX -= 1.5 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['D' - 65][0]].Pressed)
				{
					NetworkViewportX += 1.5 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['E' - 65][0]].Pressed)
				{
					NetworkViewportScale * 1.02 < 2 ? NetworkViewportScale *= 1.02 : 0;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['Q' - 65][0]].Pressed)
				{
					(NetworkWidth + 200 / NetworkViewportScale) * (NetworkViewportScale * 0.98) >= EnvironmentSurface->Width ? NetworkViewportScale *= 0.98 : 0;
				}

				if (Win->Input->MouseState.LClick && ActiveCell)
				{
					ActiveNeuron = 0;
					double mouseX = ReverseTransform(Win->Input->MouseState.X - AttributeSurface->AbsX, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);
					double mouseY = ReverseTransform(Win->Input->MouseState.Y - AttributeSurface->AbsY, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);
					for (Neuron *neuron : ActiveCell->Network.NeuronList)
					{
						if (Dist(mouseX, mouseY, neuron->X, neuron->Y) < 10.0)
						{
							ActiveNeuron = neuron;
						}
					}
				}
			}
			if (Win->Input->KeyState[Win->Input->CharacterMap['P' - 65][0]].Pressed)
			{
				Pause = !Pause;
			}
		}

		if (RenderEnable)
		{
			{/*Render*/}
			{
				EnvironmentSurface->Clear();
				AttributeSurface->Clear();
				ControlSurface->Clear();
				//EnvironmentSurface->FillRectangle(0, 0, 600, 600, Colour(240, 240, 255));
				EnvironmentSurface->FillRectangle(0, 0, 600, 600, Colour(39, 67, 95));
				EnvironmentSurface->FillRectangle(
					(int)ApplyTransform((-PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
					(int)ApplyTransform((-PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
					(int)(PlayWidth * EnvironmentViewportScale),
					(int)(PlayHeight * EnvironmentViewportScale),
					Colour(0, 0, 0));//Colour(0xD6, 0xDB, 0xD9));
				AttributeSurface->FillRectangle(0, 0, 600, 300, Colour(39, 67, 95));
				AttributeSurface->FillRectangle(
					(int)ApplyTransform((-NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
					(int)ApplyTransform((-NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
					(int)(NetworkWidth * NetworkViewportScale),
					(int)(NetworkHeight * NetworkViewportScale),
					Colour(59, 87, 115));
				//ControlSurface->FillRectangle(0, 0, 600, 300, Colour(59, 87, 115));


				{/*EnvironmentSurface*/}
				{
					for (int n = 0; n < PlantWidthDevisionNum; n++)
					{
						for (int m = 0; m < PlantWidthDevisionNum; m++)
						{
							int x = (int)ApplyTransform((n * (PlayWidth / PlantWidthDevisionNum) - PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);
							int y = (int)ApplyTransform((m * (PlayHeight / PlantHeightDevisionNum) - PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);
							int width = (int)((PlayWidth / PlantWidthDevisionNum) * EnvironmentViewportScale);
							int height = (int)((PlayHeight / PlantHeightDevisionNum) * EnvironmentViewportScale);

							//EnvironmentSurface->FillRectangle(x + 1, y + 1, width - 1, height - 1, Colour(20, (int)(PlantArray[n][m] / 100.0 * 255.0), 20));
							EnvironmentSurface->FillRectangle(x, y, width - 1, height - 1, Colour(255 - (int)(PlantArray[n][m] / 100.0 * 255.0), 255, 255 - (int)(PlantArray[n][m] / 100.0 * 255.0)));
						}
					}
					EnvironmentSurface->DrawLine(
						(int)ApplyTransform((-PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
						(int)ApplyTransform(0.0, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
						(int)ApplyTransform((PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
						(int)ApplyTransform(0.0, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
						Colour(100, 100, 100));
					EnvironmentSurface->DrawLine(
						(int)ApplyTransform(0.0, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
						(int)ApplyTransform((-PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
						(int)ApplyTransform(0.0, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
						(int)ApplyTransform((PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
						Colour(100, 100, 100));
					for (int i = 0; i < CellList.size(); i++)
					{
						Cell *cell = CellList[i];
						if (cell)
						{
							int x = (int)ApplyTransform(cell->X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);//(int)((cell->X - cell->Dna.Size) * ViewportScale);
							int y = (int)ApplyTransform(cell->Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);//(int)((cell->Y - cell->Dna.Size) * ViewportScale);
							int size = (int)(cell->Size * EnvironmentViewportScale);
							size < 1 ? size = 1 : 0;//Ensure Cell is always seen
							int width = 2 * size;
							int height = 2 * size;
							//draw rectangles when zoomed out
							if (cell == ActiveCell)
							{
								size == 1 ? EnvironmentSurface->FillRectangle(x - size, y - size, width, height, Colour(202, 81, 0)) : EnvironmentSurface->FillEllipse(x - size, y - size, width, height, Colour(202, 81, 0));
							}
							else
							{
								if (cell->Alive)
								{
									size == 1 ? EnvironmentSurface->FillRectangle(x - size, y - size, width, height, Colour(0, 122, 204)) : EnvironmentSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 122, 204));
								}
								else
								{
									size == 1 ? EnvironmentSurface->FillRectangle(x - size, y - size, width, height, Colour(255, 82, 164)) : EnvironmentSurface->FillEllipse(x - size, y - size, width, height, Colour(255, 82, 164));
								}
							}
							EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation) * size), y - (int)(cos(cell->Rotation) * size), Colour(0, 72, 154), 2.0f);

							for (int i = 0; i < cell->EyeList.size(); i++)
							{
								Eye *eye = cell->EyeList[i];
								if (eye->Value)
								{
									double range = eye->Range * EnvironmentViewportScale;
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset) * range), y - (int)(cos(cell->Rotation + eye->Offset) * range), Colour(0, 255, 255, 255 / 4), 2.0f);
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset - eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset - eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset + eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset + eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
								}
							}
							/*for (Eye *eye : cell->EyeList)
							{
								if (eye->Value)
								{
									double range = eye->Range * EnvironmentViewportScale;
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset) * range), y - (int)(cos(cell->Rotation + eye->Offset) * range), Colour(0, 255, 255, 255 / 4), 2.0f);
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset - eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset - eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
									EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset + eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset + eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
								}
							}*/
						}
					}
					for (int i = 0; i < CellList.size(); i++)
					{
						Cell *cell = CellList[i];
						if (cell && cell == ActiveCell)
						{
							int x = (int)ApplyTransform(cell->X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);//(int)((cell->X - cell->Dna.Size) * ViewportScale);
							int y = (int)ApplyTransform(cell->Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);//(int)((cell->Y - cell->Dna.Size) * ViewportScale);
							EnvironmentSurface->FillEllipse(x - 10, y - 10, 20, 20, Colour(202, 81, 0, 255 / 2));
						}
					}
					EnvironmentSurface->DrawText(10, 10,
						"ID: " + (ActiveCell ? std::to_string((long long)ActiveCell) : "N/A") +
						"\nX: " + (ActiveCell ? std::to_string(ActiveCell->X) : "N/A") +
						"\nY: " + (ActiveCell ? std::to_string(ActiveCell->Y) : "N/A") +
						"\nRotation:" + (ActiveCell ? std::to_string(ActiveCell->Rotation) : "N/A") +
						"\nHealth:" + (ActiveCell ? std::to_string(ActiveCell->Health) : "N/A") +
						"\nEnergy:" + (ActiveCell ? std::to_string(ActiveCell->Energy) : "N/A") +
						"\n\nScale: " + std::to_string(EnvironmentViewportScale),
						Font(Colour(0, 0, 0)));

					if (EnvironmentSurface->State.Focus)
					{
						EnvironmentSurface->DrawRectangle(1, 1, EnvironmentSurface->Width - 1, EnvironmentSurface->Height - 1, Colour(0, 0, 255), 2);
					}
				}

				{/*AttributeSurface*/}
				{
					AttributeSurface->DrawLine(
						(int)ApplyTransform((-NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
						(int)ApplyTransform(0.0, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
						(int)ApplyTransform((NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
						(int)ApplyTransform(0.0, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
						Colour(100, 100, 100));
					AttributeSurface->DrawLine(
						(int)ApplyTransform(0.0, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
						(int)ApplyTransform((-NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
						(int)ApplyTransform(0.0, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
						(int)ApplyTransform((NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
						Colour(100, 100, 100));
					if (ActiveCell)
					{
						for (Axon *axon : ActiveCell->Network.AxonList)
						{
							Neuron *neuronSource = axon->Source;
							Neuron *neuronDestination = axon->Destination;
							int x1 = (int)ApplyTransform(neuronSource->X, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);
							int y1 = (int)ApplyTransform(neuronSource->Y, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);
							int x2 = (int)ApplyTransform(neuronDestination->X, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);
							int y2 = (int)ApplyTransform(neuronDestination->Y, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);
							int x3 = (x1 + x2) / 2;
							int y3 = (y1 + y2) / 2;
							float size = (float)(8.0 * NetworkViewportScale);
							size < 1.0f ? size = 1.0f : 0.0f;//Ensure Axon is always seen
							AttributeSurface->DrawLine(x1, y1, x3, y3, Colour(0, 164, 30), size);
							AttributeSurface->DrawLine(x3, y3, x2, y2, Colour(164, 164, 0), size);
							AttributeSurface->DrawLine(x1, y1, x2, y2, Colour((BYTE)(255 * ((axon->Value + 1000.0) / 2000.0)), (BYTE)(255 * ((axon->Value + 1000.0) / 2000.0)), (BYTE)(255 * ((axon->Value + 1000.0) / 2000.0))), size/2);
						}
						for (Neuron *neuron : ActiveCell->Network.NeuronList)
						{
							int x = (int)ApplyTransform(neuron->X, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);//(int)((neuron->X - neuron->Dna.Size) * ViewportScale);
							int y = (int)ApplyTransform(neuron->Y, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);//(int)((neuron->Y - neuron->Dna.Size) * ViewportScale);
							int size = (int)(10 * NetworkViewportScale);
							size < 1 ? size = 1 : 0;//Ensure Neuron is always seen
							int width = 2 * size;
							int height = 2 * size;
							if (neuron == ActiveNeuron)
							{
								AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(202, 81, 0));
							}
							else
							{
								if (neuron->Type == 1)
								{
									AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 204, 50));
								}
								else if (neuron->Type == 2)
								{
									AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(204, 204, 0));
								}
								else
								{
									AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 122, 204));
								}
							}
							AttributeSurface->FillEllipse(x - size / 2, y - size / 2, width / 2, height / 2, Colour((BYTE)(255 * ((neuron->Value + 1000.0) / 2000.0)), (BYTE)(255 * ((neuron->Value + 1000.0) / 2000.0)), (BYTE)(255 * ((neuron->Value + 1000.0) / 2000.0))));
							if (neuron->Type > 0) { AttributeSurface->DrawText(x, y - 5, neuron->Label, Font(Colour(200, 255, 255))); }
						}
					}
					AttributeSurface->DrawText(10, 10,
						"ID: " + (ActiveNeuron ? std::to_string((long long)ActiveNeuron) : "N/A") +
						"\nX: " + (ActiveNeuron ? std::to_string(ActiveNeuron->X) : "N/A") +
						"\nY: " + (ActiveNeuron ? std::to_string(ActiveNeuron->Y) : "N/A") +
						"\nValue: " + (ActiveNeuron ? std::to_string(ActiveNeuron->Value) : "N/A") +
						"\n\nScale: " + std::to_string(NetworkViewportScale),
						Font(Colour(255, 255, 255)));

					if (AttributeSurface->State.Focus)
					{
						AttributeSurface->DrawRectangle(1, 1, AttributeSurface->Width - 1, AttributeSurface->Height - 1, Colour(0, 0, 255), 2);
					}
				}

				{/*ControlSurface*/}
				{
					ControlSurface->DrawText(10, 10,
						"Window Delta Time: " + std::to_string(Win->Delta) +
						"\nUpdateThread Delta Time: " + std::to_string(UpdateThreadDelta),
						Font(Colour(255, 255, 255)));

					if (ControlSurface->State.Focus)
					{
						ControlSurface->DrawRectangle(1, 1, ControlSurface->Width - 1, ControlSurface->Height - 1, Colour(0, 0, 255), 2);
					}
				}


				Win->Render();
			}
		}
		else
		{
			RenderEnableConfirm = true;
		}
	}

	UpdateControlThread.join();
	for (int i = 0; i < NumUpdateThreads; i++)
	{
		//CellUpdateThread[i] = new std::thread(CellUpdate);
		UpdateThreads[i].join();
	}

	CleanUp();
}
