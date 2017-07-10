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

int xoaVatTu(DSVatTu &ds_VT, string maVT){
	int index = timViTriVatTuTrung(ds_VT, maVT);
	if(index < 0 || index >= ds_VT.soLuongVatTu || kiemTraRongVatTu(ds_VT))
		return 0;
	for(int i = index; i < ds_VT.soLuongVatTu - 1; i++)
		ds_VT.nodesVT[i] = 	ds_VT.nodesVT[i + 1];
	ds_VT.soLuongVatTu--;
	return 1;
}

int main(){
	DSVatTu dsvt;
	dsvt.soLuongVatTu = 0;
	VatTu vt1;
	vt1.maVatTu = "a";
	vt1.tenVatTu = "Mot";
	vt1.soLuongTon = 5;
	vt1.donViTinh = "Cai";
	themVatTuVaoViTri(dsvt, vt1);
	
	VatTu vt2;
	vt2.maVatTu = "has";
	vt2.tenVatTu = "Hai";
	vt2.soLuongTon = 5;
	vt2.donViTinh = "Cai";
	themVatTuVaoViTri(dsvt, vt2);
	
	VatTu vt3;
	vt3.maVatTu = "das";
	vt3.tenVatTu = "Ba";
	vt3.soLuongTon = 5;
	vt3.donViTinh = "Cai";
	themVatTuVaoViTri(dsvt, vt3);
	
	xoaVatTu(dsvt, "A");
	for(int i = 0; i < dsvt.soLuongVatTu; i++){
		cout << dsvt.nodesVT[i].maVatTu << " ten : " << dsvt.nodesVT[i].tenVatTu << endl;
	}
	
	return 0;
}
