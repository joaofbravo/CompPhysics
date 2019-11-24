#include "EqSolver.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"
#include <iostream>
#include <cmath>

using namespace std;

EqSolver::EqSolver() : M(nullptr), line_change(false), singular(false), LU_done(false), gauss_singular(false) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

// matriz M e vector de constantes B
EqSolver::EqSolver(const FCmatrix& fM, const Vec& fb) {

	if (fb.size() != fM.size())
	{
		cout << "Wrong dimentions in assigned system!" << endl;
		exit(1);
	}

	// if (fM.GetClassName() == "full")
	// 	M = new FCmatrixFull(fM);
	// else if (fM.GetClassName() == "banded")
	// 	M = new FCmatrixBanded(fM);
	// else {
	// 	cout << "You did not complete this matrix class yet..." << endl;
	// 	exit(1);
	// }

	M = new FCmatrixFull(fM);

	b = fb;

	permute.resize(M->size());

	for (unsigned int i = 0; i < permute.size(); ++i)
		permute[i] = i;

	line_change = false;
	singular = false;
	LU_done = false;
	gauss_singular = false;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

EqSolver::~EqSolver() {
	if (M) delete M;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Set methods ===============

void EqSolver::SetMatrix(const FCmatrix& fM) {
	
	unsigned int size_old = M->size();

	if (M) delete M;

	// if (fM.GetClassName() == "full")
	// 	M = new FCmatrixFull(fM);
	// else if (fM.GetClassName() == "banded")
	// 	M = new FCmatrixFull(fM);
	// else {
	// 	cout << "You did not complete this matrix class yet..." << endl;
	// 	exit(1);
	// }
	M = new FCmatrixFull(fM);

	if(size_old != M->size() || LU_done){
		permute.resize(M->size());

		for (unsigned int i = 0; i < M->size(); ++i)
			permute[i] = i;
	}

	line_change = false;
	singular = false;
	LU_done = false;
	gauss_singular = false;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void EqSolver::SetConstants(const Vec& fb) {
	
	if (M && fb.size() != M->size())
	{
		cout << "Wrong dimentions in assigned constants vector!" << endl;
		exit(1);
	}

	b = fb;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void EqSolver::ResetFlags(){
	line_change = false;
	singular = false;
	LU_done = false;
	gauss_singular = false;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

//=============== Get methods ===============

const FCmatrix& EqSolver::GetMatrix() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (*M);
}

const Vec& EqSolver::GetConstants() const {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return b;
}

//=============== Direct methods ===============

//return triangular matrix and changed vector of constants
bool EqSolver::GaussElimination(FCmatrix& A, Vec& fb) {

	if (fb.size() != A.size())
	{
		cout << "Wrong system dimentions for Gauss Elimination!" << endl;
		exit(1);
	}

	unsigned int Nrow = A.size();
	unsigned int Mcol = A[0].size();

	double maxel;
	int maxindex;

	const float tol = 0.01f;
	bool ill_cond = false;

	bool gauss_banded = false;
	line_change = false;

	// A FAZER...
	// if (A.GetClassName() == "banded")
	// {
	// 	if gauss successful
	// 	gauss_banded = true;
	// }

	if (A.GetClassName() == "full" || !gauss_banded)
	{
		// vetor com inverso do max el em cada linha
		//double s[Nrow];

		for (int i = 0; i < Nrow-1; ++i)
		{
		
			int situation;
			// com uma coluna de quasi zeros
			if ((situation = Pivoting(A,i,fb))==-1) {
				cout << "Cannot find solution! This matrix is singular." << endl;

				singular = true;
				gauss_singular = true;

				#ifdef DEBUG
				cout << __PRETTY_FUNCTION__ << endl;
				#endif	

				return false;
			} else if(situation)
				line_change = !line_change;


			// se mal condicionada
			if (fabs(A[i][i]/A[0][0]) < (double)tol)
				ill_cond = true;

			
			// tornar matrix upper triangular
			for (int j = i+1; j < Nrow; ++j) {
				double cc = A[j][i] / A[i][i];

				if(cc == 0.) break;

				A[j] -= (cc * A[i]);
				fb[j] -= (cc * fb[i]);
			}
		}
		//cout << fabs(A[Nrow-1][Mcol-1] / A[1][1]) << endl;
		if (fabs(A[Nrow-1][Mcol-1] / A[1][1]) < 1.e-14) {
			cout << "Cannot find solution! This matrix is singular." << endl;
			
			singular = true;
			gauss_singular = true;

			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif	

			return false;
		}
	}

	if(ill_cond)
		cout << "Be careful! This system is ill-conditioned." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return true;
}

//resolução do sistema pelo método de eliminação de Gauss
Vec EqSolver::GaussEliminationSolver() {
	
	if(!M){
		cout << "No system assigned to EqSolver." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(singular) {
		cout << "Cannot find solution! This matrix is singular." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(!LU_done)
	{
		FCmatrix* A;

		// if (M->GetClassName() == "full")
		// 	A = new FCmatrixFull(*M);
		// else if (M->GetClassName() == "banded")
		// 	A = new FCmatrixFull(*M);
		// else 
		// {
		// 	cout << "You did not complete this matrix class yet..." << endl;
		// 	exit(1);
		// }
		A = new FCmatrixFull(*M);

		Vec b_copy = b;

		if(!GaussElimination(*A,b_copy)){
			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif	

			return Vec();
		}

		int Nrow = A->size();
		Vec x((*A)[0].size());

		for (int k = Nrow-1; k > -1; k--) 
		{
			double sumX = 0;

			// scan values of a row from diagonal to the right
			for (int j = k+1; j < Nrow; j++)
				sumX += x[j] * (*A)[k][j];

			// compute solution values
			x[k] = (b_copy[k] - sumX) / (*A)[k][k];
		}

		delete A;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return x;
	}
	else  // if LUdecomposition has been done 
	{
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return LUdecompositionSolver(b);
	}
}

//decomposição LU com |L|=1
//L na subdiagonal inferior, U na diagonal e subdiagonal superior
bool EqSolver::LUdecomposition(FCmatrix& A) {

	if(singular){
		cout << "Cannot find solution! This matrix is singular." << endl;

		LU_done = true;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return false;
	}

	unsigned int Nrow = A.size();
	unsigned int Mcol = A[0].size();

	double maxel;
	int maxindex;

	const float tol = 0.01f;
	bool ill_cond = false;

	bool LU_banded = false;
	line_change = false;


	// A FAZER ...
	// if (A.GetClassName() == "banded")
	// {
	// 	if gauss successful
	// 	LU_banded = true;
	// }

	if (A.GetClassName() == "full" || !LU_banded)
	{

		for (int i = 0; i < Nrow-1; ++i)
		{

			int situation;
			Vec fb(0);

			situation = Pivoting(A,i,fb);
			if ((situation==-1)) {
				cout << "Cannot find solution! This matrix is singular." << endl;

				singular = true;
				LU_done = true;

				#ifdef DEBUG
				cout << __PRETTY_FUNCTION__ << endl;
				#endif	

				return false;
			} else if(situation>0)
			{
				line_change = !line_change;
				if(situation != i)
					std::swap(permute[i], permute[situation]);
			}


			// se mal condicionada
			if (fabs(A[i][i]/A[0][0]) < (double)tol)
				ill_cond = true;

			// tornar A em LU
			for (int j = i+1; j < Nrow; ++j)
			{
				double cc = A[j][i] / A[i][i];

				A[j][i] = cc;

				for (int k = i+1; k < Mcol; ++k)
					A[j][k] -= (cc * A[i][k]);			
			}

			// cout << "A: ";	A.Print();
			// cout << "permute: ";
			// for (vector<int>::iterator i = permute.begin(); i != permute.end(); ++i)
			// 	cout << *i << " ";
			// cout << endl;
		}

		if (fabs(A[Nrow-1][Mcol-1]) / A[0][0] < 1.e-14) {
			cout << "Cannot find solution! This matrix is singular." << endl;

			singular = true;
			LU_done = true;

			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif	

			return false;
		}
	}

	if(ill_cond)
		cout << "Be careful! This system is ill-conditioned." << endl;

	LU_done = true;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return true;
}

//resolução do sistema pelo método de LU Decomposition
Vec EqSolver::LUdecompositionSolver(Vec fb) {

	if(!M){
		cout << "No system assigned to EqSolver." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if (singular){
		cout << "Cannot find solution! This matrix is singular." << endl;

		LU_done = true;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(!LU_done){
		if(!LUdecomposition(*M)){
			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif

			return Vec();
		}
	}

	if(fb.size() != M->size()){
		cout << "LU Solver will use set constants vector." << endl;
		fb = b;
	}

	unsigned int Nrow = M->size();
	Vec y((*M)[0].size());
	Vec x((*M)[0].size());

	// forward substitution (Ly=b)
	for (int k = 0; k < Nrow; k++)
	{
		double sumC = 0.;

		for (int i = 0; i < k; i++)
			sumC += y[i] * (*M)[k][i];

		y[k] = fb[permute[k]] - sumC;
	}

	// backward substitution (Ux=y)
	for (int k = Nrow-1; k > -1; k--)
	{
		double sumC = 0.;

		for (int i = k+1; i < Nrow; i++)
			sumC += x[i] * (*M)[k][i];

		x[k] = (y[k] - sumC) / (*M)[k][k];
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return x;
}

int EqSolver::Pivoting(FCmatrix& A,int row, Vec& fb)
{
	unsigned int Nrow = A.size();

	double s[Nrow];

	//Testar se dá porcaria
	/*for (int k = 0; k < row; ++k)
		s[k] = 0;

*/
	//retorna -1 caso dê porcaria
	//retorna 0 se não houver linechange
	//retorna índice da linha com a qual se trocou se houver linechange


	for (int k = row; k < Nrow; ++k)
	{
		double maxel = 0.;

		for (int n = 0; n < Nrow; ++n){
			if(maxel < fabs(A[k][n]))
				maxel = fabs(A[k][n]);
		}

		if(maxel > 0)
			s[k] = 1./maxel;
		else
			s[k] = 0.;
	}

	int maxindex = 0;

	if((maxindex = A.GetColMax(s, row, row))==-1)
		return -1;
	//cout << maxindex << endl;

	if (maxindex != row) 
	{
		A.swapRows(row, maxindex, s);
		if(fb.size()!=0)
			fb.swap(row, maxindex);

		return maxindex;
	}

	else
		return 0;
}

//=============== Iterative methods ===============

bool EqSolver::GeneralIterator(bool method, double eps, Vec& x, int N, FCmatrix& A,Vec& fb)
{	
	if(LU_done)
	{
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		if (singular)
		{
			cout << "LUdecomposition was already performed. Initial matrix was singular and has been lost." << endl;
			x= Vec();
			return false;
		}

		cout << "LU Decomposition was already performed. Returning exact solution." << endl;
		x= LUdecompositionSolver(b);
		return false;
	}

	
	const float tol = 0.01f;
	bool ill_cond = false;

	// if(M->GetClassName() == "full")
	// 	A = new FCmatrixFull(*M);
	// else if(M->GetClassName() == "banded")
	// 	A = new FCmatrixFull(*M);
	// else 
	// {
	// 	cout << "You did not complete this matrix class yet..." << endl;
	// 	exit(1);
	// }

	// A = new FCmatrixFull(*M);

	//fb = new Vec(b);

	for (int i = 0; i < A.size() - 1; ++i)
	{

		if (Pivoting(A,i,(fb))==-1|| fabs((A)[i][i]/(A)[0][0]) < (double)tol)
		{ 
			ill_cond = true;
			cout << "Be careful! This system is ill-conditioned." <<endl;
		}
	}

	cout << "Initial approximation: ";
	x.Print();



	//Vec x (x0);
	Vec x_aux (A.size()); //zero’s

	bool btol = false;
	int it = 0;

	while (!btol && (it++ < N)) 
	{
		x_aux = x;

		for (int i=0; i<A.size(); i++) 
		{
			x[i] = 0.;

			for (int j=0; j<A.size(); j++)
			{
				if (i != j) 
				{
					if(method)
						x[i] -= (A)[i][j]*x_aux[j];
					else
						x[i] -= (A)[i][j]*x[j];
				}
			}

			x[i] += fb[i];
			x[i] /= A[i][i];

			//guarantee that all vector entries are converging equally
			if (fabs(x[i]-x_aux[i]) < eps) 
				btol = true;
			else 
				btol = false;
		}
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	
	if(btol)
	{	
		if(method)
			cout << "Number of iterations for Jacobi: " << it << endl << endl;
		else
			cout << "Number of iterations for GaussSeidel: " << it << endl << endl;

		return true;
	}
	else
		return false;
}


Vec EqSolver::JacobiIterator(double eps, Vec x0)
{	
	if(!M){
		cout << "No system assigned to EqSolver." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(x0.size() != M->size()){
		if(x0.size() != 0)
			cout << "Wrong size in approximation vector given. Will use the null vector as x0." << endl;
		x0 = Vec(M->size()); //zero’s
	}
	Vec x(x0);

	FCmatrixFull A(*M);
	Vec fb (b);


	if(GeneralIterator(true,eps,x,1000,A,fb))
		return x;
	else
	{
		cout << "Cannot find solution! Jacobi was unsuccessfull." << endl << endl;
		return Vec();
	}
}

Vec EqSolver::GaussSeidelIterator(double eps, Vec x0)
{	
	if(!M){
		cout << "No system assigned to EqSolver." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(x0.size() != M->size()){
		if(x0.size() != 0)
			cout << "Wrong size in approximation vector given. Will use the null vector as x0." << endl;
		x0 = Vec(M->size()); //zero’s
	}
	Vec x(x0);

	FCmatrixFull A(*M);
	Vec fb (b);


	if(GeneralIterator(false,eps,x,1000,A,fb))
		return x;
	
	else
	{
		cout << "Cannot find solution! GaussSeidel was unsuccessfull." << endl << endl;
		return Vec();
	}
}

Vec EqSolver::SORIterator(double eps, Vec x0)
{	
	if(!M){
		cout << "No system assigned to EqSolver." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return Vec();
	}

	if(x0.size() != M->size()){
		if(x0.size() != 0)
			cout << "Wrong size in approximation vector given. Will use the null vector as x0." << endl;
		x0 = Vec(M->size()); //zero’s
	}
	Vec x(x0);
	Vec fb (b);
	FCmatrixFull A (*M);
	if(GeneralIterator(false,eps,x,10,A,fb))
		return x;
	else
	{
		/*A.Print();
		fb.Print();
		x.Print();*/
		//SOR:
		
		Vec x_aux (A.size()); //zero’s

		bool first = true;
		double delta = 0;

		bool btol = false;
		
		int it = 0;

		double w = 1;

		while (!btol && (it++ < 1000)) 
		{
			x_aux = x;

			for (int i=0; i<A.size(); i++) 
			{
				x[i] = 0.;

				for (int j=0; j<A.size(); j++)
				{
					if (i != j) 
						x[i] -= (A)[i][j]*x[j];
			
				}

				//mandar o vetor de constantes lá para dentro
				
				x[i] += (fb)[i];
				x[i] *= w/(A)[i][i];

				x[i] += (1-w)*x_aux[i];
				//guarantee that all vector entries are converging equally
				if (fabs(x[i]-x_aux[i]) < eps) 
					btol = true;
				else 
					btol = false;
			}

			if(first)
			{
				delta = !(x-x_aux);
				first = false;
			}

			else if(it == 3)
				w=2/(1+sqrt(fabs(1-pow((!(x-x_aux)/delta),1./(double)it))));
		}

		if(btol)
		{
			cout << "Number of iterations for SOR: " << it +10 << endl << endl;
	
			return x;
		}
		else
		{
			cout << "Cannot find solution! SOR was unsuccessfull." << endl << endl;
			return Vec();
		}
	}

}


//=============== work on Matrix ===============

const FCmatrix& EqSolver::Invert() {

	if(!singular && !LU_done)
		LUdecomposition(*M);

	if (singular) {
		cout << "Cannot invert! The matrix is singular. Returning empty matrix." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return FCmatrixnull;
	}

	Vec e_i(M->size());

	vector<Vec> Minverted;

	//resolve LU para cada linha de I
	for (int i = 0; i < M->size(); ++i)
	{
		e_i[i] = 1;
		Minverted.push_back(LUdecompositionSolver(e_i));
		e_i[i] = 0;
	}

	// criar inversa de M
	// if (M->GetClassName() == "full")
	// {
	// 	delete M;
	// 	M = new FCmatrixFull(Minverted);
	// 	M->Transpose();
	// }
	// else if (M->GetClassName() == "banded")
	// {
	// 	delete M;
	// 	M = new FCmatrixFull(Minverted);
	// 	M->Transpose();
	// }
	// else {
	// 	cout << "You did not complete this matrix class yet..." << endl;
	// 	exit(1);
	// }
	delete M;
	M = new FCmatrixFull(Minverted);
	M->Transpose();
	
	line_change = false;
	singular = false;
	LU_done = false;
	gauss_singular = false;

	cout << "Matrix A was inverted." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return (*M);
}

double EqSolver::Determinant(){

	if(!M){
		cout << "No matrix assigned to EqSolver." << endl;
		return 0.;
	}

	if (singular)
		return 0.;

	if(LU_done)
	{
		double detLU = 1.;

		for (int i = 0; i < M->size(); ++i)
			detLU *= (*M)[i][i];

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		if(line_change)
			return -detLU;
		return detLU;
	}

	FCmatrix* A;

	// if (M->GetClassName() == "full")
	// 	A = new FCmatrixFull(*M);
	// else if (M->GetClassName() == "banded")
	// 	A = new FCmatrixFull(*M);
	// else {
	// 	cout << "You did not complete this matrix class yet..." << endl;
	// 	exit(1);
	// }
	A = new FCmatrixFull(*M);

	Vec dummy(A->size());

	if(!GaussElimination(*A,dummy))
		return 0.;

	double det = 1.;

	for (int i = 0; i < A->size(); ++i)
		det *= (*A)[i][i];

	if(A) delete A;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	if (line_change)
		return -det;
	return det;
}

//=============== Print ===============

void EqSolver::Print(short int p, short int w) const
{
	if(!LU_done || gauss_singular)
	{
		cout << "\nPrinting the sistem Ax = b" << endl;

		if(singular)
			cout << "A is singular." << endl << endl;

		cout << "A: ";

		if(!M)
			cout << "No matrix assigned to EqSolver." << endl;
		else
			M->Print(p, w);

		cout << "b:" << endl;
		b.Print(p, w);

		cout << endl;
	}
	else
	{
		vector<Vec> vectorU;
		vector<Vec> vectorL;

		for (int i = 0; i < M->size(); ++i)
		{
			Vec U_i(M->size());

			Vec L_i(M->size());

			for(int j= i; j<M->size();j++)
				U_i[j]=(*M)[i][j];

			vectorU.push_back(U_i);

			for(int j= 0; j < i;j++)
				L_i[j]=(*M)[i][j];

			vectorL.push_back(L_i);

			vectorL[i][i] = 1;
		}

		FCmatrixFull L(vectorL);
		FCmatrixFull U(vectorU);

		cout << "\nPrinting the sistem LUx = Pb" << endl;

		if(singular)
			cout << "Matrix A is singular." << endl << endl;

		cout << "L: ";
		L.Print(p, w);

		cout << "U:";
		U.Print(p, w);

		cout << "P:" << endl;

		for (int i = 0; i < permute.size(); ++i)
			cout << permute[i] << " ";		

		cout <<"\n\nb:" << endl;
		b.Print(p, w);

		cout << endl;
	}	

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}