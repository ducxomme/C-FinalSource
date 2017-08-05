
#include "ChiTietHoaDon.cpp"

string tenCotBangHoaDon[] = {"STT", "SO HOA DON", "NGAY LAP", "LOAI"};
string tenCotBangTop10[] = {"STT", "MA VAT TU", "TEN VAT TU", "SO LUONG XUAT"};
string tenThuocTinhHoaDon[] = {"So Hoa Don", "Ngay Lap", "Loai(N/X)"};
string tenCotHoaDon[] = {"SO HD", "NGAY LAP", "LOAI HD", "HO TEN NV", "TRI GIA HD"};
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

bool insertFirstHD(PTRHoaDon &hoaDonFirst, HoaDon hd){
	PTRHoaDon r = getNodeHoaDon(hd);
	if(r == NULL) return false;
	r->HD_Next = hoaDonFirst;
	hoaDonFirst = r;
	return true;
}

bool insertNodeHoaDon(PTRHoaDon &hoaDonFirst, HoaDon hd){
	PTRHoaDon r = getNodeHoaDon(hd);
	PTRHoaDon p = hoaDonFirst;
	if(r == NULL)	return false;
	if(p == NULL)
		insertFirstHD(hoaDonFirst, hd);
	else{
		PTRHoaDon q = NULL;
		// Tim q la nut truoc node them
		for(p; p != NULL && p->hoaDon.soHoaDon < hd.soHoaDon; q = p, p=p->HD_Next);
		if(p == NULL){
			q->HD_Next = r;
			return true;
		}
		
		else if(p->hoaDon.soHoaDon == hd.soHoaDon)	return false;
		else{
			if(q == NULL){
				insertFirstHD(hoaDonFirst, hd);				
			}
			else {
				r->HD_Next = p;
				q->HD_Next = r;
				return true;	
			}
		}	
	}
}

PTRHoaDon timkiemHoaDonTheoMa(PTRHoaDon &hoaDonFirst, string maHD){
	if(emptyDSHoaDon(hoaDonFirst) == 1)
		return NULL;
	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
		if(p->hoaDon.soHoaDon == maHD){
			return p;
		}		
	}
	return NULL;
}

PTRHoaDon timKiemHoaDonTheoViTri(PTRHoaDon &hoaDonFirst, int viTri){
	int i = -1;
	PTRHoaDon p = hoaDonFirst;
	while(p != NULL){
		i++;
		if(i == viTri) return p;
		p=p->HD_Next;
	}
}

int kiemTraMaHoaDonTrung(TreeNhanVien &rootNV, string maHD){
	TreeNhanVien p = rootNV;
	if(p == NULL) return 0;
	StackNV sp = NULL;
	
	do{
		while(p != NULL){
			push(sp, p);
			p=p->nvLeft;
		}
		if(sp != NULL){
			pop(sp, p);
			PTRHoaDon ptrHD = p->nhanVien.hoaDonFirst;
			while(ptrHD != NULL){
				if(ptrHD->hoaDon.soHoaDon == maHD)
					return 1;
				ptrHD = ptrHD->HD_Next;
			}
			p=p->nvRight;
		}else return 0;		
	}while (1);
	
}



