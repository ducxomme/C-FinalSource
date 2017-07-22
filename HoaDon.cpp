#include "ChiTietHoaDon.cpp"

string tenCotBangHoaDon[] = {"STT", "SO HOA DON", "NGAY LAP", "LOAI"};
string tenThuocTinhHoaDon[] = {"So Hoa Don", "Ngay Lap", "Loai(N/X)"};

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

void lapMotHoaDon(TreeNhanVien &rootNV, NhanVien &nv, DSVatTu &dsVT){
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
	bool res;
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
			if(hoaDon.soHoaDon.length() > 0 && kiemTraHopLeNgayThangNhapVao(hoaDon.ngayLapHoaDon.ngay, hoaDon.ngayLapHoaDon.thang, hoaDon.ngayLapHoaDon.nam) && nhapXuat.length() >0){
				hoaDon.soHoaDon = chuyenChuoiThanhChuoiHoa(hoaDon.soHoaDon);
				hoaDon.loai = (chuyenChuoiThanhChuoiHoa(nhapXuat))[0];
		
		
				if(!kiemTraMaHoaDonTrung(rootNV, hoaDon.soHoaDon)) {
					res = insertNodeHoaDon(nv.hoaDonFirst, hoaDon);
					if(res == 1){
						thongBao("Them thanh cong!!", 45, 12, 27, 3);
					}else{
						thongBao("That bai!!", 45, 12, 27, 3);
					}
					goto LAPHOADON;
				}
			}
		}
		if(c == KEY_ESC){
			system("cls");
			break;
		}
	}while(1);
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
		
				string noiDungThongBao = "Cap nhat thanh cong: ";
				thongBao(noiDungThongBao, 24 + (86 - noiDungThongBao.length()) / 2, 5 + 7, noiDungThongBao.length() + 10, 5);
				break;
				}
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
				if(trang > 1) trang--;
				
				xoaDuLieuTrongBangHoaDon();
				doDuLieuRaBangHoaDon(nv, tongTrang, trang);
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";
				
		}else if(c == KEY_RIGHT){
				if(trang < tongTrang) trang++;
				
				xoaDuLieuTrongBangHoaDon();
				doDuLieuRaBangHoaDon(nv, tongTrang, trang);
				
				gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
				cout << "  ";
				
				vtLuaChon = 1;
				gotoxy(toaDoX, toaDoY);
				cout << "->";
				
		}else if(c == KEY_INSERT){
			int viTriHD = (trang - 1) * 10 + vtLuaChon - 1;
			lapMotHoaDon(rootNV, nv, dsVT);

			soLuongHoaDon = soLuongHoaDonCuaMotNV(nv.hoaDonFirst);
			tongTrang = soTrangDanhSachHoaDon(nv.hoaDonFirst);

			gotoxy(toaDoX, toaDoY + (vtLuaChon - 1) * 2);
			cout << "  ";
			
			if(vtLuaChon == 10){
				trang++;
				vtLuaChon = 1;
			}else vtLuaChon++;
			
			veKhungDanhSachHoaDon(nv);
			doDuLieuRaBangHoaDon(nv, tongTrang, trang);
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
			gotoxy(toaDoX, toaDoY);
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
			
		}
	}
	while(c != KEY_ESC);
}

//int main(){
//	
//	TreeNhanVien rootNV = NULL;
//	
//
//	NhanVien nv;
//	nv.hoaDonFirst = NULL;
//	nv.maNhanVien = "NV1";
//	nv.ho = "Nguyen";
//	nv.ten = "Duc";
//	nv.phai = 1;	
//	
//	NhanVien nv3;
//	nv3.hoaDonFirst = NULL;
//	nv3.maNhanVien = "NV3";
//	nv3.ho = "Nguyen";
//	nv3.ten = "bang";
//	nv3.phai = 0;	
//
//	NhanVien nv2;
//	nv2.hoaDonFirst = NULL;
//	nv2.maNhanVien = "NV2";
//	nv2.ho = "Nguyen";
//	nv2.ten = "w";
//	nv2.phai = 1;	
//	
//	PTRHoaDon hoaDonFirst;
//	InitHoaDon(hoaDonFirst);
//	
//	PTRHoaDon hoaDonFirst2;
//	InitHoaDon(hoaDonFirst2);
//
//	PTRHoaDon hoaDonFirst3;
//	InitHoaDon(hoaDonFirst3);
//	
//	
//	Date d;
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
//	insertNodeHoaDon(hoaDonFirst2, hd5);
//	
//	HoaDon hd3;
//	hd3.soHoaDon = "HD3";
//	hd3.loai = 'N';
//	hd3.ngayLapHoaDon = d;
//	hd3.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst3, hd3);
	
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
//	HoaDon hd8;
//	hd8.soHoaDon = "HD8";
//	hd8.loai = 'N';
//	hd8.ngayLapHoaDon = d;
//	hd8.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd8);
//	
//	HoaDon hd7;
//	hd7.soHoaDon = "HD7";
//	hd7.loai = 'X';
//	hd7.ngayLapHoaDon = d;
//	hd7.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd7);
//	
//	HoaDon hd9;
//	hd9.soHoaDon = "HD9";
//	hd9.loai = 'N';
//	hd9.ngayLapHoaDon = d;
//	hd9.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd9);
//	
//	HoaDon hd11;
//	hd11.soHoaDon = "HD11";
//	hd11.loai = 'N';
//	hd11.ngayLapHoaDon = d;
//	hd11.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd11);
//
//	HoaDon hd22;
//	hd22.soHoaDon = "HD22";
//	hd22.loai = 'N';
//	hd22.ngayLapHoaDon = d;
//	hd22.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd22);
//
//	HoaDon hd2;
//	hd2.soHoaDon = "HD2";
//	hd2.loai = 'N';
//	hd2.ngayLapHoaDon = d;
//	hd2.CT_HD_First = NULL;
//	insertNodeHoaDon(hoaDonFirst, hd2);		
//	nv.hoaDonFirst = hoaDonFirst;
//	nv2.hoaDonFirst = hoaDonFirst2;
//	nv3.hoaDonFirst = hoaDonFirst3;
//	
//	Insert_Node(rootNV, nv);
//	Insert_Node(rootNV, nv2);
//	Insert_Node(rootNV, nv3);
//	
////	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
////		cout << p->hoaDon.soHoaDon << endl;
////	}
////	cout << "Sau khi xcoa "  << endl;
////	deleteInfoHD(hoaDonFirst, "HD8");
////	for(PTRHoaDon p = hoaDonFirst; p != NULL; p=p->HD_Next){
////		cout << p->hoaDon.soHoaDon << endl;
////	}
//
//	giaoDienHoaDon(nv);
//	veGiaoDienLapHoaDon(nv);
//	DSVatTu dsVT;
//	dsVT.soLuongVatTu = 0;
//	lapMotHoaDon(rootNV, nv, dsVT);
//	return 0;
//}
