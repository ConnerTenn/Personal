
#include "World.h"

Double2::Double2() {}
Double2::Double2(double x, double y) : X(x), Y(y) {}
Double2::Double2(double pos[2]) : X(pos[0]), Y(pos[1]) {}
Double2::Double2(Double2 &pos) : X(pos.X), Y(pos.Y) {}
Double2::Double2(Int2 &pos) : X(pos.X), Y(pos.Y) {}

double Double2::operator[](int i) { if (i == 0) { return X; } else if (i == 1) { return Y; } else { Throw("ERROR::Index out Of Range\n"); return 0; } }
Double2 Double2::operator+(Double2 other) { other.X = X + other.X; other.Y = Y + other.Y; return other; }
Double2 Double2::operator-(Double2 other) { other.X = X - other.X; other.Y = Y - other.Y; return other; }
Double2 Double2::operator*(Double2 other) { other.X = X * other.X; other.Y = Y * other.Y; return other; }
Double2 Double2::operator/(Double2 other) { other.X = X / other.X; other.Y = Y / other.Y; return other; }
Double2 Double2::operator+(double val) { X += val; Y += val; return *this; }
Double2 Double2::operator-(double val) { X -= val; Y -= val; return *this; }
Double2 Double2::operator*(double val) { X *= val; Y = val; return *this; }
Double2 Double2::operator/(double val) { X /= val; Y /= val; return *this; }

Int2 Double2::ToInt2() { return { (int)X, (int)Y }; }


DnD::WorldObject::WorldObject()
{
	UuidCreate(&ObjectID);
}

void DnD::WorldObject::Draw(Surface *surface, World *world)
{

}

void DnD::Lines::Draw(Surface *surface, World *world)
{
	/*
	for (int i = 0; i < LineList.size() - 1; i++)
	{
		surface->DrawLine(world->Transform(LineList[i]).ToInt2(), world->Transform(LineList[i + 1]).ToInt2(), Colour(255, 255, 255));
	}
	if (Closed) { surface->DrawLine(world->Transform(LineList[0]).ToInt2(), world->Transform(LineList.back()).ToInt2(), Colour(255, 255, 255)); }
	*/
	surface->StartFigure();
	for (int i = 0; i < LineList.size() - 1; i++)
	{
		surface->AddLine(world->Transform(LineList[i]).ToInt2(), world->Transform(LineList[i + 1]).ToInt2());
	}
	if (Closed)
	{
		surface->AddLine(world->Transform(LineList[0]).ToInt2(), world->Transform(LineList.back()).ToInt2());
	}
}

void DnD::Ellipse::Draw(Surface *surface, World *world)
{
	surface->StartFigure();
	Int2 pos = world->Transform(Pos - Radius).ToInt2();
	Int2 dimensions = (Double2(Radius * 2) * world->Scale).ToInt2();
	surface->AddEllipse(pos, dimensions);
}

void DnD::Layer::Draw(Surface *surface, World *world)
{
	for (int i = 0; i < LineLoopList.size(); i++)
	{
		LineLoopList[i]->Draw(surface, world);
	}
}

void DnD::Environment::Draw(Surface *surface, World *world)
{
	for (int i = 0; i < LayerList.size(); i++)
	{
		LayerList[i].Draw(surface, world);
	}
}

