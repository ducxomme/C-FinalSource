#include "ChiTietHoaDon.cpp"

string tenCotBangHoaDon[] = {"STT", "SO HOA DON", "NGAY LAP", "LOAI"};
string tenThuocTinhHoaDon[] = {"So Hoa Don", "Ngay Lap", "Loai"};

int emptyDSHoaDon(PTRHoaDon hoaDonFirst){
	return (hoaDonFirst == NULL ? 1 : 0);
}

void InitHoaDon(PTRHoaDon &hoaDonFirst){
	hoaDonFirst = NULL;
}

PTRHoaDon getNodeHoaDon(HoaDon hd){
	PTRHoaDon p = new NodeHoaDon;
	p->hoaDon = hd;
	p->HD_Next = NULL;
	
	return p;
}


int insertNodeHoaDon(PTRHoaDon &hoaDonFirst, HoaDon hd){
	PTRHoaDon r = getNodeHoaDon(hd);
	if(r == NULL)	return 0;
	if(hoaDonFirst == NULL){
		hoaDonFirst = r;
		return 1;
	}
	else{
		PTRHoaDon p = hoaDonFirst;
		PTRHoaDon q;
		// Tim q la nut truoc node them
		for(p; p != NULL && p->hoaDon.soHoaDon < hd.soHoaDon; q = p, p=p->HD_Next);
		if(p == NULL){
			q->HD_Next = r;
			return 1;
		}
		
		else if(p->hoaDon.soHoaDon == hd.soHoaDon)	return 0;
		else{
			r->HD_Next = p;
			q->HD_Next = r;
			return 1;
		}	
	}
}

PTRHoaDon search_HD(PTRHoaDon &hoaDonFirst, string maHD){
	if(emptyDSHoaDon(hoaDonFirst) == 1)
		return NULL;
	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
		if(p->hoaDon.soHoaDon == maHD){
			return p;
		}		
	}
	return NULL;
}

int deleteFirstHD(PTRHoaDon &hoaDonFirst){
	if(emptyDSHoaDon(hoaDonFirst) == 1)
		return 0;
	PTRHoaDon p = hoaDonFirst;
	hoaDonFirst = p->HD_Next;
	delete p;
	return 1;
}

int deleteAfterHD(PTRHoaDon p){
	if(p == NULL || p->HD_Next == NULL)
		return 0;
	PTRHoaDon f = p->HD_Next;
	p->HD_Next = f->HD_Next;
	delete f;
}

int deleteInfoHD(PTRHoaDon &hoaDonFirst, string maHD){
	PTRHoaDon p,q;
	p = search_HD(hoaDonFirst, maHD);
	if(p == NULL)
		return 0;
	if(p == hoaDonFirst)
		deleteFirstHD(hoaDonFirst);
	else{
		q = hoaDonFirst;
		while(q->HD_Next != p)
			q=q->HD_Next;
		deleteAfterHD(q);
	}
	return 1;
}

void veGiaoDienThemHoaDon(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	system("cls");
	Normal();
	veHinhChuNhat(45, 4, 26, 3, RED);
	SetBGColor(RED);
	gotoxy(52, 5);
	cout << "LAP HOA DON";
	Normal();
	
	for(int i = 0; i < 3; i++){
		gotoxy(25, 9 + 3 * i);
		SetColor(YELLOW);
		cout << tenThuocTinhHoaDon[i];
		Normal();
		if(i == 0){
			veInputText(40, 8 + 3 * i);
		}else if(i == 1){
			veBangDanhSach(40, 11, 1, 1, 2);
			gotoxy(45, 12);	cout << "/";
			veBangDanhSach(47, 11, 1, 1, 2);
			gotoxy(52, 12);	cout << "/";
			veBangDanhSach(54, 11, 1, 1, 4);
		}else
			veBangDanhSach(40, 14, 1, 1, 3);
	}
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(46, 25);
	cout << "ESC: Tro ve \t F2: Luu";
}

//void themMotHoaDon()

void veKhungDanhSachHoaDon(){
	Normal();
	system("cls");
	// In tieu de
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DANH SACH HOA DON";
	veBangDanhSach(13, 4, 1, 11, 4);
	veKhungDanhSach(4, 11, 18, 4);
	veLaiGoc(13, 4, 11);
	
	//veChuThich();
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(13, 28);
	cout << "ESC: Thoat \t INSERT: Hieu chinh \t DELETE: Xoa \t <-Trang truoc \t Trang sau->";
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 5; i++){
		if(i == 0){
			toaDoXNhan = 15;
		}
		else toaDoXNhan =  19 + (TABLE_COLUMN_WIDTH - tenCotBangHoaDon[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangHoaDon[i];
	}
	Normal();	
}

//int main(){
//	PTRHoaDon hoaDonFirst;
//	InitHoaDon(hoaDonFirst);
//	
//	date d;
//	HamTraVeCurrentTime(d);
//		
//	HoaDon hd1;
//	hd1.soHoaDon = "HD1";
//	hd1.loai = 'N';
//	hd1.ngayLapHoaDon = d;
//	hd1.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd1);
//	
//	HoaDon hd5;
//	hd5.soHoaDon = "HD5";
//	hd5.loai = 'X';
//	hd5.ngayLapHoaDon = d;
//	hd5.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd5);
//	
//	HoaDon hd3;
//	hd3.soHoaDon = "HD3";
//	hd3.loai = 'N';
//	hd3.ngayLapHoaDon = d;
//	hd3.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd3);
//	
//	HoaDon hd6;
//	hd6.soHoaDon = "HD6";
//	hd6.loai = 'N';
//	hd6.ngayLapHoaDon = d;
//	hd6.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd6);
//	
//	HoaDon hd4;
//	hd4.soHoaDon = "HD4";
//	hd4.loai = 'X';
//	hd4.ngayLapHoaDon = d;
//	hd4.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd4);
//	
//	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
//		cout << p->hoaDon.soHoaDon << endl;
//	}
//	cout << "Sau khi xcoa "  << endl;
//	deleteInfoHD(hoaDonFirst, "HD8");
//	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
//		cout << p->hoaDon.soHoaDon << endl;
//	}

//	veGiaoDienThemHoaDon();
//	return 0;
//}
