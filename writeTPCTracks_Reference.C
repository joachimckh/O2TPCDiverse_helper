#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

void writeTPCTracks_Reference(const char* inputfile, const char* savepath)
{

    // TFile* f = TFile::Open("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/o2_tpc_sc_sim_2/tpc-trackStudy.root");
    TFile* f = TFile::Open(inputfile);


    TTree* tpc = f->Get<TTree>("tpc");



    o2::tpc::TrackTPC* iniTrack = nullptr;
    o2::track::TrackParCov *iniTrackRef = nullptr, * movTrackRef = nullptr, *mcTrack = nullptr;
    float bcTB, dz;

    tpc->SetBranchAddress("iniTrack", &iniTrack);
    tpc->SetBranchAddress("iniTrackRef", &iniTrackRef);
    tpc->SetBranchAddress("movTrackRef", &movTrackRef);

    o2::track::TrackPar * mcTr = nullptr;
    tpc->SetBranchAddress("mcTrack",&mcTr);

    tpc->SetBranchAddress("imposedTB", &bcTB);
    tpc->SetBranchAddress("dz", &dz);


    // mX, mAlpha, mP : Y, Z, sinphi (Snp), tgLambda (Tgl), q/pt (Q2Pt)
    // mC[15] correlation matrix // getCov()
    double mX, mAlpha, mY, mZ, Snp, Tgl, Q2Pt;

    // CLUSTERS
    // clSector
    // clRow
    // clIniX
    // clIniY
    // clIniZ
    // clMovX
    // clMovY
    // clMovZ

    std::vector<float> *clIniX = nullptr,*clIniY = nullptr,*clIniZ = nullptr,*clMovX = nullptr,*clMovY = nullptr,*clMovZ = nullptr;
    std::vector<short> *clSector = nullptr,*clRow = nullptr;


    tpc->SetBranchAddress("clIniX",&clIniX);
    tpc->SetBranchAddress("clIniY",&clIniY);
    tpc->SetBranchAddress("clIniZ",&clIniZ);
    tpc->SetBranchAddress("clMovX",&clMovX);
    tpc->SetBranchAddress("clMovY",&clMovY);
    tpc->SetBranchAddress("clMovZ",&clMovZ);

    tpc->SetBranchAddress("clSector",&clSector);
    tpc->SetBranchAddress("clRow",&clRow);


    // object[4] trackarray = new object[4] {iniTrack, iniTrackRef, movTrackRef, mcTr};

    unsigned long nTotalCluster = 159;

    // iniTrack
    try {

       //open file for writing
       ofstream fw(Form("%s/iniTrack.txt",savepath), std::ofstream::out);
       //check if file was successfully opened for writing
       if (fw.is_open())
       {
         cout << "\nWriting  iniTrack contents to file...";

         for (int iEntry = 0; iEntry < tpc->GetEntries(); ++iEntry) { // <- Just loop over all entries

           // Load the data for the given tree entry
          tpc->GetEntry(iEntry);
           // iniTrack->print();
          mX = iniTrack->getX();
          mAlpha = iniTrack->getAlpha();
          mY = iniTrack->getY();
          mZ = iniTrack->getZ();
          Snp = iniTrack->getSnp();
          Tgl = iniTrack->getTgl();
          Q2Pt = iniTrack->getQ2Pt();


          fw << iEntry << " " << mX << " " << mAlpha << " " << mY << " " << mZ << " " << Snp << " " << Tgl << " " << Q2Pt << " " << bcTB << " " << dz << " ";

          for (int iCov = 0; iCov<15; ++iCov){
            fw << iniTrack->getCov()[iCov] << " ";
          }

          // add cluster information

          // sector info
          for (int sectorentry(0); sectorentry < clSector->size(); ++sectorentry){
            fw << clRow[0][sectorentry] << " ";
          }
          unsigned long NPad = nTotalCluster - clSector->size();
          for (int sPad(0); sPad < NPad; ++sPad){
            fw << 0 << " ";
          }
          // row info
          for (int rowentry(0); rowentry < clRow->size(); ++rowentry){
            fw << clRow[0][rowentry] << " ";
          }
          unsigned long NRow = nTotalCluster - clRow->size();
          for (int sRow(0); sRow < NRow; ++sRow){
            fw << 0 << " ";
          }
          // coordinate
          for (int xyz(0); xyz < clIniX->size(); ++xyz){
            fw << clIniX[0][xyz] << " " << clIniY[0][xyz] << " " << clIniZ[0][xyz] << " ";
          }
          unsigned long NCo = nTotalCluster - clIniX->size();
          for (int sCo(0); sCo < NCo; ++sCo){
            fw << 0 << " " << 0 << " " << 0 << " ";
          }

          fw << "\n";
        }
          fw.close();
          cout << "\nFinished writing iniTrack contents to file...";
        }
        else cout << "Problem with opening iniTrack file";
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }



    // iniTrackRef <- burde väre den samme som iniTrack - men tjek når det er eksporteret...
    try {

       //open file for writing
       ofstream fw(Form("%s/iniTrackRef.txt",savepath), std::ofstream::out);
       //check if file was successfully opened for writing
       if (fw.is_open())
       {
         cout << "\nWriting  iniTrackRef contents to file...";
         for (int iEntry = 0; iEntry < tpc->GetEntries(); ++iEntry) { // <- Just loop over all entries
           // Load the data for the given tree entry
          tpc->GetEntry(iEntry);

           // iniTrack->print();
          mX = iniTrackRef->getX();
          mAlpha = iniTrackRef->getAlpha();
          mY = iniTrackRef->getY();
          mZ = iniTrackRef->getZ();
          Snp = iniTrackRef->getSnp();
          Tgl = iniTrackRef->getTgl();
          Q2Pt = iniTrackRef->getQ2Pt();

          fw << iEntry << " " << mX << " " << mAlpha << " " << mY << " " << mZ << " " << Snp << " " << Tgl << " " << Q2Pt << " " << bcTB << " " << dz << " ";

          for (int iCov = 0; iCov<15; ++iCov){
            fw << iniTrackRef->getCov()[iCov] << " ";
          }

          // add cluster information

          // sector info
          for (int sectorentry(0); sectorentry < clSector->size(); ++sectorentry){
            fw << clRow[0][sectorentry] << " ";
          }
          unsigned long NPad = nTotalCluster - clSector->size();
          for (int sPad(0); sPad < NPad; ++sPad){
            fw << 0 << " ";
          }
          // row info
          for (int rowentry(0); rowentry < clRow->size(); ++rowentry){
            fw << clRow[0][rowentry] << " ";
          }
          unsigned long NRow = nTotalCluster - clRow->size();
          for (int sRow(0); sRow < NRow; ++sRow){
            fw << 0 << " ";
          }
          // coordinate
          for (int xyz(0); xyz < clIniX->size(); ++xyz){
            fw << clIniX[0][xyz] << " " << clIniY[0][xyz] << " " << clIniZ[0][xyz] << " ";
          }
          unsigned long NCo = nTotalCluster - clIniX->size();
          for (int sCo(0); sCo < NCo; ++sCo){
            fw << 0 << " " << 0 << " " << 0 << " ";
          }

          fw << "\n";
        }
          fw.close();
          cout << "\nFinished writing iniTrackRef contents to file...";
        }
        else cout << "Problem with opening iniTrackRef file";
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }


    // movTrackRef
    try {
       //open file for writing
       ofstream fw(Form("%s/movTrackRef.txt",savepath), std::ofstream::out);
       //check if file was successfully opened for writing
       if (fw.is_open())
       {
         cout << "\nWriting  movTrackRef contents to file...";
         for (int iEntry = 0; iEntry < tpc->GetEntries(); ++iEntry) { // <- Just loop over all entries
           // Load the data for the given tree entry
          tpc->GetEntry(iEntry);

           // iniTrack->print();
          mX = movTrackRef->getX();
          mAlpha = movTrackRef->getAlpha();
          mY = movTrackRef->getY();
          mZ = movTrackRef->getZ();
          Snp = movTrackRef->getSnp();
          Tgl = movTrackRef->getTgl();
          Q2Pt = movTrackRef->getQ2Pt();

          fw << iEntry << " " << mX << " " << mAlpha << " " << mY << " " << mZ << " " << Snp << " " << Tgl << " " << Q2Pt << " " << bcTB << " " << dz << " ";

          for (int iCov = 0; iCov<15; ++iCov){
            fw << movTrackRef->getCov()[iCov] << " ";
          }

          // add cluster information

          // sector info
          for (int sectorentry(0); sectorentry < clSector->size(); ++sectorentry){
            fw << clRow[0][sectorentry] << " ";
          }
          unsigned long NPad = nTotalCluster - clSector->size();
          for (int sPad(0); sPad < NPad; ++sPad){
            fw << 0 << " ";
          }
          // row info
          for (int rowentry(0); rowentry < clRow->size(); ++rowentry){
            fw << clRow[0][rowentry] << " ";
          }
          unsigned long NRow = nTotalCluster - clRow->size();
          for (int sRow(0); sRow < NRow; ++sRow){
            fw << 0 << " ";
          }
          // coordinate
          for (int xyz(0); xyz < clMovX->size(); ++xyz){
            fw << clMovX[0][xyz] << " " << clMovY[0][xyz] << " " << clMovZ[0][xyz] << " ";
          }
          unsigned long NCo = nTotalCluster - clMovX->size();
          for (int sCo(0); sCo < NCo; ++sCo){
            fw << 0 << " " << 0 << " " << 0 << " ";
          }


          fw << "\n";
        }
          fw.close();
          cout << "\nFinished writing movTrackRef contents to file...";
        }
        else cout << "Problem with opening movTrackRef file";
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }


    // mcTrack
    try {
       //open file for writing
       ofstream fw(Form("%s/mcTrack.txt",savepath), std::ofstream::out);
       //check if file was successfully opened for writing
       if (fw.is_open())
       {
         cout << "\nWriting  mcTrack contents to file...";
         for (int iEntry = 0; iEntry < tpc->GetEntries(); ++iEntry) { // <- Just loop over all entries
           // Load the data for the given tree entry
          tpc->GetEntry(iEntry);

           // iniTrack->print();
          mX = mcTr->getX();
          mAlpha = mcTr->getAlpha();
          mY = mcTr->getY();
          mZ = mcTr->getZ();
          Snp = mcTr->getSnp();
          Tgl = mcTr->getTgl();
          Q2Pt = mcTr->getQ2Pt();

          fw << iEntry << " " << mX << " " << mAlpha << " " << mY << " " << mZ << " " << Snp << " " << Tgl << " " << Q2Pt << " " << bcTB << " " << dz << " ";

          for (int iCov = 0; iCov<15; ++iCov){
            fw << "0" << " ";
          }

          fw << "\n";
        }
          fw.close();
          cout << "\nFinished writing mcTrack contents to file...";
        }
        else cout << "Problem with opening mcTrack file";
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }


    // end void

    cout << endl;
    }
