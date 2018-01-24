
class Cell;
class NeuralNetwork;
struct Neuron;
struct Axion;
struct Eye;
struct DNA;

#pragma once
#include "Global.h"

/*
Operations:
0: add
1: subtract
2: multiply
3: divide
4: Constant
*/
struct NeuronAttributes
{
	uint8_t Type = 0;

	std::string Label;

	unsigned int Operation = 0;
	double X = 0;
	double Y = 0;

	int Value = 0;

	NeuronAttributes(uint8_t type = 0, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 4);
		if (Operation == 4 && Type == 0)
		{
			Value = Rand(0, 1000);
		}
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Operation = Rand(0, 4); }
		if (Rand(0, 50) == 0) { X = Rand(-NetworkWidth / 2, NetworkWidth / 2); }
		if (Rand(0, 50) == 0) { Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); }
		if (Operation == 4 && Type == 0)
		{
			if (Rand(0, 50) == 0) { Value = Rand(0, 1000); }
		}
	}
};

struct Neuron
{
	//0: Normal
	//1: Input
	//2: Output
	uint8_t Type = 0;

	std::string Label;

	unsigned int Operation = 0;
	double X = 0;
	double Y = 0;

	int Value = 0;

	std::vector<Axion *> SourceList;
	std::vector<Axion *> DestinationList;
	Neuron(NeuronAttributes attributes)
	{
		Type = attributes.Type;
		Label = attributes.Label;
		X = attributes.X;
		Y = attributes.Y;
		Operation = attributes.Operation;
		Value = attributes.Value;
	}
	/*Neuron(uint8_t type, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 4);
		if (Operation == 4)
		{
			Value = Rand(0, 1000);
		}
	}*/
};


struct AxionAttributes
{
	int SourceNeuronIndex;
	int DestinationNeuronIndex;
	double Weighting = 0;
	AxionAttributes(int maxIndex)
	{
		SourceNeuronIndex = Rand(0, maxIndex);
		DestinationNeuronIndex = Rand(0, maxIndex);
		Weighting = DRand(0, 1);
	}
	void Mutate(int maxIndex)
	{
		if (Rand(0, 50) == 0) { SourceNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { DestinationNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { Weighting = DRand(0, 1); }
	}
};

struct Axion
{
	int Value = 0;
	double Weighting = 0;

	Neuron *Source;
	Neuron *Destination;
	Axion(AxionAttributes attributes, Neuron *source, Neuron *destination)
	{
		Weighting = attributes.Weighting;

		Source = source;
		Destination = destination;
	}
};

class NeuralNetwork
{
public:
	std::vector<Neuron *> NeuronList;
	std::vector<Axion *> AxionList;


	std::vector<Neuron *> EyeInputs;
	Neuron *CellProximityInput;

	Neuron *RotateLeftOutput;
	Neuron *RotateRightOutput;
	Neuron *ForwardOutput;
	Neuron *BackwardOutput;
	Neuron *LeftOutput;
	Neuron *RightOutput;
	Neuron *ReproduceOutput;

	NeuralNetwork()
	{
	}
	~NeuralNetwork()
	{
		for (Neuron *neuron : NeuronList)
		{
			delete neuron;
		}
		for (Axion *axion : AxionList)
		{
			delete axion;
		}
	}

	void Update()
	{
		for (int i = 0; i < NeuronList.size(); i++)//Update Neurons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axion *axion = neuron->SourceList[j];
				switch (neuron->Operation)
				{
				case 0:
					neuron->Value += axion->Value;
					break;
				case 1:
					neuron->Value -= axion->Value;
					break;
				case 2:
					neuron->Value *= axion->Value;
					break;
				case 3:
					neuron->Value /= axion->Value;
					break;
				case 4:
					break;
				}
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)//update Axions with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->DestinationList.size(); j++)
			{
				Axion *axion = neuron->DestinationList[j];
				axion->Value = (int8_t)((double)neuron->Value * axion->Weighting);
			}
		}
	}
};

