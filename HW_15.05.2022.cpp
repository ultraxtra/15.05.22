
#include <iostream>
#include <cmath>
#include<fstream>

using namespace std;


class TMyEquation
{
protected:
	double* Roots;
	int RootsCount;
	double* Koefs;
	int KoefsCount;

public:

	TMyEquation(int KoefsCount = 2)
	{
		KoefsCount = KoefsCount;
		Koefs = new double[GetKoefsCount() + 1];
	}

	~TMyEquation()
	{
		delete Roots;
		delete Koefs;
	}

	int GetKoefsCount()
	{
		return KoefsCount;
	}

	int GetRootsCount()
	{
		return RootsCount;
	}
	void SetKoef()
	{
		cout << "Enter koeffitients: \n";
		for (int i = GetKoefsCount(); i >= 0; i--)
		{
			cout << "Enter koeffitient [" << i << "]: ";
			cin >> Koefs[i];
		}
	}

	virtual double* GetRoots() = 0;

};




class TMyLinearEquation : public TMyEquation
{
public:
	TMyLinearEquation() : TMyEquation(1) { }
	~TMyLinearEquation() {	}

	virtual double* GetRoots() override
	{
		cout << "\n";
		cout << Koefs[1] << " * x + " << Koefs[0] << " = 0\n";
		cout << "x = " << -Koefs[0] / Koefs[1] << "\n";
		RootsCount = 1;
		Roots = new double[GetRootsCount()];
		Roots[0] = -Koefs[0] / Koefs[1];
		return  Roots;
	}

};

class TMySquareEquation : public TMyEquation
{
public:
	TMySquareEquation() : TMyEquation(2) { }
	~TMySquareEquation() {	}

	virtual double* GetRoots() override
	{
		double discr = Koefs[1] * Koefs[1] - 4 * Koefs[2] * Koefs[0]; 
		cout << "\n";
		cout << Koefs[2] << " * x^2 + " << Koefs[1] << " * x + " << Koefs[0] << " = 0\n";

		if (discr > 0)
		{
			RootsCount = 2;
			Roots = new double[GetRootsCount()];
			Roots[0] = (-Koefs[1] + sqrt(discr)) / (2 * Koefs[2]); 
			Roots[1] = (-Koefs[1] - sqrt(discr)) / (2 * Koefs[2]);
			cout << "x1 = " << Roots[0] << "\n";
			cout << "x2 = " << Roots[1] << "\n";
		}
		else if (discr == 0)
		{
			RootsCount = 1;
			Roots = new double[GetRootsCount()];
			Roots[0] = -Koefs[1] / (2 * Koefs[2]); 
			cout << "x1 = " << Roots[0] << "\n";
		}
		else
		{
			RootsCount = 0;
			Roots = new double[GetRootsCount()];
			cout << "Square Equation have no roots!\n";

		}

		return  Roots;
	}

};


class TMyShape
{
public:
	virtual void Show() = 0;
	virtual TMyShape* Load(ifstream& inf) = 0;
	virtual void Save(ofstream& outf) = 0;

};

class TMySquare : public TMyShape
{

public:
	TMySquare(double X, double Y, double Len)
	{
		this->X = X;
		this->Y = Y;
		this->Len = Len;
	}
	virtual void Show() override
	{
		cout << "Square (" << "X = " << X << ", Y = " << Y << ", Len = " << Len << ")\n";

	}
	virtual TMyShape* Load(ifstream& inf) override
	{
		inf.read((char*)&*this, sizeof(TMySquare));
		//this->Show();
		return this;
	}
	virtual void Save(ofstream& outf) override
	{
		char ch = 'S';
		outf.write((char*)&ch, sizeof(ch));
		outf.write((char*)&*this, sizeof(*this));
	}
	double X;
	double Y;
	double Len;
};

class TMyRectangle : public TMyShape
{
public:
	TMyRectangle(double X, double Y, double LenX, double LenY)
	{
		this->X = X;
		this->Y = Y;
		this->LenX = LenX;
		this->LenY = LenY;
	}
	virtual void Show() override
	{
		cout << "Rectangle (" << "X = " << X << ", Y = " << Y << ", LenX = " << LenX << ", LenY = " << LenY << ")\n";
	}
	virtual TMyShape* Load(ifstream& inf) override
	{
		inf.read((char*)&*this, sizeof(TMyRectangle));
		//this->Show();
		return this;
	}
	virtual void Save(ofstream& outf) override
	{
		char ch = 'R';
		outf.write((char*)&ch, sizeof(ch));
		outf.write((char*)&*this, sizeof(*this));
	}

	double X;
	double Y;
	double LenX;
	double LenY;
};

class TMyCircle : public TMyShape
{
public:
	TMyCircle(double X, double Y, double Radius)
	{
		this->X = X;
		this->Y = Y;
		this->Radius = Radius;
	}

