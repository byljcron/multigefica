#ifndef GEFICA_FIELD_H
#define GEFICA_FIELD_H

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TObject.h>
#include <TVectorD.h>
#include <iostream>
#include <TF1.h>

namespace GEFICA { class Field; }

class GEFICA::Field: public TObject 
{
   public:
      int x; // number of steps along the 1st axis
      int MaxIterations;
      int n;
      bool * isbegin;
      double *E1,*C1,*P,*StepNext,*StepBefore,*Impurity,Csor,E0,ER;
      double XUpSum,XDownSum,Xlimit;

   public:
      Field(int ix) {n=ix;x=ix;};
      virtual ~Field() {delete[] E1;delete [] P;delete [] C1;
         delete[] StepNext;delete[] StepBefore;delete[] isbegin;delete[] Impurity;};

      virtual void Create(double steplength);
      virtual bool Iterate();

      virtual void Save(const char *fout=NULL);
      virtual void Load(const char *fin=NULL);
      virtual void SetImpurity(TF1 * Im);

      virtual double GetData(double tarx,int thing); // 1:Ex 2:f 0:Impurty

   protected:
      virtual void Update(int idx); 
      virtual int FindIdx(double tarx,int begin,int end);

   public:
      ClassDef(Field,1);
};
#endif