PTRHoaDon traVeHoaDonTuongUngMa(TreeNhanVien &rootNV, string maHD, string &maNV){
	TreeNhanVien p = rootNV;
	if(p == NULL)	return NULL;
	StackNV sp = NULL;
	
	do{
		while(p != NULL){
			push(sp, p);
			p = p->nvLeft;
		}
		if(sp != NULL){
			pop(sp, p);
			PTRHoaDon ptrHD = p->nhanVien.hoaDonFirst;
			while(ptrHD != NULL){
				if(ptrHD->hoaDon.soHoaDon == maHD){
					maNV = p->nhanVien.maNhanVien;
					return ptrHD;
				}
				ptrHD = ptrHD->HD_Next;
			}
			p = p->nvRight;
		}else return NULL;
	}while(1);
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
	p = timkiemHoaDonTheoMa(hoaDonFirst, maHD);
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

int soLuongHoaDonCuaMotNV(PTRHoaDon ptrHD){
	PTRHoaDon p = ptrHD;
	int dem = 0;
	while(p != NULL){
		dem++;
		p=p->HD_Next;;
	}
	return dem;
}

int soTrangDanhSachHoaDon(PTRHoaDon ptrHD){
	return soLuongHoaDonCuaMotNV(ptrHD) / 10 + (soLuongHoaDonCuaMotNV(ptrHD) % 10 == 0 ? 0 : 1);
}

void veGiaoDienLapHoaDon(NhanVien &nv){
	SetColor(WHITE);
	SetBGColor(BLACK);
	system("cls");
	Normal();
	veHinhChuNhat(45, 4, 26, 3, RED);
	SetBGColor(RED);
	gotoxy(52, 5);
	cout << "LAP HOA DON";
	Normal();
	gotoxy(2, 1);
	cout << "Ma NV : " << nv.maNhanVien;
	for(int i = 0; i < 3; i++){
		gotoxy(25, 9 + 3 * i);
		SetColor(YELLOW);
		cout << tenThuocTinhHoaDon[i];
		Normal();
		if(i == 0){
			veInputText(40, 8);
		}else if(i == 1){
			veBangDanhSach(40, 11, 1, 1, 2);
			gotoxy(45, 12);	cout << "/";
			veBangDanhSach(47, 11, 1, 1, 2);
			gotoxy(52, 12);	cout << "/";
			veBangDanhSach(54, 11, 1, 1, 4);
		}else
			veBangDanhSach(40, 14, 1, 1, 2);
	}
	gotoxy(0, 24);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(32, 25);
	cout << "ESC: Tro ve \t  F2: Luu \t F5: Nhap DS Vat Tu";
}

int lapMotHoaDon(TreeNhanVien &rootNV, NhanVien &nv, DSVatTu &dsVT){
LAPHOADON:
	veGiaoDienLapHoaDon(nv);
	
	HoaDon hoaDon;
	string ngay = "", thang = "", nam = "";
	Date d = HamTraVeCurrentTime();
	
	hoaDon.ngayLapHoaDon.ngay = d.ngay;
	hoaDon.ngayLapHoaDon.thang = d.thang;
	hoaDon.ngayLapHoaDon.nam = d.nam;
	
	ngay = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.ngay);
	thang = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.thang);
	nam = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.nam);
	
	gotoxy(41, 12);	cout << ngay;
	gotoxy(48, 12); cout << thang;
	gotoxy(55, 12); cout << nam;
	int c;
	string errors[3] = {"", "", ""};
	int sttDate = 0;
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInput = 41;
	int toaDoYInput = 9;
	string nhapXuat = "";
	
	int viTriNhapLieu = 0;	
	do{
		switch(viTriNhapLieu){
			case 0:
				c = nhapChuoiKiTuVaSo(hoaDon.soHoaDon, toaDoXInput, toaDoYInput , WIDTH_INPUT_TEXT, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(hoaDon.soHoaDon.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu]; 
				
				}else if(kiemTraMaHoaDonTrung(rootNV, chuyenChuoiThanhChuoiHoa(hoaDon.soHoaDon))){
					errors[viTriNhapLieu] = "So Hoa Don da trung";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(kiemTraChuoiCoKhoangTrang(hoaDon.soHoaDon)){
					errors[viTriNhapLieu] = "Khong duoc co khoang trang";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
					
				}else errors[viTriNhapLieu] = "";
				
				break;
			case 1:
				do{
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					if(sttDate == 0){
						c = nhapChuoiKiTuSo(ngay, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,2 , BLACK, WHITE);
						stringstream(ngay) >> hoaDon.ngayLapHoaDon.ngay;
					}else if(sttDate == 1){
						c = nhapChuoiKiTuSo(thang, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,2 , BLACK, WHITE);
						stringstream(thang) >> hoaDon.ngayLapHoaDon.thang;
					}else{
						c = nhapChuoiKiTuSo(nam, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,4 , BLACK, WHITE);
						stringstream(nam) >> hoaDon.ngayLapHoaDon.nam;
					}
					if(c == KEY_RIGHT){
						if(sttDate < 2) sttDate++;
					}
						if(c == KEY_LEFT){
						if(sttDate > 0) sttDate--;
					}
									
				
				}while(c != KEY_UP && c != KEY_DOWN && c != KEY_ENTER && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB && c!= KEY_F2);
				
				if(ngay.length() <= 0 || thang.length() <= 0 || nam.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(!kiemTraChuoiNhapVao(ngay) || !kiemTraChuoiNhapVao(thang) || !kiemTraChuoiNhapVao(nam)){
					errors[viTriNhapLieu] = "DATE khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else if(!kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam)){
					errors[viTriNhapLieu] = "Thoi gian khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else  errors[viTriNhapLieu] = "";
					
				break;
			
			case 2:
				c = nhapKyTuNhapXuat(nhapXuat, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, 1, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(nhapXuat.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				
				}else if(!kiemTraChuoiNhapVao(nhapXuat)){
					errors[viTriNhapLieu] = "Khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				}else
					errors[viTriNhapLieu] = "";
				
				break;			
			}
		if((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < 2)  viTriNhapLieu++;

		
		if(c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F2){
			stringstream(ngay) >> hoaDon.ngayLapHoaDon.ngay;
			stringstream(thang) >> hoaDon.ngayLapHoaDon.thang;
			stringstream(nam) >> hoaDon.ngayLapHoaDon.nam;
			if(hoaDon.soHoaDon.length() > 0 && kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam) && nhapXuat.length() >0){
				hoaDon.soHoaDon = chuyenChuoiThanhChuoiHoa(hoaDon.soHoaDon);
				hoaDon.loai = (chuyenChuoiThanhChuoiHoa(nhapXuat))[0];
				hoaDon.CT_HD_First = NULL;
				
				if(!kiemTraMaHoaDonTrung(rootNV, hoaDon.soHoaDon)) {
					bool res = insertNodeHoaDon(nv.hoaDonFirst, hoaDon);
					
					if(res == true){
						thongBao("Them thanh cong!!", 45, 12, 27, 3);
					}else{
						thongBao("That bai!!", 45, 12, 27, 3);
					}
					goto LAPHOADON;
				}
			}
		}
		
		if(c == KEY_F5){
			stringstream(ngay) >> hoaDon.ngayLapHoaDon.ngay;
			stringstream(thang) >> hoaDon.ngayLapHoaDon.thang;
			stringstream(nam) >> hoaDon.ngayLapHoaDon.nam;
			if(hoaDon.soHoaDon.length() > 0 && kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam) && nhapXuat.length() >0){
				hoaDon.soHoaDon = chuyenChuoiThanhChuoiHoa(hoaDon.soHoaDon);
				hoaDon.loai = (chuyenChuoiThanhChuoiHoa(nhapXuat))[0];
				hoaDon.CT_HD_First = NULL;		
				
				if(!kiemTraMaHoaDonTrung(rootNV, hoaDon.soHoaDon)){
					themMotChiTietHoaDon(dsVT, hoaDon);
					insertNodeHoaDon(nv.hoaDonFirst, hoaDon);
					return 1;
				}
			}
		}
	}while(c != KEY_ESC);
	return 0;
}

void suaHoaDon(HoaDon &hoaDon, NhanVien &nv, DSVatTu &dsVT){
	veGiaoDienLapHoaDon(nv);
	
	string ngay = "", thang = "", nam = "";
	string nhapXuat = "";	
	nhapXuat = (hoaDon.loai == 'N' ? "N" : "X");
	
	ngay = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.ngay);
	thang = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.thang);
	nam = chuyenSoThanhChuoi(hoaDon.ngayLapHoaDon.nam);
	
	SetColor(RED);
	gotoxy(41, 9);
	cout << hoaDon.soHoaDon;
	Normal();
	gotoxy(41, 15);
	cout << nhapXuat;
	
	gotoxy(41, 12);	cout << ngay;
	gotoxy(48, 12); cout << thang;
	gotoxy(55, 12); cout << nam;
	int c;
	string errors[3] = {"", "", ""};
	int sttDate = 0;
	bool res;
	int toaDoXNhan = 25;
	int toaDoYNhan = 9;
	int toaDoXInput = 41;
	int toaDoYInput = 9;
	
	int viTriNhapLieu = 1;	
	do{
		switch(viTriNhapLieu){

			case 1:
				do{
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
					if(sttDate == 0){
						c = nhapChuoiKiTuSo(ngay, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,2 , BLACK, WHITE);
						stringstream(ngay) >> hoaDon.ngayLapHoaDon.ngay;
					}else if(sttDate == 1){
						c = nhapChuoiKiTuSo(thang, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,2 , BLACK, WHITE);
						stringstream(thang) >> hoaDon.ngayLapHoaDon.thang;
					}else{
						c = nhapChuoiKiTuSo(nam, toaDoXInput + sttDate * 7, toaDoYInput + viTriNhapLieu * 3 ,4 , BLACK, WHITE);
						stringstream(nam) >> hoaDon.ngayLapHoaDon.nam;
					}
					if(c == KEY_RIGHT){
						if(sttDate < 2) sttDate++;
					}
						if(c == KEY_LEFT){
						if(sttDate > 0) sttDate--;
					}
									
				
				}while(c != KEY_UP && c != KEY_DOWN && c == KEY_ENTER && c != KEY_ESC && c != KEY_INSERT && c != KEY_F5 && c != KEY_TAB && c!= KEY_F2);
				
				if(ngay.length() <= 0 || thang.length() <= 0 || nam.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
				
				}else if(!kiemTraChuoiNhapVao(ngay) || !kiemTraChuoiNhapVao(thang) || !kiemTraChuoiNhapVao(nam)){
					errors[viTriNhapLieu] = "DATE khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else if(!kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam)){
					errors[viTriNhapLieu] = "Thoi gian khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1 ,toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];
					
				}else  errors[viTriNhapLieu] = "";
					
				break;
			
			case 2:
				c = nhapKyTuNhapXuat(nhapXuat, toaDoXInput, toaDoYInput + 3 * viTriNhapLieu, 1, BLACK, WHITE);
				
				gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
				for (int i = 0; i < errors[viTriNhapLieu].length(); i++) cout << " ";
				
				if(nhapXuat.length() <= 0){
					errors[viTriNhapLieu] = "Khong duoc de trong!";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				
				}else if(!kiemTraChuoiNhapVao(nhapXuat)){
					errors[viTriNhapLieu] = "Khong hop le";
					SetColor(TEXT_ERROR);
					gotoxy(toaDoXInput + WIDTH_INPUT_TEXT + 1, toaDoYInput + viTriNhapLieu * 3);
					cout << errors[viTriNhapLieu];					
				}else
					errors[viTriNhapLieu] = "";
				
				break;			
			}
		if((c == KEY_DOWN || c == KEY_ENTER) && viTriNhapLieu < 2)  viTriNhapLieu++;
		
		if(c == KEY_UP && viTriNhapLieu > 0) viTriNhapLieu--;
		
		if(c == KEY_F2){
			stringstream(ngay) >> hoaDon.ngayLapHoaDon.ngay;
			stringstream(thang) >> hoaDon.ngayLapHoaDon.thang;
			stringstream(nam) >> hoaDon.ngayLapHoaDon.nam;
			if(kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam) && nhapXuat.length() >0){
				hoaDon.loai = (chuyenChuoiThanhChuoiHoa(nhapXuat))[0];
				hoaDon.CT_HD_First = NULL;
		
				string noiDungThongBao = "Cap nhat thanh cong: ";
				thongBao(noiDungThongBao, 24 + (86 - noiDungThongBao.length()) / 2, 5 + 7, noiDungThongBao.length() + 10, 5);
				break;
			}
		}
		
		if(c == KEY_F5){
			themMotChiTietHoaDon(dsVT, hoaDon);
		}
	
	}while(c != KEY_ESC);	
}

