#define BANDWIDTH 9
#define FILE_NAME "B8G20"

#include "input.cpp"
#include <ctime>
#include <fstream>
#include <string>
#include <stack>

void FindSlop();
void fcolumn(int &y , queue <int> *G);
void f3(queue <int> &f ,int &i1 ,int &i2 ,int &j ,int &j1);
void Find(int n , int &i1 , int &i2 , int &j , int &j1);
bool isMember(int &p , int *q);
int Fmax();

// save load:
void yG_save(int y ,queue<int> *G , ofstream &myfile);
void copyTo(queue<int> *from , queue<int> *to);
void yG_load(int &y ,queue<int> *G , ifstream &f);
int Pow(int a , int b);
//

void clearQ(std::queue<int> &q);
void clearArrayQ(std::queue<int> *q , int n);
//int strt , os;
//int stop , oe;

int hast = 0;
int nhast = 0;
int tedad = 0;

int start_s;
int middle_s;
int ti_t; // taken time

void main(){
	/*
	int i1 = -1;
	int i2 = -1;
	int j = -1;
	int j1 = -1;
	Find(6 , i1 , i2 , j , j1);
	// cout
	cout << "salam" << endl;
	cout << a[0][2] << endl;
	//Find(4 , i1 , i2 , j , j1);
	cout << "i1 : " << i1 <<endl;
	cout << "i2 : " << i2 <<endl;
	cout << "j : " << j <<endl;
	cout << "j1 : " << j1 <<endl;
	// end cout

	s[0][0] = 2;
	*/
	cout << "start!\n";
	start_s = clock();
	middle_s = clock();
	FindSlop();
	int stop_s = clock();
	cout << endl << "gerth = " << gerth << endl << "m = " << m << endl;
	//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	cout << endl << "FindSlop execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << " sec" << endl;

	//cout << "hast : " << hast << endl << "nhast : " << nhast << endl;
}

void FindSlop(){
	int y , i1 , i2 , j , j1 , ic;
	queue<int>* G;
	G = new queue<int>[lenSolution]; // delete(G); ?
	

	// open file if exist and read context:
	if(ifstream(FILE_NAME)){
		ifstream f_in;
		f_in.open(FILE_NAME);
		yG_load(y , G , f_in);
		f_in.close();
	}
	else{

		G[0].push(0);
		/*
		Find(1 , i1 , i2 , j , j1);
		s[i1][j] = 0;
		s[i2][j] = G[0].front();
		*/
		y = 1;
		fcolumn(y , G);
	}


	ofstream f_ou;

	//ti_t = clock() - middle_s;
	//middle_s = clock();
	//cout << ti_t/1000.0 << "  ";
	// G:
	//for(int ii=0; ii<40; ii++){
	//	if(!G[ii].empty())
	//		cout << ii << " : " << G[ii].front() << endl;
	//}
	//
	bool flg = true;
	while(!G[0].empty() && (y > 1) && flg){
		if(y == lenSolution && !G[y - 1].empty() && flg){
			// solution is available , print solution
			cout << endl << "solution available!" << endl;
			// print:
			for(ic = 0; ic < lenSolution; ic++){
				cout << G[ic].front() << " ";
			} cout << endl;
			//
			flg = false;
			cout << endl << "tedad : " << tedad << endl;
		}
		if(flg){
			if(y > 0 && !G[y - 1].empty())
				G[y - 1].pop();
			while (y > 0 && G[y - 1].empty()){
				--y;
				if (y > 0 && !G[y - 1].empty())
					G[y - 1].pop();
			}
			if(y > 0){
				fcolumn(y , G);
				
				ti_t = clock() - middle_s;

				//if((ti_t/(1000.0*30.0))  >  1.0){
					middle_s = clock();
					// save:
					f_ou.open(FILE_NAME);
					yG_save(y , G , f_ou);
					f_ou.close();
					// save backup:
					f_ou.open("backup");
					yG_save(y , G , f_ou);
					f_ou.close();
				//}
			}
		}
	}

	//delete G;
}
void f1(queue<int> *M1 , queue<int> *M2 , int &u10 , int &u11 , int &u21 , int &j , int &e , int &j1 , int *aj){
	tedad++;
	int jc = 0 , ic;
	bool isMemu10ajc;

	for(jc = 0 ; jc < j ; jc++){

		if(isMember(u11 , a[jc])){
			isMemu10ajc = isMember(u10 , a[jc]); // is s[u10][a[jc]] != 0 ?

			if(!isMemu10ajc || (isMemu10ajc && u21 != jc)){
				for(ic = 0; ic < acol; ic++){
					if(a[jc][ic] != u11 /*&& a[jc][ic] >= 0*/){
						M1[e].push(a[jc][ic]);
						M2[e].push(jc);
					}
				}
			}
		}
	}
	if(isMember(u11 , aj)){
			isMemu10ajc = isMember(u10 , aj);

			if(!isMemu10ajc || (isMemu10ajc && u21 != jc)){
				for(ic = 0; ic < acol; ic++){
					if(aj[ic] != u11 /*&& a[jc][ic] >= 0*/){
						M1[e].push(aj[ic]);
						M2[e].push(jc);
					}
				}
			}
		}

}
////////////////////////////////////////////////////////////
void f2(queue<int> *M1 , queue<int> *M2 , int &p , int &j , int &j1 , int *aj){
	int u10 , u11 , u21;
	int e = M1[0].front();
	while( (!M1[e].empty()) && e <= p ){

		u10 = M1[e - 1].front();
		u11 = M1[e].front();
		u21 = M2[e].front();

		e++;
		clearQ(M1[e]);
		clearQ(M2[e]);
		f1(M1 , M2 ,u10 , u11 , u21 , j , e , j1 , aj);
	}
	M1[0].front() = e;
}


