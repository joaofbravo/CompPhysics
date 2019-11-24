void mPolymorphism () {
  TList list;

  TH1D* histo = new TH1D("histo", "histo", 100, 0., 100.);
  TF1* func = new TF1("func", "gaus(0)", 0., 100.);
  TMatrixD* mat = new TMatrixD(10,10);

  list.Add(histo);
  list.AddLast(mat);
  list.AddFirst(func);

  for (int i = 0; i < list.GetSize(); i++) {
    cout << "Object name is " << list.At(i)->GetName() << " and the type is " << list.At(i)->ClassName() << endl;
  }
}