struct EyeAttributes
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;

	EyeAttributes()
	{
		Fov = DRand(0.0, PI);
		Offset = DRand(0.0, TAU);
		Range = DRand(0.0, MaxCellViewRange);
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Fov = DRand(0.0, PI); }
		if (Rand(0, 50) == 0) { Offset = DRand(0.0, TAU); }
		if (Rand(0, 50) == 0) { Range = DRand(0.0, MaxCellViewRange); }
	}
};

struct Eye
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;
	int Value = 0;
	Eye(EyeAttributes attributes)
	{
		Fov = attributes.Fov;
		Offset = attributes.Offset;
		Range = attributes.Range;
	}
};

struct DNA
{
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<EyeAttributes> EyeAttributesList;
	std::vector<NeuronAttributes> NeuronAttributesList;
	std::vector<AxionAttributes> AxionAttributesList;
	
	DNA()
	{
		Size = DRand(MinCellSize, MaxCellSize);
		Speed = DRand(0, MaxCellSpeed);
		EatPlants = !Rand(0, 1);
		EatCell = !Rand(0, 100);
		NumEyes = NumCellEyes;

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList.push_back(EyeAttributes());
			NeuronAttributesList.push_back(NeuronAttributes(1, "EyeInput"));
		}

		NeuronAttributesList.push_back(NeuronAttributes(1, "CellProximityInput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateLeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateRightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ForwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "BackwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "LeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ReproduceOutput"));
	}

	DNA(DNA *parent)
	{
		Size = parent->Size;
		Speed = parent->Speed;
		EatPlants = parent->EatPlants;
		EatCell = parent->EatCell;
		NumEyes = parent->NumEyes;

		EyeAttributesList = parent->EyeAttributesList;
		NeuronAttributesList = parent->NeuronAttributesList;
		AxionAttributesList = parent->AxionAttributesList;

		Mutate();
	}

	DNA(DNA *parentA, DNA *parentB)
	{
		if (Rand(0, 1) == 0) { Size = parentA->Size; } else { Size = parentB->Size; }
		if (Rand(0, 1) == 0) { Speed = parentA->Speed; } else { Speed = parentB->Speed; }
		if (Rand(0, 1) == 0) { EatPlants = parentA->EatPlants; } else { EatPlants = parentB->EatPlants; }
		if (Rand(0, 1) == 0) { EatCell = parentA->EatCell; } else { EatCell = parentB->EatCell; }
		if (Rand(0, 1) == 0) { NumEyes = parentA->NumEyes; } else { NumEyes = parentB->NumEyes; }

		//Eyes
		for (int i = 0; i < NumEyes; i++)
		{
			if (Rand(0, 1) == 0) { EyeAttributesList.push_back(parentA->EyeAttributesList[i]); } else { EyeAttributesList.push_back(parentB->EyeAttributesList[i]); }
		}

		//Neurons
		for (int i = 0; i < max(parentA->NeuronAttributesList.size(), parentB->NeuronAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentA->NeuronAttributesList[i]);
				}
			}
			else
			{
				if (parentB->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentB->NeuronAttributesList[i]);
				}
			}
		}

		//Axions
		for (int i = 0; i < max(parentA->AxionAttributesList.size(), parentB->AxionAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->AxionAttributesList.size() > i)
				{
					AxionAttributesList.push_back(parentA->AxionAttributesList[i]);
				}
			}
			else
			{
				if (parentB->NeuronAttributesList.size() > i)
				{
					AxionAttributesList.push_back(parentB->AxionAttributesList[i]);
				}
			}
		}
		//Axion Check
		for (int i = 0; i < AxionAttributesList.size(); i++)
		{
			if (AxionAttributesList[i].SourceNeuronIndex >= AxionAttributesList.size() || AxionAttributesList[i].DestinationNeuronIndex >= AxionAttributesList.size())
			{
				AxionAttributesList.erase(AxionAttributesList.begin() + i);
			}
		}

		Mutate();
	}

	void Mutate()
	{
		if (Rand(0, 50) == 0) { Size = DRand(MinCellSize, MaxCellSize); }
		if (Rand(0, 50) == 0) { Speed = DRand(0, MaxCellSpeed); }
		if (Rand(0, 50) == 0) { EatPlants = !Rand(0, 1); }
		if (Rand(0, 50) == 0) { EatCell = !Rand(0, 100); }

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList[i].Mutate();;
		}

		for (int i = 0; i < NeuronAttributesList.size(); i++)
		{
			NeuronAttributesList[i].Mutate();
			if (Rand(0, 50) == 0) { NeuronAttributesList.push_back(NeuronAttributes()); }
		}

		for (int i = 0; i < AxionAttributesList.size(); i++)
		{
			AxionAttributesList[i].Mutate((int)AxionAttributesList.size());
			if (Rand(0, 50) == 0) { AxionAttributesList.push_back(AxionAttributes((int)AxionAttributesList.size())); }
		}
	}
};