void veKhungDanhSachHoaDon(NhanVien &nv){
	Normal();
	system("cls");
	// In tieu de
	veHinhChuNhat(cot, 1, 33, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DANH SACH HOA DON";
	Normal();
	gotoxy(3, 2); cout << "Ma NV : " << nv.maNhanVien;
	veBangDanhSach(23, 4, 1, 11, 4);
	veKhungDanhSach(3, 11, 28, 4);
	veLaiGoc(23, 4, 11);
	
	//veChuThich();
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(9, 28);
	cout << "ESC: Thoat     INSERT: Them HD     F2: Sua     DELETE: Xoa     F5: Chi tiet     <-Trang truoc \t Trang sau->";
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 4; i++){
		if(i == 0){
			toaDoXNhan = 25;
		}
		else toaDoXNhan =  29 + (TABLE_COLUMN_WIDTH - tenCotBangHoaDon[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangHoaDon[i];
	}
	Normal();
}

void xoaDuLieuTrongBangHoaDon(){
	SetColor(WHITE);
	SetBGColor(BLACK);
	int j = 7;
	// XOA stt
	for(int i = 0; i < 10; i++){
		gotoxy(25, j);
		cout << "   ";
		j += 2;
	}
	// Xoa SO HD
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(29, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa Ngay Lap
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(50, j);
		cout << "                    ";
		j += 2;
	}
	// Xoa LOAI
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(71, j);
		cout << "                    ";
		j += 2;
	}	
}

void doDuLieuRaBangHoaDon(NhanVien &nv, int tongTrang, int trang){
	xoaDuLieuTrongBangHoaDon();
	PTRHoaDon p = nv.hoaDonFirst;
	int dem = 0;
	int soHoaDon = soLuongHoaDonCuaMotNV(nv.hoaDonFirst);
	// Ghi du lieu moi vao bang
	SetColor(WHITE);	
	int toaDoXCuaConTro;
	int toaDoYCuaConTro;	
	int vtDau = (trang - 1) * 10;	
	while(p != NULL && dem < vtDau){
		p = p->HD_Next;
		dem++;
	}
	string str;
	int hang = 7;
	// STT
	for(int i = vtDau; i < trang * 10 && i < soHoaDon; i++){
		gotoxy(25, hang);
		str = chuyenSoThanhChuoi(i + 1);
		cout << str;
		hang += 2;
	}
	while(p != NULL && vtDau < trang * 10){
		gotoxy(28 + 0 * 21 + (20 - p->hoaDon.soHoaDon.length())/2,  7 + (vtDau % 10) * 2);
		cout << p->hoaDon.soHoaDon;
		
		gotoxy(28 + 1 * 21 + 5,  7 + (vtDau % 10) * 2);
		cout << chuyenNgayThanhChuoi(p->hoaDon.ngayLapHoaDon);

		gotoxy(28 + 2 * 21 + 9,  7 + (vtDau % 10) * 2);
		if(p->hoaDon.loai == 'N') cout << "Nhap";
		else cout << "Xuat";
		
		
		vtDau++;
		p = p->HD_Next;
	}	
	
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(81,2);
	cout << page;	
}

void giaoDienHoaDon(TreeNhanVien &rootNV, NhanVien &nv, DSVatTu &dsVT){
	int trang = 1;
	int tongTrang = soTrangDanhSachHoaDon(nv.hoaDonFirst);
	int vtLuaChon = 1;
	int c;
	int soLuongHoaDon = soLuongHoaDonCuaMotNV(nv.hoaDonFirst);
	if(soLuongHoaDon == 0) tongTrang = 1;
	int toaDoX = 20;
	int toaDoY = 7;
	
	veKhungDanhSachHoaDon(nv);
	doDuLieuRaBangHoaDon(nv, tongTrang, trang);
	
	gotoxy(toaDoX, toaDoY);
	cout << "->";
	do{
		c = keyPressed();
		if(c == KEY_UP){
			if(vtLuaChon > 1){
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				vtLuaChon--;
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "->";
			}
		}else if(c == KEY_DOWN){
				
				if(vtLuaChon < 10 && (vtLuaChon + (trang - 1) * 10) < soLuongHoaDon){
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
					vtLuaChon++;
					
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "->";
				}
				
		}else if(c == KEY_LEFT){
				if(trang > 1) {
					trang--;
					
					xoaDuLieuTrongBangHoaDon();
					doDuLieuRaBangHoaDon(nv, tongTrang, trang);
					
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
				}
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";
				
		}else if(c == KEY_RIGHT){
				if(trang < tongTrang){
					trang++;
					
					xoaDuLieuTrongBangHoaDon();
					doDuLieuRaBangHoaDon(nv, tongTrang, trang);
					
					gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
					cout << "  ";
				}
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";
				
		}else if(c == KEY_INSERT){
//			int viTriHD = (trang - 1) * 10 + vtLuaChon - 1;
			int flag = lapMotHoaDon(rootNV, nv, dsVT);
			if(flag == 1){
			
				soLuongHoaDon = soLuongHoaDonCuaMotNV(nv.hoaDonFirst);
				tongTrang = soTrangDanhSachHoaDon(nv.hoaDonFirst);
	
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				
				if(vtLuaChon == 10){
					trang++;
					vtLuaChon = 1;
				}else vtLuaChon++;
			}	
			veKhungDanhSachHoaDon(nv);
			doDuLieuRaBangHoaDon(nv, tongTrang, trang);
			
			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "  ";
			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "->";
			
		// SUA HOA DON: Chi cho phep sua khi ko co chi tiet hoa don	
		}else if(c == KEY_F2){
			int viTriHD = (trang - 1) * 10 + vtLuaChon - 1;
			
			PTRHoaDon p = timKiemHoaDonTheoViTri(nv.hoaDonFirst, viTriHD);
			PTR_CT_HoaDon ctHD = p->hoaDon.CT_HD_First;
			if(ctHD != NULL){
				string mess = "Khong duoc phep sua";
				thongBao(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, mess.length() + 10, 5);
			}else{
				suaHoaDon(p->hoaDon, nv, dsVT);
			}
				
			
			veKhungDanhSachHoaDon(nv);
			doDuLieuRaBangHoaDon(nv, tongTrang, trang);
			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "->";
			
		}else if(c == KEY_DELETE){
			int viTriHD = (trang - 1) * 10 + vtLuaChon - 1;
			
			PTRHoaDon p = timKiemHoaDonTheoViTri(nv.hoaDonFirst, viTriHD);
			PTR_CT_HoaDon ctHD = p->hoaDon.CT_HD_First;
			if(ctHD != NULL){
				string mess = "Khong duoc phep xoa";
				thongBao(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, mess.length() + 10, 5);
			}else{
				string mess = "Ban co muon xoa " + p->hoaDon.soHoaDon + " khong ?(Y/N) :";
				int xacNhanXoa = hopThoaiLuaChon(mess,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5)/2, mess.length() + 10, 4 );
				if(xacNhanXoa == 1){
					deleteInfoHD(nv.hoaDonFirst, p->hoaDon.soHoaDon);
					string mess2 = "Xoa thanh cong";
					thongBao(mess2,  WIDTH_MENU_BAR + (WIDTH_BODY - mess.length()) / 2, TOADOY + HEIGHT_HEADER + (HEIGHT_BODY - 5) / 2, mess.length() + 10, 5);
					soLuongHoaDon = soLuongHoaDonCuaMotNV(nv.hoaDonFirst);
					tongTrang = soTrangDanhSachHoaDon(p);		
					if (trang > 1 && vtLuaChon == 1){
						trang--;
						vtLuaChon = 10;
					} else if (vtLuaChon > 1) vtLuaChon--;
				}
			}
			veKhungDanhSachHoaDon(nv);
			xoaDuLieuTrongBangHoaDon();
			doDuLieuRaBangHoaDon(nv, tongTrang, trang);
			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "->";
		
		// Xem Chi tiet hoa don	
		}else if(c == KEY_F5){
			int viTriHD = (trang - 1) * 10 + vtLuaChon - 1;
			PTRHoaDon p = timKiemHoaDonTheoViTri(nv.hoaDonFirst, viTriHD);
			if(p == NULL) continue;
			giaoDienChiTietHoaDon(rootNV, dsVT, p);
			
			veKhungDanhSachHoaDon(nv);
			xoaDuLieuTrongBangHoaDon();
			doDuLieuRaBangHoaDon(nv, tongTrang, trang);
			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "->";
			
		}
	}
	while(c != KEY_ESC);
}

