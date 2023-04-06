void tmva_train() {
  //-------------------

  // I create an output file in which I can put the output of the TMVA

  auto outputFile = TFile::Open("TMVAOutputCV.root", "RECREATE");

  TMVA::Factory factory("TMVAClassification", outputFile,
                        "!V:ROC:!Correlations:!Silent:Color:"
                        "!DrawProgressBar:AnalysisType=Classification");

  //-------------------
  // Declare DataLoader
  // I add all the variables to the loader

  TMVA::DataLoader loader("dataset");

  loader.AddVariable("Length");
  loader.AddVariable("Width");
  loader.AddVariable("Size");
  loader.AddVariable("Conc");
  loader.AddVariable("Conl");
  loader.AddVariable("Asym");
  loader.AddVariable("M3Long");
  loader.AddVariable("M3Trans");
  loader.AddVariable("Alpha");
  loader.AddVariable("Dist");

  //-------------------
  // Set up Dataset (code example 9 of user guide)

  double sigWeight = 1.0;
  double bkgWeight = 1.0;
  loader.SetInputTrees("signal.txt", "background.txt", sigWeight, bkgWeight);

  // Apply additional cuts on the signal and background samples
  //  in the case I need them
  TCut mycuts = "";
  TCut mycutb = "";

  // I prepare the Trees for the training and the test
  // If no specifications, half of the events in the tree are used for training,
  // half for testing

  loader.PrepareTrainingAndTestTree(mycuts, mycutb, "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V");

  //-----------------
  // I choose 4 different methods for my evaluation and book them:

  // Boosted Decision Trees (Adaptive Boost)
  factory.BookMethod(
      &loader, TMVA::Types::kBDT, "BDT",
      "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:"
      "AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType="
      "GiniIndex:nCuts=20");

  // Multi-Layer Perceptron (Neural Network)
  factory.BookMethod(&loader, TMVA::Types::kMLP, "MLP",
                     "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:"
                     "HiddenLayers=N+5:TestRate=5:!UseRegulator");

  // Linear Discriminant Analysis (Fisher discriminant)
  factory.BookMethod(
      &loader, TMVA::Types::kFisher, "Fisher",
      "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:"
      "NbinsMVAPdf=50:NsmoothMVAPdf=10");

  // Cut optimisation
  factory.BookMethod(&loader, TMVA::Types::kCuts, "CutsPCA",
                     "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp="
                     "FSmart:VarTransform=PCA");

  //-------------------
  // Now I give to the factory the commands to train all the MVAs and then for
  // the test and evaluation

  // I train MVAs. I use the training tree that I create before.
  factory.TrainAllMethods();

  // I Evaluate all MVAs. I use the Tree that I prepared before with the test
  // events
  factory.TestAllMethods();

  // I Have an evaluation of the different methods and see a comparison of the
  // performances
  factory.EvaluateAllMethods();

  // I close the output file to save the evaluations given by TMVA
  outputFile->Close();

  // I inform the user that TMVA finished the evaluation and the results are
  // written in the output file
  cout << "\n\n\n\nMLtmva MACRO FINISHED THE EVALUATION OF THE METHODS FOR THE "
          "INSERTED SIGNAL AND BACKGROUND DATASAMPLES.\n"
       << endl;
  cout << "\nThe output of the TMVA evaluation is written in the file: "
       << outputFile << endl;

  // I ask the user if he wants to see the ROC curve
  char ROCanswer;

  cout << "\nDo you want to see the ROC curve with all the methods and to open "
          "the TMVAGui to see some plots about training and test? (y/n) \t";
  cin >> ROCanswer;

  if (ROCanswer == 'y') {
    // I plot the ROC curve
    auto canvas = factory.GetROCCurve(&loader);
    canvas->Draw("AL");
  }

  // Launch the GUI for the root macros
  if (!gROOT->IsBatch())TMVA::TMVAGui("TMVAOutputCV.root");

  cout << "\n\nNow looking at the output file and at the ROC curve you can "
          "decide which method is the best one for the analysis that you want "
          "to do."
       << endl;

  return 0;
}