void f3(queue <int> &f ,int &i1 ,int &i2 ,int &j ,int &j1 , int *aj){
	int hhhh,ffff , cnt;
	int n_negative , n_positive;
	bool mask[m] = {0}; // all elements must be zero
	bool one = false;
	int p = 2 , y , ic ,
		sum , subsum ,
		gerth2 = gerth/2;
	
	queue <int> *M1;
	M1 = new queue<int>[gerth2 +1];
	queue <int> *M2;
	M2 = new queue<int>[gerth2 +1];

	while(p < gerth2){
		clearArrayQ(M1 , gerth/2 + 1);
		clearArrayQ(M2 , gerth/2 + 1);
		for (int x = 0; x < j1 ; x++){

			clearQ(M1[0]); clearQ(M1[1]); clearQ(M1[2]);
			clearQ(M2[0]); clearQ(M2[1]); clearQ(M2[2]);

			M1[0].push(2);        M2[0].push(2);
			M1[1].push(a[j][j1]); M2[1].push(j);
			M1[2].push(a[j][x]);  M2[2].push(j);

			f2(M1, M2 , p , j , j1 , aj);
			y = M1[0].front();

			while(!M1[3].empty() && y >= 1){
				while (y == p + 1 && !M1[y].empty()){
					if (M1[1].front() == M1[y].front() && M2[1].front() != M2[y].front()){
						
						//strt = clock();
						// finduction part:
						

						/////
						//hhhh = 0;
						//ffff = 0;
						//for (int i = 1; i < y; ++i){
						//	if( M1[i + 1].front() == i2  &&  M2[i + 1].front() == j ) hhhh++;
						//	if( M1[i].front()     == i2  &&  M2[i + 1].front() == j ) ffff++;
						//}/*if(hhhh + ffff >1)*/cout << hhhh<<ffff << " ";
						
						/////
						s[i1][j] = 0;
						s[i2][j] = 0;
						//if(s[i2][j] != 0) cout << "s[" << i2 << "][" <<j<< "] = " << s[i2][j] << endl;

						n_negative = 0;
						n_positive = 0;

						sum = 0;

						for (int i = 1; i < y; ++i){
							sum += (s[M1[i].front()][M2[i + 1].front()] - s[M1[i + 1].front()][M2[i + 1].front()]);
							if( M1[i].front()     == i2  &&  M2[i + 1].front() == j ) n_positive++;
							if( M1[i + 1].front() == i2  &&  M2[i + 1].front() == j ) n_negative++;
						}
						if(n_positive - n_negative < 0) cout << "k:" << n_positive - n_negative << "  "; 
						for(ic = 0; ic < m ; ic++){
							if(!mask[ic]){
								subsum = sum+(n_positive - n_negative)*ic;
							
								if (subsum % m == 0) {
									mask[ic] = 1;
									if(n_positive - n_negative > 0) ic+=m/(n_positive - n_negative)-1;
								}
							
								//else{
								//	if(((m - (subsum % m))/(n_positive - n_negative) - 10)>0 && (n_positive - n_negative)>0)
								//		ic += (m - (subsum % m))/(n_positive - n_negative) -  10;
								//}

							//nhast++;
							}
							//else hast++;
						}//tedad++;
						// end finduction
						//stop=clock();
						//cout << "in: " << strt-stop << " ";
					}
					M1[y].pop();
					M2[y].pop();
				}
				M1[y - 1].pop();
				M2[y - 1].pop();
				M1[0].front() = y - 1;
				f2(M1, M2 , p , j , j1 , aj);
				y = M1[0].front();
			}
		}
		p++;
	}

	// create f:
	clearQ(f);
	int num = 1;
	for(ic = 0; ic < m && num <= BANDWIDTH ; ic++){
		if(mask[ic] == 0){
			f.push(ic);
			num++;
			//if(num == 5) cout << ic << endl;
		}
	}

	//delete M1;
	//delete M2;
	
	//cout/* << "t:" */<< tedad << "  ";
	cnt = 0;
	for(ic = 0; ic < m ; ic++) if(mask[ic] == 0) cnt++;
	cout << " <" << cnt << "> ";
}