void veKhungNhapSoHoaDon(){
	SetBGColor(BLACK);
	SetColor(WHITE);
	system("cls");
	veHinhChuNhat(45, 8, 30, 5, RED);
	Normal();
	SetBGColor(4);
	SetColor(YELLOW);
	gotoxy(53, 9);
	cout << "Nhap So Hoa Don";
	gotoxy(50, 11);
	SetColor(BLACK);
	SetBGColor(BLACK);
	cout << "                    ";
	
}


void nhapSoHoaDonTimKiem(TreeNhanVien &rootNV, DSVatTu &dsVT){
X:	int c;
	string soHD = "";
	string error = "";
	veKhungNhapSoHoaDon();
	string tenNV = "";
	do{
		c = nhapChuoiKiTuVaSo(soHD, 50, 11 , 18, BLACK, WHITE);
		gotoxy(53, 7);
		for(int i = 0; i < error.length(); i++) cout << " ";
		
		if(c == KEY_ENTER){
			if(soHD.length() <= 0){
				error = "Chua nhap so Hoa Don";
				SetColor(TEXT_ERROR);
				gotoxy(52, 7);
				cout << error;
			
			}else if(kiemTraChuoiCoKhoangTrang(soHD)){
				error = "Khong hop le";
				SetColor(TEXT_ERROR);
				gotoxy(52, 7);
				cout << error;
				
			}else if(!kiemTraMaHoaDonTrung(rootNV, chuyenChuoiThanhChuoiHoa(soHD))){
				error = "Khong co hoa don vua nhap";
				SetColor(TEXT_ERROR);
				gotoxy(52, 7);
				cout << error;
				
			}else{
				PTRHoaDon p = traVeHoaDonTuongUngMa(rootNV, chuyenChuoiThanhChuoiHoa(soHD), tenNV);
				giaoDienChiTietHoaDon(rootNV, dsVT, p);
				goto X;
			}
		}
		
		if(c == KEY_ESC){
			system("cls");
			break;
		}		
	}while(c != KEY_ESC);
}

