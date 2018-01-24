
#pragma once

void FindStringDymensions(std::string string, int *size)
{
	size[0] = 0; size[1] = 0;
	int buf = 0;
	if (string.size()) { size[1] = 1; }
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == '\n')
		{
			size[1]++;
			buf = 0;
		}
		else
		{
			buf++;
			if (buf > size[0]) { size[0] = buf; }
		}
	}
}

void FindGridDymensions(std::vector<std::vector<std::string>> grid, std::vector<int> &widthList, std::vector<int> &heightList)
{
	heightList.resize(grid.size());
	if (grid.size()) { widthList.resize(grid[0].size()); }

	//calculate the gratest size of each element of the grid
	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			int size[2];
			FindStringDymensions(grid[y][x], size);
			if (size[0] > widthList[x]) { widthList[x] = size[0]; }
			if (size[1] > heightList[y]) { heightList[y] = size[1]; }
		}
	}
}

std::string HorizontalBorderStyle = " ## ";
std::string VerticalBorderStyle = " \n#\n#\n ";
std::vector<std::string> BoarderStyles =
{
	{//Top Left
"\
    \n\
 ###\n\
 ###\n\
 ## \n\
"
	},
	{//Top Middle
"\
    \n\
####\n\
####\n\
 ## \n\
"
	},
	{//Top Right
"\
    \n\
### \n\
### \n\
 ## \n\
"
	},
	{//Middle Left
"\
 ## \n\
 ###\n\
 ###\n\
 ## \n\
"
	},
	{//Middle Middle
"\n\
    \n\
 ## \n\
 ## \n\
    \n\
"
	},
	{//Middle Right
"\n\
 ## \n\
### \n\
### \n\
 ## \n\
"
	},
	{//Bottom Left
"\n\
 ## \n\
 ###\n\
 ###\n\
    \n\
"
	},
	{//Bottom Middle
"\n\
 ## \n\
####\n\
####\n\
    \n\
"
	},
	{//Bottom Right
"\n\
 ## \n\
### \n\
### \n\
    \n\
"
	},
};

void PlaceText(char **grid, int x, int y, int width, int height, std::string text)
{
	int offX = x , offY = y;
	/*for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '\n' || offY >= width) { offY++; offX = x; }
		else
		{
			if (offX - x < width && offY - y < width) { grid[offY][offX] = text[i]; }
		}
		offX++;
	}*/
	int i = 0; 
	while (i < text.size() && offY - y < height)
	{
		if (text[i] == '\n' || offX - x >= width) { offY++; offX = x; i++; }
		else
		{
			grid[offY][offX] = text[i];
			i++;
			offX++;
		}
	}
}

//grid format:
//list of elemnts
void DisplayGird(std::vector<std::vector<std::string>> grid)
{
	int borderStyleSize = 1;
	//initialize vars
	std::string out;
	std::vector<int> widthList;
	std::vector<int> heightList;
	FindGridDymensions(grid, widthList, heightList);
	int width = 0; int height = 0;
	for (int i = 0; i < widthList.size(); i++) { width += widthList[i]; }
	for (int i = 0; i < heightList.size(); i++) { height += heightList[i]; }
	width += (int)widthList.size() * borderStyleSize + borderStyleSize;
	height += (int)heightList.size() * borderStyleSize + borderStyleSize;
	
	//init out array buffer
	char **outArray;
	outArray = new char*[height];
	for (int y = 0; y < height; y++)
	{
		outArray[y] = new char[width + 1];
		for (int x = 0; x < width; x++)
		{
			outArray[y][x] = ' ';
		}
		outArray[y][width] = '\n';
	}

	{/*Place Elements*/}
	{
		int y = borderStyleSize;
		for (int gridY = 0; gridY < grid.size(); gridY++)
		{
			int x = borderStyleSize;
			for (int gridX = 0; gridX < grid[gridY].size(); gridX++)
			{
				PlaceText(outArray, x, y, widthList[gridX], heightList[gridY], grid[gridY][gridX]);
				x += borderStyleSize + widthList[gridX];
			}
			y += borderStyleSize + 1;
		}
	}
	{/*Place Boarder*/ }
	{
		//int borderIndex = 0; borderIndex;
		//PlaceText(outArray, x, y, borderStyleSize, borderStyleSize, BoarderStyles[borderIndex]);
		//float gridX = 0, gridY = 0;

		//while ()
		//gridX += 0.5;

		//if (/*X at 0 && Y at 0*/) {}
		//if (/*X at max && Y at 0*/) {}
		//if (/*X at 0 && Y at max*/) {}
		//if (/*X at max && Y at max*/) {}

		//if (/*X at 0*/) {}
		//if (/*Y at 0*/) {}
		//if (/*X at max*/) {}
		//if (/*Y at max*/) {}

		/*center*/
		//else {}


		
	}

	out = "";
	for (int y = 0; y < height; y++)
	{
		for (int x = 00; x < width + 1; x++)
		{
			out += outArray[y][x];
		}
	}
	std::cout << out;

	//cleanup
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width + 1; x++) { outArray[y][x] = 0; }
		delete[] outArray[y]; outArray[y] = 0;
	}
	delete[] outArray; outArray = 0;
}
