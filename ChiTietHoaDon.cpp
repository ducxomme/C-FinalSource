#include "DuLieu.cpp"

int kiemTraRongCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	return (ctHoaDonFirst == NULL ? 1 : 0);
}

void InitCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	ctHoaDonFirst = NULL;
}

PTR_CT_HoaDon getNodeCTHoaDon(ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = new ds_ChiTiet_HD;
	p->chiTietHD = ctHD;
	p->CT_HD_Next = NULL;
}

void insertCTHoaDonLast(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = getNodeCTHoaDon(ctHD);
	PTR_CT_HoaDon q;
	if(ctHoaDonFirst == NULL){
		ctHoaDonFirst = p;
		return;
	}
	
	for(q = ctHoaDonFirst; q->CT_HD_Next != NULL; q=q->CT_HD_Next);
	q->CT_HD_Next = p;
}

void insertCTHoaDonFirst(PTR_CT_HoaDon &ctHoaDonFirst, ChiTiet_HD ctHD){
	PTR_CT_HoaDon p = getNodeCTHoaDon(ctHD);
	if(ctHoaDonFirst == NULL){
		ctHoaDonFirst = p;
	}
	else{
		p->CT_HD_Next = ctHoaDonFirst;
		ctHoaDonFirst = p;
	}
}

int deleteFirstCTHoaDon(PTR_CT_HoaDon &ctHoaDonFirst){
	if(kiemTraRongCTHoaDon(ctHoaDonFirst))	return 0;
	PTR_CT_HoaDon p = ctHoaDonFirst;
	ctHoaDonFirst = p->CT_HD_Next;
	delete p;
	return 1;
}

int deleteAfterCTHoaDon(PTR_CT_HoaDon p){
	if(p == NULL || p->CT_HD_Next == NULL)
		return 0;
	PTR_CT_HoaDon q = p->CT_HD_Next;
	p->CT_HD_Next = q->CT_HD_Next;
	delete q;
	return 1;
}

PTR_CT_HoaDon timViTriCoMaVT(PTR_CT_HoaDon ctHoaDonFirst, string maVT){
	if(ctHoaDonFirst == NULL)
		return NULL;
	for(PTR_CT_HoaDon p = ctHoaDonFirst; p != NULL; p=p->CT_HD_Next){
		if(p->chiTietHD.maVT == maVT)
			return p;
	}
	return NULL;
}

int deleteCTHoaDonTheoMaVT(PTR_CT_HoaDon &ctHoaDonFirst, string maVT){
	PTR_CT_HoaDon p = timViTriCoMaVT(ctHoaDonFirst, maVT);
	if(p == NULL)	return 0;
	PTR_CT_HoaDon q = ctHoaDonFirst;
	if(q == p)
	{
		deleteFirstCTHoaDon(ctHoaDonFirst);
		return 1;	
	}
	for(q; q->CT_HD_Next != NULL && q->CT_HD_Next != p; q=q->CT_HD_Next);
	deleteAfterCTHoaDon(q);
	return 1;
}

int demSoChiTietHD(PTR_CT_HoaDon ctHoaDonFirst){
	int dem = 0;
	for(PTR_CT_HoaDon p = ctHoaDonFirst; p != NULL; p=p->CT_HD_Next)
		dem++;
	return dem;
}

void duyetDanhSach(PTR_CT_HoaDon first){
	
	if(first == NULL){
		cout << "Danh sach hoa don rong" << endl;
		return;
	}
	PTR_CT_HoaDon p = first;
	while(p != NULL){
		cout << p->chiTietHD.maVT << "\t" << p->chiTietHD.soLuong << "\t" << p->chiTietHD.donGia << "\t" << p->chiTietHD.vat << endl;
		p = p->CT_HD_Next;
	}
	
}


int main(){
	PTR_CT_HoaDon ctHoaDonFirst;
	InitCTHoaDon(ctHoaDonFirst);
	
	ChiTiet_HD cthd1;
	cthd1.maVT = "VT1";
	cthd1.soLuong = 100;
	cthd1.donGia = 200000;
	cthd1.vat = 0.1;
	insertCTHoaDonLast(ctHoaDonFirst, cthd1);

	ChiTiet_HD cthd2;
	cthd2.maVT = "VT2";
	cthd2.soLuong = 400;
	cthd2.donGia = 100000;
	cthd2.vat = 0.1;
	insertCTHoaDonLast(ctHoaDonFirst, cthd2);
	
	ChiTiet_HD cthd3;
	cthd3.maVT = "VT3";
	cthd3.soLuong = 300;
	cthd3.donGia = 300000;
	cthd3.vat = 0.1;
	insertCTHoaDonLast(ctHoaDonFirst, cthd3);
	
	ChiTiet_HD cthd4;
	cthd4.maVT = "VT4";
	cthd4.soLuong = 200;
	cthd4.donGia = 400000;
	cthd4.vat = 0.1;
	insertCTHoaDonLast(ctHoaDonFirst, cthd4);
	
	ChiTiet_HD cthd5;
	cthd5.maVT = "VT5";
	cthd5.soLuong = 100;
	cthd5.donGia = 500000;
	cthd5.vat = 0.1;
	insertCTHoaDonLast(ctHoaDonFirst, cthd5);
	
	//deleteCTHoaDonTheoMaVT(ctHoaDonFirst, "VT8");
	duyetDanhSach(ctHoaDonFirst);
	return 0;
}