int traVeDanhSachHoaDonHopLe(TreeNhanVien &rootNV, PTRHoaDon &ptrHD, Date ngayBatDau, Date ngayKetThuc){
	ptrHD = NULL;
	StackNV sp = NULL;
	TreeNhanVien p = rootNV;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->nvLeft;
		}
		if(sp != NULL){
			pop(sp, p);
			PTRHoaDon hd = p->nhanVien.hoaDonFirst;
			while(hd != NULL){
				if(kiemTraNgayGiua2Ngay(ngayBatDau, ngayKetThuc, hd->hoaDon.ngayLapHoaDon)){
					insertNodeHoaDon(ptrHD, hd->hoaDon);
				}
				hd = hd->HD_Next;
			}
			p = p->nvRight;
		}else break;
	}while(1);
}

void veKhungNhapVaoNgayThang(){
	SetBGColor(BLACK);
	SetColor(WHITE);
	system("cls");
	veHinhChuNhat(30, 8, 60, 5, RED);
	Normal();
	SetBGColor(4);
	SetColor(YELLOW);
	gotoxy(49, 9);
	cout << "Nhap Khoang Thoi Gian";
	gotoxy(36, 11);
	SetColor(WHITE);
	cout << "Tu : ";
	veHinhChuNhat(41, 11, 15, 1, BLACK);
	gotoxy(59, 11);
	SetColor(WHITE);
	SetBGColor(RED);
	cout << "Den : ";
	veHinhChuNhat(65, 11, 15, 1, BLACK);
	gotoxy(44, 11); cout << "/";
	gotoxy(49, 11); cout << "/";
	gotoxy(68, 11); cout << "/";
	gotoxy(73, 11); cout << "/";
	
}