DnD::World::World(Window *parentWindow)
{
	ParentWindow = parentWindow;

	EnvironmentList.push_back(Environment());
	EnvironmentList[0].LayerList.push_back(Layer());
	//LayerList.push_back(Layer());

	Lines *line;
	for (int i = 0; i < 1000; i++)
	//for (int i = 0; i < 0; i++)
	{
		line = new Lines();
		int sides = rand() % 10 + 3;
		double size = double(rand() % 100 + 1)/50.0;
		Int2 center = { rand() % 10000 - 5000, rand() % 10000 - 5000 };
		for (int j = 0; j < sides; j++)
		{
			//wall->LineList.push_back(center + Int2{rand() % 40 - 20, rand() % 40 - 20});
			line->LineList.push_back(center + Int2{ (int)((rand() % 50 + 2) * size * sin((double)j*TAU / (double)sides)), (int)((rand() % 40 + 10) * size * -cos((double)j*TAU / (double)sides)) });
		}
		line->Closed = true;
		//LayerList[0].LineLoopList.push_back(wall);
		EnvironmentList[0].LayerList[0].LineLoopList.push_back(line);
	}

	Ellipse *ellipse;
	for (int i = 0; i < 1000; i++)
		//for (int i = 0; i < 0; i++)
	{
		ellipse = new Ellipse();
		ellipse->Pos = { rand() % 10000 - 5000, rand() % 10000 - 5000 };
		ellipse->Radius = { (rand() % 80 + 20), (rand() % 80 + 20) };
		//LayerList[0].LineLoopList.push_back(wall);
		EnvironmentList[0].LayerList[0].LineLoopList.push_back(ellipse);
	}
}

DnD::World::~World()
{

}

void DnD::World::Draw()
{
	//for (int i = 0; i < LayerList.size(); i++)
	//{
		/*
		for (int j = 0; j < LayerList[i].LineLoopList.size(); j++)
		{
			LayerList[i].LineLoopList[j]->Draw(ParentWindow->WindowSurface, this);
		}
		*/

		//*

		//Implement GraphicsPaths to WinLib
		//Use graphics paths here

		//Add Environments; which contain Layers
		/*
		int size = 0;
		for (int j = 0; j < LayerList[i].LineLoopList.size(); j++)
		{
			for (int k = 0; k < LayerList[i].LineLoopList[j]->LineList.size() - 1; k++) { size+=2; }
			if (LayerList[i].LineLoopList[j]->Closed) { size+=2; }
		}
		std::vector<Int2> points; points.resize(size);
		int q = 0;
		for (int j = 0; j < LayerList[i].LineLoopList.size(); j++)
		{
			for (int k = 0; k < LayerList[i].LineLoopList[j]->LineList.size() - 1; k++)
			{
				points[q++] = (Transform(LayerList[i].LineLoopList[j]->LineList[k]).ToInt2());
				points[q++] = (Transform(LayerList[i].LineLoopList[j]->LineList[k + 1]).ToInt2());
			}
			if (LayerList[i].LineLoopList[j]->Closed)
			{
				points[q++] = (Transform(LayerList[i].LineLoopList[j]->LineList[0]).ToInt2());
				points[q++] = (Transform(LayerList[i].LineLoopList[j]->LineList.back()).ToInt2());
			}
		}
		ParentWindow->WindowSurface->DrawPath(points, Colour(255, 255, 255));
		*/
	//}

	ParentWindow->WindowSurface->ClearPath();
	for (int i = 0; i < EnvironmentList.size(); i++)
	{
		EnvironmentList[i].Draw(ParentWindow->WindowSurface, this);
	}
	ParentWindow->WindowSurface->DrawPath(Colour(255,255,255));
}

Double2 DnD::World::Transform(Double2 point)
{
	return{ (point.X - ViewPos.X) * Scale + 400, (point.Y - ViewPos.Y) * Scale + 300 };
}

Double2 DnD::World::ReverseTransform(Double2 point)
{
	return{ (point.X - 400) / Scale + ViewPos.X, (point.Y - 300) / Scale + ViewPos.Y };
}

void DnD::World::AddWall()
{

}
/*
void World::AddObject()
{

}

void World::AddBoarders()
{

}

void World::AddGroundPlane()
{

}*/

void DnD::World::BeginNewLineLoop(Int2 point)
{

}

void DnD::World::AddPointToCurrentLineLoop(Int2 point)
{

}

void DnD::World::UpdateNewPointPos(Int2 point)
{

}

void DnD::World::EndLineLoop(bool closed)
{

}

void DnD::World::CancelLineLoop()
{

}