void fcolumn(int &y , queue <int> *G){
	int i1 , i2 , j , j1;

	for(int ic = 0; ic < y ; ic++){
		Find(ic + 1 , i1 , i2 , j , j1);
		s[i1][j] = 0;
		s[i2][j] = G[ic].front();
		// for ic=y..lenSoloution find(ic+1 , ...) ->
		// s[i1][j] = 0;
		// s[i2][j] = 0
	}


	queue<int> f;
	f.push(0);
	while(!f.empty() && y<lenSolution){

		Find(y + 1 , i1 , i2 , j , j1);

		// aj:
		int aj[acol];
		for(int ic = 0; ic < acol; ic++)
			if(ic <= j1) aj[ic] = a[j][ic];
			else aj[ic] = -20000;
		//
		//os = clock();
		f3(f , i1 , i2 , j , j1 , aj);
		//oe = clock();
		//cout << "ou: " << oe-os<<" ";
		if(!f.empty()){
			++y;
			G[y - 1] = f;
			s[i1][j] = 0;
			s[i2][j] = G[y - 1].front();
		}
	}
}



//void finduction(queue <int> &f ,int &i1 ,int &i2 ,int &j ,int &j1){
//	// Random Shuffle:
//	vector<int> vec;
//	for (int ic=1; ic<10; ++ic) vec.push_back(ic);
//	random_shuffle ( vec.begin(), vec.end());
//	// end Random Shuffle
//
//	/*
//	for (std::vector<int>::iterator it=vec.begin(); it!=vec.end(); ++it){
//		s[i1][j] = 0;
//		s[i2][j] = *it;
//	}
//	*/
//}


void Find(int n , int &i1 , int &i2 , int &j , int &j1){
	int count = 0;
	for(j=0 ; j<alen ; j++)
		for(j1=1; j1<acol; j1++)
			if(a[j][j1] >= 0){
				count++;
				if(count == n){
					i1 = a[j][0];
					i2 = a[j][j1];
					return;
				}
			}
}