int tongSoHDTrongMotThoiGian(TreeNhanVien &rootNV, Date ngayBD, Date ngayKT){
	StackNV sp = NULL;
	int soHD = 0;
	TreeNhanVien p = rootNV;
	do{
		while(p != NULL){
			push(sp, p);
			p = p->nvLeft;
		}
		if(sp != NULL){
			pop(sp, p);
			PTRHoaDon hd = p->nhanVien.hoaDonFirst;
			while(hd != NULL){
				if(kiemTraNgayGiua2Ngay(ngayBD, ngayKT, hd->hoaDon.ngayLapHoaDon))
					soHD++;
				hd = hd->HD_Next;
			}
			p = p->nvRight;
		}else break;
	}while(1);
	return soHD;
}

void nhapNgayThangThongKe(TreeNhanVien &rootNV){
FIRST:	
	veKhungNhapVaoNgayThang();
	int viTriNhap = 0;
	int c;
	Date ngayBD, ngayKT;
	string ngayBDStr, thangBDStr, namBDStr = "";
	string ngayKTStr, thangKTStr, namKTStr = "";
	
	int tongTrang = 1; int trang = 1;
	PTRHoaDon ptrHD = NULL;
	int ktNgayBD;
	int ktNgayKT;
	string mess;
	do{
		switch(viTriNhap){
			case 0:
				c = nhapChuoiKiTuSo(ngayBDStr, 41, 11, 2, BLACK, WHITE);
				
				break;
			case 1:
				c = nhapChuoiKiTuSo(thangBDStr, 46, 11, 2, BLACK, WHITE);
			
				break;
			case 2:
				c = nhapChuoiKiTuSo(namBDStr, 51, 11, 4, BLACK, WHITE);

				break;
			case 3:
				c = nhapChuoiKiTuSo(ngayKTStr, 65, 11, 2, BLACK, WHITE);
		
				break;
			case 4:
				c = nhapChuoiKiTuSo(thangKTStr, 70, 11, 2, BLACK, WHITE);
				
				break;
			case 5:
				c = nhapChuoiKiTuSo(namKTStr, 75, 11, 4, BLACK, WHITE);
				
				break;
				
		}
		
		if(c == KEY_RIGHT && viTriNhap < 5) viTriNhap++;
		if(c == KEY_LEFT && viTriNhap > 0) viTriNhap--;
		if (c == KEY_ENTER){
			if (ngayBDStr == "" || thangBDStr == "" || namBDStr == "" || ngayKTStr == "" || thangKTStr == "" || namKTStr == ""){	
				if (ngayBDStr == "") viTriNhap = 0;
				else if (thangBDStr == "") viTriNhap = 1;
				else if (namBDStr == "") viTriNhap = 2;
				else if (ngayKTStr == "") viTriNhap = 3;
				else if (thangKTStr == "") viTriNhap = 4;
				else if (namKTStr == "") viTriNhap = 5;
			
				mess = "Thoi Gian Khong Hop Le!";
				BaoLoi(mess);
			}else{
				stringstream(ngayBDStr) >> ngayBD.ngay;
				stringstream(thangBDStr) >> ngayBD.thang;
				stringstream(namBDStr) >> ngayBD.nam;
				
				stringstream(ngayKTStr) >> ngayKT.ngay;
				stringstream(thangKTStr) >> ngayKT.thang;
				stringstream(namKTStr) >> ngayKT.nam;
				
				ktNgayBD = kiemTraHopLeNgayThangNhapVao(ngayBD.ngay, ngayBD.thang, ngayBD.nam);
				ktNgayKT = kiemTraHopLeNgayThangNhapVao(ngayKT.ngay, ngayKT.thang, ngayKT.nam);
				if(ktNgayBD == 0){
					viTriNhap = 0;
					
					mess = "Thoi Gian Bat Dau Khong Hop Le!";
					BaoLoi(mess);

				}else if(ktNgayKT == 0){
					viTriNhap = 3;
					
					mess = "Thoi Gian Ket Thuc Khong Hop Le!";
					BaoLoi(mess);

				}else{
					if(soSanhThoiGian(ngayBD, ngayKT) == 1){
						viTriNhap = 2;
						mess = "Thoi Gian Khong Hop Le!";
						BaoLoi(mess);
					}else{
						mess = "";
						
						int soHoaDon = tongSoHDTrongMotThoiGian(rootNV, ngayBD, ngayKT);
						if(soHoaDon <= 0){
							mess = "Danh sach HOA DON rong!";
							thongBao(mess, 40, 15, mess.length() + 10, 3);	
							goto FIRST;
						}else{
							traVeDanhSachHoaDonHopLe(rootNV, ptrHD, ngayBD, ngayKT);
							
							tongTrang = soHoaDon / 10 + (soHoaDon % 10 == 0 ? 0 : 1);
							if(soHoaDon == 0) tongTrang = 1;							
							
							veGiaoDienThongKeHoaDon();
							doDuLieuRaBangThongKeHoaDon(rootNV, ptrHD, tongTrang, trang);
							
							do{
								c = keyPressed();
								if(c == KEY_RIGHT){
									if(trang < tongTrang)
										trang++;
									xoaDuLieuTrongBangThongKe();
									doDuLieuRaBangThongKeHoaDon(rootNV, ptrHD, tongTrang, trang);
									
								}
								
								else if(c == KEY_LEFT){
									if(trang > 1)
										trang--;
									xoaDuLieuTrongBangThongKe();
									doDuLieuRaBangThongKeHoaDon(rootNV, ptrHD, tongTrang, trang);										
									
								}
							}while(c != KEY_ESC);
						}
					}
					
				}
			}
		}
	}while(c != KEY_ESC);
}