class Cell
{
public:
	double X; double Y;
	double Rotation;
	double Energy = InitialCellEnergy;
	double Health = MaxCellHealth;
	NeuralNetwork Network;
	bool Alive = true;

	//DNA
	DNA Dna;
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<Eye> EyeList;

	Cell() :
		Dna()
	{
		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		//Dna
		Initilize();
	}

	Cell(Cell *parent) :
		Dna(&(parent->Dna))
	{
		{
			double rotation = DRand(0, TAU);
			X = parent->X + sin(rotation) * (2 * parent->Size);
			Y = parent->Y - cos(rotation) * (2 * parent->Size);
		}
		Rotation = DRand(0, TAU);

		Initilize();
	}

	Cell(Cell *parentA, Cell *parentB) :
		Dna(&(parentA->Dna), &(parentB->Dna))
	{
		{
			double rotation = DRand(0, TAU);
			X = (parentA->X + parentB->X) / 2.0 + sin(rotation) * (2 * max(parentA->Size, parentB->Size));
			Y = (parentA->Y + parentB->Y) / 2.0 - cos(rotation) * (2 * max(parentA->Size, parentB->Size));
		}
		Rotation = DRand(0, TAU);

		Initilize();
	}

	~Cell()
	{
		//EyeList.clear();
		//for (int i = 0; i < NumEyes; i++)
		//{
			//delete EyeList[i]; EyeList[i] = 0;
		//}
	}

	void Initilize()
	{
		Size = Dna.Size;
		Speed = Dna.Speed;
		EatPlants = Dna.EatPlants;
		EatCell = Dna.EatCell;
		NumEyes = Dna.NumEyes;


		for (EyeAttributes attributes : Dna.EyeAttributesList)
		{
			EyeList.push_back(Eye(attributes));
		}

		for (NeuronAttributes attributes : Dna.NeuronAttributesList)
		{
			Neuron *neuron = new Neuron(attributes);
			Network.NeuronList.push_back(neuron);
			if (attributes.Label == "EyeInput") { Network.EyeInputs.push_back(neuron); }
			if (attributes.Label == "CellProximityInput") { Network.CellProximityInput = neuron; }
			if (attributes.Label == "RotateLeftOutput") { Network.RotateLeftOutput = neuron; }
			if (attributes.Label == "RotateRightOutput") { Network.RotateRightOutput = neuron; }
			if (attributes.Label == "ForwardOutput") { Network.ForwardOutput = neuron; }
			if (attributes.Label == "BackwardOutput") { Network.BackwardOutput = neuron; }
			if (attributes.Label == "LeftOutput") { Network.LeftOutput = neuron; }
			if (attributes.Label == "RightOutput") { Network.RightOutput = neuron; }
			if (attributes.Label == "ReproduceOutput") { Network.ReproduceOutput = neuron; }
		}

		for (AxionAttributes attributes : Dna.AxionAttributesList)
		{
			Neuron *source = Network.NeuronList[attributes.SourceNeuronIndex];
			Neuron *destination = Network.NeuronList[attributes.DestinationNeuronIndex];

			Axion *axion = new Axion(attributes, source, destination);
			Network.AxionList.push_back(axion);
			source->DestinationList.push_back(axion);
			destination->SourceList.push_back(axion);
		}
	}

