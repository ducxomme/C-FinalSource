#include "DuLieu.cpp"


int kiemTraRongVatTu(DSVatTu &ds_VT){
	return (ds_VT.soLuongVatTu == 0 ? 1 : 0);
}

int kiemTraDayVatTu(DSVatTu &ds_VT){
	return (ds_VT.soLuongVatTu == MAX ? 1 : 0);
}

int timViTriVatTuTrung(DSVatTu &ds_VT, string maVT){
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		if(ds_VT.nodesVT[i].maVatTu == maVT)
			return i;
	}
	return -1;
}

int timViTriThemVatTu(DSVatTu ds_VT, string maVT){
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		if(ds_VT.nodesVT[i].maVatTu == maVT)	return -1;
		if(ds_VT.nodesVT[i].maVatTu > maVT)		return i;
	}
	return ds_VT.soLuongVatTu;
}

int themVatTuVaoViTri(DSVatTu &ds_VT, VatTu vatTu){
	int index = timViTriThemVatTu(ds_VT, vatTu.maVatTu);
	if(index < 0 || index > ds_VT.soLuongVatTu || kiemTraDayVatTu(ds_VT) == 1)   
		return 0;      
	
	for(int j = ds_VT.soLuongVatTu; j > index; j--){
		ds_VT.nodesVT[j] = ds_VT.nodesVT[j-1];
	}
	ds_VT.nodesVT[index] = vatTu;
	ds_VT.soLuongVatTu++;
	return 1;
}
// Trc khi xoa vat tu: kiem tra xem co hoa don nao ton tai ma VT ko?
int xoaVatTu(DSVatTu &ds_VT, string maVT){
	int index = timViTriVatTuTrung(ds_VT, maVT);
	if(index < 0 || index >= ds_VT.soLuongVatTu || kiemTraRongVatTu(ds_VT))
		return 0;
	for(int i = index; i < ds_VT.soLuongVatTu - 1; i++)
		ds_VT.nodesVT[i] = 	ds_VT.nodesVT[i + 1];
	ds_VT.soLuongVatTu--;
	return 1;
}

void sapXepTenVatTuTangDan(DSVatTu &ds_VT){
	for(int i = 0; i < ds_VT.soLuongVatTu - 1; i++){
		for (int j = i + 1; j < ds_VT.soLuongVatTu; j++){
			if(ds_VT.nodesVT[i].tenVatTu > ds_VT.nodesVT[j].tenVatTu){
				VatTu t = ds_VT.nodesVT[i];
				ds_VT.nodesVT[i] = ds_VT.nodesVT[j];
				ds_VT.nodesVT[j] = t;
			}
		}
	}
}

int saveFileVatTu(DSVatTu &ds_VT, char tenFile[]){
	ofstream myFile;
	myFile.open(tenFile, ios::out);
	if(!myFile){
		return 0;
	}
	for(int i = 0; i < ds_VT.soLuongVatTu; i++){
		VatTu vt = ds_VT.nodesVT[i];
		myFile << vt.maVatTu << endl;
		myFile << vt.tenVatTu << endl;
		myFile << vt.donViTinh << endl;
		myFile << vt.soLuongTon;
		if(i == ds_VT.soLuongVatTu - 1)
			continue;
		myFile << endl;
	}
	myFile.close();
	return 1;
}

int loadFileVatTu(DSVatTu &ds_VT, char tenFile[]){
	ifstream myFile;
	myFile.open(tenFile, ios::in);
	if(!myFile){
		return 0;
	}
	string slt =""; 
	VatTu vt;
	while(!myFile.eof()){
		getline(myFile, vt.maVatTu);
		getline(myFile, vt.tenVatTu);
		getline(myFile, vt.donViTinh);
		getline(myFile, slt);
		stringstream(slt) >> vt.soLuongTon;
		
		themVatTuVaoViTri(ds_VT, vt);
	}
	myFile.close();
	return 1;
}