void veGiaoDienThongKeHoaDon(){
	Normal();
	veHinhChuNhat(40, 1, 33, 3, 4);
	gotoxy(48, 2);
	SetBGColor(4);
	cout << "THONG KE HOA DON";
	Normal();
	
	veKhungDanhSach(5, 11, 7 , 4);
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 5; i++){
		toaDoXNhan = 7 + i * 21 + (20 - tenCotHoaDon[i].length()) / 2;
		gotoxy(toaDoXNhan, 5);
		cout << tenCotHoaDon[i];
	}
	Normal();
	gotoxy(0, 27);
	for(int i = 0; i < 120; i++){
		cout << (char)205;
	}
	gotoxy(35, 28);
	cout << "ESC: Thoat \t <-Trang truoc \t Trang sau->";
}

void xoaDuLieuTrongBangThongKe(){
	int j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(8, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(29, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(50, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(71, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(92, j);
		cout << "                    ";
		j += 2;
	}	
}

void doDuLieuRaBangThongKeHoaDon(TreeNhanVien &rootNV, PTRHoaDon &ptrHD, int tongTrang, int trang){
	int vtDau = (trang - 1) * 10;
	PTRHoaDon p = ptrHD;
	int dem = 0;
	while(p != NULL && dem < vtDau){
		p = p->HD_Next;
		dem++;
	}
	
	while(p != NULL && vtDau < trang * 10){
		gotoxy(7 + 0 * 21 + (20 - p->hoaDon.soHoaDon.length()) / 2, 7 + (vtDau % 10) * 2);
		cout << p->hoaDon.soHoaDon;
		
		gotoxy(7 + 1 * 21 + 5, 7 + (vtDau % 10) * 2);
		cout << chuyenNgayThanhChuoi(p->hoaDon.ngayLapHoaDon);
		
		gotoxy(7 + 2 * 21 + 9, 7 + (vtDau % 10) * 2);
		if(p->hoaDon.loai == 'N') cout << "Nhap";
		else cout << "Xuat";
		
		string tenNV = tenNVCuaHoaDon(rootNV, p->hoaDon.soHoaDon);
		gotoxy(7 + 3 * 21 + (20 - tenNV.length()) / 2, 7 + (vtDau % 10) * 2);
		cout << tenNV;
		
		long long triGiaHD = tinhTongGiaTriHoaDon(p->hoaDon.CT_HD_First);
		gotoxy(7 + 4 * 21 + (20 - chuyenSoThanhChuoi(triGiaHD).length()) / 2, 7 + (vtDau % 10) * 2);
		cout << triGiaHD;

		vtDau++;
		p = p->HD_Next;
	}
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(81,2);
	cout << page;		
	
}

void veBangTop10(){
	Normal();
	system("cls");
	veHinhChuNhat(cot, 1, 40, 3, 4);
	gotoxy(cot + 8, 2);
	SetBGColor(4);
	cout << "DANH SACH TOP 10 VAT TU XUAT";
	veBangDanhSach(26, 4, 1, 11, 6);
	veKhungDanhSach(3, 11, 31, 4);
	veLaiGoc(26, 4, 11);
	veChuThich();
	
	gotoxy(13, 28);
	cout << "                                                                               ";
	gotoxy(13, 28);
	cout << "                 ESC: Thoat \t\t <-Trang truoc \t Trang sau->                  ";	
	Normal();
	
	SetColor(YELLOW);
	SetBGColor(BLACK);
	int toaDoXNhan;
	for (int i = 0; i < 4; i++){
		if(i == 0){
			toaDoXNhan = 28;
		}
		else toaDoXNhan =  32 + (20 - tenCotBangTop10[i].length())/2 + 21 * (i-1);
		gotoxy(toaDoXNhan, 5);
		cout << tenCotBangTop10[i];
	}
	Normal();	
}

void xoaDuLieuTrongBangTop10(){
	int j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(28, j);
		cout << "   ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(32, j);
		cout << "                    ";
		j += 2;
	}	
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(53, j);
		cout << "                    ";
		j += 2;
	}
	j = 7;
	for(int i = 0; i < 10; i++){
		gotoxy(74, j);
		cout << "                    ";
		j += 2;
	}
}

int kiemTraVatTuThu10(int *mangSoLuongXuat, int *mangChiSoGiamDan, DSVatTu &dsVT){
	int i;
	int dem = 0;
	for(i = 0; i < 10; i++){
		if(mangSoLuongXuat[mangChiSoGiamDan[i]] > 0){
			dem++;
		}
	}
	int j = dem;
	while(mangSoLuongXuat[mangChiSoGiamDan[j + 1]] == mangSoLuongXuat[mangChiSoGiamDan[dem-1]] && j < dsVT.soLuongVatTu){
		j++;
	}
	return j;
}

void doDuLieuRaBangTop10(int *mangSoLuongXuat, int *mangChiSoGiamDan, DSVatTu &dsVT, int trang, int tongTrang){
	int vtDau = (trang - 1) * 10;
	int soLuongVatTuThoaMan = kiemTraVatTuThu10(mangSoLuongXuat, mangChiSoGiamDan, dsVT);
	
	for(int i = vtDau; i < trang * 10 && i < soLuongVatTuThoaMan; i++){
//		if(mangSoLuongXuat[mangChiSoGiamDan[i]] > 0){
										
			//STT
			string s = chuyenSoThanhChuoi(i + 1);
			gotoxy(28, 7 + 2 * (i % 10));
			cout << s;
										
			//MA VT
			gotoxy(32 + (20 - dsVT.nodesVT[mangChiSoGiamDan[i]].maVatTu.length()) / 2, 7 + 2 * (i % 10));
			cout << dsVT.nodesVT[mangChiSoGiamDan[i]].maVatTu;
										
			//Ten VT
			gotoxy(32 + (20 - dsVT.nodesVT[mangChiSoGiamDan[i]].tenVatTu.length()) / 2 + 21 * 1, 7 + 2 * (i % 10));
			cout << dsVT.nodesVT[mangChiSoGiamDan[i]].tenVatTu;
										
			//SO LUONG XUAT
			gotoxy(32 + (20 - chuyenSoThanhChuoi(mangSoLuongXuat[mangChiSoGiamDan[i]]).length()) / 2 + 21 * 2, 7 + 2 * (i % 10));
			cout << mangSoLuongXuat[mangChiSoGiamDan[i]];
//		}
	}
	string page = "Trang: " + chuyenSoThanhChuoi(trang) + "/" + chuyenSoThanhChuoi(tongTrang);	
	gotoxy(85,2);
	cout << page;	
}

void nhapThoiGianThongKeTop10(TreeNhanVien &rootNV, DSVatTu &dsVT){
SECOND:	
	veKhungNhapVaoNgayThang();
	int viTriNhap = 0;
	int c;
	Date ngayBD, ngayKT;
	string ngayBDStr, thangBDStr, namBDStr = "";
	string ngayKTStr, thangKTStr, namKTStr = "";
	
	int ktNgayBD;
	int ktNgayKT;
	string mess;
	
	int *mangSoLuongXuat;
	int *mangChiSoGiamDan;
	do{
		switch(viTriNhap){
			case 0:
				c = nhapChuoiKiTuSo(ngayBDStr, 41, 11, 2, BLACK, WHITE);
				
				break;
			case 1:
				c = nhapChuoiKiTuSo(thangBDStr, 46, 11, 2, BLACK, WHITE);
			
				break;
			case 2:
				c = nhapChuoiKiTuSo(namBDStr, 51, 11, 4, BLACK, WHITE);

				break;
			case 3:
				c = nhapChuoiKiTuSo(ngayKTStr, 65, 11, 2, BLACK, WHITE);
		
				break;
			case 4:
				c = nhapChuoiKiTuSo(thangKTStr, 70, 11, 2, BLACK, WHITE);
				
				break;
			case 5:
				c = nhapChuoiKiTuSo(namKTStr, 75, 11, 4, BLACK, WHITE);
				
				break;
				
		}
		
		if(c == KEY_RIGHT && viTriNhap < 5) viTriNhap++;
		if(c == KEY_LEFT && viTriNhap > 0) viTriNhap--;
		if (c == KEY_ENTER){
			if (ngayBDStr == "" || thangBDStr == "" || namBDStr == "" || ngayKTStr == "" || thangKTStr == "" || namKTStr == ""){	
				if (ngayBDStr == "") viTriNhap = 0;
				else if (thangBDStr == "") viTriNhap = 1;
				else if (namBDStr == "") viTriNhap = 2;
				else if (ngayKTStr == "") viTriNhap = 3;
				else if (thangKTStr == "") viTriNhap = 4;
				else if (namKTStr == "") viTriNhap = 5;
			
				mess = "Thoi Gian Khong Hop Le!";
				BaoLoi(mess);
			}else{
				stringstream(ngayBDStr) >> ngayBD.ngay;
				stringstream(thangBDStr) >> ngayBD.thang;
				stringstream(namBDStr) >> ngayBD.nam;
				
				stringstream(ngayKTStr) >> ngayKT.ngay;
				stringstream(thangKTStr) >> ngayKT.thang;
				stringstream(namKTStr) >> ngayKT.nam;
				
				ktNgayBD = kiemTraHopLeNgayThangNhapVao(ngayBD.ngay, ngayBD.thang, ngayBD.nam);
				ktNgayKT = kiemTraHopLeNgayThangNhapVao(ngayKT.ngay, ngayKT.thang, ngayKT.nam);
				if(ktNgayBD == 0){
					viTriNhap = 0;
					
					mess = "Thoi Gian Bat Dau Khong Hop Le!";
					BaoLoi(mess);

				}else if(ktNgayKT == 0){
					viTriNhap = 3;
					
					mess = "Thoi Gian Ket Thuc Khong Hop Le!";
					BaoLoi(mess);

				}else{
					if(soSanhThoiGian(ngayBD, ngayKT) == 1){
						viTriNhap = 2;
						mess = "Thoi Gian Khong Hop Le!";
						BaoLoi(mess);
					}else{
						mess = "";
						
						mangSoLuongXuat = traVeMangSoLuongXuatCuaCacVT(rootNV, dsVT, ngayBD, ngayKT);
						
						mangChiSoGiamDan = traVeMangThuTuGiamDanChiSoCuaVT(dsVT, mangSoLuongXuat);
						if(mangSoLuongXuat[mangChiSoGiamDan[0]] == 0){
							mess = "Danh sach RONG";
							thongBao(mess, 40, 15, mess.length() + 10, 3);	
							goto SECOND;
							
						}else{
							veBangTop10();
							int trang = 1;
							int soLuongVTThoa = kiemTraVatTuThu10(mangSoLuongXuat, mangChiSoGiamDan, dsVT);
							int tongTrang = soLuongVTThoa / 10 + (soLuongVTThoa % 10 == 0 ? 0 : 1);
							 
							doDuLieuRaBangTop10(mangSoLuongXuat, mangChiSoGiamDan, dsVT, trang, tongTrang);

							do {
								c = keyPressed();
								
								if(c == KEY_RIGHT){
									if(trang < tongTrang) {
										trang++;
										xoaDuLieuTrongBangTop10();
										doDuLieuRaBangTop10(mangSoLuongXuat, mangChiSoGiamDan, dsVT, trang, tongTrang);
									}
									
								}else if(c == KEY_LEFT){
									if(trang > 1) {
										trang--;
										xoaDuLieuTrongBangTop10();
										doDuLieuRaBangTop10(mangSoLuongXuat, mangChiSoGiamDan, dsVT, trang, tongTrang);
									}
								}
								
								if (c == KEY_ESC) return;
								
							} while (true);
							
						}
					}
					
				}
			}
		}
	}while(c != KEY_ESC);
}
