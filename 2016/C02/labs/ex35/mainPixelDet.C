#include "PixelDet.h"
#include "cFCgraphics.h"
#include "TGraph.h"
#include "TH1.h"

int main()
{
	PixelDet simulator;
	simulator.EventNoise(0.005);

	float point[2] = {250., 400.};

	simulator.EventSignal(point);

	TH2C Data1 = simulator.DrawEvent();

	event Hit =  simulator.RecEvent();

	cFCgraphics g;

	//g.Draw();
	
	//g.Clear();
	
	simulator.DumpEvent();
	

	TH1F hist("Histogram0","False hits Plot",100,0,600);

	point[0] = 400.;
	point[1] = 400.;
	float c0 = 0.1;
	float c1 = 0.1;
	
	for (int i = 0; i < 1000; ++i)
	{
		if (point[0] <= 0. || point[0] >= 500.)
			c0 = -c0;
		if (point[1] <= 0. || point[1] >= 500.)
			c1 = -c1;

		point[0] += c0;
		point[0] += c1;

		simulator.EventNoise(0.1);
		simulator.EventSignal(point);
		event Hit = simulator.RecEvent();

		if(Hit.success)
		{
			float error = sqrt((point[0]-Hit.x)*(point[0]-Hit.x) + (point[1]-Hit.y)*(point[1]-Hit.y));
			if(error > 10)
				hist.Fill(error);
		}
		
		simulator.DumpEvent();
	}

	TPad* pad1 = g.CreatePad("pad1");
	
	g.AddObject(&Data1,"pad1");
	g.AddObject(pad1);

	TPad *pad2 = g.CreatePad("pad2");
	

	if(Hit.success)
	{
		PixelDet isolated(Hit.pixels);
		TH2C Data2 = isolated.DrawEvent();
		g.AddObject(&Data2,"pad2");
		g.AddObject(pad2);
	}

	TPad* pad3 = g.CreatePad("pad3");
	g.AddObject(&hist,"pad3");
	g.AddObject(pad3);

	g.Draw();
	g.Print("save.png");

	g.Clear();
	cout << "g.Clear()" << endl;

	return 0;
}