int demSoLuongVatTu(DSVatTu &ds_VT){
}
//int main(){
//	char tenFile[] = "dsVatTu.txt";
//	DSVatTu dsvt;
//	dsvt.soLuongVatTu = 0;
//	VatTu vt1;
//	vt1.maVatTu = "D01";
//	vt1.tenVatTu = "Den Loai 1";
//	vt1.donViTinh = "Cai";
//	vt1.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt1);
//	VatTu vt2;
//	vt2.maVatTu = "D02";
//	vt2.tenVatTu = "Den Loai 2";
//	vt2.donViTinh = "Cai";
//	vt2.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt2);
//	VatTu vt3;
//	vt3.maVatTu = "D03";
//	vt3.tenVatTu = "Den Loai 3";
//	vt3.donViTinh = "Cai";
//	vt3.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt3);
//	VatTu vt4;
//	vt4.maVatTu = "D04";
//	vt4.tenVatTu = "Den Loai 4";
//	vt4.donViTinh = "Cai";
//	vt4.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt4);
//	VatTu vt5;
//	vt5.maVatTu = "G01";
//	vt5.tenVatTu = "Gach Loai 1";
//	vt5.donViTinh = "Vien";
//	vt5.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt5);
//	VatTu vt6;
//	vt6.maVatTu = "G02";
//	vt6.tenVatTu = "Gach Loai 2";
//	vt6.donViTinh = "Vien";
//	vt6.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt6);
//	VatTu vt7;
//	vt7.maVatTu = "G03";
//	vt7.tenVatTu = "Gach Loai 3";
//	vt7.donViTinh = "Vien";
//	vt7.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt7);
//	VatTu vt8;
//	vt8.maVatTu = "G04";
//	vt8.tenVatTu = "Gach Loai 4";
//	vt8.donViTinh = "Vien";
//	vt8.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt8);
//	VatTu vt9;
//	vt9.maVatTu = "X01";
//	vt9.tenVatTu = "Xi Mang Loai 1";
//	vt9.donViTinh = "Bao";
//	vt9.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt9);
//	VatTu vt11;
//	vt11.maVatTu = "X02";
//	vt11.tenVatTu = "Xi Mang Loai 2";
//	vt11.donViTinh = "Bao";
//	vt11.soLuongTon = 300;
//	themVatTuVaoViTri(dsvt, vt11);
//	VatTu vt12;
//	vt12.maVatTu = "X03";
//	vt12.tenVatTu = "Xi Mang Loai 3";
//	vt12.donViTinh = "Bao";
//	vt12.soLuongTon = 300;
//themVatTuVaoViTri(dsvt, vt12);
//	VatTu vt13;
//	vt13.maVatTu = "X04";
//	vt13.tenVatTu = "Xi Mang Loai 4";
//	vt13.donViTinh = "Bao";
//	vt13.soLuongTon = 300;			
//themVatTuVaoViTri(dsvt, vt13);
//	VatTu vt14;
//	vt14.maVatTu = "S01";
//	vt14.tenVatTu = "Son Loai 1";
//	vt14.donViTinh = "Thung";
//	vt14.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt14);
//	VatTu vt15;
//	vt15.maVatTu = "S02";
//	vt15.tenVatTu = "Son Loai 2";
//	vt15.donViTinh = "Thung";
//	vt15.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt15);
//	VatTu vt16;
//	vt16.maVatTu = "S03";
//	vt16.tenVatTu = "Son Loai 3";
//	vt16.donViTinh = "Thung";
//	vt16.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt16);
//	VatTu vt17;
//	vt17.maVatTu = "S04";
//	vt17.tenVatTu = "Son Loai 4";
//	vt17.donViTinh = "Thung";
//	vt17.soLuongTon = 50;
//	themVatTuVaoViTri(dsvt, vt17);
//	saveFileVatTu(dsvt, tenFile);
//	xoaVatTu(dsvt, "A");
//	sapXepTenVatTuTangDan(dsvt);
//	loadFileVatTu(dsvt, tenFile);
//	cout << dsvt.soLuongVatTu << endl;
//	cout << "Ma" << "\tTen" << "\t\tDon Vi Tinh" << "\tSo Luong Ton" << endl;
//	for(int i = 0; i < dsvt.soLuongVatTu; i++){
//		cout << dsvt.nodesVT[i].maVatTu  << "\t" << dsvt.nodesVT[i].tenVatTu << "\t\t" << dsvt.nodesVT[i].donViTinh << "\t" << dsvt.nodesVT[i].soLuongTon << endl;
//	}
	
//	return 0;
//}