int Fmax(){
	int Max = 0; 
	for(int ic = 0; ic<alen; ic++)
		for(int jc = 0; jc<acol; jc++)
			Max = Max < a[ic][jc] ? a[ic][jc] : Max;
	return Max;
}



// clear
// std ?
/*
void clear( std::queue<int> &q )
{
   std::queue<int> empty;
   std::swap( q, empty );
}
*/

void clearQ(std::queue<int> &q){
	std::queue<int> empty;
	std::swap(q , empty);
}

void clearArrayQ(std::queue<int> *q , int n){
	for(int i=0; i<n; i++)
		clearQ(q[i]);
}

bool isMember(int &p , int *q){
	for(int i=0; i<acol; i++)
		if(p == q[i]) return true;
	return false;
}

bool isj1Member(int &p, int*q , int &j1){
	for(int i=0; i<j1; i++)
		if(p == q[i]) return true;
	return false;
}


void yG_save(int y ,queue<int> *G , ofstream &myfile){

	queue<int>* F;
	F = new queue<int>[lenSolution];
	copyTo(G , F);

	char Name[40];

	myfile << y << '\n';

	for(int i=0 ; i<y ; i++){
		while(!F[i].empty()){
			myfile << F[i].front() << ' ';
			F[i].pop();
		}
		myfile << '\n';
	}

	myfile << '\n' << "saved.";
}

void yG_load(int &y ,queue<int> *G , ifstream &f){
	string line;
	stack<int> num;
	int i , j , k , N;
	int al = 0;
	y = 0;
	getline(f , line);
	for(i=0; i<line.length(); i++){
		if     (line[i] == '0') num.push(0);
		else if(line[i] == '1') num.push(1);
		else if(line[i] == '2') num.push(2);
		else if(line[i] == '3') num.push(3);
		else if(line[i] == '4') num.push(4);
		else if(line[i] == '5') num.push(5);
		else if(line[i] == '6') num.push(6);
		else if(line[i] == '7') num.push(7);
		else if(line[i] == '8') num.push(8);
		else if(line[i] == '9') num.push(9);
	}
	// Calculate y
	i = 0;
	while(!num.empty()){
		y = y + num.top()*Pow(10 , i);
		num.pop();
		i++;
	}
	//
	j = 0;
	while(getline(f , line)){
		for(i=0; i<line.length(); i++){
			if(j == 30){
				al++;
			}
			if     (line[i] == '0') num.push(0);
			else if(line[i] == '1') num.push(1);
			else if(line[i] == '2') num.push(2);
			else if(line[i] == '3') num.push(3);
			else if(line[i] == '4') num.push(4);
			else if(line[i] == '5') num.push(5);
			else if(line[i] == '6') num.push(6);
			else if(line[i] == '7') num.push(7);
			else if(line[i] == '8') num.push(8);
			else if(line[i] == '9') num.push(9);
			if(line[i] == ' '){
				// Calculate N
				k = 0; N = 0;
				while(!num.empty()){
					N = N + num.top()*Pow(10 , k);
					num.pop();
					k++;
				}
				//
				if(j < y)
					G[j].push(N);
			}
		}

		j++;
	}

	
}


void copyTo(queue<int> *from , queue<int> *to){

	int middle[lenSolution][BANDWIDTH]={{0}};
	int i , j;

	for(i=0 ; i<lenSolution ; i++){
		for(j=0; j<BANDWIDTH; j++){
			if(!from[i].empty()){
				middle[i][j] = from[i].front();
				to[i].push(from[i].front());
				from[i].pop();
			}
			else middle[i][j] = -234512;
		}
	}

	for(i=0 ; i<lenSolution ; i++){
		for(j=0; j<BANDWIDTH; j++){
			if(middle[i][j] != -234512)
				from[i].push(middle[i][j]);
		}
	}



}

int Pow(int a , int b){
	// a^b
	int c = 1;
	for(int i=0; i < b; i++){
		c = c * a;
	}
	return c;
}