	TMyCircle(const TMyCircle& ref_circle)
	{
		this->X = ref_circle.X;
		this->Y = ref_circle.Y;
		this->Radius = ref_circle.Radius;
	}

	virtual void Show() override
	{
		cout << "Circle (" << "X = " << X << ", Y = " << Y << ", Radius = " << Radius << ")\n";
	}
	virtual TMyShape* Load(ifstream& inf) override
	{
		//TMyCircle* ShapeTmp = new TMyCircle(1, 5, 10);
		//TMyCircle _ShapeTmp = TMyCircle(10, 50, 100);
		inf.read((char*)&*this, sizeof(TMyCircle));
		//this->Show();
		return this;
	}
	virtual void Save(ofstream& outf) override
	{
		char ch = 'C';
		outf.write((char*)&ch, sizeof(ch));
		outf.write((char*)&*this, sizeof(*this));
	}
	double X;
	double Y;
	double Radius;
};

class TMyEllipse : public TMyShape
{
public:
	TMyEllipse(double X, double Y, double LenX, double LenY)
	{
		this->X = X;
		this->Y = Y;
		this->LenX = LenX;
		this->LenY = LenY;
	}
	virtual void Show() override
	{
		cout << "Ellipse (" << "X = " << X << ", Y = " << Y << ", LenX = " << LenX << ", LenY = " << LenY << ")\n";

	}
	virtual TMyShape* Load(ifstream& inf) override
	{
		inf.read((char*)&*this, sizeof(TMyEllipse));
		//this->Show();
		return this;
	}
	virtual void Save(ofstream& outf) override
	{
		char ch = 'E';
		outf.write((char*)&ch, sizeof(ch));
		outf.write((char*)&*this, sizeof(*this));
	}
	double X;
	double Y;
	double LenX;
	double LenY;
};


int main()
{

	cout << "Task 2\n";

	TMyShape* Shapes[8];
	TMyShape* LoadedShapes[8];


	Shapes[0] = new TMyRectangle(100, 5, 50, 86);
	Shapes[1] = new TMyCircle(215, 151, 100);
	Shapes[2] = new TMySquare(255, 250, 159);
	Shapes[3] = new TMyEllipse(120, 425, 130, 9930);

	Shapes[4] = new TMyRectangle(1, 1, 50, 50);
	Shapes[5] = new TMyCircle(5, 5, 500);
	Shapes[6] = new TMySquare(25, 25, 150);
	Shapes[7] = new TMyEllipse(7, 8, 9, 10);

	//TMyShape* CirclePtr = new TMyCircle(3, 4, 50);
	string FileName = "Shapes.txt";
	//cout << "Basic shape: ";
	//CirclePtr->Show();*/

	//ofstream outF(FileName, ofstream::app);
	ofstream outF(FileName);
	cout << "\ Shapes array: " << "\n";
	for (int i = 0; i < 8; i++)
	{
		Shapes[i]->Show();
		if (outF) Shapes[i]->Save(outF);
		else cout << "File open error: " << FileName << "\n";

		cout << " - saved \n";
	}
	outF.close();

	ifstream inF(FileName);
	char ch = ' ';
	int i = 0;

	while (!inF.eof())
	{
		inF.read((char*)&ch, sizeof(ch));
		if (!inF.eof())
		{
			cout << "Figure N " << i << " ";
			switch (ch)
			{
			case 'C':
				//ShapeTmp->Show();
				LoadedShapes[i] = new TMyCircle(0, 0, 0);
				if (inF)  LoadedShapes[i]->Load(inF);
				else cout << "File open error: " << FileName << endl;
				LoadedShapes[i]->Show();
				i++;
				break;
			case 'R':
				//ShapeTmp->Show();
				LoadedShapes[i] = new TMyRectangle(0, 0, 0, 0);
				if (inF)  LoadedShapes[i]->Load(inF);
				else cout << "File open error: " << FileName << endl;
				LoadedShapes[i]->Show();
				i++;
				break;
			case 'S':
				//ShapeTmp->Show();
				LoadedShapes[i] = new TMySquare(0, 0, 0);
				if (inF)  LoadedShapes[i]->Load(inF);
				else cout << "File open error: " << FileName << endl;
				LoadedShapes[i]->Show();
				i++;
				break;
			case 'E':
				//ShapeTmp->Show();
				LoadedShapes[i] = new TMyEllipse(0, 0, 0, 0);
				if (inF)  LoadedShapes[i]->Load(inF);
				else cout << "File open error: " << FileName << endl;
				LoadedShapes[i]->Show();
				i++;
				break;
			default:
				break;
			}
		}
	}
	inF.close();



	cout << "\n";
	cout << "Task 1\n";

	TMySquareEquation SquareEQ;
	SquareEQ.SetKoef();
	SquareEQ.GetRoots();
	cout << "\n";

	TMyLinearEquation LinearEQ;
	LinearEQ.SetKoef();
	LinearEQ.GetRoots();




}