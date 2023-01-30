#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

void writeTPCTracks_Reference()//const char* inputfile, const char* suffix, const char* fName)
{

    TFile* f = TFile::Open("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/o2_tpc_sc_sim_2/tpc-trackStudy.root");

    TTree* tpc = f->Get<TTree>("tpc");



    o2::tpc::TrackTPC* iniTrack = nullptr;
    o2::track::TrackParCov *intTrackRef = nullptr, * movTrackRef = nullptr, *mcTrack = nullptr;
    float bcTB, dz;

    tpc->SetBranchAddress("iniTrack", &iniTrack);
    tpc->SetBranchAddress("intTrackRef", &intTrackRef);
    tpc->SetBranchAddress("movTrackRef", &movTrackRef);

    o2::track::TrackPar * mcTr = nullptr;
    tpc->SetBranchAddress("mcTrack",&mcTr);

    tpc->SetBranchAddress("imposedTB", &bcTB);
    tpc->SetBranchAddress("dz", &dz);


    // mX, mAlpha, mP : Y, Z, sinphi (Snp), tgLambda (Tgl), q/pt (Q2Pt)
    // mC[15] correlation matrix // getCov()
    double mX, mAlpha, mY, mZ, Snp, Tgl, Q2Pt;

    // object[4] trackarray = new object[4] {iniTrack, intTrackRef, movTrackRef, mcTr};



    // iniTrack
    try {

       //open file for writing
       ofstream fw("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/iniTrack.txt", std::ofstream::out);
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



    // intTrackRef <- burde väre den samme som iniTrack - men tjek når det er eksporteret...
    try {

       //open file for writing
       ofstream fw("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/iniTrackRef.txt", std::ofstream::out);
       //check if file was successfully opened for writing
       if (fw.is_open())
       {
         cout << "\nWriting  iniTrackRef contents to file...";
         for (int iEntry = 0; iEntry < tpc->GetEntries(); ++iEntry) { // <- Just loop over all entries
           // Load the data for the given tree entry
          tpc->GetEntry(iEntry);

           // iniTrack->print();
          mX = intTrackRef->getX();
          mAlpha = intTrackRef->getAlpha();
          mY = intTrackRef->getY();
          mZ = intTrackRef->getZ();
          Snp = intTrackRef->getSnp();
          Tgl = intTrackRef->getTgl();
          Q2Pt = intTrackRef->getQ2Pt();

          fw << iEntry << " " << mX << " " << mAlpha << " " << mY << " " << mZ << " " << Snp << " " << Tgl << " " << Q2Pt << " " << bcTB << " " << dz << " ";

          for (int iCov = 0; iCov<15; ++iCov){
            fw << intTrackRef->getCov()[iCov] << " ";
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
       ofstream fw("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/movTrackRef.txt", std::ofstream::out);
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
       ofstream fw("/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/mcTrack.txt", std::ofstream::out);
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

    cout << endl;
    }
