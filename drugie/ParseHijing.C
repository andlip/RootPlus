/*
 *  Macro for reading HIJING data from 
 *  
 */

int ParseHijing(TString InFileName, TString OutFileName){
	
	ifstream in;
	in.open(InFileName);
	
	int nPart, EventIdx, PDG, Id, Stable, MotherIdx;
	float px, py, pz, b, m;
	float pT;
	//float eta;
	//float phi;
	TLorentzVector *mom;
	
	TFile f(OutFileName,"recreate");

	/* Define tree here */

	//###########################

	/* Define tree branches here */	

	//###########################	
	string tempString;
	
	int nEvnt = 200; // 3

	for (int i = 1; i <= nEvnt; i++){ // event loop
		
		getline(in, tempString); // Read Event header
		if (in.eof() || in.bad()) break; // check if theres anything elese to read
		
		if(tempString != " BEGINNINGOFEVENT"){ // Parse garbage
			getline(in, tempString);
			cout << tempString << endl;
			getline(in, tempString);
			cout << tempString << endl;
		}
		  
		// Parse event header
		
		cout << "###"<<tempString << " " << i << endl;
		in >> EventIdx >> nPart >> b;		
		cout << EventIdx << endl << nPart << endl;

		// particle loop
		for (int j = 0; j < nPart; j++){
		
			// Parse input	
			in >> Id 
			>> PDG 
			>> MotherIdx
			>> Stable
			>> px  
			>> py 
			>> pz 
			>> m;
			pT = TMath::Sqrt(px*px + py*py);
			
			/* Fill tree here*/
			
			//###########################	
			
			// print to crosscheck
			cout <<  Id << " " << 
			PDG  << " " << 
			MotherIdx << " " << 
			Stable << " " << 
			px   << " " << 
			py  << " " << 
			pz << " " <<  
			m << " " << 
			pT << endl;
		
		} // end of part. loop
		getline(in, tempString); // An additional \n at the end o part-list?
	} // end of evnt loop	
	in.close();
   
   /* Save tree to a file here */
   
   //###########################
   
return 0;
}