	void Update()
	{
		if (Alive)
		{
			{/*Update Senses*/}
			{
				Cell* cell;
				for (int i = 0; i < CellList.size(); i++)
				{
					cell = CellList[i];
					if (cell != this && cell->Alive)
					{
						double dist = Dist(X, Y, cell->X, cell->Y);

						{/*Eye*/}
						{
							if (dist <= MaxCellViewRange)
							{
								for (int j = 0; j < EyeList.size(); j++)
								{
									Eye &eye = EyeList[j];
									if (dist <= eye.Range)
									{
										//calculate within FOV
										//double angle = GetAngle(cell->X - X, cell->Y - Y);
										//if (angle > fmod(Rotation, TAU) + fmod(eye->Offset, TAU) - fmod(eye->Fov, TAU) && angle < fmod(Rotation, TAU) + fmod(eye->Offset, TAU) + fmod(eye->Fov, TAU))
										//{
										//	int val = (int)(255.0 - 255.0 * (dist / eye->Range));
										//	if (val > eye->Value) { eye->Value = val; }
										//}
										if (AngleBetweenPoints(X, Y, X + sin(eye.Offset + Rotation), Y - cos(eye.Offset + Rotation), cell->X, cell->Y) <= eye.Fov)
										{
											double ang = AngleBetweenPoints(X, Y, X + sin(eye.Offset + Rotation), Y - cos(eye.Offset + Rotation), cell->X, cell->Y);
											double xa = X + sin(eye.Offset + Rotation); double ya = Y - cos(eye.Offset + Rotation);
											int val = (int)(1000.0 - 1000.0 * (dist / eye.Range));
											if (val > eye.Value)
											{
												eye.Value = val;
											}
										}
										else
										{
											eye.Value = 0;
										}
									}
									else
									{
										eye.Value = 0;
									}
								}
							}

							for (int i = 0; i < Network.EyeInputs.size(); i++)
							{
								Network.EyeInputs[i]->Value = EyeList[i].Value;
							}
						}

						{/*CellProximity*/}
						{
							if (dist <= Size + cell->Size)
							{
								Network.CellProximityInput->Value = 1000;
							}
						}
					}
				}
			}

			Network.Update();

			{/*Update Actions*/}
			{
				double rotationLeft;
				double rotationRight;
				rotationLeft = ((double)Network.RotateLeftOutput->Value / 1000.0) * (TAU / 1000.0);
				rotationRight = ((double)Network.RotateRightOutput->Value / 1000.0) * (TAU / 1000.0);
				Rotation += rotationLeft + rotationRight;

				double forward = 0;
				double back = 0;
				double left = 0;
				double right = 0;
				forward += (double)(Network.ForwardOutput->Value) / 1000 * Speed;
				back += (double)(Network.BackwardOutput->Value) / 1000 * Speed;
				left += (double)(Network.LeftOutput->Value) / 1000 * Speed;
				right += (double)(Network.RightOutput->Value) / 1000 * Speed;

				X += (right - left) * cos(Rotation) + (forward - back) * sin(Rotation);
				Y -= -(right - left) * sin(Rotation) + (forward - back) * cos(Rotation);

				if (X > PlayWidth / 2) { X = PlayWidth / 2; }
				else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
				if (Y > PlayHeight / 2) { Y = PlayHeight / 2; }
				else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }

				Energy -= abs(forward + back + left + right + rotationLeft + rotationRight + 2.0 * Size) / 10.0;
				Energy -= 1.0;
				if (Energy <= 0.0)
				{
					Energy = 0;
					Health -= 1.0;
				}
				if (Health <= 0.0)
				{
					Health = 0.0;
					Alive = false;
				}
			}
		}
	}
};
