 // Pierwsze zajęcia	
 // https://github.com/andlip/RootPlus
 // ZBThr20.root
 


double Wykladnicza(double *x, double *p){
	// a^(bx+c) 
	
	// chcemy dopasować do punktow w zakresie (60, 80) i 300 +
	
	if (x[0] < 60 || (x[0] > 80 && x[0] < 300)) { TF1::RejectPoint(); }
	return TMath::Power(p[0], p[1]*x[0]+p[2]);
	
}

 int Pierwsze(){

	 TFile *f = new TFile("ZBThr20.root"); // wczytanie pliku .root
	 TH2D* Histogram = (TH2D*)f->Get("BbcAnalysis/ADC_vs_BbcTileId"); // f-kcja pobierająca obiekt z pliku
	 //Histogram->Draw("colz");	
 	 
	 TH1D* ProjY = Histogram->ProjectionY("ProjY", 25,25); // projekcja na ygreki, arg = nry binu: <a; b)
	 
	// Fitowanie tła statystycznego:
	// 1 - funkcja do fitowania
	TF1* FitFun = new TF1("FitFun", Wykladnicza, 1, 1000, 3);
	// 2 - Inicjalizacja fitu
	FitFun->SetParameters(1,1, 1); // ta metoda dziala do 10 parametrow
	// FitFun->SetParameter(nr_parametru , wartosc); // alternatywa
	// 3 - Fit
	ProjY->Fit(FitFun);
	// 4 - Wyniki
	ProjY->Draw("colz");
	
	double p1, p2, p3, e1, e2, e3;
	
	p1 = FitFun->GetParameter(0);
	p2 = FitFun->GetParameter(1);
	p3 = FitFun->GetParameter(2);
	e1 = FitFun->GetParError(0);
	e2 = FitFun->GetParError(1);
	e3 = FitFun->GetParError(2);

	cout << "\n Parametry fitu: \np1 \t p2 \t p3 \n " << p1 << " \t "<< p2 << " \t "<< p3 << endl;

	// Zaprezentowac histogram po odjeciu fitu
	// 1 - potrzebny histogram - container
	
	TH1D* Signal = (TH1D*)ProjY->Clone(); // to powoduje ze mamy ten sam zakres i liczbe binow na osiach
	Signal->SetName("Signal");
	// 2 - odjac jedno od drugiego
	double BinValue, FunValue, Delta, BinCentre;
	for (int i = 1; i <= ProjY->GetNbinsX(); i++){
		BinValue = ProjY->GetBinContent(i);
		BinCentre = ProjY->GetBinCenter(i);
		FunValue = FitFun->Eval( BinCentre );
		Delta = BinValue - FunValue;
		Signal ->SetBinContent(i, Delta);
	}
		Signal->SetLineColor(kBlue);
		
		Signal->Draw("EPSAME");
		
		TLegend *legend = new TLegend(0.78,0.6,0.98,0.75); // x-low, y-loow, x-up, y-up
		//legend->SetHeader("Header","C"); // option "C" allows to center the header
		legend->AddEntry("ProjY","Signal+Background","l");
		legend->AddEntry("Signal","Background subtracted","lep");
		legend->AddEntry(FitFun,"Background fit","l");
		legend->Draw();

		ProjY->GetXaxis()->SetRangeUser(1, 1000); // setrangeuser - przyjmuje wartości x_min, x_max
		//ProjY->SetRange(1, 1000); // setrange - przyjmuje bin_min i bin_max
		ProjY->SetTitle("ADC count in BBC tile 25; ADC value; N entries");
		
	return 0;


 }
 
 
 
 
 
